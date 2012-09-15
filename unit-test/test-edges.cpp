//
//  test-edges.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 7/9/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//


#include "tests.h"


REGISTER_TEST(test_edges);
REGISTER_TEST(test_edge_compare);
REGISTER_TEST(test_edge_set);

#define DESCRIPTION_1 "\
This is a test \
" \


std::pair<int, std::string> test_edges(std::ostream& strm,int argc, const char *argv[])
{
      strm << std::string(DESCRIPTION_1) << std::endl;      
      simple_edge_t e(1,2,1);
      strm << e << std::endl;
      labeled_edge_t l("from", "to", 1);
      strm << l << std::endl;
      return DONE;
      
}

std::pair<int, std::string> test_edge_compare(std::ostream& strm,int argc, const char *argv[])
{
      
      simple_edge_t e(1,2,1);
      ASSERT(e == e);
      ASSERT(e != e.reverse());
      simple_edge_t p(5,6,2);
      ASSERT(p!=e);
      ASSERT(e < p);
      ASSERT(simple_edge_t(1,1,1) < simple_edge_t(1,2,1));
      ASSERT(simple_edge_t(1,1,1) <= simple_edge_t(1,1,1));
      ASSERT(simple_edge_t(1,1,0.9) < simple_edge_t(1,1,1));
      return DONE;
      
}

std::pair<int, std::string> test_edge_set(std::ostream& strm,int argc, const char *argv[])
{
      std::set<simple_edge_t> S;
      TRACE;
      S.insert(simple_edge_t(1,2,2));
      TRACE;
      S.insert(simple_edge_t(1,2,2));
      TRACE;
      ASSERT(S.size() ==1);

      ASSERT(S.find(simple_edge_t(1,2,2)) != S.end());
             
      return DONE;
}
