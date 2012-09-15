//
//  digraph-strong-components.cpp
//  graph-repl
//
//  Created by alfons haffmans on 8/27/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_kosaraju);
REGISTER_TEST(test_tarjan);
REGISTER_TEST(test_gabow);

std::pair<int, std::string> test_kosaraju(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string fn = "/Users/fons/Dvlp/graphviz/test_kosaraju.dot";
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
      s10.insert(simple_edge_t(7,8,1));//15Ç
      s10.insert(simple_edge_t(8,7,1));//16
      s10.insert(simple_edge_t(8,9,1));//17
      s10.insert(simple_edge_t(9,10,1));//18
      s10.insert(simple_edge_t(9,11,1));//19
      s10.insert(simple_edge_t(10,12,1));//20
      s10.insert(simple_edge_t(11,12,1));//21
      s10.insert(simple_edge_t(12,9,1));//22

      s10.graphviz(fn);
      //auto R = reverse(s10);
      //component_kosaraju<simple_edge_t> k(s10);
      strong_components<simple_edge_t, component_kosaraju<simple_edge_t>> k(s10);
      k.pp(strm);
      ASSERT(k.count() == 4);
      ASSERT(!k(0,1));
      ASSERT(k(3,2) && k(2,3));
      ASSERT(k(7,8) && k(8,7));
      ASSERT(!k(8,11));
      ASSERT(!k(9,8) && k(9,10) && k(9,11) && k(9,12) && k(9,9));
      ASSERT(k[9] == k[10]);
      return DONE;
}

std::pair<int, std::string> test_tarjan(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string fn = "/Users/fons/Dvlp/graphviz/test_tarjan.dot";
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
      strong_components<simple_edge_t, component_tarjan<simple_edge_t>> k(s10);
      k.pp(strm);
      ASSERT(k.count() == 4);
      ASSERT(!k(0,1));
      ASSERT(k(3,2) && k(2,3));
      ASSERT(k(7,8) && k(8,7));
      ASSERT(!k(8,11));
      ASSERT(!k(9,8) && k(9,10) && k(9,11) && k(9,12) && k(9,9));
      ASSERT(k[9] == k[10]);
      return DONE;
}

std::pair<int, std::string> test_gabow(std::ostream& strm,int argc, const char *argv[])
{
      
      std::string fn = "/Users/fons/Dvlp/graphviz/test_tarjan.dot";
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
      strong_components<simple_edge_t> k(s10);
      k.pp(strm);
      ASSERT(k.count() == 4);
      ASSERT(!k(0,1));
      ASSERT(k(3,2) && k(2,3));
      ASSERT(k(7,8) && k(8,7));
      ASSERT(!k(8,11));
      ASSERT(!k(9,8) && k(9,10) && k(9,11) && k(9,12) && k(9,9));
      ASSERT(k[9] == k[10]);
      return DONE;
}
