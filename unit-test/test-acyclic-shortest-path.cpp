//
//  test-acyclic-paths.cpp
//  graph-repl
//
//  Created by alfons haffmans on 11/2/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_dag_longest_path);
REGISTER_TEST(test_dag_shortest_path);

std::pair<int, std::string> test_dag_longest_path(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.41));//1
      s10.insert(simple_edge_t(0,7,0.41));//2
      s10.insert(simple_edge_t(0,9,0.41));//3
      s10.insert(simple_edge_t(1,2,0.51));//4
      s10.insert(simple_edge_t(7,8,0.32));//5
      s10.insert(simple_edge_t(8,2,0.32));//6
      s10.insert(simple_edge_t(7,3,0.32));//7
      s10.insert(simple_edge_t(6,8,0.21));//8
      s10.insert(simple_edge_t(6,3,0.21));//9
      s10.insert(simple_edge_t(9,4,0.29));//10
      s10.insert(simple_edge_t(9,6,0.29));//11
      s10.insert(simple_edge_t(5,5,0));//12

      dag_all_longest_paths<simple_edge_t> LP(s10);
      LP.pp(strm);
      
      strm << "------------- distance ----------" << std::endl;
      std::vector<double> expected_dist= {0, 0.41, 1.23, 0.91, 0.70,0,0.70, 0.41, 0.91,0.41};
      size_t index = expected_dist.size();
      while (index-- > 0 ) {
            strm << "index : " << index << " expected : " << expected_dist[index] << " found : " << LP.dist(index) << std::endl;
            ASSERT(LP.dist(index).second && abs(LP.dist(index).first - expected_dist[index]) < 0.0001);
      }
      strm << "------------ predecessor ---------" << std::endl;
      std::vector<typename simple_edge_t::label_value_type> expected_pred = {0, 0, 8, 6, 9, 5, 9, 0, 6, 0};
      index = expected_pred.size();
      while (index-- > 0 ) {
            strm << "index : " << index << " expected : " << expected_pred[index] << " found : " << LP.pred(index) << std::endl;
            ASSERT(LP.pred(index).second && LP.pred(index).first == expected_pred[index]);
      }
      
      strm << std::endl;
      return DONE;
}

std::pair<int, std::string> test_dag_shortest_path(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.41));//1
      s10.insert(simple_edge_t(0,7,0.41));//2
      s10.insert(simple_edge_t(0,9,0.41));//3
      s10.insert(simple_edge_t(1,2,0.51));//4
      s10.insert(simple_edge_t(7,8,0.32));//5
      s10.insert(simple_edge_t(8,2,0.32));//6
      s10.insert(simple_edge_t(7,3,0.32));//7
      s10.insert(simple_edge_t(6,8,0.21));//8
      s10.insert(simple_edge_t(6,3,0.21));//9
      s10.insert(simple_edge_t(9,4,0.29));//10
      s10.insert(simple_edge_t(9,6,0.29));//11
      s10.insert(simple_edge_t(5,5,0));//12
      dag_all_shortest_paths<simple_edge_t> LP(s10);
      LP.pp(strm);
      strm << std::endl;
      return DONE;
}