//
//  check-flow.h
//  graph-repl
//
//  Created by alfons haffmans on 11/19/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_check_flow_h
#define graph_repl_check_flow_h

template <typename edge_t, typename traits=edge_trait_t<edge_t>>
struct check_flow {
  
      typedef typename traits::weight_value_type                  weight_t;
      typedef typename weight_traits_t<weight_t>::value_type      flow_t;
      typedef typename traits::label_value_type                   label_t;
      
      static flow_t flow (flow_graph_t& G, const label_t& v) {
            typename flow_graph_t::adjacency_edge_generator adj(G, v);
            auto flow = flow_t();
            while (! adj.iter_done()) {
                  auto e = adj.yield();
                  
                  flow += traits::is_from(e, v) ? traits::weight(e)->flow() : -traits::weight(e)->flow();
            }
            return flow;
      }
      static bool flow (flow_graph_t& F, const label_t& s, const label_t& t)
      {
            typename flow_graph_t::vertex_generator vg(F);
            while (! vg.iter_done()) {
                  auto v = vg.yield();
                  if (v == s || v == t) {
                        continue;
                  }
                  if (flow(F, v) != 0 ) return false;
            }
            auto sflow = flow(F, s);
            if (sflow < 0) return false;
            if (sflow + flow(F, t) != 0) return false;
            return true;
      }
      check_flow (flow_graph_t& F) : F(F){}

      bool flow (const label_t& s, const label_t& t)
      {
            return flow (F, s,t);
      }
      
      flow_t flow (const label_t& v)
      {
            return flow(F, v);
      }
      
      private :
      flow_graph_t& F;
};


#endif
