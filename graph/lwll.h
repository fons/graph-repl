//
//  lwll.h
//  graph-repl
//
//  Created by Alfons Haffmans on 3/31/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_lwll_h
#define graph_repl_lwll_h

template<typename l, typename r>
std::ostream& operator<<(std::ostream& strm, const std::pair<l,r>& p){
      return strm << "[" << p.first << "," << p.second << "]";
}

template<typename el_t>
class lwll {

      typedef struct lwll_el {
            lwll_el(const el_t& el) : el(el),next(0){}
            el_t el;
            lwll_el* next;
      } lwll_el_t;
 
public:
      lwll() : head(0), popped(0) {}
      
      lwll(const lwll& that) {
            lwll_el_t *new_head = cp (const_cast<lwll&>(that));
            swap(&head, &new_head);
            rm(new_head);                     
      }
      
      const lwll& operator=(const lwll& that) {
            if (&that != this) {
                  lwll_el_t *new_head = cp (const_cast<lwll&>(that));
                  swap(&head, &new_head);
                  rm(new_head);
            }
            return *this;
            
      }
      
      ~lwll() { head = rm(head); popped = rm(popped);}
      
      lwll& operator+=(const el_t& el) {
            head = cons(el, head);
            return *this;
      }
      
      lwll& operator-=(const el_t& el) {            
            
            lwll_el_t* ptr = head;
            if (head && head->el == el){
                  head = head->next;
                  delete ptr;      
                  return *this;
            }
            lwll_el_t* prev = head;
            while ((ptr = ptr->next) != 0) {
                  if (el == ptr->el) {
                        prev->next = ptr->next;
                        delete ptr;
                        return *this;
                  }
                  prev = ptr;
            }
            return *this;
      }
      
      bool contains(const el_t& el) {return (find(head, el) != 0);}
      
      struct lwll_iterator {
            explicit lwll_iterator(lwll_el_t* p) : ptr(p) {}            
            lwll_iterator() : ptr(0) {}
            lwll_iterator(const lwll_iterator& that) {             
                  ptr   = that.ptr;                                    
            }
            const lwll_iterator& operator=(const lwll_iterator& that) {
                  ptr = that.ptr;
                  return *this;
            }
            ~lwll_iterator(){}
            void  operator++()      { if (ptr!= 0) ptr = ptr->next;}
            void  operator++(int i) { if (ptr!= 0) ptr = ptr->next;}
            el_t& operator*() { return ptr->el;}
            
            bool  operator==(const lwll_iterator& that) { 
                  if (that.ptr == ptr) {
                        return true;   
                  }
                  return false;                                                      
            }
            
            bool  operator!=(const lwll_iterator& that) { return !(*this == that);}
      private:           
            lwll_el_t* ptr;            
      };
      
      typedef  lwll_iterator iterator;
      iterator begin() { return lwll_iterator(head);}
      iterator end()   { return lwll_iterator(0);}

      iterator operator--(int) {
            if (head == 0) {
                  return end();
            }
            lwll_el_t* ptr = head;
            head           = head->next; 
            popped = push(ptr, popped);
            return iterator(ptr);
      }
      
      lwll& reverse()
      {
            head = reverse_it(head);
            return *this;
      }
      
private:
                            
      lwll_el_t* head;
      lwll_el_t* popped;
      
      static lwll_el_t*  find(lwll_el_t* head, const el_t& el) 
      { 
            
            for (lwll_el_t* ptr = head; ptr != 0; ptr = ptr->next) {
                  if (ptr && el == ptr->el) {
                        return ptr;
                  }
            }
            return 0;
      }
      
      static lwll_el_t* cons(const el_t& el, lwll_el_t* head)
      {
            lwll_el_t* p = new lwll_el_t(el);
            p->next = head;
            return p;
      }
      
      static lwll_el_t* prune(lwll_el_t* ptr)
      {
            if (ptr->next != 0) {
                  lwll_el_t* n = prune(ptr->next);
                  delete n;
            };
            return *ptr;            
      }

      static lwll_el_t* rm(lwll_el_t* ptr) 
      {            
            if (ptr == 0) return 0;
            
            lwll_el_t* head = ptr;
            lwll_el_t* nxt  = ptr->next;
            do {
                  delete head;
                  head = nxt;
                  if (head != 0) nxt  = head->next;
            } while (nxt);
            return head;
      }
      
      static void swap(lwll_el_t** l, lwll_el_t** r) {
            lwll_el_t* tmp = *l;
            *l = *r;
            *r = tmp;
      }
                
      static lwll_el_t* cp (lwll& l)
      {
            lwll_el_t *h = 0;
            
            for (lwll<el_t>::iterator it = l.begin(); it != l.end(); it++) {
                  h = cons(*it, h);
            }
            return h;
      }

      static lwll_el_t* reverse_it(lwll_el_t* head)
      {
            lwll_el_t* newhead = 0;
            while (head) {
                  lwll_el_t* p = head;
                  head = head->next;
                  p->next = newhead;
                  newhead = p;
            }
            return newhead;
      }
      static lwll_el_t* push(lwll_el_t* ptr, lwll_el_t* lst)
      {
            ptr->next = lst;
            return ptr;
      }
};     

template <typename el_t>
std::ostream& operator<<(std::ostream& strm, lwll<el_t>& l) {
      strm << "{";
      for (typename lwll<el_t>::iterator it = l.begin(); it != l.end(); it++) {
            strm << *it << ",";
      }
      strm << "}";
      return strm;   
}

#endif
