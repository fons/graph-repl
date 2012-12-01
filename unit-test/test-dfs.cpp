//
//  test-dfs.cpp
//  graph-repl
//
//  Created by alfons haffmans on 8/10/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_dfs_property);

std::pair<int, std::string> test_dfs_property(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(20, graph_type_t::UNDIRECTED);
      
      //DIRECTED GRAPH fig. 19.1 p 149
      s10.insert(simple_edge_t(0,1,1));//1
      s10.insert(simple_edge_t(0,2,1));//2
      s10.insert(simple_edge_t(0,3,1));//3
      s10.insert(simple_edge_t(0,5,1));//1
      s10.insert(simple_edge_t(0,6,1));//2
      s10.insert(simple_edge_t(2,3,1));//5
      s10.insert(simple_edge_t(3,4,1));//6
      s10.insert(simple_edge_t(3,5,1));//7
      s10.insert(simple_edge_t(6,4,1));//12
      s10.insert(simple_edge_t(6,9,1));//13
      s10.insert(simple_edge_t(7,6,1));//16
      s10.insert(simple_edge_t(8,7,1));//16
      s10.insert(simple_edge_t(4,2,1));//9
      s10.insert(simple_edge_t(4,3,1));//8
      s10.insert(simple_edge_t(4,11,1));//10
      s10.insert(simple_edge_t(5,4,1));//11
      s10.insert(simple_edge_t(9,10,1));//18
      s10.insert(simple_edge_t(9,11,1));//19
      s10.insert(simple_edge_t(9,12,1));//20
      s10.insert(simple_edge_t(11,12,1));//21
      
      simple_dfs dfs(s10);
      dfs();
      ASSERT( (dfs.property<postorder_t>(3) ==  property<simple_edge_t, postorder_t>(dfs, 3)));
      ASSERT( (dfs.property<preorder_t>(3) ==  property<simple_edge_t, preorder_t>(dfs, 3)));
      return DONE;
}