//
//  test-random-graph.cpp
//  graph-repl
//
//  Created by alfons haffmans on 7/27/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"


REGISTER_TEST(test_undirected_random_graph);
REGISTER_TEST(test_directed_random_graph);

std::pair<int, std::string> test_undirected_random_graph(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string mn = "/Users/fons/Dvlp/graphviz/undirected_random_graph.dot";
      double fill    = 0.20;
      size_t size    = 50;
      sparse_graph_t s12(size);
      s12 = manhattan_neighbor_graph(size * fill, s12);
      s12.graphviz(mn);

      return simple_prompt(strm);
      
}

std::pair<int, std::string> test_directed_random_graph(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string mn = "/Users/fons/Dvlp/graphviz/directed_random_graph.dot";
      double fill    = 0.20;
      size_t size    = 50;
      sparse_graph_t s12(size, graph_type_t::DIRECTED);
      s12 = manhattan_neighbor_graph(size * fill, s12);
      s12.graphviz(mn);
      
      return simple_prompt(strm);
      
}
