//
//  adjacency_list.h
//  graph-repl
//
//  Created by Alfons Haffmans on 4/5/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_adjacency_list_h
#define graph_repl_adjacency_list_h
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "graph_utils.h"
#include "lwll.h"
#include "tuple.h"
//template <typename T = double>
class adjacency_list {
public:  
      typedef double edge_weight_t;
      constexpr static const edge_weight_t null_weight = edge_weight_t();

      typedef std::pair<size_t, edge_weight_t> weighted_edge_t;
      typedef std::tuple<size_t, size_t, edge_weight_t> edge_tuple_t;
      
      adjacency_list (size_t size) : msize(size) {lst = init(size, lst);}
      adjacency_list(adjacency_list&& that) : msize(that.msize), elcnt(that.elcnt), lst(std::move(that.lst)){}
      adjacency_list& operator=(adjacency_list&& that) {
            msize = that.msize;
            elcnt = that.elcnt;
            lst   = std::move(that.lst);
            return *this;
      }
      ~adjacency_list(){}
      
      void operator()(size_t from, size_t to, edge_weight_t w) {
            //std::cerr << "(" << from << "," << to << "," << w << ")" << std::endl;
            if (check(from , to)) {
                  //std::cerr << "adding node " <<std::endl; 
                  elcnt++;      
                  lst[from] += weighted_edge_t(to, w);
            }
      }
      
      //need const references/iterators
      edge_weight_t operator()(size_t from, size_t to)  {
            if (! check(from, to)) return edge_weight_t();
            lwll<weighted_edge_t>& l = lst[from]; 
            for (typename lwll<weighted_edge_t>::iterator it = l.begin(); it != l.end(); it++) {
                  if ((*it).first == to) {
                        return (*it).second;
                  }
            }           
            return edge_weight_t();      
      }
      
      void rm(size_t from, size_t to) {
            lwll<weighted_edge_t>& l = lst[from];
            edge_weight_t w = edge_weight_t();
            for (lwll< weighted_edge_t>::iterator it = l.begin(); it != l.end(); it++) {
                  if ((*it).first == to) {
                        w = (*it).second;
                        break;
                  }
            }
            // this is not very efficient as the list is scanned twice 
            if ( w != edge_weight_t()) {
                  l -= weighted_edge_t(to, w);
            }
            elcnt--;
      }
      
      inline size_t size() const { return elcnt;}
      inline size_t max_size() const  { return msize;}

      // ITERATOR CLASSS  =======================
      class adjacency_list_iterator {
      public:
            adjacency_list_iterator(size_t row, size_t coll, adjacency_list& m) : lst(m), s(row) {                  
                  set_iterator_state(row);                     
            }
            
            void operator++() {
                  s = nxt(s);                  
            }
            
            void operator++(int) {
                  s = nxt(s);
            }
            
            bool operator==(const adjacency_list_iterator& that) {
                  if (empty() && that.empty() ) return true;
                  if (finished() && that.finished()) return true;
                  return s == that.s;                  
            }
            
            bool operator!=(const adjacency_list_iterator& that) {
                  return !(*this == that);
            }

            adjacency_list::edge_tuple_t operator*() {
                  if (finished()) return edge_tuple_t();                  
                  lwll<adjacency_list::weighted_edge_t>::iterator it = s.it_to;
                  lwll<weighted_edge_t>& lnxt = lst.lst[s.it_from];
                  if (s.it_to == lnxt.end()) return edge_tuple_t();
                  return edge_tuple_t(s.it_from, (*it).first, (*it).second);
            }
            
            adjacency_list::weighted_edge_t operator()(){
                  return adjacency_list::weighted_edge_t(size_t(),adjacency_list::edge_weight_t());
            }
            
            bool coll_start () {
                  if (!(s.it_from < lst.size())) return false;
                  return s.it_to == lst.lst[s.it_from].begin();   
            }

//            bool coll_end() {
//                  std::cerr << "s.it_from : " << s.it_from << " ";
//                  std::cerr << "lst.size() : " << lst.size() << " ";
//                  std::cerr << "deref : " << *(s.it_to) << " ";
//                  std::cerr << std::endl;
//                  if (!(s.it_from < lst.size())) return true; 
//                  return s.it_to == lst.lst[s.it_from].end();//this will never be true
//            }
            
      private: 
            adjacency_list& lst;
            
            typedef struct iterator_state {
                  iterator_state(size_t from) : it_from(from){}
                  iterator_state(size_t f, typename lwll<adjacency_list::weighted_edge_t>::iterator& t): it_to(t), it_from(f) {}
                  typename lwll<adjacency_list::weighted_edge_t>::iterator it_to;
                  size_t   it_from; 
                  bool operator==(const iterator_state& s) {                        
                        return (it_from == s.it_from) && (it_to == s.it_to);
                  }
                  bool operator!=(iterator_state& s) { return ! (*this == s);} 
            } iterator_state_t;
            iterator_state_t s;

            void set_iterator_state (size_t row)
            {
                  s.it_to = lst.lst[s.it_from].begin();                  
                  while ((s.it_to == lst.lst[s.it_from].end()) && (s.it_from < lst.max_size())) {                        
                        s.it_from++;
                        s.it_to = lst.lst[s.it_from].begin();
                  }      
                  if (s.it_from > lst.max_size()) {                        
                        s.it_from = lst.max_size();
                        s.it_to   = lst.lst[lst.size() - 1].end();
                  }
                  
            }

            virtual iterator_state& nxt (iterator_state& s) {
                  if (!(s.it_from < lst.max_size())) {
                        //std::cerr << "it_from larger than " << lst.max_size() << std::endl;
                        return s;
                  }
                  s.it_to++;
                  lwll<weighted_edge_t>& l = lst.lst[s.it_from];
                  if (s.it_to != l.end()) {
                        return s;
                  }                  
                  //std::cerr << "start loop" << std::endl;
                  bool stop = false;                  
                  do {
                        s.it_from++;
                        //std::cerr << "from : " << s.it_from << std::endl;
                        if (!(s.it_from < lst.max_size())) {
                              //std::cerr << "from exceeds max _size : " << lst.max_size() << std::endl;
                              return s;
                        }
                        lwll<weighted_edge_t>& lnxt = lst.lst[s.it_from];
                        s.it_to = lnxt.begin();
                        if (s.it_to != lnxt.end()) {
                              //std::cerr << "returning valid row iterator for coll " << s.it_from << std::endl;
                              return s;
                        }
                  } while (! stop);                  
                  return s;
            }
            inline bool empty() const {
                  return lst.size() == 0;
            }
            
            inline bool finished() const {
                  return !(s.it_from < lst.max_size());
            }
      };
      
      typedef adjacency_list_iterator iterator;
      
      iterator begin() {
            static iterator b(0, 0, *this);
            return b;
      }

      iterator end() {
            static iterator e(max_size(), max_size(), *this);
            return e;
      }
      
      
      
private:
      typedef std::vector< lwll<weighted_edge_t> >  coll_t;      
      coll_t lst;
      static coll_t& init (size_t s, coll_t& m) {
            m = coll_t (s);
            std::fill(m.begin(), m.begin() + s, lwll<weighted_edge_t>()); 
            return m;
      }
      size_t msize;
      size_t elcnt = 0;
      bool check (size_t row, size_t coll) {            
            return (row < msize) && (coll < msize);
      }
      adjacency_list(const adjacency_list& that) : msize(that.msize) { lst = that.lst;}
      const adjacency_list& operator=(const adjacency_list& that) {
            if (this == &that) {
                  return *this;
            }
            lst = that.lst;
            return *this;
      }

};
typedef adjacency_list adjacency_list_t;
std::ostream& operator<<(std::ostream& strm, adjacency_list& lst);

#endif
