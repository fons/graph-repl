//
//  test-preflow-push.cpp
//  graph-repl
//
//  Created by alfons haffmans on 11/30/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_init_preflow_push);

REGISTER_TEST(test_preflow_push);

std::pair<int, std::string> test_init_preflow_push(std::ostream& strm,int argc, const char *argv[])
{
      flow_graph_t s10(10, graph_type_t::UNDIRECTED);
      s10.insert(make_simple_flow_edge(0,1, 2));
      s10.insert(make_simple_flow_edge(0,2, 3));
      s10.insert(make_simple_flow_edge(1,3, 3));
      s10.insert(make_simple_flow_edge(1,4, 1));
      s10.insert(make_simple_flow_edge(2,3, 1));
      s10.insert(make_simple_flow_edge(2,4, 1));
      s10.insert(make_simple_flow_edge(3,5, 2));
      s10.insert(make_simple_flow_edge(4,5, 3));
      std::string dn = test_path("preflow_push_init_graph.dot");
      s10.graphviz(dn);
      
      init_preflow_height<flow_graph_t> ih(s10,0,5);
      typename init_preflow_height<flow_graph_t>::cont_t c;
      ih(c);
      for (auto& v : c) {
            strm << v << std::endl;
      }
      ASSERT(ih.check(c));
      strm << std::endl;
      strm << "------------------------------" << std::endl;
      return DONE;
}

std::pair<int, std::string> test_preflow_push(std::ostream& strm,int argc, const char *argv[])
{

      flow_graph_t s10(10, graph_type_t::DIRECTED);
      s10.insert(make_simple_flow_edge(0,1, 2));
      s10.insert(make_simple_flow_edge(0,2, 3));
      s10.insert(make_simple_flow_edge(1,3, 3));
      s10.insert(make_simple_flow_edge(1,4, 1));
      s10.insert(make_simple_flow_edge(2,3, 1));
      s10.insert(make_simple_flow_edge(2,4, 1));
      s10.insert(make_simple_flow_edge(3,5, 2));
      s10.insert(make_simple_flow_edge(4,5, 3));
      std::string dn = test_path("preflow_push_graph.dot");
      s10.graphviz(dn);
      auto s = 0;
      auto t = 5;
      preflow_push_maxflow<flow_graph_t> ppm(s10, s, t);
      dn = test_path("preflow_push_maxflow_graph.dot");
      s10.graphviz(dn);
      check_flow<simple_flow_edge_ptr_t> fc(s10);
      auto flow_ok = fc.flow(s, t);
      ASSERT(flow_ok );
      strm << "flow : " << fc.flow(5) << std::endl;     
      ASSERT(fc.flow(0) == 4);
      ASSERT(fc.flow(5) == -fc.flow(0));
      strm << "..... done ..... " << std::endl;
      return DONE;
}