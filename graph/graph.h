//
//  graph.h
//  graph-repl
//
//  Created by Alfons Haffmans on 4/18/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_graph_h
#define graph_repl_graph_h


#include "edge.h"
typedef edge_t<size_t, double>       simple_edge_t;
typedef edge_t<std::string, double>  labeled_edge_t;

#include "adjacency_matrix.h"
#include "adjacency_list.h"

#include "graph-type.h"

#include "graph_impl.h"
typedef graph_impl<adjacency_matrix_t, simple_edge_t> dense_graph_t;
typedef graph_impl<adjacency_list_t, simple_edge_t>   sparse_graph_t;

#include "dfs.h"
typedef dfs<simple_edge_t> simple_dfs;

#include "graph_gen.h"

#include "transitive-clojure.h"
typedef transitive_closure<sparse_graph_t> sparse_tc_t;
typedef transitive_closure<dense_graph_t>  dense_tc_t;

#endif
