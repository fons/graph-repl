//
//  stack.h
//  graph-repl
//
//  Created by alfons haffmans on 9/1/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_stack_h
#define graph_repl_stack_h

#include <iostream>
#include <vector>

template <typename T>
class stack {
public:
      stack () {};
      stack (typename std::vector<T>::iterator& b, typename std::vector<T>::iterator& e) : s(b,e){}
      stack (size_t n, T& elem) : s(n,elem) {}
      stack (const stack& o) : s(o.s){}
      stack& operator=(const stack& o)
      {
            if (&o == this) return *this;
            s = o.s;
            return *this;
      }
      ~stack(){}
      
      void push (const T& elem)
      {
            s.push_back(elem);
      }
      
      bool empty() const
      {
            return s.empty();
      }
      
      T top() const
      {
            return s.back();
      }
      
      T pop ()
      {
            T elem = s.back();
            s.pop_back();
            return elem;
      }
      
      size_t size() const
      {
            return s.size();
      }
      
      T& operator[](size_t i) {
            return s[i];
      }
      
      std::ostream& pp(std::ostream& strm)
      {
            strm << "[";
            for (auto& val : s) {
                  strm << val << ",";
            }
            strm << "]";
            return strm;
      }
      
private:
      std::vector<T> s;
};

template<typename T>
std::ostream& operator<<(std::ostream& strm, stack<T>& s)
{
      return s.pp(strm);
}
#endif
