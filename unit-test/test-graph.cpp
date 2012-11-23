//
//  test-directed-graph.cpp
//  graph-repl
//
//  Created by alfons haffmans on 7/27/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"



REGISTER_TEST(test_degree);
REGISTER_TEST(test_graph);
REGISTER_TEST(test_vertex_generator);
REGISTER_TEST(test_adjacency_generator);
REGISTER_TEST(test_adjacency_edge_generator);

std::pair<int, std::string> test_graph(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      
      s10.insert(simple_edge_t(0,1,1));//1
      s10.insert(simple_edge_t(0,2,1));//2
      s10.insert(simple_edge_t(0,6,1));//3
      s10.insert(simple_edge_t(0,5,1));//4
      s10.insert(simple_edge_t(5,3,1));//5
      s10.insert(simple_edge_t(3,4,1));//6
      s10.insert(simple_edge_t(5,4,1));//7
      s10.insert(simple_edge_t(4,6,1));//8
      s10.insert(simple_edge_t(7,8,1));//9
      
      strm << "edges : " << s10.E() << std::endl;
      ASSERT(s10.E() == 9);
      
      strm << "vertices : " << s10.V() << std::endl;
      ASSERT(s10.V() == 9);
      
      ASSERT(s10.is_directed() == false);
      ASSERT(s10.has_edge(simple_edge_t(0,1,1)));
      ASSERT(s10.has_edge(simple_edge_t(0,1,1).reverse()));
      ASSERT(!(s10.has_edge(simple_edge_t(1,4,1))));
      return DONE;
}

std::pair<int, std::string> test_degree(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      
      //                 p 101 fig. 18.11
      //undirected graph p 14 fig 17.6
      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(0,6,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(5,3,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(4,6,1));
      s10.insert(simple_edge_t(7,8,1));
      s10.insert(simple_edge_t(9,10,1));
      s10.insert(simple_edge_t(9,11,1));
      s10.insert(simple_edge_t(9,12,1));
      s10.insert(simple_edge_t(11,12,1));
      
      std::string dn = test_path("degrees_graph.dot");
      s10.graphviz(dn);
            
      Degree deg(s10);
      strm << deg << std::endl;
      strm << deg[1] << std::endl;
      ASSERT(deg[0] == 4);
      ASSERT(deg[1] == 1);
      ASSERT(deg[2] == 1);
      ASSERT(deg[5] == 3);
      ASSERT(deg[7] == 1);
      ASSERT(deg[9] == 3);
      return DONE;
}

std::pair<int, std::string> test_vertex_generator(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(0,6,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(5,3,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(4,6,1));
      s10.insert(simple_edge_t(7,8,1));
      s10.insert(simple_edge_t(9,10,1));
      s10.insert(simple_edge_t(9,11,1));
      s10.insert(simple_edge_t(9,12,1));
      s10.insert(simple_edge_t(11,12,1));
      
      sparse_graph_t::vertex_generator s(s10);

      std::set<simple_edge_t::label_value_type> expected = {0,1,2,3,4,5,6,7,8,9,10,11,12};
      std::set<simple_edge_t::label_value_type> nodes;
      while (! s.iter_done() ) {
            nodes.insert(s.yield());
      }
      ASSERT_CONDITION("nodes exppected in the graph", expected == nodes);
      return DONE;
}


std::pair<int, std::string> test_adjacency_generator(std::ostream& strm,int argc, const char *argv[])
{
      
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);

      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(0,6,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(5,3,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(4,6,1));
      s10.insert(simple_edge_t(7,8,1));
      s10.insert(simple_edge_t(9,10,1));
      s10.insert(simple_edge_t(9,11,1));
      s10.insert(simple_edge_t(9,12,1));
      s10.insert(simple_edge_t(11,12,1));
      
      simple_edge_t::label_value_type node = 0;
      sparse_graph_t::adjacency_generator s(s10, node);
      std::set<simple_edge_t::label_value_type> expected = {1,2,5,6};
      std::set<simple_edge_t::label_value_type> nodes;
      while (! s.iter_done() ) {
            nodes.insert(s.yield());
      }
      ASSERT_CONDITION("nodes expected adjacent to 0 in the graph", expected == nodes);
      return DONE;
}

std::pair<int, std::string> test_adjacency_edge_generator(std::ostream& strm,int argc, const char *argv[])
{
      
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      
      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(0,6,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(5,3,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(4,6,1));
      s10.insert(simple_edge_t(7,8,1));
      s10.insert(simple_edge_t(9,10,1));
      s10.insert(simple_edge_t(9,11,1));
      s10.insert(simple_edge_t(9,12,1));
      s10.insert(simple_edge_t(11,12,1));
      
      simple_edge_t::label_value_type node = 0;
      sparse_graph_t::adjacency_edge_generator s(s10, node);
      std::set<simple_edge_t> expected = {simple_edge_t(0,1,1),simple_edge_t(0,2,1), simple_edge_t(0,6,1), simple_edge_t(0,5,1)};
      // for undirected graphs you have an edge going both ways..
      for (auto& v : expected) {
            expected.insert (reverse (v));
      }
      std::set<simple_edge_t> nodes;
      while (! s.iter_done() ) {
            auto e = s.yield();
            strm << e << std::endl;
            nodes.insert(e);
      }
      ASSERT_CONDITION("nodes expected adjacent to 0 in the graph", expected == nodes);
      return DONE;
}
