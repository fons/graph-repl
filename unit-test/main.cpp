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
      
      try {
            //test_priority_queue_base_2(std::cerr, argc, argv);
            test_priority_queue_kv_1(std::cerr, argc, argv);
            //run_tests(std::cerr, argc, argv);
      }
      catch(const std::exception& e) {
            std::cerr << "caught exception : " << e.what() << std::endl;
      }
      
      return 0;
}

