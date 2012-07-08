//
//  adjacency_matrix.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 3/12/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "adjacency_matrix.h"


std::ostream& operator<< (std::ostream &stream, adjacency_matrix_t &m)
{
      stream << "(";
      for (adjacency_matrix_t::iterator it = m.begin(); it != m.end(); it++) {
            size_t row = it().first;
            size_t coll = it().second;
            
            if (coll == 0) {
                  stream << "(";
            }
            stream << *it;
            if (coll < (m.size() - 1)) {
                  stream << ",";
            }
            else {
                  stream << ")";                  
                  if (row < (m.size() - 1)) {
                        stream << std::endl << " ";
                  }
            }
      }
      stream << ")";
      return stream;
}

adjacency_matrix::adjacency_matrix(std::ifstream& strm) 
{
      
      std::vector<std::string> coll;
      std::copy(std::istream_iterator<std::string>(strm), std::istream_iterator<std::string>(), std::back_inserter(coll));
      for (std::vector<std::string>::iterator it = coll.begin(); it != coll.end(); it++){
            std::vector<std::string> res = split (*it, "(), ");
            m.push_back(std::vector<double>());      
            std::transform(res.begin(), res.end(), std::back_inserter(m.back()), string_to_double);              
      }
           
      msize = m.size();
}



adjacency_matrix::row_then_coll_iterator::iter_state_t&
adjacency_matrix::row_then_coll_iterator::next(size_t size, size_t width, iter_state_t& i) {
      if (row(i) < width) {                        
            next_row(i);                 
      }
      if (row(i) == width && coll(i) < width) {
            next_coll(i);                                          
            if (coll(i) < width) {
                  i = iter_state_t(0, coll(i));                     
            }                        
      }     
      
      if ((row(i) == width) && (coll(i) == width)) {
            i = iter_state_t(size, size);   
      }
      
      return i;
}

adjacency_matrix::coll_then_row_iterator::iter_state_t&
adjacency_matrix::coll_then_row_iterator::next(size_t size, size_t width, iter_state_t& i) {
      if (coll(i) < width) {                        
            next_coll(i);                 
      }

      if (coll(i) == width && row(i) < width) {
            next_row(i);                                          
            if (row(i) < width) {
                  i = iter_state_t(row(i), 0);                     
            }                        
      }     
      
      if ((row(i) == width) && (coll(i) == width)) {
            i = iter_state_t(size, size);   
      }
      
      return i;
}


