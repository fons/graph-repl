//
//  graph_gen.h
//  graph-repl
//
//  Created by Alfons Haffmans on 5/15/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_graph_gen_h
#define graph_repl_graph_gen_h
#include <random>

template<typename edge_t, typename container_t> graph_impl<edge_t, container_t>&& complete_graph(graph_impl<edge_t, container_t>& graph)
{
      for (auto i = 0; i < graph.V(); i++) {
            for (auto j = 0; j < i; j++) {
                  graph.insert(simple_edge_t(i, j, 1));
                  if (graph.is_directed()) {
                        graph.insert(simple_edge_t(j, i, 1));      
                  }
            }
      }
      return std::move(graph);  
}
extern size_t random_number(size_t max);

template<typename edge_t, typename container_t> graph_impl<edge_t, container_t>&& random_graph(graph_impl<edge_t, container_t>& graph)
{
      std::default_random_engine dre(static_cast<int>(time(0)));
      std::uniform_int_distribution<size_t> di (0, graph.V());
      std::set<std::pair<size_t, size_t>> seen;
      for (auto i = 0; i < graph.V(); i++) {
            size_t f = di(dre);
            size_t t = di(dre);
            auto pair = std::make_pair(f,t);
            auto riap = std::make_pair(t,f);
            if (seen.find(pair) == seen.end()) {            
                  graph.insert(simple_edge_t(f,t,1));
                  seen.insert(pair);
            }
            if (seen.find(riap) == seen.end()) {            
                  if (graph.is_directed()){
                        graph.insert(simple_edge_t(t,f,1));
                  }
                  seen.insert(riap);
            }
      }
      return std::move(graph);
}
template<typename edge_t, typename container_t> graph_impl<edge_t, container_t>&& example_graph_1(graph_impl<edge_t, container_t>& graph)
{
      graph.insert(simple_edge_t(0,1,1));
      graph.insert(simple_edge_t(0,2,1));
      graph.insert(simple_edge_t(0,6,1));
      graph.insert(simple_edge_t(0,5,1));
      graph.insert(simple_edge_t(5,3,1));      
      graph.insert(simple_edge_t(5,4,1));
      graph.insert(simple_edge_t(4,6,1));
      graph.insert(simple_edge_t(4,3,1));
      graph.insert(simple_edge_t(7,8,1));
      graph.insert(simple_edge_t(9,10,1));
      graph.insert(simple_edge_t(9,12,1));
      graph.insert(simple_edge_t(9,11,1));
      graph.insert(simple_edge_t(11,12,1));
      return std::move(graph);  
}
extern std::vector <simple_edge_t> random_plane_edges(size_t R, size_t N);

template<typename edge_t, typename container_t> graph_impl<edge_t, container_t>&& manhattan_neighbor_graph(size_t R, graph_impl<edge_t, container_t>& graph)
{
      std::vector<simple_edge_t> edges = random_plane_edges(R, graph.V());
      for (auto edge : edges) {
            graph.insert(edge);
      }
      return std::move(graph);
}

#endif
