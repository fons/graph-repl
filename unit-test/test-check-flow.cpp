//
//  test-check-flow.cpp
//  graph-repl
//
//  Created by alfons haffmans on 11/19/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"
REGISTER_TEST(test_check_flow);
REGISTER_TEST(test_flow_edge);

std::pair<int, std::string> test_flow_edge(std::ostream& strm,int argc, const char *argv[])
{
      auto e = make_simple_flow_edge(0, 1, 20);
      strm << *e << std::endl;
      flow_edge fe(e);
      fe.addflowRto(1, 12);
      strm << fe << std::endl;
      strm << "residual flow to 0 " << fe.capRto(0) << std::endl;
      strm << "residual flow to 1 " << fe.capRto(1) << std::endl;

      flow_graph_t s10(10, graph_type_t::DIRECTED);
      s10.insert(make_simple_flow_edge(0, 1, 30));
      s10.insert(make_simple_flow_edge(0,2, 3));
      s10.insert(make_simple_flow_edge(1,3, 3));
      s10.insert(make_simple_flow_edge(1,4, 1));
      s10.insert(make_simple_flow_edge(2,3, 1));
      flow_edge fe2(s10.edge(1,3));
      fe2.addflowRto(1, 1);
      auto e2 = s10.edge(1,3);
      strm << fe2 << std::endl;
      strm << *e2 << std::endl;
      strm << "------------------------------" <<std::endl;
      std::vector<flow_edge> ve;
      
      for (flow_graph_t::iterator it = s10.begin(); it != s10.end(); it++) {
            ve.push_back(flow_edge(*it));
      }
      for (auto& v: ve){
            strm << v << std::endl;
      }
      return DONE;
}

std::pair<int, std::string> test_check_flow(std::ostream& strm,int argc, const char *argv[])
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
      
      check_flow<simple_flow_edge_ptr_t> fc(s10);
      auto f = fc.flow(2);
      strm << "flow : " << f << std::endl;
      auto res = change_flow(s10, 0, 4, 1);
      ASSERT(res == false);
      res = change_flow(s10, 0, 2, 1);
      ASSERT(res);
      auto e = s10.edge(0, 1);
      strm << *e << std::endl;
      f = fc.flow(2);
      strm << "flow : " << f << std::endl;
      auto s = 0;
      auto t = 5;
      auto flow_ok = fc.flow(s, t);
      ASSERT(flow_ok == false);
      change_flow(s10, 2, 3, 1);
      change_flow(s10, 3, 5, 1);
      flow_ok = fc.flow(s, t);
      ASSERT(flow_ok );
      change_flow(s10, 0, 1, 1);
      change_flow(s10, 1, 4, 1);
      change_flow(s10, 4, 5, 1);
      flow_ok = fc.flow(s, t);
      ASSERT(flow_ok );
      f = fc.flow(0);
      ASSERT(f ==2);
      std::string dn = test_path("test_check_flow_graph.dot");
      s10.graphviz(dn);

      return DONE;
}