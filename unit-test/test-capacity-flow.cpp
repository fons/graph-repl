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


std::pair<int, std::string> test_capacity_flow(std::ostream& strm,int argc, const char *argv[])
{
      simple_capacity_flow_t cap(1);
      simple_capacity_flow_ptr_t cap_ptr = make_capacity_flow<long>(30);
      strm << *cap_ptr << std::endl;
      strm << cap << std::endl;
      auto e = make_simple_flow_edge(0, 1, 67);
      strm << edge_trait_t<simple_flow_edge_ptr_t>::deref(e) << std::endl;
      strm << *e << std::endl;
      e->weight->flow(23);
      strm << *e << std::endl;
      ASSERT(e->weight->flow() == 23);
      try {
            e->weight->flow(100);
            ASSERT_CONDITION(1==2, "flow out-of-range-error is not thrown");
      }
      catch(const std::exception& e) {
            std::cerr << "caught exception : " << e.what() << std::endl;
      }
      return DONE;
}

std::pair<int, std::string> test_capacity_flow_graph(std::ostream& strm,int argc, const char *argv[])
{
      flow_graph_t s10(10, graph_type_t::DIRECTED);
//      

      s10.insert(make_simple_flow_edge(0,1, 2));
      s10.insert(make_simple_flow_edge(0,2, 3));
      s10.insert(make_simple_flow_edge(1,3, 3));
      s10.insert(make_simple_flow_edge(1,4, 1));
      s10.insert(make_simple_flow_edge(2,3, 1));
      s10.insert(make_simple_flow_edge(2,4, 1));
      s10.insert(make_simple_flow_edge(3,5, 2));
      s10.insert(make_simple_flow_edge(4,5, 3));
      s10.edge(1,3)->weight->flow(2);
      std::string dn = "/Users/fons/Dvlp/graphviz/test_simple_flow_capacity_graph.dot";
      s10.graphviz(dn);
//
      ASSERT (s10.edge(1,3)->weight->flow() == 2);
      ASSERT (s10.edge(1,3)->weight->capacity() == 3)
      return DONE;
}