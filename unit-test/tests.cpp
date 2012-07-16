//
//  tests.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 7/12/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include <iostream>
#include <exception>

#include "tests.h"

#include "assertion.h"
REGISTER_TEST(test_case_1);
REGISTER_TEST(divide_by_zero);

std::pair<int, std::string> test_case_1(std::ostream& strm, int argc, const char *argv[])
{
      strm << "test_case_1 is called...." << std::endl;
      return std::make_pair(0, "not implemented");
}

std::pair<int, std::string> divide_by_zero(std::ostream& strm, int argc, const char *argv[])
{

      strm << "divide_by_zero is called...." << std::endl;
      auto val = 10.990 / 0.000;
      ASSERT_CONDITION("INF DETECTED", val != 2 * val);
      //char *p = nullptr;
      //throw 1;
      //std::cerr << "result 10 / 0 : " << val << *p << std::endl;
      return std::make_pair(0, "not implemented");
}
