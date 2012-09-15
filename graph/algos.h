//
//  algos.h
//  graph-repl
//
//  Created by Alfons Haffmans on 5/21/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_algos_h
#define graph_repl_algos_h
#include <vector>
#include <map>
#include <deque>

#include "graph_base.h"
#include "degree.h"
#include "edge.h"

template <typename edge_t>
class is_connected {
      typedef typename edge_t::label_value_type Value;
public:
      is_connected(graph_base<edge_t>& g) : G(g){}
      bool operator()() {
            return construct_alt_3(G);
      }
private:
      graph_base<edge_t>& G;
      
      //      template <typename container_t>
      //      std::set<std::pair<Value, Value>> gen_path_set(container_t& vert)
      //      {
      //            std::set<std::pair<Value, Value>> path_set;
      //            for (auto& h : vert) {
      //                  for (auto& t : vert) {
      //                        if (h < t) {
      //                              path_set.insert(std::make_pair(h,t));
      //                        }
      //                  }
      //            }
      //            return path_set;
      //      }
      ////
      //      std::set<std::pair<Value, Value>>& drop_visited_paths(std::set<std::pair<Value, Value>>& path_set, std::set<std::pair<Value, Value>>& paths)
      //      {
      //            for (auto& path : paths) {
      //                  path_set.erase(path);
      //            }
      //            return path_set;
      //      }
      //      bool construct(graph_base<edge_t>& G)
      //      {
      //            std::set<Value> vert;
      //            for (typename graph_base<edge_t>::iterator it = G.begin(); it != G.end(); it++) {
      //                  vert.insert((*it).from);
      //            }
      //            auto path_set = gen_path_set(vert);
      //            auto iter_set = path_set;
      //            simple_path<edge_t> sp(G);
      //            for (auto& h_t : iter_set) {//path_set is being mutated..
      //                  auto head = h_t.first;
      //                  auto tail = h_t.second;
      //                  if (sp(head, tail)) {
      //                        auto path        = sp();
      //                        auto inter_paths = gen_path_set(path);
      //                        path_set = drop_visited_paths(path_set, inter_paths);
      //                        if (path_set.size() == 0) {
      //                              return true;
      //                        }
      //                  }
      //                  else {
      //                        //std::cerr << "no path from " << head << " to " << tail << std::endl;
      //                        return false;
      //                  }
      //            }
      //            return (path_set.size() == 0);
      //      }
      //
      //      std::set<std::pair<Value, Value>> add_visited_paths(std::set<std::pair<Value, Value>>& path_set, std::set<std::pair<Value, Value>>& vert)
      //      {
      //            for (auto&  h_t : vert) {
      //                  auto head = h_t.first;
      //                  auto tail = h_t.second;
      //                  if (head < tail){
      //                        path_set.insert(std::make_pair(head,tail));
      //                  }
      //                  else {
      //                        path_set.insert(std::make_pair(tail,head));
      //                  }
      //            }
      //            return path_set;
      //      }
      //
      //      bool construct_alt(graph_base<edge_t>& G)
      //      {
      //            std::set<Value> vert;
      //            for (typename graph_base<edge_t>::iterator it = G.begin(); it != G.end(); it++) {
      //                  vert.insert((*it).from);
      //            }
      //            size_t max = (G.V() * (G.V() - 1)) / 2;
      //            std::set<std::pair<Value, Value>> path_set;
      //            simple_path<edge_t> sp(G);
      //            for (auto& head  : vert) {
      //                  for (auto& tail : vert) {
      //                        if (! sp(head, tail) ) {
      //                              return false;
      //                        }
      //                        auto path        = sp();
      //                        auto inter_paths = gen_path_set(path);
      //                        path_set = add_visited_paths(path_set, inter_paths);
      //                        if (path_set.size() == max) {
      //                              //std::cerr << "1 : size " << path_set.size() << std::endl;
      //                              return true;
      //                        }
      //                  }
      //            }
      //            //std::cerr << "2 : size " << path_set.size() << std::endl;
      //            return (path_set.size() == max);
      //      }
      //
      bool construct_alt_2(graph_base<edge_t>& G)
      {
            std::set<Value> vert;
            for (typename graph_base<edge_t>::iterator it = G.begin(); it != G.end(); it++) {
                  vert.insert((*it).from);
            }
            simple_path<edge_t> sp(G);
            auto head = *(vert.begin());
            vert.erase(head);
            while (vert.size() > 0) {
                  auto tail = *(vert.begin());
                  if (! sp(head, tail) ) {
                        return false;
                  }
                  auto path        = sp();
                  for (auto& v : path) {
                        vert.erase(v);
                  }
                  
                  if (vert.size() == 0) {
                        return true;
                  }
            }
            
            return (vert.size() == 0);
      }
      
      bool construct_alt_3(graph_base<edge_t>& G)
      {
            size_t max = G.V();
            //            size_t mod = 0.10 * max;
            std::deque<Value> Q;
            std::set<Value> visited;
            auto head = (*G.begin()).from;
            Q.push_back(head);
            visited.insert(head);
            while (Q.size() > 0) {
                  auto node = Q.front();
                  Q.pop_front();
                  sparse_graph_t::adjacency_generator s(G, node);
                  while (! s.iter_done() ) {
                        auto adj = s.yield();
                        if (visited.find(adj) == visited.end()) {
                              Q.push_back(adj);
                              visited.insert(adj);
                              if (visited.size() == max) {
                                    return true;
                              }
                              
                              //                              if ((visited.size() % mod) == 0) {
                              //                                    double done = 100 * (1.0 * visited.size()) / (1.0 * max);
                              //                                    std::cerr << done << "% done " << std::endl;
                              //                              }
                        }
                  }
            }
            return (visited.size() == max);
      }
      
};


#endif
