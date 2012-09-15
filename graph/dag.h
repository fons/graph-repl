//
//  dag.h
//  graph-repl
//
//  Created by alfons haffmans on 8/8/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_dag_h
#define graph_repl_dag_h


template <typename edge_t>
struct is_dag {
      explicit is_dag (graph_base<edge_t>& G) : is_a_dag(init(G)){}
      inline bool operator()() const
      {
            return is_a_dag;
      }
private:
      const bool is_a_dag;
      bool init (graph_base<edge_t>& g)
      {
            dfs<edge_t> dfs(g);
            dfs();
            for (typename graph_base<edge_t>::iterator it = g.begin(); it != g.end(); it++) {
                  if (dfs.is_back_edge(*it)) {
                        return false;
                  }
            }
            return true;
      }
      
};

#endif
