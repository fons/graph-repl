//
//  maxflow.h
//  graph-repl
//
//  Created by alfons haffmans on 11/26/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_maxflow_h
#define graph_repl_maxflow_h


template <typename graph_t>
struct find_path_noop
{
      typedef typename graph_t::label_value_type               label_t;
      typedef typename std::unordered_map<label_t, flow_edge>  edge_cont_t;
      find_path_noop (const graph_t& G,const label_t& s, const label_t& v) {}
      bool operator()(edge_cont_t& st){
            return false;
      }
};

template<typename graph_t>
struct augmenting_paths_dfs {
      
      typedef typename graph_t::label_value_type               label_t;
      typedef typename std::unordered_map<label_t, flow_edge>  edge_cont_t;
      typedef typename graph_t::weight_value_type              weight_t;
      typedef typename weight_traits_t<weight_t>::value_type   flow_t;
      typedef typename std::unordered_map<label_t, flow_t>     flow_cont_t;
      
      augmenting_paths_dfs(graph_t& G, const label_t& s, const label_t& t) : G(G), s(s), t(t) {}
      bool operator()(edge_cont_t& st)
      {
            priority_queue_stl<label_t, double> PQ;
            typename graph_t::vertex_generator wg(G);
            while (! wg.iter_done()) {
                  auto v = wg.yield();
                  wt[v]  = 0;
                  PQ.insert(v, wt[v]);
                  st[v] = flow_edge(); //basically a null ptr
            }
            
            wt[s] = -std::numeric_limits<flow_t>::max();
            PQ.update(s, wt[s]);
            while (! PQ.empty()) {
                  auto min = PQ.getmin();
                  label_t v = min.first;
                  wt[v]     = -std::numeric_limits<flow_t>::max();
                  if (v == t) break; //we're done
                  if ((v != s) && st[v].null()) break;
                  typename graph_t::adjacency_edge_generator vg(G, v);
                  while (! vg.iter_done()){
                        auto fe = flow_edge(vg.yield());
                        auto w = fe.other(v);
                        flow_t cap = fe.capRto(w);
                        flow_t P   = (cap < wt[v]) ? cap : -wt[v];
                        if (cap > 0 && -P < wt[w]) {
                              wt[w] = -P;
                              PQ.update(w, wt[w]);
                              st[w] = fe;
                        }
                  }
            }
            return (! st[t].null());
            
      }
      private :
      graph_t& G;
      label_t s;
      label_t t;
      flow_cont_t wt;
};


template <typename graph_t, typename find_path = augmenting_paths_dfs<graph_t>>
struct augmenting_paths_maxflow {
private :
      typedef typename graph_t::label_value_type  label_t;
      typedef typename graph_t::weight_value_type weight_t;
      
      typedef typename weight_traits_t<weight_t>::value_type flow_t;
      typedef typename std::unordered_map<label_t, flow_edge> edge_cont_t;
      
public :
      augmenting_paths_maxflow(graph_t& G, const label_t& s, const label_t& t) : s(s), t(t), G(G)
      {
            init();
      }
private :
      graph_t& G;
      label_t s;
      label_t t;
      edge_cont_t st;
      //flow_cont_t wt;
      label_t ST(const label_t& v) {
            return st[v].other(v);
      }
      void augment (const label_t& s, label_t& t)
      {
            flow_t d = st[t].capRto(t);
            for (label_t v = ST(t); v != s; v = ST(v)) {
                  if (st[v].capRto(v) < d) {
                        d = st[v].capRto(v);
                  }
            }
            st[t].addflowRto(t, d);
            for (label_t v = ST(t); v != s; v = ST(v)) {
                  st[v].addflowRto(v,d);
            }
      }
      void init ()
      {
            find_path A(G, s ,t);
            while (A(st)) augment(s, t);
      }
};

#endif
