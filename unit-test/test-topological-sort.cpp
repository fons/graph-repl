//
//  test-topological-sort.cpp
//  graph-repl
//
//  Created by alfons haffmans on 8/8/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//
#include "tests.h"

REGISTER_TEST(test_not_dag);
REGISTER_TEST(test_dag);
REGISTER_TEST(test_reverse_topological_sort_dfs);
REGISTER_TEST(test_topological_sort_dfs);
REGISTER_TEST(test_topological_sort_queue);


std::pair<int, std::string> test_not_dag(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string fn = "/Users/fons/Dvlp/graphviz/not_dag_graph.dot";
      size_t size = 50;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
      //DIRECTED GRAPH fig. 19.1 p 149
      s10.insert(simple_edge_t(0,1,1));//1
      s10.insert(simple_edge_t(0,2,1));//2
      s10.insert(simple_edge_t(2, 0, 1));
      
      s10.graphviz(fn);
      
      is_dag<simple_edge_t> is_dag(s10);
      
      ASSERT_CONDITION("graph is no longer a DAG", ! is_dag());
      return DONE;
}

std::pair<int, std::string> test_dag(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string fn = "/Users/fons/Dvlp/graphviz/dag_graph.dot";
      size_t size = 50;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
      //fig 19.21 p 191
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
                                         
      s10.graphviz(fn);
      is_dag<simple_edge_t> is_dag(s10);
      ASSERT_CONDITION("graph is a DAG", is_dag());
     
      return DONE;
}

std::pair<int, std::string> test_reverse_topological_sort_dfs(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string fn = "/Users/fons/Dvlp/graphviz/reverse_topological_sort_dfs_graph.dot";
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
      
      topological_sort<sparse_graph_t, rev_top_sort_dfs<simple_edge_t>> rts(s10);
      strm << rts << std::endl;
      for (sparse_graph_t::iterator it = s10.begin(); it != s10.end(); it++) {
            auto edge = *it;
            if (edge.from == edge.to) continue;
            ASSERT(rts(edge.from) > rts(edge.to));
      }

      return DONE;
}

std::pair<int, std::string> test_topological_sort_dfs(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string fn = "/Users/fons/Dvlp/graphviz/topological_sort_dfs_graph.dot";
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
      
      topological_sort<sparse_graph_t> rts(s10);
      strm << rts << std::endl;
      
    
      for (sparse_graph_t::iterator it = s10.begin(); it != s10.end(); it++) {
            auto edge = *it;
            if (edge.from == edge.to) continue;
            ASSERT(rts(edge.from) < rts(edge.to));
      }
      
      return DONE;
}


std::pair<int, std::string> test_topological_sort_queue(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string fn = "/Users/fons/Dvlp/graphviz/topological_sort_queue_graph.dot";
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
      
      topological_sort<sparse_graph_t, top_sort_queue <simple_edge_t>> rts(s10);
      strm << rts << std::endl;
      for (sparse_graph_t::iterator it = s10.begin(); it != s10.end(); it++) {
            auto edge = *it;
            if (edge.from == edge.to) continue;
            ASSERT(rts(edge.from) < rts(edge.to));
      }
      
      return DONE;
}
