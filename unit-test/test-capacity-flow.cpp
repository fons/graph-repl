//
//  test-capacity-flow.cpp
//  graph-repl
//
//  Created by alfons haffmans on 11/13/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"
REGISTER_TEST(test_capacity_flow);
REGISTER_TEST(test_capacity_flow_graph);

typedef capacity_flow_t<long>                 simple_capacity_flow_t;
typedef edge_t<long, simple_capacity_flow_t>  simple_flow_edge_t;
typedef graph_impl<adjacency_list_t, simple_flow_edge_t>   flow_graph_t;

std::pair<int, std::string> test_capacity_flow(std::ostream& strm,int argc, const char *argv[])
{
      simple_capacity_flow_t cap(1);
      simple_capacity_flow_t ncap;
      simple_flow_edge_t e(0, 1, simple_capacity_flow_t(100));
      strm << e << std::endl;
      ASSERT(cap != ncap);
      auto w = edge_trait_t<simple_flow_edge_t>::weight(e);
      strm << " weight : " << w << std::endl;
      w.flow(23);
      strm << " weight : " << w << std::endl;
      ASSERT(w.flow() == 23);
      ASSERT(w.capacity() == 100);
      return DONE;
}

std::pair<int, std::string> test_capacity_flow_graph(std::ostream& strm,int argc, const char *argv[])
{
//      flow_graph_t s10(10, graph_type_t::UNDIRECTED);
//      
//      // fig 17.23 p 67
//      s10.insert(simple_flow_edge_t(0,1, simple_capacity_flow_t(20)));
//      
//      
//      std::string dn = "/Users/fons/Dvlp/graphviz/test_simple_path.dot";
//      s10.graphviz(dn);

      return DONE;
}