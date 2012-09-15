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
//
// use the dfs to construct the transitive closure of the graph
//
template<typename edge_t>
struct tc_dfs {
public:
      //lazy evaluation
      explicit tc_dfs (graph_base<edge_t>& G) : G(G){}
      //eager evaluation
      explicit tc_dfs (graph_base<edge_t>& G, graph_base<edge_t>& T) : G(G){
            init(G,T);
      }
      //lazy evaluation; re-evaluation
      void operator()(graph_base<edge_t>& T) {
            init(G,T);
      }
private :
      graph_base<edge_t>& G;
      
      void init(graph_base<edge_t>& G, graph_base<edge_t>& T) 
      {
            typename graph_base<edge_t>::vertex_generator vg(G);
            while (! vg.iter_done() ) {
                  auto node = vg.yield(); 
                  trans(G, edge_t(node, node, 1), T); 
            }      
      }
     
      void trans(graph_base<edge_t>& G, edge_t e, graph_base<edge_t>&T) 
      {
            T.insert(e);
            auto v = e.from;
            auto w = e.to;
            typename graph_base<edge_t>::adjacency_generator ag(G, w);                        
            while (! ag.iter_done() ) {
                  auto t = ag.yield();
                  edge_t ne(v, t, 1);
                  if (! T.has_edge(ne)) {
                        trans(G, ne, T);
                  }
            }
      }
};

template <typename edge_t> 
struct tc_warshall {
public:
      explicit tc_warshall(graph_base<edge_t>& G) : G(G){}
      explicit tc_warshall (graph_base<edge_t>& G, graph_base<edge_t>& T) : G(G){
            init(G,T);
      }
      void operator()(graph_base<edge_t>& T) {
            init(G, T);
      }
private:
     graph_base<edge_t>& G;
      void init (graph_base<edge_t>& G, graph_base<edge_t>& T) 
      {
            for (typename graph_base<edge_t>::iterator it = G.begin(); it != G.end(); it++)
            {
                  T.insert(*it);
            }
            typename graph_base<edge_t>::vertex_generator vg(T);
            while (! vg.iter_done() ) {
                  auto n = vg.yield(); 
                  auto e = edge_t(n, n, 1);
                  if (! T.has_edge(e)) {
                        T.insert(e);
                  }
            }
            typename graph_base<edge_t>::vertex_generator vg1(T);
            while (! vg1.iter_done()) {
                  auto i = vg1.yield();
                  typename graph_base<edge_t>::vertex_generator vg2(T);
                  while (!vg2.iter_done()) {
                        auto s = vg2.yield();
                        if (T.has_edge(edge_t (s, i, 1))) {
                              typename graph_base<edge_t>::vertex_generator vg3(T); 
                              while (!vg3.iter_done()) {
                                    auto t = vg3.yield();
                                    if (T.has_edge(edge_t(i, t, 1))) {
                                          edge_t ne(s,t,1);
                                          if (! T.has_edge(ne)) {
                                                T.insert(ne);
                                          }
                                    }
                              }
                        }
                  }
                  
            }
    }
};

//-------

template <typename edge_t>
struct tc_dag {
public:
      explicit tc_dag(graph_base<edge_t>& G) : G(G){}
      explicit tc_dag (graph_base<edge_t>& G, graph_base<edge_t>& T) : G(G), T(T){
            init();
      }
      void operator()(graph_base<edge_t>& T) {
            init();
      }
private:
      graph_base<edge_t>& G;
      graph_base<edge_t>& T;
      typedef std::map<typename edge_t::label_value_type, size_t> cont_t;
      cont_t pre;
      size_t cnt = 0;
      bool visited (typename edge_t::label_value_type val) const
      {
            return (pre.find(val) != pre.end());
      }
      void init ()
      {
            typename graph_base<edge_t>::vertex_generator v(G);
            while (! v.iter_done()) {
                  auto val = v.yield();
                  if (!visited(val)) {
                        tcr (val);
                  }
            }
      }

      void tcr (typename edge_t::label_value_type w)
      {
            pre[w] = cnt++;
            typename graph_base<edge_t>::adjacency_generator adj(G, w);
            while (! adj.iter_done()) {
                  auto t = adj.yield();
                  // edge t is reachable from w
                  T.insert(edge_t(w, t, 1));
                  if (visited(t) && (pre[t] > pre[w])) continue; // ignore back and cross edges
                  if (!visited(t)) tcr(t);
                  typename  graph_base<edge_t>::vertex_generator vit(T);
                  while (!vit.iter_done()) {
                        auto i = vit.yield();
                        if (T.has_edge(edge_t(t,i, 1)) && ! T.has_edge(edge_t(w,i,1))) T.insert(edge_t(w,i,1));
                  }
                  
            }
      }
};

template<typename edge_t>
struct tc_kernel_dag {

      explicit tc_kernel_dag(graph_base<edge_t>& G) : G(G){
            init(G);
      }
      
      bool operator()(const edge_t& edge) const {
            return kernel_tc->has_edge(edge_t(sc->id(edge.from), sc->id(edge.to), 1));
      }
      
      std::ostream& pp(std::ostream& strm)
      {
            sc->pp(strm);
            strm << std::endl;
            return strm;
      }

private :
      typedef std::unique_ptr<strong_components<edge_t>> sc_ptr_t;
      typedef std::unique_ptr<graph_impl<adjacency_matrix_t, edge_t>> dg_ptr_t;
      graph_base<edge_t>& G;
      sc_ptr_t sc;
      dg_ptr_t kernel_tc;
      void init (graph_base<edge_t>& G)
      {
            sc.reset(new strong_components<edge_t>(G));
            graph_impl<adjacency_matrix_t, edge_t> kernel(G.V(),direction(G));
            typename graph_base<edge_t>::vertex_generator vg(G);
            while (! vg.iter_done()) {
                  auto f = vg.yield();
                  typename graph_base<edge_t>::adjacency_generator adj(G, f);
                  while (!adj.iter_done()) {
                        auto t = adj.yield();
                        kernel.insert(edge_t(sc->id(f),sc->id(t),1));
                  }
            }
            kernel_tc.reset(new graph_impl<adjacency_matrix_t, edge_t>(kernel.V(), direction(kernel)));
            is_dag<edge_t> is_dag(kernel);            
            tc_warshall<edge_t> dag_tc(kernel, *kernel_tc);
      }
};

//provides a way to get at the transitive closure;
//captures the tc and provides a type for it (type wrapper)
template <typename graph_t, typename algo_t=tc_dfs<typename graph_t::edge_value_type>>
class transitive_closure {

public:
      
      transitive_closure(graph_base<typename graph_t::edge_value_type>& G) : T(G.V(), direction(G)), algo(G,T) {}
                 
      bool operator()(const typename graph_t::edge_value_type& e) const {
            return T.has_edge(e);  
      }

      graph_t& operator*() {
            return T;
      }
      
private:
      
      graph_t  T;
      algo_t   algo;
};


#endif
