//
//  graph_impl.h
//  graph-repl
//
//  Created by Alfons Haffmans on 4/16/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_graph_impl_h
#define graph_repl_graph_impl_h

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

#include "graph-type.h"
#include "graph_base.h"


template <typename container_t, typename edge_t> 
class graph_impl : public graph_base <edge_t> {
public:
      explicit graph_impl(size_t size) : m(size), is_directed_flg(graph_type_t::UNDIRECTED){}
      explicit graph_impl(size_t size, graph_type_t is_directed) : m(size), is_directed_flg(is_directed){}

      graph_impl(graph_impl&& obj) : m(std::move(obj.m)), ecnt(obj.ecnt){}
      static graph_impl deserialize(std::istream& s);
      static graph_impl deserialize(const std::string & fn) {
            std::ifstream ifile (fn);
            if (! ifile.good()) {
                  return graph_impl(0);
            }
            graph_impl s = graph_impl::deserialize(ifile);            
            ifile.close();
            return s;
      }
      graph_impl& operator=(graph_impl&& g) {
            if (this == &g) return *this;
            m = std::move(g.m);
            std::swap(eip, g.eip);
            std::swap(bip, g.bip);
            ecnt = g.ecnt;
            is_directed_flg = g.is_directed_flg;
            return *this;
      }
      void state() {
            std::cerr << m << std::endl;
      }
      
private:
      graph_impl(const graph_impl& obj) : m(0) {}
      const graph_impl& operator=(const graph_impl& obj) {}
      /// ITERATOR
      struct iterator_impl : public graph_base<edge_t>::iterator_base 
      {
            iterator_impl(size_t coll, size_t row, container_t& m) : it(coll,row,m) {}
            
      private:
            typename container_t::iterator it;
            
            virtual bool equal_to(const typename graph_base<edge_t>::iterator_base& that) {                  
                  typename container_t::iterator that_it =  dynamic_cast<const iterator_impl&>(that).it;
                  return it == that_it;
            }
            virtual const edge_t deref() {
                  std::pair<size_t, size_t> loc        = it();
                  typename container_t::edge_tuple_t w = *it;
                  return edge_t(std::get<0>(w), std::get<1>(w), std::get<2>(w));
            }
            virtual void increment() {            
                  it++;
            }
      };
      typedef iterator_impl iterator_impl_t;
      iterator_impl_t* bip = std::nullptr_t();
      iterator_impl_t* eip = std::nullptr_t();
      
      container_t m; //needs to be initialized BEFORE the iterators !!            
                     //bool is_digraph; 
      size_t ecnt          = 0;      
      graph_type_t is_directed_flg = graph_type_t::UNDIRECTED;
      
      std::set<typename edge_t::label_value_type> list_root;
      
      virtual size_t E_impl() const  { return ecnt;}  
      virtual size_t V_impl() const  { return m.max_size();}
      
      virtual void insert_impl(const edge_t& edge) {
            if (is_directed_impl() && (list_root.find(edge.from) == list_root.end())) {
                  m(edge.from, edge.from, 1); 
                  list_root.insert(edge.from);
                  //ecnt++;
            }
            ecnt++;
            m(edge.from, edge.to, edge.weight);
            if (! is_directed_impl()) {
                  //ecnt++;
                  m(edge.to, edge.from, edge.weight);//invisible edge
            }
      }
      
      virtual void remove_impl(const edge_t& edge)  {
            if (ecnt > 0) ecnt--;
            m.rm(edge.from, edge.to);
            if (! is_directed_impl()) {
                  if (ecnt > 0) ecnt--;
                  m.rm(edge.to, edge.from);
            }
      }
      
      virtual bool has_edge_impl(const edge_t& edge) {
            return container_t::null_weight != m(edge.from, edge.to);
      }
      
      virtual typename graph_base<edge_t>::iterator_base& begin_impl()   {            
            if (bip) delete bip;
            bip = new iterator_impl(0,0,m);            
            return *bip;
      }
      
      
      virtual typename graph_base<edge_t>::iterator_base& end_impl() {
            if (eip) delete eip;
            eip = new iterator_impl(m.max_size(), m.max_size(), m);
            return *eip;
      }
      virtual bool is_directed_impl() const { return is_directed_flg == graph_type_t::DIRECTED;}
      std::ostream& pretty_print_impl(std::ostream& strm);
      
};


template<typename container_t, typename edge_t> 
std::ostream& graph_impl<container_t,edge_t>::pretty_print_impl(std::ostream& strm) 
{
      typename container_t::edge_tuple_t start = typename container_t::edge_tuple_t();      
      auto lf = std::get<0>(start) + m.size();
      for (typename container_t::iterator it = m.begin(); it != m.end(); it++) {
            typename container_t::edge_tuple_t t = *it;
            auto from   = std::get<0>(t);
            auto to     = std::get<1>(t);
            auto weight = std::get<2>(t);
            if (lf != from) {
                  strm << std::endl << from << " : ";                  
            }
            lf = from;            
            if (weight != container_t::null_weight) {
                  strm << "[" << to << "," << weight << "],";
            }                        
           
      }
      
      return strm;
}

extern std::ostream& dump_stream(std::ostream& o, std::istream& i); 
extern bool   parse_directed(std::istream& i);
extern size_t parse_size(std::istream& i);

template<typename container_t, typename edge_t> 
graph_impl<container_t, edge_t> graph_impl<container_t,edge_t>::deserialize (std::istream& i)
{
      bool   directed = parse_directed(i);
      size_t count    = parse_size(i);      
      graph_impl<container_t, edge_t> g(count, directed);      
      std::string s;      
      auto edges = edge_t::deserialize(i);  
      g.insert(edges);      
      return g;
}

template<typename graph_t>
graph_t reverse(graph_t& G)
{
      graph_t R(G.V(), direction(G));
      
      for (typename graph_t::iterator it = G.begin(); it != G.end(); it++) {            
            auto edge = *it;
            R.insert(typename graph_t::edge_value_type(edge.to, edge.from, edge.weight));
      }      
      
      return R;
}

#endif
