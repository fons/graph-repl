//
//  tests.h
//  graph-repl
//
//  Created by Alfons Haffmans on 7/11/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_tests_h
#define graph_repl_tests_h
#include "regression-test.h"


extern std::pair<int, std::string> test_edges(std::ostream& strm, int argc, const char *argv[]);
extern std::pair<int, std::string> test_case_1(std::ostream& strm, int argc, const char *argv[]);
extern std::pair<int, std::string> divide_by_zero(std::ostream& strm, int argc, const char *argv[]);


#endif
