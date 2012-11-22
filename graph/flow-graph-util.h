//
//  flow-graph-util.h
//  graph-repl
//
//  Created by alfons haffmans on 11/22/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef __graph_repl__flow_graph_util__
#define __graph_repl__flow_graph_util__

typedef capacity_flow_t<long>                                     simple_capacity_flow_t;
typedef std::shared_ptr<simple_capacity_flow_t>                   simple_capacity_flow_ptr_t;
typedef edge_t<size_t, simple_capacity_flow_ptr_t>                simple_flow_edge_t;
typedef std::shared_ptr<simple_flow_edge_t>                       simple_flow_edge_ptr_t;

typedef adjacency_list<simple_capacity_flow_ptr_t>                flow_adjacency_list_t;
typedef graph_impl<flow_adjacency_list_t, simple_flow_edge_ptr_t> flow_graph_t;

template<typename T>
std::shared_ptr<capacity_flow_t<T>> make_capacity_flow(const T& capacity)
{
      return std::shared_ptr<capacity_flow_t<T>>(new capacity_flow_t<T>(capacity));
}


template <>
struct weight_traits_t<std::shared_ptr<simple_capacity_flow_t>>
{
      typedef long value_type;
      
      static const simple_capacity_flow_t& deref(const std::shared_ptr<simple_capacity_flow_t>& e) {
            return *e;
      }
};

extern simple_flow_edge_ptr_t make_simple_flow_edge(const size_t& from, const size_t& to, const long& capacity);

extern bool change_flow(flow_graph_t& F, size_t from, size_t to, long flow);

#endif /* defined(__graph_repl__flow_graph_util__) */
