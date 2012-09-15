//
//  regression-test.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 7/10/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include <iostream>
#include <vector>
#include <map>
#include "regression-test.h"

void run_tests(int argc, const char *argv[])
{
      
      run_tests(std::cout, argc, argv); 
}

void run_tests()
{
      run_tests(0, nullptr);
}

void run_tests(std::ostream& strm, int argc, const char* argv[])
{
      strm << "*********  starting the test runs... **********" << std::endl;

      def<max_tests>::run(strm, argc, argv); 
      
      strm << "*********  finished the test runs *******************" << std::endl;

}

std::pair<int, std::string> simple_prompt(std::ostream& strm)
{
      static prompt p;
      return p(strm);
}

std::pair<int, std::string> simple_return(return_t state)
{
      if (state == return_t::NOT_IMPLEMENTED) {
            return std::make_pair(0, "not implemented");
      }

      if (state == return_t::SUCCESS) {
            return std::make_pair(1, "done");
      }

      if (state == return_t::FAILURE) {
            return std::make_pair(-1, "failure");
      }

      return std::make_pair(-20, "undefined error state");
      
}


