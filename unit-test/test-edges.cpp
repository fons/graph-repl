//
//  test-edges.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 7/9/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include <iostream>
#include "graph.h"
#include "tests.h"


REGISTER_TEST(test_edges);

std::pair<int, std::string> test_edges(std::ostream& strm,int argc, const char *argv[])
{
      
      simple_edge_t e(1,2,1);
      strm << e << std::endl;
      labeled_edge_t l("from", "to", 1);
      strm << l << std::endl;
      return std::make_pair(1, "done");
      
}
