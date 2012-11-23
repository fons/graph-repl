//
//  test-check-flow.cpp
//  graph-repl
//
//  Created by alfons haffmans on 11/19/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"
REGISTER_TEST(test_check_flow);

//simple_flow_edge_ptr_t( new simple_flow_edge_t(0,1, simple_capacity_flow_t(3)))
template<typename edge_t, typename traits=edge_trait_t<edge_t>>
struct flow_graph_wrapper
{
      flow_graph_wrapper(graph_base<edge_t>& G) : G(G){};
      graph_base<edge_t>& G;
      graph_base<edge_t>& operator*() {
            return G;
      }
      
      graph_base<edge_t>* operator->() {
            return &G;
      }
      
      void flow(const typename traits::label_value_type& from,
                const typename traits::label_value_type& to,
                const typename traits::weight_value_type::flow_value_type& v) {
            
            auto e = G.edge(from, to);
            e->weight.flow(v);
            e = G.edge(from, to);
            //std::cerr << edge_trait_t<simple_flow_edge_ptr_t>::deref(e) << std::endl;
            
      }
};


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