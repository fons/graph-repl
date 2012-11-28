//
//  flow-graph-util.cpp
//  graph-repl
//
//  Created by alfons haffmans on 11/22/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "graph.h"
simple_flow_edge_ptr_t make_simple_flow_edge(const size_t& from, const size_t& to, const long& capacity)
{
      auto p = make_capacity_flow<long>(capacity);
      return std::shared_ptr<simple_flow_edge_t>(new simple_flow_edge_t(from, to, p));
}

bool change_flow(flow_graph_t& F, size_t from, size_t to, long flow)
{
      
      auto e = F.edge(from, to);
      if (!e || ! e->weight || flow > e->weight->capacity()) {
            return false;
      }
      e->weight->flow(flow);
      return true;
}

std::ostream& operator<<(std::ostream& strm, const flow_edge& fe) {
      return fe.pp(strm) ;
}

