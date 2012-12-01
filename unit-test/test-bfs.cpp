//
//  test-bfs.cpp
//  graph-repl
//
//  Created by alfons haffmans on 11/30/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//


#include "tests.h"

REGISTER_TEST(test_bfs);

std::pair<int, std::string> test_bfs(std::ostream& strm,int argc, const char *argv[])
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
      s10.insert(simple_edge_t(4,11,1));//10
      s10.insert(simple_edge_t(5,4,1));//11
      s10.insert(simple_edge_t(9,10,1));//18
      s10.insert(simple_edge_t(9,11,1));//19
      s10.insert(simple_edge_t(11,12,1));//21
      
      simple_bfs bfs(s10);
      bfs();
      std::string dn = test_path("bfs_graph.dot");
      s10.graphviz(dn);
      auto p = bfs.property<parent_t>(3);

      strm << "parent of 3 : " << p << std::endl;

      p = bfs.property<parent_t>(11);
      strm << "parent of 11 : " << p << std::endl;
      
      p = property<simple_edge_t, parent_t>(bfs, 12);
      strm << "parent of 12 : " << p << std::endl;
      size_t depth = 0;
      typename simple_edge_t::label_value_type s = 0;
      typename simple_edge_t::label_value_type t = 12;
      strm << "start from : " << t << " -> ";
      while (t != s) {
            t = bfs.property<parent_t>(t);
            strm << t;
            if (t != s) strm << " -> ";
            depth++;
      }
      ASSERT(depth == 4);
      strm << std::endl;
      //typename simple_edge_t::label_value_type
      t     = 8;
      depth = 0;
      strm << "start from : " << t << " -> ";
      while (t != s) {
            t = bfs.property<parent_t>(t);
            strm << t;
            if (t != s) strm << " -> ";
            depth++;
      }
      strm << std::endl;
      ASSERT(depth == 3);
      ASSERT(bfs.property<parent_t>(12) == 11);
      ASSERT(bfs.property<parent_t>(10) == 9);
      ASSERT(bfs.property<parent_t>(5) == 0);
      if (property<simple_edge_t, parent_t>(bfs,5) != 0) {
            ASSERT(1==5);
      }
      strm << ".........done............." << std::endl;
      return DONE;
}