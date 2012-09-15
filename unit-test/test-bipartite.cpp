//
//  test-bipartite.cpp
//  graph-repl
//
//  Created by alfons haffmans on 7/29/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"
#include "assertion.h"
REGISTER_TEST(test_bipartite);
REGISTER_TEST(test_bipartite_negative);

std::pair<int, std::string> test_bipartite(std::ostream& strm,int argc, const char *argv[])
{

      sparse_graph_t s10(10, graph_type_t::UNDIRECTED);
      //bipartite graph
      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(0,3,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(1,2,1));
      s10.insert(simple_edge_t(2,9,1));
      s10.insert(simple_edge_t(9,6,1));
      s10.insert(simple_edge_t(6,7,1));
      s10.insert(simple_edge_t(7,8,1));
      s10.insert(simple_edge_t(8,9,1));
      s10.insert(simple_edge_t(9,10,1));
      s10.insert(simple_edge_t(9,12,1));
      s10.insert(simple_edge_t(11,12,1));
      s10.insert(simple_edge_t(4,11,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(4,5,1));

      std::string dn = "/Users/fons/Dvlp/graphviz/test_bipartite.dot";
      s10.graphviz(dn);
      simple_dfs dfs(s10);
      dfs();
      std::cerr << dfs << std::endl;
      std::string df = "/Users/fons/Dvlp/graphviz/test_bipartite_dfs.dot";
      dfs.graphviz(df);
      std::cerr << "bipartite  : " << dfs.property<bipartite_t>() << std::endl;
      ASSERT(dfs.property<bipartite_t>() == 1);
      
      return DONE;
}

std::pair<int, std::string> test_bipartite_negative(std::ostream& strm,int argc, const char *argv[])
{
      
      sparse_graph_t s10(10, graph_type_t::UNDIRECTED);
      //bipartite graph
      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(0,3,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(1,2,1));
      s10.insert(simple_edge_t(1,3,1));
      s10.insert(simple_edge_t(2,9,1));
      s10.insert(simple_edge_t(9,6,1));
      s10.insert(simple_edge_t(6,7,1));
      s10.insert(simple_edge_t(7,8,1));
      s10.insert(simple_edge_t(8,9,1));
      s10.insert(simple_edge_t(9,10,1));
      s10.insert(simple_edge_t(9,12,1));
      s10.insert(simple_edge_t(11,12,1));
      s10.insert(simple_edge_t(4,11,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(4,5,1));
      
      std::string dn = "/Users/fons/Dvlp/graphviz/test_bipartite_negative.dot";
      s10.graphviz(dn);
      simple_dfs dfs(s10);
      dfs();
      std::cerr << dfs << std::endl;
      std::string df = "/Users/fons/Dvlp/graphviz/test_bipartite_negative_dfs.dot";
      dfs.graphviz(df);
      std::cerr << "bipartite  : " << dfs.property<bipartite_t>() << std::endl;
      ASSERT(dfs.property<bipartite_t>() == 0);
      
      return DONE;
}
