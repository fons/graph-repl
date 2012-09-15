//
//  dfs.h
//  graph-repl
//
//  Created by Alfons Haffmans on 5/30/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_dfs_h
#define graph_repl_dfs_h
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>

#include "graph-property.h"
#include "search_base.h"

template<typename edge_t>
class dfs : public search_base<edge_t> 
{    
      
public:
      dfs(graph_base<edge_t>& G) : search_base<edge_t>(G){}
      void operator()() {
            search_base<edge_t>::search();
      }
      
      static std::ostream& graphviz (std::ostream& strm, dfs<edge_t>& g);
      void graphviz (const std::string& fn) {
            with_open_file(fn, graphviz);
      }
      
      
private:
      int cnt      = 0;
      int post_cnt = 0;
      
      virtual void search_c(edge_t e,  typename search_base<edge_t>::color_t c)
      {
            auto w = e.to;
            auto v = e.from;
            search_base<edge_t>::component[w]   = search_base<edge_t>::comp_count;
            
            search_base<edge_t>::order[w]       = cnt;
            search_base<edge_t>::preorder[w]    = cnt;
            cnt++;

            search_base<edge_t>::low[w]         = search_base<edge_t>::order.at(w);
            search_base<edge_t>::color[w]       = search_base<edge_t>::flip_color(c);
            search_base<edge_t>::parent_link[w] = v;

            typename graph_base<edge_t>::adjacency_generator s(search_base<edge_t>::G, w);                        
            while (! s.iter_done() ) {
                  auto t = s.yield();
                  
                  if (search_base<edge_t>::order.at(t) == search_base<edge_t>::SENTINEL){
                        
                        assert(search_base<edge_t>::preorder.at(t) == search_base<edge_t>::SENTINEL);
                        
                        //start recursion
                        search_c(edge_t(w, t, 1),  search_base<edge_t>::color.at(w));
                        
                        // recursion returns..
                        
                        if (search_base<edge_t>::low.at(w) > search_base<edge_t>::low.at(t)) {
                              search_base<edge_t>::low[w] = search_base<edge_t>::low.at(t); 
                        }
                        
                        if (search_base<edge_t>::low.at(t) == search_base<edge_t>::order.at(t)) {
                              search_base<edge_t>::bridge_count++;
                              search_base<edge_t>::add_edge(search_base<edge_t>::bridges, edge_t(w,t,1));
                        }
                        
                        if (search_base<edge_t>::low.at(t) >= search_base<edge_t>::order.at(w)) {
                              search_base<edge_t>::articulation_count++;
                              search_base<edge_t>::add_vertex(search_base<edge_t>::artics, w);
                        }
                  }
                  else {
                        if (search_base<edge_t>::color.at(t) != c) {                             
                              search_base<edge_t>::not_bipartite();
                        }
                        if (t != v) {                              
                              if (search_base<edge_t>::low.at(w) > search_base<edge_t>::low.at(t)) {
                                    search_base<edge_t>::low[w] = search_base<edge_t>::low.at(t); 
                              }
                        }
                        else {
                              //detected a cycle
                              search_base<edge_t>::cycle_count++;
                        }
                  }
                  
            }
            //done visting w's edges...
            search_base<edge_t>::postorder[w]    = post_cnt++;     
      }
      
      typedef std::ostream& (*Func)(std::ostream& , dfs<edge_t>&);
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


template <typename edge_t>
std::ostream& dfs<edge_t>::graphviz (std::ostream& strm, dfs<edge_t>& g)
{
      std::set<edge_t, edge_compare<edge_t>> vis;
      strm << "graph DFS { " ;
      //step through the parent->child links; this identifies the tree edges.
      for (auto it : g.parent_link) {
            if (it.first != it.second) {
                  strm << "n" << it.second << " -- n" << it.first << std::endl;
            }
      }
      //this section deals with the back /down etc links (i.e. links back to previously vistited nodes
      for (typename graph_base<edge_t>::iterator it = g.G.begin(); it != g.G.end(); it++) {

            //if this is an parent-child edge, ignore it as we processed those above
            if (! g.G.is_directed()) {
                  auto pos = g.parent_link.find((*it).from); 
                  if (pos != g.parent_link.end() && g.parent_link[(*it).from] == (*it).to) {
                        continue;
                  }
            }
            auto pos = g.parent_link.find((*it).to); 
            if (pos != g.parent_link.end() && g.parent_link[(*it).to] == (*it).from) {
                  continue;
            }
            
            //----------------------------------------------------------------------
            if (! g.G.is_directed()) {
                  if (vis.find (*it) == vis.end() ) {
                        vis.insert(edge_t((*it).to, (*it).from, (*it).weight));
                        strm << "nk"<< (*it).from <<"[shape=box,style=filled];" << std::endl;
                        strm << "n" << (*it).to << " -- nk" << (*it).from << "[style=dotted,color=red];"<< std::endl;             
                        
                  }
            }
            else {
                  
                  if ((*it).to != (*it).from) {
                        //ignore self loops
                        if (g.is_back_edge(*it)) {                              
                              strm << "_n"<< (*it).to <<"[shape=oval,style=filled];" << std::endl;  
                        }
                        
                        if (g.is_down_edge(*it)) {                             
                              strm << "_n"<< (*it).to <<"[shape=box,style=filled];" << std::endl;  
                        }
                        
                        if (g.is_cross_edge(*it)) {                             
                              strm << "_n"<< (*it).to <<"[shape=box];" << std::endl;  
                        }

                        strm << "n" << (*it).from << " -- _n" << (*it).to << std::endl;
                  }
            }
      }
      strm << "}";
      return strm;
}



 

#endif
