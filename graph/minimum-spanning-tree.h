//
//  minimum-spanning-tree.h
//  graph-repl
//
//  Created by alfons haffmans on 9/17/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_minimum_spanning_tree_h
#define graph_repl_minimum_spanning_tree_h


template <typename edge_t, typename traits=edge_trait_t<edge_t>>
struct mst_prim {
      
      explicit mst_prim (graph_base<edge_t, traits>& G)  {
            init(G);
      }

      std::ostream& pp(std::ostream& strm) {
            for (auto& val : mst) {
                  strm << val << std::endl;
            }
                  
            return strm;
      }
      
      graph_base<edge_t>& operator()(graph_base<edge_t>& T) {
            for (auto& e : mst) {
                  T.insert(e);
            }
            return T;
      }
      
      std::vector<edge_t> operator()() {
            return mst;
      }
private:
      
      typedef typename std::unordered_map<typename traits::label_value_type, edge_t> edge_cont_t;
      typedef typename std::unordered_map<typename traits::label_value_type, double> value_cont_t;
      typedef typename traits::label_value_type                            label_t;      
      
      std::vector<edge_t> mst;
      struct state {
            state() {}
            
            bool mst(const label_t& l, const edge_t& e) {
                  if (traits::weight(e) == 0) return false;
                  return push(mst_c, l, e);
            }
            
            std::pair<bool, edge_t> mst (label_t l) {
                  auto v = peek(mst_c, l);
                  if (traits::weight(v.second) == 0) return std::make_pair(false, edge_t(0,0,0));
                  return v;
            }
            
            bool fringe(const label_t& l, const edge_t& e) {
                  return push(fr, l, e);
            }
            
            std::pair<bool,edge_t> fringe(const label_t& l) {
                  auto v = peek(fr, l);
                  if (traits::weight(v.second) == 0) return std::make_pair(false, edge_t(0,0,0));
                  return v;
            }
            
            
            bool weight (const label_t& l, double w) {
                  return push(wt, l, w);
            }
            
            std::pair<bool, double> weight (const label_t&l ) {
                  auto v = peek(wt, l);
                  if (v.second == 0) return std::make_pair(false, 0);
                  return v;
            }

            bool fringe_to_mst (const label_t& l) {
                  auto v = fringe(l);
                  if (! v.first) return false;
                  return mst(l, v.second);
            }

            std::vector<edge_t>& mst(graph_base<edge_t>&G, std::vector<edge_t>& v_mst) {
                  typename graph_base<edge_t>::vertex_generator vg(G);
                  while (!vg.iter_done()) {
                        auto v = vg.yield();
                        //strm << v << ":";
                        auto e = mst_c[v];
                        //strm << e << std::endl;
                        if (traits::weight(e) == 0) continue;
                        v_mst.push_back(e);
                  }
                  return v_mst;
            }

            
            private :
            template<typename C, typename T>
            bool push (C& c, const label_t& w, const T& e)
            {
                 
                  c[w] = e;
                  return true;
            }
            template <typename C>
            std::pair<bool, typename C::mapped_type> peek(C& c, const label_t& l) {
                  auto it = c.find(l);
                  if (it != c.end()) {
                        return std::make_pair(true, it->second);
                  }
                  return std::make_pair(false, typename C::mapped_type());
            }
            
            edge_cont_t  mst_c;
            edge_cont_t  fr;
            value_cont_t wt;
      };
      
      template <typename T>
      bool valid(const std::pair<bool, T>& v) {
            return v.first;
      }
      
      template <typename T>
      T value(const std::pair<bool, T>& v) {
            return v.second;
      }

      
      void init(graph_base<edge_t, traits>& G)
      {
            state S;
            typename graph_base<edge_t>::vertex_generator vg(G);
            typename traits::label_value_type v;
            typename traits::label_value_type min;
            typename traits::label_value_type start = vg.yield();
            for (v = start; min !=start; v = min ) {
                  min = start;
                  typename graph_base<edge_t>::vertex_generator wg(G);
                  while (! wg.iter_done()) {
                        auto w = wg.yield();
                        if (w == start)      continue;
                        if (!valid(S.mst(w))) {
                              
                              edge_t e = G.edge(v,w);
                              //std::cerr << "processing " << e << std::endl;
                              if (traits::weight(e) != 0) {
                                    double P = traits::weight(e);
                                    auto wtw = S.weight(w);
                                    if ( !valid(wtw) || P < value(wtw)) {
                                          S.fringe(w, e);
                                          S.weight(w, P);
                                    }
                              }
                              if (min == start) {
                                    min = w;
                              }
                              auto wtmin = S.weight(min);
                              auto wtw   = S.weight(w);
                              if (valid(wtw) && valid(wtmin) && (value(wtw) < value(wtmin))) {
                                    min = w;
                              }
                        }
                  }//end of inner loop
                  if (min != start) {
                        S.fringe_to_mst(min);
                  }
                  
            }// end of outer loop
            mst = S.mst(G,mst);
      }// end of init
};


template <typename edge_t, typename traits=edge_trait_t<edge_t>>
struct mst_prim_pfs {
      
      explicit mst_prim_pfs (graph_base<edge_t, traits>& G) {
            init(G);
      }
      
      std::ostream& pp(std::ostream& strm) {
            for (auto& val : mst_e) {
                  strm << val << std::endl;
            }
            
            return strm;
      }
      
      graph_base<edge_t>& operator()(graph_base<edge_t>& T) {
            for (auto& e : mst_e) {
                  T.insert(e);
            }
            return T;
      }
      
      std::vector<edge_t> operator()() {
            return mst_e;
      }
private:
      
      typedef typename std::unordered_map<typename traits::label_value_type, edge_t> edge_cont_t;
      typedef typename std::unordered_map<typename traits::label_value_type, double> value_cont_t;
      typedef typename traits::label_value_type                            label_t;
      typedef typename traits::weight_value_type                           weight_t;

      
      std::vector<edge_t> mst_e;
      edge_cont_t  fr;
      edge_cont_t  mst_c;
      
      template<typename C, typename T>
      bool push (C& c, const label_t& w, const T& e)
      {
            c[w] = e;
            return true;
      }
      template <typename C>
      std::pair<bool, typename C::mapped_type> peek(C& c, const label_t& l) {
            auto it = c.find(l);
            if (it != c.end()) {
                  return std::make_pair(true, it->second);
            }
            return std::make_pair(false, typename C::mapped_type());
      }

      bool fringe(const label_t& l, const edge_t& e) {
            return push(fr, l, e);
      }
      std::pair<bool,edge_t> fringe(const label_t& l) {
            auto v = peek(fr, l);
            if (traits::weight(v.second) == 0) return std::make_pair(false, edge_t(0,0,0));
            return v;
      }

      bool fringe_to_mst (const label_t& l) {
            auto v = fringe(l);
            if (! v.first) return false;
            return mst(l, v.second);
      }
      bool mst(const label_t& l, const edge_t& e) {
            if (traits::weight(e) == 0) return false;
            return push(mst_c, l, e);
      }
      std::vector<edge_t>& mst(graph_base<edge_t>&G, std::vector<edge_t>& v_mst) {
            typename graph_base<edge_t>::vertex_generator vg(G);
            while (!vg.iter_done()) {
                  auto v = vg.yield();
                  auto e = mst_c[v];
                  if (traits::weight(e) == 0) continue;
                  v_mst.push_back(e);
            }
            return v_mst;
      }
      std::pair<bool, edge_t> mst (label_t l) {
            auto v = peek(mst_c, l);
            if (traits::weight(v.second) == 0) return std::make_pair(false, edge_t(0,0,0));
            return v;
      }
      
      template <typename T>
      bool valid(const std::pair<bool, T>& v) {
            return v.first;
      }
      
      template <typename T>
      T value(const std::pair<bool, T>& v) {
            return v.second;
      }
      
      void init(graph_base<edge_t, traits>& G)
      {
            typename graph_base<edge_t>::vertex_generator vg(G);
            while (!vg.iter_done()) {
                  auto v = vg.yield();
                  if (valid(mst(v))) continue;
                  pfs(G,v);
            }
            mst_e = mst(G,mst_e);
            
      }
      
      void pfs(graph_base<edge_t>& G, label_t start)
      {
            priority_queue_kv<label_t, weight_t> pq(G.V());
            pq.insert(start);
            pq.push_back(0);
            while (! pq.empty()) {
                  label_t v = pq.getmin();
                  fringe_to_mst(v);
                  typename graph_base<edge_t>::adjacency_edge_generator vg(G, v);
                  while (! vg.iter_done()) {
                        auto   e  = vg.yield();                        
                        label_t w = traits::to(e);
                        if (w == start) continue; //start is on the mst per definition
                        double P  = traits::weight(e);
                        auto wfr  = fringe(w);                        
                        if (!valid(wfr)) {
                              fringe(w, e);
                              //order of these two operations is important
                              pq.push_back(P);
                              pq.insert(w);
                        }
                        else if (!valid(mst(w)) && (P < pq[w])) {
                              pq[w] = P;
                              pq.lower(w);
                              fringe(w, e);
                        }
                  }
            }
      }// end of pfs
};

template <typename edge_t, typename traits=edge_trait_t<edge_t>>
struct mst_kruskal {
      
      explicit mst_kruskal (graph_base<edge_t, traits>& G) {
            init(G);
      }
      
      std::ostream& pp(std::ostream& strm) {
            for (auto& val : mst_e) {
                  strm << val << std::endl;
            }
            
            return strm;
      }
      
      graph_base<edge_t>& operator()(graph_base<edge_t>& T) {
            for (auto& e : mst_e) {
                  T.insert(e);
            }
            return T;
      }
      
      std::vector<edge_t> operator()() {
            return mst_e;
      }
private:
      template <bool asc = false>
      struct weight_order {
            weight_order () {}
            bool operator()(const edge_t& lhs, const edge_t& rhs) {
                  if (asc) {
                        return traits::weight(rhs) > traits::weight(lhs);
                  }
                  return traits::weight(rhs) < traits::weight(lhs);
            }
      private:
      };

      typedef std::vector<edge_t>                 edge_cont_t;
      typedef typename traits::label_value_type   label_t;
      typedef typename traits::weight_value_type  weight_t;
      edge_cont_t mst_e;      
      
      void init (graph_base<edge_t, traits>& G)
      {
            union_find_t<label_t> uf;
            std::priority_queue<simple_edge_t, std::vector<edge_t>, weight_order<>> pq;
            graph_base<simple_edge_t>::edge_generator E(G);
            while (! E.iter_done()) {
                  pq.push(E.yield());
            }
            while (! pq.empty() && mst_e.size() < G.V()) {
                  auto e = pq.top();
                  pq.pop();
                  if (! uf.connected(traits::from(e), traits::to(e))) {
                        uf(traits::from(e), traits::to(e));
                        mst_e.push_back(e);
                  }
            }
           
      }
};
#endif
