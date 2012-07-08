//
//  tuple.h
//  graph-repl
//
//  Created by Alfons Haffmans on 4/10/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_tuple_h
#define graph_repl_tuple_h

#include <iostream>

#include <tuple>

template<int index, int max, typename... args>
struct print_tuple {
      static void print(std::ostream& strm, const std::tuple<args...>& t) {
            strm << std::get<index>(t) << ((index + 1 == max) ? "" : ",");
            print_tuple<index + 1,max,args...>::print(strm, t); 
      }
};
template<int max, typename... args>
struct print_tuple<max, max, args...> {
      static void print(std::ostream& strm, const std::tuple<args...>& t) {                    
      }
};

template<typename... args>
std::ostream& operator<<(std::ostream& strm, const std::tuple<args...>& t) {
      strm << "tuple@" << "[";
      print_tuple<0, sizeof... (args), args...>::print(strm, t);
      return strm << "]";
}


#endif

