//
//  edge-traits.h
//  graph-repl
//
//  Created by alfons haffmans on 9/15/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_edge_traits_h
#define graph_repl_edge_traits_h

template <typename edge_t>
struct edge_trait_t {
      typedef edge_t                             edge_type;
      typedef edge_t                             value_type;
      typedef typename edge_t::label_value_type  label_value_type;
      typedef typename edge_t::weight_value_type weight_value_type;
      
      static label_value_type from (const edge_t& e) {
            return e.from;
      }
      static label_value_type to (const edge_t& e) {
            return e.to;
      }
      static weight_value_type weight(const edge_t& e) {
            return e.weight;
      }
      
      static const edge_t& deref(const edge_t& e) {
            return e;
      }
      
      static value_type make_edge(const label_value_type& f, const label_value_type& t, const weight_value_type& w) {
            return edge_t(f,t,w);
      }
      static const size_t salt;
};

template<typename edge_t> const size_t edge_trait_t<edge_t>::salt = 0xeface1;

template<typename edge_t>
struct edge_trait_t <edge_t*> {
      typedef edge_t                            edge_type;
      typedef edge_t*                           value_type;
      typedef typename edge_t::label_value_type label_value_type;
      typedef typename edge_t::weight_value_type weight_value_type;

      static label_value_type from (const edge_t* e) {
            return e->from;
      }
      
      static label_value_type to (const edge_t* e) {
            return e->to;
      }

      static weight_value_type weight(const edge_t* e) {
            return e->weight;
      }

      static const edge_t& deref(const edge_t* e) {
            return *e;
      }
      
      static value_type make_edge(const label_value_type& f, const label_value_type& t, const weight_value_type& w) {
            return new edge_t(f,t,w);
      }
      static const size_t salt;
};

template<typename edge_t> const size_t edge_trait_t<edge_t*>::salt = 0xbab0face;

template<typename edge_t>
struct edge_trait_t <std::shared_ptr<edge_t>> {
      typedef edge_t                             edge_type;
      typedef std::shared_ptr<edge_t>           value_type;
      typedef typename edge_t::label_value_type label_value_type;
      typedef typename edge_t::weight_value_type weight_value_type;
      
      static label_value_type from (const std::shared_ptr<edge_t>& e) {
            return e->from;
      }

      static label_value_type to (const std::shared_ptr<edge_t>& e) {
            return e->to;
      }
      
      static weight_value_type weight(const std::shared_ptr<edge_t>& e) {
            return e->weight;
      }
      
      static const edge_t& deref(const std::shared_ptr<edge_t>& e) {
            return *e;
      }

      static value_type make_edge(const label_value_type& f, const label_value_type& t, const weight_value_type& w) {
            return std::shared_ptr<edge_t>(new edge_t(f,t,w));
      }
      static const size_t salt;
};

template<typename edge_t> const size_t edge_trait_t<std::shared_ptr<edge_t>>::salt = 0xaaface0;


#endif
