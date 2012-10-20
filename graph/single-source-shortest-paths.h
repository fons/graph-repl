//
//  single-source-shortest-paths.h
//  graph-repl
//
//  Created by alfons haffmans on 10/8/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_single_source_shortest_paths_h
#define graph_repl_single_source_shortest_paths_h

template <typename edge_t, typename traits=edge_trait_t<edge_t>>
struct shortest_path_dijkstra_dense {
      
      explicit shortest_path_dijkstra_dense (graph_base<edge_t, traits>& G, const typename traits::label_value_type& v)  {
            init(G,v);
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
                  fr.erase(l);
                  return mst(l, v.second);
            }
            
            bool flush_fringe_to_mst()
            {
                  for (auto& el : fr) {
                        mst(el.first, el.second);
                  }
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
            
            
            //private :
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
      
      
      void init(graph_base<edge_t, traits>& G, const typename traits::label_value_type& start)
      {
            state S;
            
            typename traits::label_value_type v;
            typename traits::label_value_type min;
            
            for (v = start; min !=start; v = min ) {
                  std::cerr << "start processing : v = " << v << std::endl;
                  min = start;
                  typename graph_base<edge_t>::vertex_generator wg(G);
                  while (! wg.iter_done()) {
                        auto w = wg.yield();
                        if (w == start)      continue;                        
                        if (!valid(S.mst(w))) {
                              edge_t e = G.edge(v,w);
                              if (traits::weight(e) == 0) continue;
                              std::cerr << "w : " << w << "  processing " << e << std::endl;
                              if (traits::weight(e) != 0) {
                                    auto vwt = S.weight(v);
                                    double P = traits::weight(e);
                                    if (valid(vwt) ) {
                                          P += value(vwt);
                                    }
                                    auto wtw = S.weight(w);
                                    if (!valid(wtw) || P < value(wtw)) {
                                          std::cerr << "\t\tadding to fringe : " << e << std::endl;
                                          S.fringe(w, e);
                                          S.weight(w, P);
                                    }
                              }
                              if (min == start) {
                                    std::cerr << "\t\tassigning to min " << w << std::endl;
                                    min = w;
                              }
                              auto wtmin = S.weight(min);
                              auto wtw   = S.weight(w);
                              if (valid(wtw) && valid(wtmin) && (value(wtw) < value(wtmin))) {
                                    std::cerr << "\t\tsecond assigning to min " << w << std::endl;
                                    min = w;
                              }
                        }
                  }//end of inner loop
                  if (min != start) {
                        std::cerr << "move to mst : " << min << std::endl;
                        S.fringe_to_mst(min);
                  }
                  
            }// end of outer loop
            S.flush_fringe_to_mst();
//            for (auto& val : S.fr) {
//                  std::cerr << "fringe :" << val << std::endl;
//            }
            mst = S.mst(G,mst);
      }// end of init
};

template <typename edge_t, typename traits=edge_trait_t<edge_t>>
struct shortest_path_dijkstra_pq {
      private :
      
      typedef typename traits::label_value_type            label_t;
      typedef typename std::unordered_map<label_t, edge_t>  edge_cont_t;
      typedef typename std::unordered_map<label_t, label_t> label_cont_t;
      typedef typename std::unordered_map<label_t, double>  value_cont_t;

      public :
      explicit shortest_path_dijkstra_pq (graph_base<edge_t, edge_trait_t<edge_t>>& G, const label_t& v) : start(v), G(G) {
            init(G,v);
      }
      
      std::ostream& pp(std::ostream& strm) const {
            for (auto& v : dist_c) {
                  strm << v << std::endl;
            }
            for (auto& v : pred_c) {                  
                  auto w = G.edge(v.second, v.first);
                  if (traits::weight(w) != 0){
                        strm << "from "<< v.second << " to " << v.first << " edge :";
                        strm << " " << w << std::endl;
                  }
            }
            for (auto& val : dist_c) {
                  strm << start << " -> " << val.first << " : " << val.second << std::endl;
            }
            return strm;
      }
      
      typename std::pair<typename traits::weight_value_type, bool> dist(const label_t& v)
      {
            auto it = dist_c.find(v);
            if (it == dist_c.end()) return std::make_pair(typename traits::weight_value_type(), false);
            return std::make_pair(it->second, true);
      }
      
      std::pair<label_t,bool> pred(const label_t& v)
      {
            auto it = pred_c.find(v);
            if (it == pred_c.end()) return std::make_pair(label_t(), false);
            return std::make_pair(it->second, true);
      }
private:
      const label_t& start;
      graph_base<edge_t, traits>& G;
      value_cont_t dist_c;
      edge_cont_t  mst;
      label_cont_t pred_c;
      
      void init(graph_base<edge_t, traits>& G, const typename traits::label_value_type& start)
      {
            priority_queue_stl<label_t, double> PQ;
            typename graph_base<edge_t>::vertex_generator wg(G);
            while (! wg.iter_done()) {
                  auto v = wg.yield();
                  dist_c[v] = std::numeric_limits<double>::max();
                  PQ.insert(v, dist_c[v]);
                  pred_c[v] = v;
            }
            
            dist_c[start] = 0;
            PQ.update(start, dist_c[start]);
            while (! PQ.empty()) {
                  auto min = PQ.getmin();
                  label_t u = min.first;
                  typename graph_base<edge_t>::adjacency_edge_generator vg(G, u);
                  while (! vg.iter_done()){
                        auto e = vg.yield();
                        auto v = traits::to(e);
                        auto w = traits::weight(e);
                        auto newlen = dist_c[u] + w;
                        if (newlen < dist_c[v]) {
                              PQ.update(v, newlen);
                              dist_c[v] = newlen;
                              mst[v]  = e;
                              pred_c[v] = u;
                        }
                  }
            }
      }
};
template <typename edge_t, typename algo_t=shortest_path_dijkstra_pq<edge_t, edge_trait_t<edge_t>>, typename traits=edge_trait_t<edge_t>>
struct single_source_shortest_path
{
      typedef typename traits::label_value_type    label_t;
      typedef typename traits::weight_value_type   weight_t;
public :
      single_source_shortest_path(graph_base<edge_t, traits>& G, const typename traits::label_value_type& s) : G(G), algo(G,s) {}
      
      std::pair<weight_t, bool> dist(const label_t& v)
      {
            return algo.dist(v);
      }
      
      std::pair<label_t,bool> pred(const label_t& v)
      {
            return algo.pred(v);
      }
      
      graph_base<edge_t, traits>& operator()(graph_base<edge_t, traits>& T)
      {
            
            typename graph_base<edge_t>::vertex_generator wg(G);
            while (! wg.iter_done()) {
                  auto to   = wg.yield();
                  auto from = algo.pred(to);
                  if (!from.second) continue;
                  auto e    = G.edge(from.first, to);
                  if (traits::weight(e) == 0) continue;
                  T.insert(e);
              }
      
             return T;
      }

      std::ostream& pp(std::ostream& strm) const {
            return algo.pp(strm);
      }
      
private :
      graph_base<edge_t, traits>& G;
      algo_t algo;
};

template<typename edge_t>
std::ostream operator<<(std::ostream& strm, const single_source_shortest_path<edge_t>& t) {
      return t.pp(strm);
}

#endif
