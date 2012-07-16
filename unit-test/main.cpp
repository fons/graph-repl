//
//  main.cpp
//  unit-test
//
//  Created by Alfons Haffmans on 7/9/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include <iostream>
//#include "regression-test.h"
#include "tests.h"

//def<max_tests> P("test_case_1", test_case_1);

int main (int argc, const char * argv[])
{
      float r =78;
      float b = 0;
      std::cerr << r/b << std::endl;
      run_tests();
      
      return 0;
}

