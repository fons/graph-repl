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
            //test_weighted_graph(std::cerr, argc, argv);
            //test_edge_ptr(std::cerr, argc, argv);
            //test_graph_edge_naked_ptr(std::cerr, argc, argv);
            //test_graph_edge_shared_ptr(std::cerr, argc, argv);
            test_mst_dense_prim(std::cerr, argc, argv);
            //test_kosaraju(std::cerr, argc, argv);
            //test_tarjan(std::cerr, argc, argv);
            //test_gabow(std::cerr, argc, argv);
            //test_transitive_closure_kernel_dag(std::cerr, argc, argv);
            //test_transitive_closure_dag(std::cerr, argc, argv);
            //run_tests(std::cerr, argc, argv);
      }
      catch(const std::exception& e) {
            std::cerr << "caught exception : " << e.what() << std::endl;
      }
      
      return 0;
}

