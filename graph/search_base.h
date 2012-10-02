//
//  search_base.h
//  graph-repl
//
//  Created by Alfons Haffmans on 6/4/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_search_base_h
#define graph_repl_search_base_h

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <set>
#include <map>

#include <assert.h>

#include "graph-property.h"
#include "graph_impl.h"

template <typename edge_t>
class search_base {
protected:
      typedef int                               color_t;    
      typedef typename edge_t::label_value_type value_t;
      
      typedef std::unordered_map<value_t, int>       cont_t;
      typedef std::unordered_map<value_t, value_t>   link_t;
      typedef std::unordered_map<value_t, color_t>   color_cont_t;
      typedef std::set<edge_t>             edge_cont_t;
      typedef std::set<value_t>            vertex_cont_t;

   
      const int      SENTINEL = -1;
      const color_t  RCOLOR   = 0;

      template <typename T> struct type {
            
      };
      
public :
      template <typename edge_t_, typename property_t, typename retval_t>
      friend retval_t property(search_base<edge_t_>& , typename edge_t_::label_value_type n);
      
      search_base(graph_base<edge_t>& G) : G(G)
      {
            cont_init(order,       G, SENTINEL);
            cont_init(preorder,   G, SENTINEL);
            cont_init(postorder,  G, SENTINEL);
            cont_init(parent_link, G, 0);
      }       
      
      //virtual std::ostream& pretty_print(std::ostream& strm) = 0;
      std::ostream& pretty_print(std::ostream& strm) {
            strm << std::setw(4);
            strm << "key  :" << std::setw(8) << "  ord     :  low     :  parent  : component" ;
            strm << ": preorder :  post order "<< std::endl;
            for (auto it : parent_link) {
                  strm << std::setw(4) << it.first;  
                  if (exists(order, it.first)){
                        strm << " : " << std::setw(8) << order.at(it.first);
                  }
                  else {
                        strm << " : " << std::setw(7) << "?";
                  }
                  if (exists(low, it.first)) {
                        strm << " : " << std::setw(8) << low.at(it.first);
                  }
                  else {
                        strm << " : " << std::setw(7) << "?";
                  }
                  strm << " : " << std::setw(8) << it.second;

                  if (exists(component, it.first)) {
                        strm << " : " << std::setw(8) << component.at(it.first);
                  }
                  else {
                        strm << " : " << std::setw(7) << "?";
                  }
                  
                  if (exists (preorder, it.first)) {
                        strm << " : " << std::setw(8) << preorder.at(it.first);
                  }
                  else {
                        strm << " : " << std::setw(7) << "?";
                  }
                  
                  if (exists (postorder, it.first)) {
                        strm << " : " << std::setw(8) << postorder.at(it.first);
                  }
                  else {
                        strm << " : " << std::setw(7) << "?";
                  }

                  strm << std::endl;                  
            }
            return strm;
      }
      
      template<typename prop_t=graph_property_t>
      typename prop_t::retval property(typename edge_t::label_value_type node) {            
            return get_val(type<prop_t>(), node);
      }
      
      template<typename prop_t=graph_property_t>
      typename prop_t::retval property(const edge_t& e) {            
            return get_val(type<prop_t>(), e);
      }
      template<typename prop_t=graph_property_t>
      typename prop_t::retval property() {            
            return get_val(type<prop_t>());
      }
      
      bool is_tree_edge(const edge_t& edge) {
            auto pos = parent_link.find(edge.to);
            if (G.has_edge(edge) && (pos != parent_link.end()) && (parent_link[edge.to] == edge.from)) {
                  return true;
            }
            return false;
      }
      
      bool is_back_edge(const edge_t& edge) {
            return (G.has_edge(edge) && (!is_tree_edge(edge)) &&
                    (preorder.at(edge.from) > preorder.at(edge.to)) && (postorder.at(edge.from) < postorder.at(edge.to)));
      }
      
      bool is_down_edge(const edge_t& edge) {            
            return (G.has_edge(edge) && (!is_tree_edge(edge)) &&
                   (preorder.at(edge.from) < preorder.at(edge.to)) && (postorder.at(edge.from) > postorder.at(edge.to)));
      }
      
      bool is_cross_edge(const edge_t& edge) {
            return (G.has_edge(edge) && (!is_tree_edge(edge)) &&
                    (preorder.at(edge.from) > preorder.at(edge.to)) && (postorder.at(edge.from) > postorder.at(edge.to)));
      }
      int post_order(const value_t& v)
      {
            if (postorder.find(v) == postorder.end()) {
                  return -1;
            }
            return postorder[v];
      }
protected:
      
      // DATA SECTION
      
      link_t              parent_link; // holds parent links;
      
      graph_base<edge_t>& G;
      
      cont_t              order;
      cont_t              low;
      cont_t              component;
      cont_t              preorder;
      cont_t              postorder;
      
      color_cont_t        color;
      edge_cont_t         bridges;
      vertex_cont_t       artics;
      
      bool                bipartite           = true;

      int                 comp_count          = 0;
      int                 bridge_count        = 0;
      int                 cycle_count         = 0;
      int                 articulation_count  = 0;

      // STATIC METHOD SECTION
      
      static bool exists(cont_t& cont, const size_t el) {
            return cont.find(el) != cont.end();
      }
                            
      static edge_cont_t& add_edge(edge_cont_t& edge_cont, const edge_t& e) {
            edge_cont.insert(e);
            return edge_cont;
      }
      
      static vertex_cont_t& add_vertex(vertex_cont_t& vertex_cont, const value_t& v) {
            vertex_cont.insert(v);
            return vertex_cont;
      }
      
      static color_t flip_color(const color_t& c) {            
            return (c + 1) % 2;
      }
      
            
      virtual void search_c(edge_t edge, color_t color) = 0;
      
      virtual void search () {
            typename graph_base<edge_t>::vertex_generator s(G);            
            while (! s.iter_done() ) {
                  auto node = s.yield();
                  if (order.at(node) == SENTINEL) {  
                        assert (preorder.at(node) == SENTINEL);      
                        search_c(edge_t(node, node, 1), RCOLOR);
                        comp_count++;
                  }
            }
            
      }

      template<typename cont_t>
      static cont_t& cont_init(cont_t& cont , graph_base<edge_t>& G, const typename cont_t::mapped_type& sentinel)
      {
            typename graph_base<edge_t>::vertex_generator s(G);
            while (! s.iter_done() ) {
                  auto key  = s.yield();
                  cont[key] = sentinel;
            }
            return cont;
      }

      void not_bipartite() {
            bipartite = false;
      }

      
      component_t::retval get_val(const type<component_t>& t, typename edge_t::label_value_type node) {
            return search_base<edge_t>::component.at(node);
      }
      
      component_t::retval get_val(const type<component_t>& t) {
            return search_base<edge_t>::comp_count;
      }
      
      preorder_t::retval get_val(const type<preorder_t>& t, typename edge_t::label_value_type node) {
            return search_base<edge_t>::preorder.at(node);
      }
      
      postorder_t::retval get_val(const type<postorder_t>& t, typename edge_t::label_value_type node) {
            return search_base<edge_t>::postorder.at(node);
      }
      
      void get_val(const type<graph_property_t>& val, typename edge_t::label_value_type node) {
            return ;
      }
      
      void get_val(const type<graph_property_t>& val) {
            return ;
      }
      
      bridge_t::retval get_val(const type<bridge_t>& t) {
            return static_cast<bridge_t::retval>(search_base<edge_t>::bridges.size());
      }
      
      articulation_t::retval get_val(const type<articulation_t>& t) {
            return static_cast<articulation_t::retval>(search_base<edge_t>::artics.size());
      }
      
      cycle_t::retval get_val(const type<cycle_t>& t) {
            return search_base<edge_t>::cycle_count;
      }      
      
      typename bridges_t<edge_t>::retval get_val(const type<bridges_t<edge_t>>& t) {
            return search_base<edge_t>::bridges;
      } 
      
      typename artics_t<edge_t>::retval get_val(const type<artics_t<edge_t>>& t) {
            return search_base<edge_t>::artics;
      } 
      
      typename bipartite_t::retval get_val(const type<bipartite_t>& t) {
            return search_base<edge_t>::bipartite;
      }
 
      parent_t::retval get_val(const type<parent_t>& t, typename edge_t::label_value_type node) {
            return parent_link.at(node);
      }
      
    
};

template<typename edge_t>
std::ostream& operator<< (std::ostream &strm, search_base<edge_t>& g)
{
      return g.pretty_print(strm);      
}


template<typename edge_t, typename property_t, typename retval_t= typename property_t::retval>
retval_t property (search_base<edge_t>& g, typename edge_t::label_value_type node)
{
      return g.get_val(typename search_base<edge_t>::template type<property_t>(), node);
}

template<typename edge_t, typename property_t>
typename property_t::retval property (search_base<edge_t>& g)
{
      return typename property_t::retval();
}

#endif
