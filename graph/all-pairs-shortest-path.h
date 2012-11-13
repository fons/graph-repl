//
//  all-pairs-shortest-path.h
//  graph-repl
//
//  Created by alfons haffmans on 10/20/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_all_pairs_shortest_path_h
#define graph_repl_all_pairs_shortest_path_h

template <typename edge_t, typename traits=edge_trait_t<edge_t>>
struct all_pairs_shortest_path_dijkstra {
private:
      typedef graph_base<edge_t,traits>         graph_t;
      typedef typename traits::label_value_type label_t;
      typedef std::shared_ptr<single_source_shortest_path<edge_t>> s3p_ptr_t;
      typedef std::unordered_map<label_t, s3p_ptr_t> s3p_cont_t;
      typedef typename traits::weight_value_type weight_t;
public :
      all_pairs_shortest_path_dijkstra(graph_base<edge_t, traits>& G) 
      {
            init(G);
      }
      
      std::pair<weight_t, bool> dist(const label_t& from, const label_t& to) {
            return s3p[from]->dist(to);
      }

      std::pair<label_t, bool> pred(const label_t& from, const label_t& to) {
            return s3p[from]->pred(to);
      }

private :
      //graph_base<edge_t, traits>& G;
      s3p_cont_t s3p;
      void init(graph_base<edge_t, traits>& G)
      {
            typename graph_t::vertex_generator vg(G);
            while (!vg.iter_done()) {
                  auto v = vg.yield();
                  s3p[v] = s3p_ptr_t(new single_source_shortest_path<edge_t>(G, v));
            }
      }
};

template <typename edge_t, typename traits=edge_trait_t<edge_t>>
struct all_pairs_shortest_path_floyd_warshall {
private:
      typedef graph_base<edge_t,traits>                   graph_t;
      typedef typename traits::label_value_type           label_t;
      typedef typename traits::weight_value_type          weight_t;
      typedef typename std::pair<label_t, label_t>        label_pair_t;

public :
      all_pairs_shortest_path_floyd_warshall(graph_base<edge_t, traits>& G) : G(G)
      {
            init(G);
      }
      
      std::pair<weight_t, bool> dist(const label_t& from, const label_t& to) {
            auto it = mdist.find(key(from,to));
            if (it == mdist.end()) return std::make_pair(weight_t(), false);
            return std::make_pair(it->second, true);
      }
      
      std::pair<label_t, bool> pred(const label_t& from, const label_t& to) {
            auto it = mpred.find(key(from,to));
            if (it == mpred.end()) return std::make_pair(label_t(), false);
            return std::make_pair(it->second, true);
      }
      
      std::ostream& pp(std::ostream& strm)
      {
            pp_h(strm, mdist);
            strm << std::endl << "---------------------------------------" << std::endl;
            pp_h(strm, mpred);
            
            return strm;
      }
private :
      graph_t& G;
      std::map<label_pair_t, weight_t>  mdist;
      std::map<label_pair_t, label_t>   mpred;

      template <typename T>
      std::ostream& pp_h(std::ostream& strm, const T& cont)
      {
            const size_t MAX = 15;
            size_t cnt = MAX;
            strm << "    ";
            std::set<label_t> vs;
            
            typename graph_t::vertex_generator vg(G);
            while (! vg.iter_done() && --cnt > 0) {
                  vs.insert(vg.yield());
            }
            for (auto& v : vs ) {
                  column(strm, v, 5);
                  strm << "," ;
            }
            strm << std::endl;
            
            for (auto& u : vs) {
                  strm << u << " : ";
                  for (auto& v : vs) {
                        if (cont.find(key(u,v)) != cont.end()) {
                              column(strm , cont.at(key(u,v)), 5);
                        }
                        else {
                              column(strm , " * ", 5) ;
                        }
                        strm <<  ",";
                  }
                  strm << std::endl;
            }
            return strm;
      }
      
      label_pair_t key(const label_t& f, const label_t& t )
      {
            return std::make_pair(f,t);
      }
      
      void init(graph_base<edge_t, traits>& G)
      {
            std::set<label_t> vs;
            
            typename graph_t::vertex_generator vg(G);
            while (! vg.iter_done()) {
                  vs.insert(vg.yield());
            }
            
            for (auto& u : vs) {
                  mdist[key(u,u)] = 0;
                  typename graph_t::adjacency_generator ag(G, u);
                  while (! ag.iter_done()) {
                        auto v = ag.yield();
                        auto e = G.edge(u, v);
                        if (traits::weight(e) == weight_t()) continue;
                        mdist[key(u,v)] = traits::weight(e);
                        mpred[key(u,v)] = u;
                  }
            }
            for (auto& t : vs) {
                  for (auto& u : vs) {
                        for (auto& v : vs) {
                              if (mdist.find(key(u,t)) == mdist.end()) continue;
                              if (mdist.find(key(t,v)) == mdist.end()) continue;
                              auto newlen = mdist.at(key(u,t)) + mdist.at(key(t,v));
                              if ((mdist.find(key(u,v)) == mdist.end()) || newlen < mdist.at(key(u,v))) {
                                    mdist[key(u,v)] = newlen;
                                    mpred[key(u,v)] = mpred[key(t,v)];
                              }
                        }
                  }
            }
      }
};
template <typename edge_t, typename algo_t=all_pairs_shortest_path_dijkstra<edge_t, edge_trait_t<edge_t>>, typename traits=edge_trait_t<edge_t>>
struct all_pairs_shortest_path
{
private :
      typedef typename traits::label_value_type           label_t;
      typedef typename traits::weight_value_type          weight_t;
 
public:
      all_pairs_shortest_path(graph_base<edge_t, traits>& G) : algo(G) {}

      std::pair<weight_t, bool> dist(const label_t& from, const label_t& to)
      {
            return algo.dist(from, to);
      }
      std::pair<label_t, bool> pred(const label_t& from, const label_t& to) {
            return algo.pred(from, to);
      }
      
      std::ostream& pp(std::ostream& strm)
      {
            return algo.pp(strm);
      }
      
      
private:
      algo_t algo;
};
#endif
