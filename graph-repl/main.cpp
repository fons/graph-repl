//
//  main.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 7/7/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//


#include <vector>
#include <iostream>
#include <bitset>
#include <cstdlib>
#include "graph.h"

int main (int argc, const char * argv[])
{  
          
      //auto dir = graph_type_t::DIRECTED;
#if 1
      std::string fn = "/Users/fons/Dvlp/graphviz/test.dot";  
      //std::string fn = "/tmp/test.txt";
      //std::ofstream ofile (fn);
      size_t size = 50;
      double fill = 0.19;
      sparse_graph_t s10(size, graph_type_t::DIRECTED);
      
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
            
      std::string dn = "/Users/fons/Dvlp/graphviz/test.dot";  
      s10.graphviz(dn);
      std::cerr << "-----------------------" << std::endl;    
           sparse_tc_t tc(s10);
      
      std::string dt = "/Users/fons/Dvlp/graphviz/tc.dot";  
      (*tc).graphviz(dt);
      transitive_closure<sparse_graph_t, tc_warshall<simple_edge_t>> wtc(s10);
      std::string wts = "/Users/fons/Dvlp/graphviz/wtc.dot"; 
      (*wtc).graphviz(wts);
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
      //      
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
      
#endif
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

