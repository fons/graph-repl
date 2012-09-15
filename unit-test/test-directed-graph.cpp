//
//  test-directed-graph.cpp
//  graph-repl
//
//  Created by alfons haffmans on 8/3/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_directed_graph);
REGISTER_TEST(test_reverse_directed_graph);
REGISTER_TEST(test_directed_graph_dfs);

std::pair<int, std::string> test_directed_graph(std::ostream& strm,int argc, const char *argv[])
{
      std::string fn = "/Users/fons/Dvlp/graphviz/directed_graph.dot";
      size_t size = 50;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
      //DIRECTED GRAPH fig. 19.1 p 149
      s10.insert(simple_edge_t(0,6,1));//1
      s10.insert(simple_edge_t(0,5,1));//2
      s10.insert(simple_edge_t(0,1,1));//3
      s10.insert(simple_edge_t(2,0,1));//4
      s10.insert(simple_edge_t(2,3,1));//5
      s10.insert(simple_edge_t(3,2,1));//6
      s10.insert(simple_edge_t(3,5,1));//7
      s10.insert(simple_edge_t(4,2,1));//9
      s10.insert(simple_edge_t(4,3,1));//8
      s10.insert(simple_edge_t(4,11,1));//10
      s10.insert(simple_edge_t(5,4,1));//11
      s10.insert(simple_edge_t(6,4,1));//12
      s10.insert(simple_edge_t(6,9,1));//13
      s10.insert(simple_edge_t(7,6,1));//14
      s10.insert(simple_edge_t(7,8,1));//15
      s10.insert(simple_edge_t(8,7,1));//16
      s10.insert(simple_edge_t(8,9,1));//17
      s10.insert(simple_edge_t(9,10,1));//18
      s10.insert(simple_edge_t(9,11,1));//19
      s10.insert(simple_edge_t(10,12,1));//20
      s10.insert(simple_edge_t(11,12,1));//21
      s10.insert(simple_edge_t(12,9,1));//22
      
      s10.graphviz(fn);
           
      std::set<simple_edge_t> exp_sl;
      std::set<simple_edge_t::label_value_type> vertex;

      sparse_graph_t::vertex_generator s(s10);
      while (! s.iter_done() ) {
            auto v = s.yield();
            vertex.insert(v);
            exp_sl.insert(simple_edge_t(v,v,1));
      }

      ASSERT_CONDITION("vertix count is accurate" , vertex.size() == s10.V());
      size_t edge_count = 0;
      std::set<simple_edge_t> self_loops;
      for (sparse_graph_t::iterator it = s10.begin(); it != s10.end(); it++ ){
            edge_count++;
            if ((*it).to != (*it).from) continue;
            self_loops.insert(*it);
      }
      strm << "# vertices : " << vertex.size() << " ; # self loops " << self_loops.size() << std::endl;
      ASSERT_CONDITION("self loops equal to nodes", self_loops.size() == vertex.size());
      ASSERT_CONDITION("expected self loops found", exp_sl == self_loops);
      strm << "edges : " << edge_count << " : " << s10.E() << std::endl;
      ASSERT_CONDITION("edge count is accurate", edge_count == s10.E());

      strm<<std::endl;
      strm << "------------------done------------------" << std::endl;
      return DONE;
      
}

//reversing a directed graph
std::pair<int, std::string> test_reverse_directed_graph(std::ostream& strm,int argc, const char *argv[])
{
      std::string fn = "/Users/fons/Dvlp/graphviz/reverse_directed_graph.dot";
      size_t size = 50;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
      //DIRECTED GRAPH fig. 19.1 p 149
      s10.insert(simple_edge_t(0,6,1));//1
      s10.insert(simple_edge_t(0,5,1));//2
      s10.insert(simple_edge_t(0,1,1));//3
      s10.insert(simple_edge_t(2,0,1));//4
      s10.insert(simple_edge_t(2,3,1));//5
      s10.insert(simple_edge_t(3,2,1));//6
      s10.insert(simple_edge_t(3,5,1));//7
      s10.insert(simple_edge_t(4,2,1));//9
      s10.insert(simple_edge_t(4,3,1));//8
      s10.insert(simple_edge_t(4,11,1));//10
      s10.insert(simple_edge_t(5,4,1));//11
      s10.insert(simple_edge_t(6,4,1));//12
      s10.insert(simple_edge_t(6,9,1));//13
      s10.insert(simple_edge_t(7,6,1));//14
      s10.insert(simple_edge_t(7,8,1));//15
      s10.insert(simple_edge_t(8,7,1));//16
      s10.insert(simple_edge_t(8,9,1));//17
      s10.insert(simple_edge_t(9,10,1));//18
      s10.insert(simple_edge_t(9,11,1));//19
      s10.insert(simple_edge_t(10,12,1));//20
      s10.insert(simple_edge_t(11,12,1));//21
      s10.insert(simple_edge_t(12,9,1));//22
      
      auto s11 = reverse(s10);
      s11.graphviz(fn);
      ASSERT_CONDITION("have the same number of vertices", s10.V() == s11.V());
      ASSERT_CONDITION("have the same number of edges", s10.E() == s11.E());
      strm << "test : each edge should have a reverse" << std::endl;
      for (sparse_graph_t::iterator it = s10.begin(); it != s10.end(); it++) {
            //strm << "testing edge " << *it << std::endl;
            ASSERT( s11.has_edge((*it).reverse()));
      }
      return DONE;      
}

//dfs of a digraph
std::pair<int, std::string> test_directed_graph_dfs(std::ostream& strm,int argc, const char *argv[])
{
      std::string fn = "/Users/fons/Dvlp/graphviz/directed_graph_dfs.dot";
      size_t size = 50;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
      //DIRECTED GRAPH fig. 19.1 p 149
      s10.insert(simple_edge_t(0,6,1));//1
      s10.insert(simple_edge_t(0,5,1));//2
      s10.insert(simple_edge_t(0,1,1));//3
      s10.insert(simple_edge_t(2,0,1));//4
      s10.insert(simple_edge_t(2,3,1));//5
      s10.insert(simple_edge_t(3,2,1));//6
      s10.insert(simple_edge_t(3,5,1));//7
      s10.insert(simple_edge_t(4,2,1));//9
      s10.insert(simple_edge_t(4,3,1));//8
      s10.insert(simple_edge_t(4,11,1));//10
      s10.insert(simple_edge_t(5,4,1));//11
      s10.insert(simple_edge_t(6,4,1));//12
      s10.insert(simple_edge_t(6,9,1));//13
      s10.insert(simple_edge_t(7,6,1));//14
      s10.insert(simple_edge_t(7,8,1));//15
      s10.insert(simple_edge_t(8,7,1));//16
      s10.insert(simple_edge_t(8,9,1));//17
      s10.insert(simple_edge_t(9,10,1));//18
      s10.insert(simple_edge_t(9,11,1));//19
      s10.insert(simple_edge_t(10,12,1));//20
      s10.insert(simple_edge_t(11,12,1));//21
      s10.insert(simple_edge_t(12,9,1));//22
      
      simple_dfs dfs(s10);
      dfs();
      dfs.graphviz(fn);
      strm << dfs << std::endl;
      
      ASSERT(dfs.is_down_edge(simple_edge_t(4,2,1)));
      ASSERT(!dfs.is_down_edge(simple_edge_t(4,2,1).reverse()));
      ASSERT(dfs.is_back_edge(simple_edge_t(2,0,1)));
      ASSERT(!dfs.is_back_edge(simple_edge_t(2,9,1))); // non-existing edge
      ASSERT(dfs.is_cross_edge(simple_edge_t(7,6,1)));
      ASSERT(!dfs.is_down_edge(simple_edge_t(4,11,1)));
      ASSERT(dfs.is_tree_edge(simple_edge_t(4,11,1)));
      ASSERT(dfs.is_tree_edge(simple_edge_t(0,6,1)));
      ASSERT(dfs.is_tree_edge(simple_edge_t(9,10,1)));
      return DONE;
}


//convert digraph to DAG using the dfs..

//reachiblity/ transitive closure-> warshall's algo, dfs based algo

