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

//#include "graph-type.h"
//#include "graph_base.h"


template <typename container_t, typename edge_t, typename traits=edge_trait_t<edge_t>>
class graph_impl : public graph_base <edge_t> {
public:
      typedef container_t                       container_value_type;
      typedef edge_t                            edge_value_type;
      typedef typename traits::label_value_type label_value_type;
      typedef typename traits::value_type       value_type;
      
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
                  typename container_t::edge_tuple_t w = *it;
                  return traits::make_edge(std::get<0>(w), std::get<1>(w), std::get<2>(w));
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
      std::set<label_value_type> vertices;
      graph_type_t is_directed_flg = graph_type_t::UNDIRECTED;
      
      std::unordered_set<label_value_type> list_root;

      bool has_self_loop(label_value_type v) {
            return ! (list_root.find(v) == list_root.end());
      }
      
      bool list_root_insert(label_value_type v)
      {
            if (! has_self_loop(v)) {
                  list_root.insert(v);
                  return true;
            }
            return false;
      }
      void add_self_loop(const edge_t& edge)
      {
            if (list_root_insert(traits::from(edge)) ) {
                  m(traits::from(edge), traits::from(edge), 1);
            }

            if (list_root_insert(traits::to(edge))) {
                  m(traits::to(edge), traits::to(edge), 1);
            }
      }
                                                            
      void mark_self_loop (const edge_t& edge) {
            list_root_insert(traits::from(edge));
            list_root_insert(traits::to(edge));
      }
      
      virtual size_t E_impl() const  { return ecnt + list_root.size();}
      virtual size_t V_impl() const  { return vertices.size();}
      
      virtual void insert_impl(const edge_t& edge) {
            // add loopback for directed graphs
            if (is_directed_impl() && traits::deref(edge).is_self_loop() && has_self_loop(traits::from(edge))) {
                  return;
            }
            ecnt++;
            vertices.insert(traits::from(edge));
            vertices.insert(traits::to(edge));
            m(traits::from(edge), traits::to(edge), traits::weight(edge));
            if (is_directed_impl()) {
//                  if (traits::from(edge) != traits::to(edge)) {
//                        add_self_loop(edge);
//                  }
//                  else {
//                        mark_self_loop(edge);
//                  }
            }
            else {
                  //invisible edge for undirected graphs
                  m(traits::to(edge), traits::from(edge), traits::weight(edge));
            }
      }
      
      virtual void remove_impl(const edge_t& edge)  {
            if (ecnt > 0) ecnt--;
            m.rm(traits::from(edge), traits::to(edge));
            if (! is_directed_impl()) {
                  if (ecnt > 0) ecnt--;
                  m.rm(traits::to(edge), traits::from(edge));
            }
      }
      
      virtual bool has_edge_impl(const edge_t& edge) const {
            return container_t::null_weight != const_cast<graph_impl*>(this)->m(traits::from(edge), traits::to(edge));
            //return edge.weight == const_cast<graph_impl*>(this)->m(edge.from, edge.to);
      }
      //
      virtual value_type edge_impl(const label_value_type& f, const label_value_type& t) const {
            return traits::make_edge(f, t,const_cast<graph_impl*>(this)->m(f, t));
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


template<typename container_t, typename edge_t, typename traits>
std::ostream& graph_impl<container_t,edge_t,traits>::pretty_print_impl(std::ostream& strm)
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


template<typename container_t, typename edge_t, typename traits>
graph_impl<container_t, edge_t, traits> graph_impl<container_t,edge_t,traits>::deserialize (std::istream& i)
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
            R.insert(typename graph_t::edge_value_type(edge_trait_t<typename graph_t::edge_value_type>::to(edge),
                                                       edge_trait_t<typename graph_t::edge_value_type>::from(edge),
                                                       edge_trait_t<typename graph_t::edge_value_type>::weight(edge)));
            
      }
      return R;
}

#endif
