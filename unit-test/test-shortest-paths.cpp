//
//  test-shortest-paths.cpp
//  graph-repl
//
//  Created by alfons haffmans on 10/8/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"
REGISTER_TEST(test_shortest_path_dijkstra_dense);
REGISTER_TEST(test_shortest_path_dijkstra_pq);
REGISTER_TEST(test_shortest_path_bellman_ford);
REGISTER_TEST(test_bellman_ford_negative_cycle);

std::pair<int, std::string> test_shortest_path_dijkstra_dense(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.41));//1
      s10.insert(simple_edge_t(1,2,0.51));//2
      s10.insert(simple_edge_t(2,3,0.50));//3
      s10.insert(simple_edge_t(4,3,0.36));//4
      s10.insert(simple_edge_t(3,5,0.38));//5
      s10.insert(simple_edge_t(3,0,0.45));//6
      s10.insert(simple_edge_t(0,5,0.29));//7
      s10.insert(simple_edge_t(5,4,0.21));//8
      s10.insert(simple_edge_t(1,4,0.32));//9
      s10.insert(simple_edge_t(4,2,0.32));//10
      s10.insert(simple_edge_t(5,1,0.29));//11
      
      
      std::string dn = "/Users/fons/Dvlp/graphviz/dense_dijkstra_graph.dot";
      s10.graphviz(dn);
      
      single_source_shortest_path<simple_edge_t> SP(s10, 3);
      SP.pp(strm);
      sparse_graph_t t10(15, graph_type_t::DIRECTED);
      SP(t10);
      std::string dt = "/Users/fons/Dvlp/graphviz/dense_dijkstra_shortest_path.dot";
      t10.graphviz(dt);
      strm << "vertices : " << t10.V() << " : " << s10.V() << std::endl;
      ASSERT(t10.V() == s10.V());
      ASSERT(SP.pred(4).first == 5);
      ASSERT(SP.pred(1).first == 5);
      ASSERT(SP.pred(5).first == 3);
      ASSERT(SP.dist(4).first == (s10.edge(5,4).weight + s10.edge(3,5).weight));
      ASSERT(SP.dist(1).first == (s10.edge(5,1).weight + s10.edge(3,5).weight));
      strm<< "DONE" <<std::endl;
      return DONE;
}

std::pair<int, std::string> test_shortest_path_dijkstra_pq(std::ostream& strm,int argc, const char *argv[])
{
      
      sparse_graph_t s10(15, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,1, 6));//1
      s10.insert(simple_edge_t(0,2, 8));//2
      s10.insert(simple_edge_t(0,3,18));//3
      s10.insert(simple_edge_t(1,4,11));//4
      s10.insert(simple_edge_t(4,5, 3));//5
      s10.insert(simple_edge_t(5,3, 4));//6
      s10.insert(simple_edge_t(5,2, 7));//7
      s10.insert(simple_edge_t(2,3, 9));//8
      
      
      std::string dn = "/Users/fons/Dvlp/graphviz/pq_dijkstra_graph.dot";
      s10.graphviz(dn);
      
      single_source_shortest_path<simple_edge_t> SP(s10, 0);
      SP.pp(strm);
      sparse_graph_t t10(15, graph_type_t::DIRECTED);
      SP(t10);
      std::string dt = "/Users/fons/Dvlp/graphviz/pq_dijkstra_shortest_path.dot";
      t10.graphviz(dt);
      ASSERT(t10.V() == s10.V());
      ASSERT(SP.pred(4).first == 1);
      ASSERT(SP.pred(1).first == 0);
      ASSERT(SP.pred(3).first == 2);
      ASSERT(SP.dist(4).first == (s10.edge(1,4).weight + s10.edge(0,1).weight));
      ASSERT(SP.dist(3).first == (s10.edge(2,3).weight + s10.edge(0,2).weight));

      return DONE;
}

std::pair<int, std::string> test_shortest_path_bellman_ford(std::ostream& strm,int argc, const char *argv[])
{
      
      sparse_graph_t s10(15, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0, 4,  2));//1
      s10.insert(simple_edge_t(4, 3,  4));//2
      s10.insert(simple_edge_t(4, 1,  5));//3
      s10.insert(simple_edge_t(1, 3, -2));//4
      s10.insert(simple_edge_t(3, 2,  6));//5
      s10.insert(simple_edge_t(2, 1, -3));//6
            
      
      std::string dn = "/Users/fons/Dvlp/graphviz/bellman_ford_graph.dot";
      s10.graphviz(dn);
      single_source_shortest_path<simple_edge_t, shortest_path_bellman_ford<simple_edge_t>> SP(s10, 0);
      SP.pp(strm);

      sparse_graph_t t10(15, graph_type_t::DIRECTED);
      SP(t10);
      std::string dt = "/Users/fons/Dvlp/graphviz/bellman_ford_shortest_path.dot";
      t10.graphviz(dt);
      ASSERT(t10.V() == s10.V());
      
      ASSERT(SP.pred(1).first == 4);
      ASSERT(SP.pred(3).first == 1);
      ASSERT(SP.dist(1).first == (s10.edge(0,4).weight + s10.edge(4,1).weight));
      ASSERT(SP.dist(3).first == (s10.edge(0,4).weight + s10.edge(4,1).weight) + s10.edge(1,3).weight);
      ASSERT(!SP.negative_cycle());
      return DONE;
}

std::pair<int, std::string> test_bellman_ford_negative_cycle(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0, 4,  2));//1
      s10.insert(simple_edge_t(4, 3,  4));//2
      s10.insert(simple_edge_t(4, 1,  5));//3
      s10.insert(simple_edge_t(1, 3, -2));//4
      s10.insert(simple_edge_t(3, 2, -6));//5
      s10.insert(simple_edge_t(2, 1, -3));//6
      
      
      std::string dn = "/Users/fons/Dvlp/graphviz/bellman_ford_negative_cycle_graph.dot";
      s10.graphviz(dn);
      shortest_path_bellman_ford<simple_edge_t> SP(s10, 0);
      SP.pp(strm);
      ASSERT_CONDITION("graph has negative cycle", SP.negative_cycle())
      return DONE;
}