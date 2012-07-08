//
//  transitive-clojure.h
//  graph-repl
//
//  Created by Alfons Haffmans on 7/6/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_transitive_clojure_h
#define graph_repl_transitive_clojure_h

#include "graph-type.h"
#include "graph_base.h"

template <typename graph_t>
class transitive_closure {

public:
      
      transitive_closure(graph_base<typename graph_t::edge_value_type>& G) : T(G.V(), direction(G)) {
            init(G);
      }
            
      bool operator()(const typename graph_t::edge_value_type& e) {
            return T.has_edge(e);  
      }

      graph_t& operator*() {
            return T;
      }
      
private:
      
      graph_t  T;

      void init(graph_base<typename graph_t::edge_value_type>& G) 
      {
            typename graph_t::vertex_generator vg(G);
            while (! vg.iter_done() ) {
                  auto node = vg.yield(); 
                  trans(G, typename graph_t::edge_value_type(node, node, 1)); 
            }      
      }

      void trans(graph_base<typename graph_t::edge_value_type>& G, typename graph_t::edge_value_type e) 
      {
            T.insert(e);
            auto v = e.from;
            auto w = e.to;
            typename graph_t::adjacency_generator ag(G, w);                        
            while (! ag.iter_done() ) {
                  auto t = ag.yield();
                  typename graph_t::edge_value_type ne(v, t, 1);
                  if (! T.has_edge(ne)) {
                        trans(G, ne);
                  }
            }
      }
};

//template <typename graph_t> 
//graph_t warshall_transitive_closure (graph_t& G)
//{
//      graph_t T(G.V(), direction(G));
//      
//      for (typename graph_base<typename graph_t::edge_value_type>::iterator it = G.begin(); it != G.end(); it++) {
//            T.insert(*it);
//      }
//
//      typename graph_t::vertex_generator vg(T);
//      while (! vg.iter_done() ) {
//            auto n = vg.yield(); 
//            auto e = typename graph_t::edge_value_type (n, n, 1);
//            if (! T.has_edge(e)) {
//                  T.insert(e);
//            }
//      }      
//      
//      typename graph_t::vertex_generator vg1(T);
//      typename graph_t::vertex_generator vg2(T);
//      typename graph_t::vertex_generator vg3(T);
//
////      while (! vg1.iter_done()) {
////            auto i = vg1.yield();
////            while (!vg2.iter_done()) {
////                  auto s = vg2.yield();
////                  if (T.has_edge(typename graph_t::edge_value_type (s, i, 1))) {
////                        while (!vg3.iter_done()) {
////                              auto t = vg3.yield();
////                              if (T.has_edge(typename graph_t::edge_value_type (i, t, 1))) {            
////                                    T.insert(typename graph_t::edge_value_type (s, t, 1));
////                              }
////                        }
////                  }
////            }
////            
////      }
//      return T;
//}
//



#endif
