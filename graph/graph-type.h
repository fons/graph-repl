//
//  graph-type.h
//  graph-repl
//
//  Created by Alfons Haffmans on 7/7/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_graph_type_h
#define graph_repl_graph_type_h

enum class graph_type_t {
      DIRECTED,
      UNDIRECTED    
};

template <typename graph_t>
graph_type_t direction(const graph_t& G)
{
      if (G.is_directed()) {
            return graph_type_t::DIRECTED;
      }
      return graph_type_t::UNDIRECTED;
}



#endif
