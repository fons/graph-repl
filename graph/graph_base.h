/*
 *  graph_base.h
 *  graph_base
 *
 *  Created by Alfons Haffmans on 3/10/12.
 *  Copyright (c) 2012 mohegan skunk works. All rights reserved.
 *
 */

#ifndef graph_base_
#define graph_base_

/* The classes below are exported */
#pragma GCC visibility push(default)

#include <iostream>
#include <fstream>
#include <vector>
#include <set>

template<typename edge_t>
struct edge_compare {
      bool operator() (const edge_t& lhs, const edge_t& rhs) {
            if (lhs.from == rhs.from) {
                  return lhs.to < rhs.to;
            }
            return lhs.from < rhs.from;
      }
};


template <typename edge_t>
class graph_base
{
      class generator_base {
      protected:
            struct construct_filter {
                  virtual std::vector<typename edge_t::label_value_type>& operator()(std::vector<typename edge_t::label_value_type>& cont, const edge_t& e) = 0;
            };
            struct id : public construct_filter {
                  std::vector<typename edge_t::label_value_type>& operator()(std::vector<typename edge_t::label_value_type>& cont, const edge_t& e) {
                        return cont;
                  }
            };
      public:
            generator_base(graph_base& G) {id ident; construct(G, ident);}
            generator_base(graph_base& G, construct_filter&& f) {construct(G,f);}
            typename edge_t::label_value_type yield() {
                  if (it == vert.end()) {
                        it = vert.begin();
                  }
                  typename edge_t::label_value_type v = *it;
                  ++it;
                  return v;
            }
            bool iter_done() const {
                  return it == vert.end();
            }
      private:
            generator_base(const generator_base& ){}
            generator_base& operator=(const generator_base&) {}
            
            std::vector<typename edge_t::label_value_type> vert;
            typename std::vector<typename edge_t::label_value_type>::iterator it;
            
            void construct(graph_base& G, construct_filter& f) {
                  for (typename graph_base<edge_t>::iterator it = G.begin(); it != G.end(); it++) {                                    
                        vert = f(vert, *it);                        
                  }
                  it = vert.begin();
            }
      };

public:
      typedef edge_t edge_value_type;
      static std::ostream& serialize (std::ostream& strm, graph_base<edge_t>& g);
      static std::ostream& graphviz (std::ostream& strm, graph_base<edge_t>& g);
      void serialize (const std::string& fn) { 
            with_open_file(fn, serialize);
      }
      void graphviz (const std::string& fn) {
            with_open_file(fn, graphviz);
      }
     
      size_t E() const { return E_impl(); }
      size_t V() const { return V_impl(); }
      void   insert (const   edge_t& edge) { return insert_impl(edge);}
      void   insert (const std::vector<edge_t>& edges) {return insert_impl(edges);}
      void   remove (const   edge_t& edge) { return remove_impl(edge);}
      bool   has_edge (const edge_t& edge) { return has_edge_impl(edge);}
      bool   is_directed() const { return is_directed_impl();}
      class iterator_base {
      public:
            bool operator==(const iterator_base& that) { return equal_to(that);}
            bool operator!=(const iterator_base& that) { return !(*this == that);}
            const edge_t operator*() { return deref();}
            void  operator++() {increment();}
            void  operator++(int) {increment();}            
      private:  
            virtual bool equal_to(const iterator_base& that) = 0;      
            virtual const edge_t deref()                = 0; 
            virtual void increment()                    = 0;
      };
           
      std::ostream& pretty_print(std::ostream& strm) { return pretty_print_impl(strm);}

      struct iterator {
            iterator(iterator_base& base) : base(base){}
            
            void operator++() {
                  base++;
            }
            
            void operator++(int) {
                  base++;
            }
            
            bool operator==(const iterator_base& that) {
                  return base==(that);
            }
            
            bool operator!=(const iterator_base& that) {
                  return base!=(that);
            }
            
            edge_t operator*() {
                  return *base;
            }
            
      private:
            iterator_base& base;      
      };
      
      
      iterator_base& begin() { return begin_impl();}
      iterator_base& end()   { return end_impl(); }

      ///------------------------------------------------------------------------
            
            
      class adjacency_generator : public generator_base {
            class adjacent_to_edge : public generator_base::construct_filter {
            public :
                  adjacent_to_edge(typename edge_t::label_value_type& v) : v(v){}
                  std::vector<typename edge_t::label_value_type>& operator()(std::vector<typename edge_t::label_value_type>& cont, const edge_t& e)  {
                        if (v == e.from) {
                              cont.push_back(e.to);
                        }
                        return cont;
                  }
            private:
                  typename edge_t::label_value_type& v;
            };
      public:
            adjacency_generator(graph_base& G, typename edge_t::label_value_type v) : generator_base(G, adjacent_to_edge(v)) {}
            
      };
      class vertex_generator : public generator_base {
            class unique : public generator_base::construct_filter {
                  public :
                  std::vector<typename edge_t::label_value_type>& operator()(std::vector<typename edge_t::label_value_type>& cont, const edge_t& e) {
                        cont = add_uniq(cont, e.from);
                        cont = add_uniq(cont, e.to);
                        return cont;
                  }
            private:
                  std::vector<typename edge_t::label_value_type>& add_uniq(std::vector<typename edge_t::label_value_type>& cont ,
                                                                           typename edge_t::label_value_type v) {
                             
                        auto ret = S.insert(v);
                        if (ret.second) {
                              cont.push_back(v);
                        }
                        return cont;
                  }
                  std::set<typename edge_t::label_value_type> S;
            };
      public:
            vertex_generator(graph_base& G) : generator_base(G, unique()){}
      };
private:
      virtual size_t E_impl() const                                  = 0;      
      virtual size_t V_impl() const                                  = 0;        
      virtual void insert_impl(const edge_t& edge)                   = 0;   
      virtual void insert_impl(const std::vector<edge_t>& edges) {
            for (auto p : edges) {
                  insert(p);
            }
      }
      virtual void remove_impl(const edge_t& edge)                   = 0;      
      virtual bool has_edge_impl(const edge_t& edge)                 = 0;      
      virtual iterator_base& begin_impl()                            = 0;
      virtual iterator_base& end_impl()                              = 0;
      virtual std::ostream& pretty_print_impl(std::ostream& strm)    = 0;
      virtual bool is_directed_impl() const                          = 0;
      //typedef std::ostream& Func* (std::ostream& , graph_base<edge_t>&);
      typedef std::ostream& (*Func)(std::ostream& , graph_base<edge_t>&);
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

template<typename edge_t>
std::ostream& operator<< (std::ostream &strm, graph_base<edge_t>& g)
{
      return g.pretty_print(strm);      
}

template<typename edge_t> std::ostream& 
graph_base<edge_t>::serialize (std::ostream& strm, graph_base<edge_t>& g)
{
      std::set<edge_t, edge_compare<edge_t>> vis;
      size_t count = 0;
      strm << "(directed ";
      if (g.is_directed()) {
            strm << " t)" <<std::endl;
      }
      else {
            strm << " f)" <<std::endl;
      }
      strm << "(vertices  " << g.V() << ")" << std::endl;  //keep space here
      count++;
      for (typename graph_base<edge_t>::iterator it = g.begin(); it != g.end(); it++) {
            if (! g.is_directed()) {
                  if (vis.find (*it) == vis.end() ) {
                        edge_t::serialize(strm, *it);
                        vis.insert(edge_t((*it).to, (*it).from, (*it).weight));
                        if (++count > 20) strm << std::endl;
                  }
            }
            else {
                  edge_t::serialize(strm, *it);
            }
      }      
      return strm;
}

template<typename edge_t> std::ostream& 
graph_base<edge_t>::graphviz (std::ostream& strm, graph_base<edge_t>& g)
{
      std::set<edge_t, edge_compare<edge_t>> vis;
      size_t count = 0;

      if (g.is_directed()) {
            strm << "digraph G { " << std::endl;      
      }
      else {
            strm << "graph G { " << std::endl;  
      }

      count++;

      for (typename graph_base<edge_t>::iterator it = g.begin(); it != g.end(); it++) {            
            if (! g.is_directed()) {
                  if (vis.find (*it) == vis.end() ) {
                        edge_t::graphviz(strm, *it, g.is_directed());
                        strm << std::endl;
                        vis.insert(edge_t((*it).to, (*it).from, (*it).weight));
                  }
            }
            else {
                  if ((*it).from != (*it).to) {
                        edge_t::graphviz(strm, *it, g.is_directed());
                  }
                  strm << std::endl;
            }
            
      }      
      
      return strm << "}" << std::endl;
}
#pragma GCC visibility pop
#endif