//
//  test-all-pairs-shortest-path.cpp
//  graph-repl
//
//  Created by alfons haffmans on 10/20/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"
REGISTER_TEST(test_all_pairs_shortest_path_dijkstra);
REGISTER_TEST(test_all_pairs_shortest_path_floyd_warshall);

std::pair<int, std::string> test_all_pairs_shortest_path_dijkstra(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.41));//1
      s10.insert(simple_edge_t(1,2,0.51));//2
      s10.insert(simple_edge_t(2,3,0.50));//3
      s10.insert(simple_edge_t(4,3,0.36));//4
      s10.insert(simple_edge_t(3,5,0.38));//5
      s10.insert(simple_edge_t(3,0,0.45));//6
      s10.insert(simple_edge_t(0,5,0.29));//7
      s10.insert(simple_edge_t(5,4,0.21));//8
      s10.insert(simple_edge_t(1,4,0.32));//9
      s10.insert(simple_edge_t(4,2,0.32));//10
      s10.insert(simple_edge_t(5,1,0.29));//11
      
      
      std::string dn = "/Users/fons/Dvlp/graphviz/all_pairs_shortest_path_dijkstra_graph.dot";
      s10.graphviz(dn);
      
      all_pairs_shortest_path_dijkstra<simple_edge_t> AP(s10);
      
      graph_base<simple_edge_t>::vertex_generator vga(s10);
      while (! vga.iter_done()) {
            auto y = vga.yield();
            single_source_shortest_path<simple_edge_t> SP(s10, y);
            graph_base<simple_edge_t>::vertex_generator vg(s10);
            while (!vg.iter_done()) {
                  auto v = vg.yield();
                  strm << "from : " << y << " to : " << v << " ";
                  strm << "distance : " << AP.dist(y,v) << " : " << SP.dist(v) << std::endl;
                  ASSERT(AP.dist(y,v) == SP.dist(v));
                  ASSERT(AP.pred(y,v) == SP.pred(v));
            }
      }
      strm << "done" << std::endl;
      return DONE;
}



std::pair<int, std::string> test_all_pairs_shortest_path_floyd_warshall(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(15, graph_type_t::DIRECTED);
      
      s10.insert(simple_edge_t(0,1,0.41));//1
      s10.insert(simple_edge_t(1,2,0.51));//2
      s10.insert(simple_edge_t(2,3,0.50));//3
      s10.insert(simple_edge_t(4,3,0.36));//4
      s10.insert(simple_edge_t(3,5,0.38));//5
      s10.insert(simple_edge_t(3,0,0.45));//6
      s10.insert(simple_edge_t(0,5,0.29));//7
      s10.insert(simple_edge_t(5,4,0.21));//8
      s10.insert(simple_edge_t(1,4,0.32));//9
      s10.insert(simple_edge_t(4,2,0.32));//10
      s10.insert(simple_edge_t(5,1,0.29));//11
      
      
      std::string dn = "/Users/fons/Dvlp/graphviz/all_pairs_shortest_path_floyd_warshall_graph.dot";
      s10.graphviz(dn);
      
      all_pairs_shortest_path_floyd_warshall<simple_edge_t> AP(s10);
      
      graph_base<simple_edge_t>::vertex_generator vga(s10);
      while (! vga.iter_done()) {
            auto y = vga.yield();
            single_source_shortest_path<simple_edge_t> SP(s10, y);
            graph_base<simple_edge_t>::vertex_generator vg(s10);
            while (!vg.iter_done()) {
                  auto v = vg.yield();
                  strm << "from : " << y << " to : " << v << " ";
                  strm << "distance : " << AP.dist(y,v) << " : " << SP.dist(v);
                  strm << " pred :" << AP.pred(y,v) << " : " << SP.pred(v) << std::endl;                  
                  ASSERT(abs(AP.dist(y,v).first - SP.dist(v).first) < 0.00001) ;
                  ASSERT(AP.dist(y,v).second == SP.dist(v).second);
                  if (y != v) ASSERT(AP.pred(y,v) == SP.pred(v));
            }
      }
      AP.pp(strm);
      strm << "done" << std::endl;
      return DONE;
}

