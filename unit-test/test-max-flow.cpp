//
//  test-max-flow.cpp
//  graph-repl
//
//  Created by alfons haffmans on 11/26/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_augmenting_paths_dfs);
REGISTER_TEST(test_augmenting_paths_maxflow);

static size_t ST(const std::unordered_map<size_t, flow_edge>& st, const size_t& v){
      return st.at(v).other(v);
}

std::pair<int, std::string> test_augmenting_paths_dfs(std::ostream& strm,int argc, const char *argv[])
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
      std::string dn = test_path("augmenting_paths_dfs_graph.dot");
      s10.graphviz(dn);
      auto s = 0;
      auto t = 5;
      augmenting_paths_dfs<flow_graph_t> dfs(s10,s,t);
      std::unordered_map<size_t, flow_edge> st;

      auto done = dfs(st);
      strm << "-------------" << std::endl;
      for (auto& v: st){
            strm << v << std::endl;
      }
      long d = st[t].capRto(t);
      strm << "--> d " << d << std::endl;
      for (size_t v = ST(st,t); v != s; v = ST(st, v)){
            strm << " v : " << v << std::endl;
            auto n = st[v].capRto(v);
            if (n < d){
                  d = n;
            }
      }
      
      st[t].addflowRto(t, d);
      
      for (size_t v = ST(st,t); v != s; v = ST(st, v)){
            st[v].addflowRto(v, d);
      }
      dn = test_path("augmenting_paths_dfs_graph_iter1.dot");
      s10.graphviz(dn);
      strm << "dfs done..... : "  << done << std::endl;
      
      return DONE;
}
std::pair<int, std::string> test_augmenting_paths_maxflow(std::ostream& strm,int argc, const char *argv[])
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
      std::string dn = test_path("augmenting_paths_maxflow_graph.dot");
      s10.graphviz(dn);
      auto s = 0;
      auto t = 5;
      augmenting_paths_maxflow<flow_graph_t, augmenting_paths_dfs<flow_graph_t>>(s10, s, t);
      dn = test_path("augmenting_paths_maxflow_graph_final.dot");
      s10.graphviz(dn);
      check_flow<simple_flow_edge_ptr_t> fc(s10);
      auto flow_ok = fc.flow(s, t);
      ASSERT(flow_ok );
      strm << "..... done ..... " << std::endl;
      return DONE;
}
