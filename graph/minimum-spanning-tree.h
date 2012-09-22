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
      
      mst_prim (graph_base<edge_t, traits>& G) :G(G) {
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
      
      typedef typename std::map<typename traits::label_value_type, edge_t> edge_cont_t;
      typedef typename std::map<typename traits::label_value_type, double> value_cont_t;
      typedef typename traits::label_value_type                            label_t;      
      //edge_cont_t mst;
      graph_base<edge_t, traits>& G;
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

#endif
