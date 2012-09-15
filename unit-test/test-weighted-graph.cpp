//
//  test-weighted-graph.cpp
//  graph-repl
//
//  Created by alfons haffmans on 9/11/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_weighted_graph);

std::pair<int, std::string> test_weighted_graph(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.5));//1
      s10.insert(simple_edge_t(0,2,0.98));//2
      s10.insert(simple_edge_t(0,6,0.25));//3
      s10.insert(simple_edge_t(0,5,0.33));//4
      s10.insert(simple_edge_t(5,3,0.12));//5
      s10.insert(simple_edge_t(3,4,0.15));//6
      s10.insert(simple_edge_t(5,4,0.56));//7
      s10.insert(simple_edge_t(4,6,0.37));//8
      s10.insert(simple_edge_t(7,8,0.89));//9
//
      strm << "edges : " << s10.E() << std::endl;
      ASSERT(s10.E() == 9);
//
      strm << "vertices : " << s10.V() << std::endl;
      ASSERT(s10.V() == 9);
//      strm << s10 << std::endl;<=== this is problematic
      
      ASSERT(s10.edge(0,1).weight == 0.5);
      ASSERT(s10.edge(0,1).from == 0);
      ASSERT(s10.edge(0,1).to   == 1);
      
      ASSERT(s10.edge(5,3).weight == 0.12);
      ASSERT(s10.edge(5,3).from   == 5);
      ASSERT(s10.edge(5,3).to     == 3);

      
      ASSERT(s10.is_directed() == false);
      ASSERT(s10.has_edge(simple_edge_t(0,1,0.5)));
      ASSERT(s10.has_edge(simple_edge_t(0,1,0.5).reverse()));
      ASSERT(!(s10.has_edge(simple_edge_t(1,4,1))));
      return DONE;
}

