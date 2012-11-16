//
//  adjacency_list.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 4/5/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include <iostream>
#include "adjacency_list.h"

//template<typename T>
//std::ostream& operator<<(std::ostream& strm, adjacency_list<T>& lst) {
//      strm << "{" << std::endl;
//      bool open_bracket = false;
//      for (typename adjacency_list<T>::iterator it = lst.begin(); it != lst.end(); it++) {
//            if (it.coll_start()) {
//                  if (open_bracket) {
//                         strm << ")"<<std::endl;
//                  }
//                  open_bracket = true;
//                  strm << "(";
//            }
//            strm << *it << ",";            
//      }
//      if (open_bracket) {
//            strm << ")"<<std::endl;
//      }
//      strm << "}";
//      return strm;
//}
//
