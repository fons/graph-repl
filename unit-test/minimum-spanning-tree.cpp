//
//  minimum-spanning-tree.cpp
//  graph-repl
//
//  Created by alfons haffmans on 9/18/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"


REGISTER_TEST(test_mst_dense_prim);

std::pair<int, std::string> test_mst_dense_prim(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::UNDIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.32));//1
      s10.insert(simple_edge_t(0,2,0.29));//2
      s10.insert(simple_edge_t(0,6,0.51));//3
      s10.insert(simple_edge_t(5,3,0.18));//4
      s10.insert(simple_edge_t(7,4,0.46));//5
      s10.insert(simple_edge_t(5,4,0.40));//6
      s10.insert(simple_edge_t(0,5,0.60));//7
      s10.insert(simple_edge_t(6,4,0.51));//8
      s10.insert(simple_edge_t(7,0,0.31));//9
      s10.insert(simple_edge_t(7,6,0.25));//10
      s10.insert(simple_edge_t(7,1,0.21));//11
      s10.insert(simple_edge_t(4,3,0.34));//12
      
      std::string dn = "/Users/fons/Dvlp/graphviz/dense_prim_graph.dot";
      s10.graphviz(dn);
      
      mst_prim<simple_edge_t> P(s10);
      P.pp(strm);
      strm<< "DONE" <<std::endl;
      return DONE;
}


