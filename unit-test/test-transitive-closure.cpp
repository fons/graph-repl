//
//  test-transitive-closure.cpp
//  graph-repl
//
//  Created by alfons haffmans on 8/7/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_transitive_closure);
REGISTER_TEST(test_transitive_closure_warshall);
REGISTER_TEST(test_transitive_closure_dag);
REGISTER_TEST(test_transitive_closure_kernel_dag);

std::pair<int, std::string> test_transitive_closure(std::ostream& strm,int argc, const char *argv[])
{
      
      size_t size = 50;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(2,1,1));
      s10.insert(simple_edge_t(1,0,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(4,5,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(3,2,1));
      
      std::string dn = "/Users/fons/Dvlp/graphviz/test_tc_graph.dot";
      s10.graphviz(dn);
      
      sparse_tc_t tc(s10);
      std::string dt = "/Users/fons/Dvlp/graphviz/test_tc_graph_tc.dot";
      (*tc).graphviz(dt);

      ASSERT(tc(simple_edge_t(1,2,1)));
      ASSERT(tc(simple_edge_t(2,1,1)))
      ASSERT(!tc(simple_edge_t(2,3,1)));
      ASSERT(tc(simple_edge_t(3,2,1)))
      
      ASSERT(tc(simple_edge_t(0,5,1)));
      ASSERT(tc(simple_edge_t(5,4,1)))
      ASSERT(tc(simple_edge_t(1,4,1)));
      ASSERT(!tc(simple_edge_t(4,1,1)))
     
      ASSERT(tc(simple_edge_t(0,2,1)));
      ASSERT(tc(simple_edge_t(2,0,1)))
      ASSERT(tc(simple_edge_t(2,4,1)));

      
      return DONE;
}

std::pair<int, std::string> test_transitive_closure_warshall(std::ostream& strm,int argc, const char *argv[])
{
      
      size_t size = 50;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(2,1,1));
      s10.insert(simple_edge_t(1,0,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(4,5,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(3,2,1));
      
      std::string dn = "/Users/fons/Dvlp/graphviz/test_tc_graph.dot";
      s10.graphviz(dn);

      transitive_closure<sparse_graph_t, tc_warshall<simple_edge_t>> tc(s10);
      std::string wts = "/Users/fons/Dvlp/graphviz/test_tc_graph_tc_warshall.dot";
      (*tc).graphviz(wts);

      
      ASSERT(tc(simple_edge_t(1,2,1)));
      ASSERT(tc(simple_edge_t(2,1,1)))
      ASSERT(!tc(simple_edge_t(2,3,1)));
      ASSERT(tc(simple_edge_t(3,2,1)))
      
      ASSERT(tc(simple_edge_t(0,5,1)));
      ASSERT(tc(simple_edge_t(5,4,1)))
      ASSERT(tc(simple_edge_t(1,4,1)));
      ASSERT(!tc(simple_edge_t(4,1,1)))
      
      ASSERT(tc(simple_edge_t(0,2,1)));
      ASSERT(tc(simple_edge_t(2,0,1)))
      ASSERT(tc(simple_edge_t(2,4,1)));
      
      
      return DONE;
}

std::pair<int, std::string> test_transitive_closure_dag(std::ostream& strm,int argc, const char *argv[])
{
      std::string fn = "/Users/fons/Dvlp/graphviz/test_tc_dag_graph.dot";
      size_t size = 50;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(0,3,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(0,6,1));
      s10.insert(simple_edge_t(2,3,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(3,5,1));
      s10.insert(simple_edge_t(4,9,1));
      s10.insert(simple_edge_t(6,4,1));
      s10.insert(simple_edge_t(6,9,1));
      s10.insert(simple_edge_t(7,6,1));
      s10.insert(simple_edge_t(8,7,1));
      s10.insert(simple_edge_t(9,10,1));
      s10.insert(simple_edge_t(9,11,1));
      s10.insert(simple_edge_t(9,12,1));
      s10.insert(simple_edge_t(11,12,1));
      
      is_dag<simple_edge_t> is_dag(s10);
      ASSERT_CONDITION("graph is a DAG", is_dag());
      
      s10.graphviz(fn);
      transitive_closure<sparse_graph_t, tc_dag<simple_edge_t>> tc(s10);
      std::string wts = "/Users/fons/Dvlp/graphviz/test_tc_graph_tc_dag.dot";
      (*tc).graphviz(wts);
      ASSERT(tc(simple_edge_t(0,1,1)));
      ASSERT(tc(simple_edge_t(0,12,1)))
      ASSERT(tc(simple_edge_t(0,11,1)));
      ASSERT(tc(simple_edge_t(8,12,1)))
      
      ASSERT(tc(simple_edge_t(0,10,1)));
      ASSERT(tc(simple_edge_t(3,4,1)))
      ASSERT(!tc(simple_edge_t(1,4,1)));
      ASSERT(!tc(simple_edge_t(4,1,1)))
      
      ASSERT(tc(simple_edge_t(0,2,1)));
      ASSERT(!tc(simple_edge_t(2,0,1)))
      ASSERT(tc(simple_edge_t(2,4,1)));
      
      return DONE;
}
std::pair<int, std::string> test_transitive_closure_kernel_dag(std::ostream& strm,int argc, const char *argv[])
{
      
      size_t size = 50;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(2,1,1));
      s10.insert(simple_edge_t(1,0,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(4,5,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(3,2,1));
      
      std::string dn = "/Users/fons/Dvlp/graphviz/test_tc_sc_graph.dot";
      s10.graphviz(dn);
      
      tc_kernel_dag<simple_edge_t> tc(s10);
      //tc.pp(strm);
      
      ASSERT(tc(simple_edge_t(1,2,1)));
      ASSERT(tc(simple_edge_t(2,1,1)))
      ASSERT(!tc(simple_edge_t(2,3,1)));
      ASSERT(tc(simple_edge_t(3,2,1)))
      
      ASSERT(tc(simple_edge_t(0,5,1)));
      ASSERT(tc(simple_edge_t(5,4,1)))
      ASSERT(tc(simple_edge_t(1,4,1)));
      ASSERT(!tc(simple_edge_t(4,1,1)))
      
      ASSERT(tc(simple_edge_t(0,2,1)));
      ASSERT(tc(simple_edge_t(2,0,1)))
      ASSERT(tc(simple_edge_t(2,4,1)));
      
      
      return DONE;
}