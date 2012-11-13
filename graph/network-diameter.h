//
//  network-diameter.h
//  graph-repl
//
//  Created by alfons haffmans on 10/31/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_network_diameter_h
#define graph_repl_network_diameter_h

template <typename edge_t typename traits=edge_trait_t<edge_t>>
class network_diameter
{
public:
      network_diameter(graph_base<edge_t, traits>& G) {
            init(G);
      }
private:
      void init(graph_base<edge_t, traits>& G)
      {
            
      }
};

#endif
