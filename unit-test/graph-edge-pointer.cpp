//
//  graph-edge-pointer.cpp
//  graph-repl
//
//  Created by alfons haffmans on 9/15/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"
REGISTER_TEST(test_graph_edge_naked_ptr);
REGISTER_TEST(test_graph_edge_shared_ptr);

std::pair<int, std::string> test_graph_edge_naked_ptr(std::ostream& strm,int argc, const char *argv[])
{
      graph_impl<adjacency_list, simple_edge_t*> s10(20, graph_type_t::UNDIRECTED);
      std::string mn = "/Users/fons/Dvlp/graphviz/graph_with_naked_pointers.dot";
      
      s10.insert(new simple_edge_t(0,1,1));//1
      s10.insert(new simple_edge_t(0,2,1));//2
      s10.insert(new simple_edge_t(0,6,1));//3
      s10.insert(new simple_edge_t(0,5,1));//4
      s10.insert(new simple_edge_t(5,3,1));//5
      s10.insert(new simple_edge_t(3,4,1));//6
      s10.insert(new simple_edge_t(5,4,1));//7
      s10.insert(new simple_edge_t(4,6,1));//8
      s10.insert(new simple_edge_t(7,8,1));//9
      s10.graphviz(mn);
      strm << "edges : " << s10.E() << std::endl;
      ASSERT(s10.E() == 9);
      
      strm << "vertices : " << s10.V() << std::endl;
      ASSERT(s10.V() == 9);
      
      ASSERT(s10.is_directed() == false);
      auto p = new simple_edge_t(3,4,1);
      s10.has_edge(p);
      ASSERT(s10.has_edge(new simple_edge_t(0,1,1)));
      auto e = new simple_edge_t(0,1,1);
      e->reverse();
      ASSERT(s10.has_edge(e));
      ASSERT(!(s10.has_edge(new simple_edge_t(1,4,1))));
      
      e = s10.edge(3,4);
      ASSERT(edge_trait_t<simple_edge_t*>::from(e)   == 3);
      ASSERT(edge_trait_t<simple_edge_t*>::to(e)     == 4);
      ASSERT(edge_trait_t<simple_edge_t*>::weight(e) == 1);

      graph_impl<adjacency_list, simple_edge_t*>::vertex_generator s(s10);
      std::set<simple_edge_t::label_value_type> expected = {0,1,2,3,4,5,6,7,8};
      std::set<simple_edge_t::label_value_type> nodes;
      while (! s.iter_done() ) {
            nodes.insert(s.yield());
      }
      ASSERT_CONDITION("nodes expected in the graph", expected == nodes);

      nodes.clear();
      graph_base<simple_edge_t*>::vertex_generator salt(s10);
            while (! salt.iter_done() ) {
            nodes.insert(salt.yield());
      }
      ASSERT_CONDITION("nodes expected in the graph", expected == nodes);

      nodes.clear();
      std::set<simple_edge_t::label_value_type> expected_neighbours = {1,2,5,6};
      graph_base<simple_edge_t*>::adjacency_generator adj(s10, 0);
      while (!adj.iter_done()) {
            nodes.insert(adj.yield());
      }
      ASSERT_CONDITION("nodes expected as neighbours in the graph", expected_neighbours == nodes);
      std::set<simple_edge_t, edge_compare<simple_edge_t>> edges;
      
      std::set<simple_edge_t, edge_compare<simple_edge_t>> exp_edges = {
            simple_edge_t(0,1,1),
            simple_edge_t(0,2,1),
            simple_edge_t(0,6,1),
            simple_edge_t(0,5,1),
            simple_edge_t(5,3,1),
            simple_edge_t(3,4,1),
            simple_edge_t(5,4,1),
            simple_edge_t(4,6,1),
            simple_edge_t(7,8,1),
            simple_edge_t(1,0,1),//reverse
            simple_edge_t(2,0,1),
            simple_edge_t(6,0,1),
            simple_edge_t(5,0,1),
            simple_edge_t(3,5,1),
            simple_edge_t(4,3,1),
            simple_edge_t(4,5,1),
            simple_edge_t(6,4,1),
            simple_edge_t(8,7,1)};
      strm << "number of expected edges : " << exp_edges.size() << std::endl;
      ASSERT(exp_edges.size() == 18);
      for (auto &val : exp_edges) {
            strm << "expected edges : " << val << std::endl;
            strm << (exp_edges.find(val) == exp_edges.end()) << std::endl;
            ASSERT(exp_edges.find(val) != exp_edges.end());
      }
      for (graph_base<simple_edge_t*>::iterator it = s10.begin(); it != s10.end(); it++) {
            strm << edge_trait_t<simple_edge_t*>::deref(*it) << " : ";
            strm << *(*it) << std::endl;
            edges.insert(edge_trait_t<simple_edge_t*>::deref(*it));
            if (exp_edges.find(*(*it)) == exp_edges.end()) {
                  strm << *(*it) << "not found in expected edges list" << std::endl;
            }
            ASSERT_CONDITION("edges can be found in set", exp_edges.find(*(*it)) != exp_edges.end());
                  
      }
      ASSERT_CONDITION("expected edges", edges == exp_edges);
      return DONE;
}

std::pair<int, std::string> test_graph_edge_shared_ptr(std::ostream& strm,int argc, const char *argv[])
{
      graph_impl<adjacency_list, std::shared_ptr<simple_edge_t>> s10(20, graph_type_t::UNDIRECTED);
      std::string mn = "/Users/fons/Dvlp/graphviz/graph_with_naked_pointers.dot";
      
      s10.insert(std::shared_ptr<simple_edge_t>( new simple_edge_t(0,1,1)));//1
      s10.insert(std::shared_ptr<simple_edge_t>( new simple_edge_t(0,2,1)));//2
      s10.insert(std::shared_ptr<simple_edge_t>( new simple_edge_t(0,6,1)));//3
      s10.insert(std::shared_ptr<simple_edge_t>( new simple_edge_t(0,5,1)));//4
      s10.insert(std::shared_ptr<simple_edge_t>( new simple_edge_t(5,3,1)));//5
      s10.insert(std::shared_ptr<simple_edge_t>( new simple_edge_t(3,4,1)));//6
      s10.insert(std::shared_ptr<simple_edge_t>( new simple_edge_t(5,4,1)));//7
      s10.insert(std::shared_ptr<simple_edge_t>( new simple_edge_t(4,6,1)));//8
      s10.insert(std::shared_ptr<simple_edge_t>( new simple_edge_t(7,8,1)));//9
      s10.graphviz(mn);
      strm << "edges : " << s10.E() << std::endl;
      ASSERT(s10.E() == 9);
      
      strm << "vertices : " << s10.V() << std::endl;
      ASSERT(s10.V() == 9);
      
      ASSERT(s10.is_directed() == false);
      auto p = std::shared_ptr<simple_edge_t>(new simple_edge_t(3,4,1));
      s10.has_edge(p);
      ASSERT(s10.has_edge(std::shared_ptr<simple_edge_t>(new simple_edge_t(0,1,1))));
      auto e = std::shared_ptr<simple_edge_t>(new simple_edge_t(0,1,1));
      e->reverse();
      ASSERT(s10.has_edge(e));
      ASSERT(!(s10.has_edge(std::shared_ptr<simple_edge_t>(new simple_edge_t(1,4,1)))));
      
      auto e1 = s10.edge(3,4);
      ASSERT(edge_trait_t<std::shared_ptr<simple_edge_t>>::from(e1)   == 3);
      ASSERT(edge_trait_t<std::shared_ptr<simple_edge_t>>::to(e1)     == 4);
      ASSERT(edge_trait_t<std::shared_ptr<simple_edge_t>>::weight(e1) == 1);
      
      graph_impl<adjacency_list, std::shared_ptr<simple_edge_t>>::vertex_generator s(s10);
      std::set<simple_edge_t::label_value_type> expected = {0,1,2,3,4,5,6,7,8};
      std::set<simple_edge_t::label_value_type> nodes;
      while (! s.iter_done() ) {
            nodes.insert(s.yield());
      }
      ASSERT_CONDITION("nodes expected in the graph", expected == nodes);
      
      nodes.clear();
      graph_base<std::shared_ptr<simple_edge_t>>::vertex_generator salt(s10);
      while (! salt.iter_done() ) {
            nodes.insert(salt.yield());
      }
      ASSERT_CONDITION("nodes expected in the graph", expected == nodes);
      
      nodes.clear();
      std::set<simple_edge_t::label_value_type> expected_neighbours = {1,2,5,6};
      graph_base<std::shared_ptr<simple_edge_t>>::adjacency_generator adj(s10, 0);
      while (!adj.iter_done()) {
            nodes.insert(adj.yield());
      }
      ASSERT_CONDITION("nodes expected as neighbours in the graph", expected_neighbours == nodes);
      std::set<simple_edge_t, edge_compare<simple_edge_t>> edges;
      
      std::set<simple_edge_t, edge_compare<simple_edge_t>> exp_edges = {
            simple_edge_t(0,1,1),
            simple_edge_t(0,2,1),
            simple_edge_t(0,6,1),
            simple_edge_t(0,5,1),
            simple_edge_t(5,3,1),
            simple_edge_t(3,4,1),
            simple_edge_t(5,4,1),
            simple_edge_t(4,6,1),
            simple_edge_t(7,8,1),
            simple_edge_t(1,0,1),//reverse
            simple_edge_t(2,0,1),
            simple_edge_t(6,0,1),
            simple_edge_t(5,0,1),
            simple_edge_t(3,5,1),
            simple_edge_t(4,3,1),
            simple_edge_t(4,5,1),
            simple_edge_t(6,4,1),
            simple_edge_t(8,7,1)};
      strm << "number of expected edges : " << exp_edges.size() << std::endl;
      ASSERT(exp_edges.size() == 18);
      for (auto &val : exp_edges) {
            strm << "expected edges : " << val << std::endl;
            strm << (exp_edges.find(val) == exp_edges.end()) << std::endl;
            ASSERT(exp_edges.find(val) != exp_edges.end());
      }
      for (graph_base<std::shared_ptr<simple_edge_t>>::iterator it = s10.begin(); it != s10.end(); it++) {
            strm << edge_trait_t<std::shared_ptr<simple_edge_t>>::deref(*it) << " : ";
            strm << *(*it) << std::endl;
            edges.insert(edge_trait_t<std::shared_ptr<simple_edge_t>>::deref(*it));
            if (exp_edges.find(*(*it)) == exp_edges.end()) {
                  strm << *(*it) << "not found in expected edges list" << std::endl;
            }
            ASSERT_CONDITION("edges can be found in set", exp_edges.find(*(*it)) != exp_edges.end());
            
      }
      ASSERT_CONDITION("expected edges", edges == exp_edges);
      std::shared_ptr<simple_edge_t> val = s10.edge(2,0);
      std::cerr << *val << std::endl;
      ASSERT(*val == simple_edge_t(2,0,1));
      return DONE;
}