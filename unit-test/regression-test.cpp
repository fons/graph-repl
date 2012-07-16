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
      
      strm << "*********  finshed the runs *******************" << std::endl;

}