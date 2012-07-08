//
//  main.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 7/7/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

//#include <iostream>


#include <vector>
#include <iostream>
#include <bitset>
#include <cstdlib>


#include "graph.h"
//#include "degree.h"
//#include "graph_gen.h"
//#include "algos.h"
//#include "graph_search.h"
//#include "transitive-clojure.h"

//template <typename graph_t>

int main (int argc, const char * argv[])
{  
      simple_edge_t e(1,2,1);
      std::cerr << e << std::endl;
      labeled_edge_t l("from", "to", 1);
      std::cerr << l << std::endl;
      //auto dir = graph_type_t::DIRECTED;
      adjacency_matrix a1(4);
      a1(0,2,1);
      a1(1,3,1);
      std::cerr << a1 << std::endl;
      adjacency_list l1(5);
      l1(0,3,1);
      l1(0,0,1);
      l1(0,1,1);
      l1(1,4,1);
      l1(3,2,1);
      std::cerr << l1 << std::endl;
#if 1
      std::string fn = "/Users/fons/Dvlp/graphviz/test.dot";  
      //std::string fn = "/tmp/test.txt";
      //std::ofstream ofile (fn);
      size_t size = 50;
      double fill = 0.19;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
    
      //DIRECTED GRAPH fig. 19.1 p 149
      s10.insert(simple_edge_t(0,6,1));//1
      s10.insert(simple_edge_t(0,5,1));//2
      s10.insert(simple_edge_t(0,1,1));//3
      s10.insert(simple_edge_t(2,0,1));//4
      s10.insert(simple_edge_t(2,3,1));//5
      s10.insert(simple_edge_t(3,2,1));//6
      s10.insert(simple_edge_t(3,5,1));//7
      s10.insert(simple_edge_t(4,2,1));//9
      s10.insert(simple_edge_t(4,3,1));//8
      s10.insert(simple_edge_t(4,11,1));//10
      s10.insert(simple_edge_t(5,4,1));//11
      s10.insert(simple_edge_t(6,4,1));//12
      s10.insert(simple_edge_t(6,9,1));//13
      s10.insert(simple_edge_t(7,6,1));//14
      s10.insert(simple_edge_t(7,8,1));//15
      s10.insert(simple_edge_t(8,7,1));//16
      s10.insert(simple_edge_t(8,9,1));//17
      s10.insert(simple_edge_t(9,10,1));//18
      s10.insert(simple_edge_t(9,11,1));//19
      s10.insert(simple_edge_t(10,12,1));//20
      s10.insert(simple_edge_t(11,12,1));//21
      s10.insert(simple_edge_t(12,9,1));//22
      //     
      //
      
      //      s10.insert(simple_edge_t(0,5,1));//1
      //      s10.insert(simple_edge_t(0,2,1));//2
      //      s10.insert(simple_edge_t(0,7,1));//3
      //      s10.insert(simple_edge_t(2,6,1));//4      
      //      s10.insert(simple_edge_t(6,4,1));//5
      //      s10.insert(simple_edge_t(4,7,1));//6
      //      s10.insert(simple_edge_t(7,1,1));//7
      //      s10.insert(simple_edge_t(4,3,1));//8
      //      s10.insert(simple_edge_t(3,5,1));//9
      //      s10.insert(simple_edge_t(4,5,1));//10
      //
      
      // EDGE SEPERABILITY
      
      //      s10.insert(simple_edge_t(0,1,1));
      //      s10.insert(simple_edge_t(1,2,1));
      //      s10.insert(simple_edge_t(2,6,1));
      //      s10.insert(simple_edge_t(0,6,1));
      //      s10.insert(simple_edge_t(6,7,1));
      //      s10.insert(simple_edge_t(7,8,1));
      //      s10.insert(simple_edge_t(7,10,1));
      //      s10.insert(simple_edge_t(8,10,1));
      //      s10.insert(simple_edge_t(0,5,1));
      //      s10.insert(simple_edge_t(5,3,1));
      //      s10.insert(simple_edge_t(5,4,1));
      //      s10.insert(simple_edge_t(3,4,1));
      //      s10.insert(simple_edge_t(4,9,1));
      //      s10.insert(simple_edge_t(4,11,1));
      //      s10.insert(simple_edge_t(9,11,1));
      //      s10.insert(simple_edge_t(11,12,1));
      
      //bipartite graph
      //      s10.insert(simple_edge_t(0,1,1));
      //      s10.insert(simple_edge_t(0,3,1));
      //      s10.insert(simple_edge_t(0,5,1));
      //      s10.insert(simple_edge_t(1,2,1));
      //      s10.insert(simple_edge_t(2,9,1));
      //      s10.insert(simple_edge_t(9,6,1));
      //      s10.insert(simple_edge_t(6,7,1));
      //      s10.insert(simple_edge_t(7,8,1));
      //      s10.insert(simple_edge_t(8,9,1));
      //      s10.insert(simple_edge_t(9,10,1));
      //      s10.insert(simple_edge_t(9,12,1));
      //      s10.insert(simple_edge_t(11,12,1));
      //      s10.insert(simple_edge_t(4,11,1));
      //      s10.insert(simple_edge_t(3,4,1));
      //      s10.insert(simple_edge_t(4,5,1));
      std::string mn = "/Users/fons/Dvlp/graphviz/manhattan.dot";  
      sparse_graph_t s12(size, graph_type_t::DIRECTED);
      s12 = manhattan_neighbor_graph(size * fill, s12);
      s12.graphviz(mn);
      
      std::string dn = "/Users/fons/Dvlp/graphviz/test.dot";  
      s10.graphviz(dn);
      std::cerr << "-----------------------" << std::endl;    
      simple_dfs dfs(s10);
      dfs();
      std::cerr << dfs << std::endl;
      std::string df = "/Users/fons/Dvlp/graphviz/dfs.dot";  
      dfs.graphviz(df);

      sparse_tc_t tc(s10);
      
      std::string dt = "/Users/fons/Dvlp/graphviz/tc.dot";  
      (*tc).graphviz(dt);

      //sparse_graph_t wtc = warshall_transitive_closure(s10);
      //std::string wts = "/Users/fons/Dvlp/graphviz/wtc.dot"; 
      //wtc.graphviz(wts);
      //dfs.property<back_edge_t>(simple_edge_t(0,1, 1));
      
      //      dfs.property(0);
      //      auto val = dfs.property<component_t>(0);
      //      std::cerr << "component  : " << val << std::endl; 
      //      //==std::cerr << "parent     : " << dfs.property<parent_t>(6) << std::endl;
      //      std::cerr << "pre order  : " << dfs.property<preorder_t>(8) << std::endl;
      //      std::cerr << "components : " << dfs.property<component_t>() << std::endl;
      //      std::cerr << "bridges    : " << dfs.property<bridge_t>() << std::endl;
      //      std::cerr << "artics     : " << dfs.property<articulation_t>() << std::endl;
      //      std::cerr << "cycles     : " << dfs.property<cycle_t>() << std::endl;
      //      std::cerr << "bipartite  : " << dfs.property<bipartite_t>() << std::endl;
      //      auto bridges = dfs.property<bridges_t<simple_edge_t>>();
      //      for (auto it : bridges) {
      //            std::cerr << " bridges : " << it << std::endl;
      //      }
      //      
      //      auto artics = dfs.property<artics_t<simple_edge_t>>();
      //      for (auto it : artics) {
      //            std::cerr << " artic : " << it << std::endl;
      //      }
      //
      //      Degree deg(s10);
      //      std::cerr << deg << std::endl;
#endif
      //      degree_distribution<simple_edge_t> dd (deg);
      //      std::cerr << dd << std::endl;
      //      size_t node = 10;
      //      //sparse_graph_t::adjacency_generator s(s10, node);
      //      sparse_graph_t::vertex_generator s(s10);
      //
      //      while (! s.iter_done() ) {
      //            std::cerr << node << " --> " << s.yield() << std::endl; 
      //      }
      //      simple_edge_path_t sp(s10);
      //      size_t fr = 0;
      //      size_t to = 5;
      //      if (sp(fr, to)) {
      //            std::vector<size_t> p = sp();
      //            std::cerr << " there is a simple path from " << fr << " to " << to << std::endl;
      //            for(auto& elem : p) {
      //                  std::cerr << elem << "->";
      //            }
      //            std::cerr << std::endl;
      //      }
      //      else {
      //            std::cerr << " No path from " << fr << " to " << to << std::endl;
      //      }
      //      to = 3;
      //      if (sp(fr, to)) {
      //            std::vector<size_t> p = sp();
      //            std::cerr << " there is a simple path from " << fr << " to " << to << std::endl;
      //            for(auto& elem : p) {
      //                  std::cerr << elem << "->";
      //            }
      //            std::cerr << std::endl;
      //      }
      //      else {
      //            std::cerr << " No path from " << fr << " to " << to << std::endl;
      //      }
      // 
      //      is_connected<simple_edge_t> connected(s10);
      //      //connected.state();
      //      
      //      std:: cerr << " this graph is ";      
      //      if (!connected()) {
      //            std::cerr << "not ";
      //      }
      //      std::cerr << "connected..." << std::endl;
      //if (!sp(0,3)) {
      //      std::cerr << "no path from 0->3" << std::endl;
      //}
      return 0;
}


//int main (int argc, const char * argv[])
//{
//      simple_edge_t e(1,2,1);
//      std::cerr << e << std::endl;
//      labeled_edge_t l("from", "to", 1);
//      std::cerr << l << std::endl;
//      //graphtest G;
//      //G.HelloWorld("hello");
//      // insert code here...
//      std::cout << "Hello, World!\n";
//    return 0;
//}

