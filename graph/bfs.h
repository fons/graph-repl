//
//  bfs.h
//  graph-repl
//
//  Created by Alfons Haffmans on 6/25/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_bfs_h
#define graph_repl_bfs_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <deque>
#include <set>


#include "graph-property.h"
#include "search_base.h"

template<typename edge_t, typename traits=edge_trait_t<edge_t> >
class bfs : public search_base<edge_t> 
{    
      
public:
      bfs(graph_base<edge_t>& G) : search_base<edge_t>(G){}
      void operator()() {
            search_base<edge_t>::search();
      }
      
      static std::ostream& graphviz (std::ostream& strm, bfs<edge_t, traits>& g);
      void graphviz (const std::string& fn) {
            with_open_file(fn, graphviz);
      }
      
      
private:
      int cnt = 0;
      typedef typename traits::weight_value_type weight_t_t;
      typedef typename weight_traits_t<weight_t_t>::value_type weight_t;
      
      virtual void search_c(edge_t e,  typename search_base<edge_t>::color_t c)
      {
            weight_t_t sw = weight_traits_t<weight_t_t>::make_weight(1);
            
            std::deque<edge_t> que;
            que.push_back(e);
            search_base<edge_t>::order[traits::to(e)] = cnt++;
            while (! que.empty()) {
                  e    = que.front();
                  que.pop_front();
                  auto v = traits::from(e);
                  search_base<edge_t>::parent_link[traits::to(e)]        = traits::from(e);
                  //search_base<edge_t>::component[e.to] = search_base<edge_t>::comp_count;
                  search_base<edge_t>::low[traits::to(e)]       = search_base<edge_t>::order.at(traits::to(e));
                  search_base<edge_t>::color[traits::to(e)]     = search_base<edge_t>::flip_color(c);
                  c = search_base<edge_t>::flip_color(c);
                  typename graph_base<edge_t>::adjacency_generator s(search_base<edge_t>::G, traits::to(e));
                  while (! s.iter_done() ) {
                        auto t = s.yield();
                        if (search_base<edge_t>::order.at(t) == search_base<edge_t>::SENTINEL){
                              que.push_back(traits::make_edge(traits::to(e), t, sw));
                              search_base<edge_t>::order[t] = cnt++;
                              search_base<edge_t>::low[t]       = search_base<edge_t>::order.at(t);
                              search_base<edge_t>::color[t]     = search_base<edge_t>::flip_color(c);
                              if (search_base<edge_t>::low.at(traits::to(e)) > search_base<edge_t>::low.at(t)) {
                                    search_base<edge_t>::low[traits::to(e)] = search_base<edge_t>::low.at(t);
                              }
                              if (search_base<edge_t>::low.at(t) == search_base<edge_t>::order.at(t)) {
                                    search_base<edge_t>::bridge_count++;
                                    search_base<edge_t>::add_edge(search_base<edge_t>::bridges,
                                                                  traits::make_edge(traits::to(e),t, sw));
                              }
                              if (search_base<edge_t>::low.at(t) >= search_base<edge_t>::order.at(traits::to(e))) {
                                    search_base<edge_t>::articulation_count++;
                                    search_base<edge_t>::add_vertex(search_base<edge_t>::artics, traits::to(e));
                              }
                        }
                        else {
                              if (search_base<edge_t>::color.at(t) != c) {                             
                                    search_base<edge_t>::not_bipartite();
                              }
                              if (t != v) {                              
                                    if (search_base<edge_t>::low.at(traits::to(e)) > search_base<edge_t>::low.at(t)) {
                                          search_base<edge_t>::low[traits::to(e)] = search_base<edge_t>::low.at(t);
                                    }
                              }
                              else {
                                    //detected a cycle
                                    search_base<edge_t>::cycle_count++;
                              }
                        }
                        
                  }
            }// while que not empty
            
      }
      
      typedef std::ostream& (*Func)(std::ostream& , bfs<edge_t>&);
      struct close_file {
            void operator()(std::ofstream* strm) {                  
                  if (strm && strm->good()) {
                        strm->close();
                  }
            }
      };
      
      void with_open_file(const std::string& fn, Func F) {
            std::unique_ptr<std::ofstream, close_file> ofile (new std::ofstream(fn));
            if (! ofile->good() ) {
                  return;
            }
            F(*ofile, *this);            
      }
      
      
};


template <typename edge_t, typename traits>
std::ostream& bfs<edge_t, traits>::graphviz (std::ostream& strm, bfs<edge_t, traits>& g)
{
//      std::set<edge_t, edge_compare<edge_t>> vis;
//      strm << "graph BFS { " ;
//      for (auto it : g.st) {
//            if (it.first != it.second) {
//                  strm << "n" << it.second << " -- n" << it.first << std::endl;
//            }
//      }
//      
//      for (typename graph_base<edge_t>::iterator it = g.G.begin(); it != g.G.end(); it++) {
//            auto pos = g.st.find((*it).from); 
//            
//            if (pos != g.st.end() && g.st[(*it).from] == (*it).to) {
//                  continue;
//            }
//            pos = g.st.find((*it).to); 
//            if (pos != g.st.end() && g.st[(*it).to] == (*it).from) {
//                  continue;
//            }
//            if (! g.G.is_directed()) {
//                  if (vis.find (*it) == vis.end() ) {
//                        vis.insert(edge_t((*it).to, (*it).from, (*it).weight));
//                        strm << "nk"<< (*it).from <<"[shape=box,style=filled];" << std::endl;
//                        strm << "n" << (*it).to << " -- nk" << (*it).from << "[style=dotted,color=red];"<< std::endl;             
//                  }
//            }
//            else {
//                  strm << "n" << (*it).to << " -- nk" << (*it).from << std::endl; 
//            }
//      }
      strm << "}";
      return strm;
}


#endif
