//
//  graph.h
//  graph-repl
//
//  Created by Alfons Haffmans on 4/18/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_graph_h
#define graph_repl_graph_h

#include <random>

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <sstream>


#include "proto.h"
#include "format.h"
#include "stack.h"
#include "queue.h"
#include "graph_utils.h"
#include "priority-queue.h"
#include "weight-traits.h"
#include "edge.h"
#include "tuple.h"

typedef edge_t<size_t, double>       simple_edge_t;
typedef edge_t<std::string, double>  labeled_edge_t;

template<typename l, typename r>
std::ostream& operator<<(std::ostream& strm, const std::pair<l,r>& p)
{
 return strm << "[" << p.first << "," << p.second << "]";

}
      
#include "edge-traits.h"
#include "edge-assoc-array.h"
#include "union-find.h"

#include "adjacency_matrix.h"
#include "adjacency_list.h"

#include "graph-type.h"
#include "graph_base.h"
#include "graph_impl.h"
typedef graph_impl<adjacency_matrix_t, simple_edge_t> dense_graph_t;
typedef graph_impl<adjacency_list_t, simple_edge_t>   sparse_graph_t;
#include "graph_gen.h"

#include "dfs.h"
typedef dfs<simple_edge_t> simple_dfs;
#include "bfs.h"
typedef bfs<simple_edge_t> simple_bfs;
      
#include "graph_gen.h"
#include "dag.h"
#include "strong-components.h"
#include "transitive-clojure.h"
typedef transitive_closure<sparse_graph_t> sparse_tc_t;
typedef transitive_closure<dense_graph_t>  dense_tc_t;

#include "degree.h"
typedef degree<simple_edge_t> Degree;

#include "simple-path.h"
typedef simple_path<simple_edge_t> simple_edge_path_t;
typedef paths<simple_edge_t>       simple_path_t;

#include "topological-sort.h"
#include "minimum-spanning-tree.h"
#include "single-source-shortest-paths.h"
#include "all-pairs-shortest-path.h"
#include "acyclic_shortest_path.h"
      
#include "capacity-flow.h"
#include "flow-graph-util.h"
#include "check-flow.h"
      
#include "maxflow.h"
#include "preflow-push-maxflow.h"
#endif
