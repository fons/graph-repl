//
//  test-adjacency-matrix.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 7/17/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//



//#include "adjacency_matrix.h"
#include "tests.h"


REGISTER_TEST(test_adjacency_matrix);

std::pair<int, std::string> test_adjacency_matrix(std::ostream& strm,int argc, const char *argv[])
{
      
      adjacency_matrix a1(4);

      std::set<adjacency_matrix::edge_tuple_t> expected =
      {
            std::make_tuple(0,2,1),
            std::make_tuple(1,3,1)
      };
      
      a1(0,2,1);
      a1(1,3,1);
      std::cerr << a1 << std::endl;
      // size is dimension (this is a square matrix)
      strm << "size : " << a1.size() << std::endl;
      ASSERT(a1.size() == 4);

      strm << "a1 max size : " << a1.max_size() << std::endl;
      ASSERT(a1.max_size() == 4);
      
      ASSERT(a1(1,3)  == 1);
      std::set<adjacency_matrix::edge_tuple_t> found;
      std::set<adjacency_matrix::edge_tuple_t> skip;
      for (adjacency_matrix::iterator it = a1.begin(); it != a1.end(); it++) {
            if (std::get<2>(*it) != 0) {
                  found.insert(*it);
            }
            else {
                  skip.insert(*it);
            }
      }
      ASSERT(found.size() == expected.size());
      strm << "found : " << found.size() << " ; skipped : " << skip.size() << std::endl;
      ASSERT(found.size() + skip.size() == a1.max_size() * a1.max_size());
      ASSERT(expected == found);
      return DONE;
      
}
