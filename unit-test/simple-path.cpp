//
//  simple-path.cpp
//  graph-repl
//
//  Created by alfons haffmans on 8/1/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//


#include "tests.h"

REGISTER_TEST(test_simple_path);

std::pair<int, std::string> test_simple_path(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(10, graph_type_t::UNDIRECTED);
     
      // fig 17.23 p 67
      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(0,6,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(1,2,1));
      s10.insert(simple_edge_t(2,3,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(2,4,1));
      s10.insert(simple_edge_t(4,6,1));

      s10.insert(simple_edge_t(7,8,1));
      
      s10.insert(simple_edge_t(9,10,1));
      s10.insert(simple_edge_t(9,11,1));
      s10.insert(simple_edge_t(9,12,1));
      s10.insert(simple_edge_t(11,12,1));

      std::string dn = test_path("simple_path.dot");
      s10.graphviz(dn);
      simple_edge_path_t sp(s10);
      simple_path_t p = sp(0, 5);
      ASSERT_CONDITION("there is a path from 0 to 5", p == true);
      ASSERT_CONDITION("there is a path no path from 0 to 9", sp(0,9) == false);
      return DONE;
}