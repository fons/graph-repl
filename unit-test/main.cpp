//
//  main.cpp
//  unit-test
//
//  Created by Alfons Haffmans on 7/9/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include <iostream>

#include "tests.h"


int main (int argc, const char * argv[])
{
      test_preflow_push(std::cerr, argc, argv);
      try {
            //run_tests(std::cerr, argc, argv);
      }
      catch(const std::exception& e) {
            std::cerr << "caught exception : " << e.what() << std::endl;
      }
      
      return 0;
}

