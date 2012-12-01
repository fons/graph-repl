//
//  preflow-push-maxflow.h
//  graph-repl
//
//  Created by alfons haffmans on 11/29/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_preflow_push_maxflow_h
#define graph_repl_preflow_push_maxflow_h


template <typename graph_t>
struct init_preflow_height
{
      typedef typename graph_t::edge_value_type          edge_t;
      typedef typename graph_t::label_value_type         label_t;
      typedef typename std::unordered_map<label_t, long> cont_t;
      
      init_preflow_height(graph_t& G, const label_t& s, const label_t& t) : G(G), source(s), sink(t){}
      
      init_preflow_height(const init_preflow_height& o) : G(o.G), source(o.source), sink(o.sink){}
      
      const init_preflow_height& operator=(const init_preflow_height& o) {
            if (this != &o){
                  G=o.G;
                  source =o.source;
                  sink   =o.sink;
            }
            return *this;
      }
      
      cont_t& operator()(cont_t& c) {
            bfs<typename graph_t::edge_value_type> bfs(G);
            bfs();
            typename graph_t::vertex_generator vg(G);
            while (! vg.iter_done()) {
                  auto u  = vg.yield();
                  c[u]    = 0;
                  auto p  = u;
                  size_t count = G.V() + 2;
                  while (p != source) {
                        p = property<typename graph_t::edge_value_type, parent_t>(bfs, p);
                        c[u]++;
                        if (count-- == 0) break;
                  }
            }
            // renormalize b/c we start from source above..
            auto M = c[sink];
            for (auto& v : c) {
                  v.second = M - v.second;
            }
            return c;
      }
      bool check(cont_t& c) {
            if (c[sink] != 0) return false;
            if (c[source] > G.V()) return false;
            for (typename graph_t::iterator it = G.begin(); it != G.end(); it++) {
                  auto e = *it;
                  auto f = edge_trait_t<edge_t>::from(e);
                  auto t = edge_trait_t<edge_t>::to(e);
                  if (c[t] > c[f] + 1) return false;
            }
            return true;
      }
private:
      graph_t& G;
      const label_t& source;
      const label_t& sink;
};

template <typename graph_t, typename queue_t = queue_t<typename graph_t::label_value_type>, typename init_heights_t = init_preflow_height<graph_t>>
struct preflow_push_maxflow {
      
      private :
      typedef typename graph_t::label_value_type  label_t;
      typedef typename graph_t::weight_value_type weight_t;
      
      typedef typename weight_traits_t<weight_t>::value_type flow_t;
      typedef typename std::unordered_map<label_t, flow_edge> edge_cont_t;
      typedef typename std::unordered_map<label_t, flow_t>    flow_cont_t;
      typedef typename std::unordered_map<label_t, long>      height_cont_t;
      
      public :
      preflow_push_maxflow(graph_t& G, const label_t& s, const label_t& t) : s(s), t(t), G(G)
      {
            init();
      }
      private :
      graph_t& G;
      label_t s;
      label_t t;
      edge_cont_t st;
      height_cont_t h;
      flow_cont_t wt;
      
      void init_heights (flow_cont_t& h) {
            init_heights_t ih(G,s,t);
            ih(h);
      }
      
      void init ()
      {
            init_heights(h);
            queue_t Q;
            Q.put(s);
            wt[s] = G.V()*3;
            wt[t] = -wt[s];
            while (! Q.empty()) {
                  label_t v = Q.get();
                  typename graph_t::adjacency_edge_generator vg(G, v);
                  while (! vg.iter_done()){
                        auto fe = flow_edge(vg.yield());
                        label_t w  = fe.other(v);
                        flow_t cap = fe.capRto(w);
                        flow_t P   = (cap < wt[v]) ? cap : wt[v];
                        if (P > 0 && (v ==s || h[v] == h[w] + 1)) {
                              fe.addflowRto(w, P);
                              wt[v] = wt[v] - P;
                              wt[w] = wt[w] + P;
                              if ((w !=s) && (w != t)) {
                                    Q.put(w);
                              }
                        }
                  }
                  if ((v !=s) && (v != t) && (wt[v] > 0)) {
                        h[v]++;
                        Q.put(v);
                  }
                  
            }
      }
};


#endif
