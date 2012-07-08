//
//  graph-property.h
//  graph-repl
//
//  Created by Alfons Haffmans on 6/25/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_graph_property_h
#define graph_repl_graph_property_h


struct graph_property_t {
      typedef void retval;      
};
template<typename T>
struct retval_t {
      typedef T retval;
};

struct component_t : public retval_t<int> {
      
};

struct preorder_t : public retval_t<int> {
      
};

struct parent_t : public retval_t<size_t> {
      
};

struct bridge_t : public retval_t<int> {
      
};

struct articulation_t : public retval_t<int> {
      
};


template <typename edge_t>
struct bridges_t : public retval_t< std::vector<edge_t> > {
      
};

template <typename edge_t>
struct artics_t : public retval_t< std::set<typename edge_t::label_value_type> > {
      
};


struct cycle_t : public retval_t<int> {
      
};

struct bipartite_t : public retval_t<bool> {
      
};

template<typename container_t, typename edge_t>
struct spanning_tree_t : public retval_t <graph_impl<container_t, edge_t>> {
      
};


#endif
