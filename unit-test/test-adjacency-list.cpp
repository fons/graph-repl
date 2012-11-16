//
//  test-adjacency-list.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 7/24/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"


REGISTER_TEST(test_adjacency_list);
REGISTER_TEST(test_adjacency_list_rm);

std::pair<int, std::string> test_adjacency_list(std::ostream& strm,int argc, const char *argv[])
{
      std::set<adjacency_list_t::edge_tuple_t> exp_edges =
      {
            std::make_tuple(0,3,1),
            std::make_tuple(0,0,1),
            std::make_tuple(0,1,1),
            std::make_tuple(1,4,1),
            std::make_tuple(3,2,1)
      };

      adjacency_list_t l1(10);

      l1(0,3,1);
      l1(0,0,1);
      l1(0,1,1);
      l1(1,4,1);
      l1(3,2,1);
      std::cerr << l1 << std::endl;
      
      ASSERT(l1.size() == 5);
      ASSERT(l1.max_size() == 10);
      ASSERT(l1(1,4) == 1);
      
      std::set<adjacency_list_t::edge_tuple_t> edges;
      for (adjacency_list_t::iterator it = l1.begin(); it != l1.end(); it++) {
            edges.insert(*it);
      }
      ASSERT_CONDITION("expected edges are iterated over", exp_edges == edges);

      return DONE;
}

std::pair<int, std::string> test_adjacency_list_rm(std::ostream& strm,int argc, const char *argv[])
{
      std::set<adjacency_list_t::edge_tuple_t> exp_edges =
      {
            std::make_tuple(0,3,1),
            std::make_tuple(0,0,1),
            std::make_tuple(0,1,1),
            std::make_tuple(3,2,1)
      };
      
      adjacency_list_t l1(10);
      
      l1(0,3,1);
      l1(0,0,1);
      l1(0,1,1);
      l1(1,4,1);
      l1(3,2,1);
      
      l1.rm(1,4);
      std::cerr << l1 << std::endl;
      
      ASSERT(l1.size() == 4);
      ASSERT(l1.max_size() == 10);
      ASSERT(l1(1,4) == 0);
      ASSERT(l1(0,3) == 1);
      std::set<adjacency_list_t::edge_tuple_t> edges;
      for (adjacency_list_t::iterator it = l1.begin(); it != l1.end(); it++) {
            edges.insert(*it);
      }
      ASSERT_CONDITION("rm : expected edges are iterated over", exp_edges == edges);
      
      return DONE;
}
