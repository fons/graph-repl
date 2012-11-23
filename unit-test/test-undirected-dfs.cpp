//
//  test-undirected-dfs.cpp
//  graph-repl
//
//  Created by alfons haffmans on 7/27/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//


#include "tests.h"


REGISTER_TEST(test_undirected_dfs);
REGISTER_TEST(test_components);
REGISTER_TEST(test_edge_seperability);

std::pair<int, std::string> test_undirected_dfs(std::ostream& strm,int argc, const char *argv[])
{
      sparse_graph_t s10(10, graph_type_t::UNDIRECTED);
      
      
      //undirected graph p 88 fig 18.5
      s10.insert(simple_edge_t(0,2,1));//1
      s10.insert(simple_edge_t(0,5,1));//2
      s10.insert(simple_edge_t(0,7,1));//3
      s10.insert(simple_edge_t(2,6,1));//4
      s10.insert(simple_edge_t(6,4,1));//5
      s10.insert(simple_edge_t(4,7,1));//6
      s10.insert(simple_edge_t(7,1,1));//7
      s10.insert(simple_edge_t(4,3,1));//8
      s10.insert(simple_edge_t(3,5,1));//9
      s10.insert(simple_edge_t(4,5,1));//10
      std::string dn = test_path("undirected_dfs_graph.dot");
      s10.graphviz(dn);
      simple_dfs dfs(s10);
      dfs();
      std::cerr << dfs << std::endl;
      std::string df = test_path("undirected_dfs_dfs.dot");
      // p 98 fig 18.9
      dfs.graphviz(df);

      return simple_prompt(strm);
      //return DONE;
}

std::pair<int, std::string> test_components(std::ostream& strm,int argc, const char *argv[])
{
      
      sparse_graph_t s10(15);
      
      //graph p 101 fig. 18.11
      
      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(0,2,1));
      s10.insert(simple_edge_t(0,6,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(5,3,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(4,6,1));
      s10.insert(simple_edge_t(7,8,1));
      s10.insert(simple_edge_t(9,10,1));
      s10.insert(simple_edge_t(9,11,1));
      s10.insert(simple_edge_t(9,12,1));
      s10.insert(simple_edge_t(11,12,1));
     
      std::string dn = test_path("test_components_graph.dot");
      s10.graphviz(dn);
      simple_dfs dfs(s10);
      TRACE;
      dfs();
      TRACE;
      std::cerr << dfs << std::endl;
      std::string df = test_path("test_components_dfs.dot");
      dfs.graphviz(df);
      dfs.property(0);
      ASSERT_CONDITION("edge 0 in component 0", dfs.property<component_t>(0) == 0);
      std::cerr << "component edge 0  : " << dfs.property<component_t>(0) << std::endl;
      ASSERT_CONDITION("edge 6's parent is edge  4", dfs.property<parent_t>(6) == 4);
      std::cerr << "parent of edge 6  : " << dfs.property<parent_t>(6) << std::endl;
      ASSERT_CONDITION("preorder of edge 8 is 8", dfs.property<preorder_t>(8) == 8);
      std::cerr << "pre order  : " << dfs.property<preorder_t>(8) << std::endl;
      ASSERT_CONDITION("number of componets is 3", dfs.property<component_t>() == 3);
      std::cerr << "components : " << dfs.property<component_t>() << std::endl;
     
      return DONE;
}

std::pair<int, std::string> test_edge_seperability(std::ostream& strm,int argc, const char *argv[])
{
      
      // EDGE SEPERABILITY
      sparse_graph_t s10(15);
      
      s10.insert(simple_edge_t(0,1,1));
      s10.insert(simple_edge_t(1,2,1));
      s10.insert(simple_edge_t(2,6,1));
      s10.insert(simple_edge_t(0,6,1));
      s10.insert(simple_edge_t(6,7,1));
      s10.insert(simple_edge_t(7,8,1));
      s10.insert(simple_edge_t(7,10,1));
      s10.insert(simple_edge_t(8,10,1));
      s10.insert(simple_edge_t(0,5,1));
      s10.insert(simple_edge_t(5,3,1));
      s10.insert(simple_edge_t(5,4,1));
      s10.insert(simple_edge_t(3,4,1));
      s10.insert(simple_edge_t(4,9,1));
      s10.insert(simple_edge_t(4,11,1));
      s10.insert(simple_edge_t(9,11,1));
      s10.insert(simple_edge_t(11,12,1));
      std::string dn = test_path("edge_seperability_graph.dot");
      s10.graphviz(dn);

      simple_dfs dfs(s10);
      dfs();
      std::cerr << dfs << std::endl;
      std::string df = test_path("edge_seperability_dfs.dot");
      dfs.graphviz(df);
      dfs.property(0);
      auto val = dfs.property<component_t>(0);
      std::cerr << "component  : " << val << std::endl;
      std::cerr << "parent     : " << dfs.property<parent_t>(6) << std::endl;
      std::cerr << "pre order  : " << dfs.property<preorder_t>(8) << std::endl;

      
      std::cerr << "components : " << dfs.property<component_t>() << std::endl;
      ASSERT(dfs.property<component_t>() == 1);
      
      std::cerr << "bridges    : " << dfs.property<bridge_t>() << std::endl;
      ASSERT(dfs.property<bridge_t>() == 3);

      std::cerr << "artics     : " << dfs.property<articulation_t>() << std::endl;
      ASSERT(dfs.property<articulation_t>() == 6);

      std::cerr << "cycles     : " << dfs.property<cycle_t>() << std::endl;
      ASSERT(dfs.property<cycle_t>() == 12);
      
      //bridges
      auto bridges = dfs.property<bridges_t<simple_edge_t>>();
      for (auto it : bridges) {
            std::cerr << " bridges : " << it << std::endl;
      }
      std::set<simple_edge_t> exp_bridges = {simple_edge_t(0,5,1), simple_edge_t(6,7,1), simple_edge_t(11,12,1)};
      ASSERT_CONDITION("bridges", bridges == exp_bridges);
      
      //articulation points
      auto artics = dfs.property<artics_t<simple_edge_t>>();
      for (auto it : artics) {
            std::cerr << " artic : " << it << std::endl;
      }
      std::set<size_t> exp_art_p = {0,4,5,6,7,11};
      ASSERT_CONDITION("articulation points", artics == exp_art_p);
      
      return DONE;
      
}
