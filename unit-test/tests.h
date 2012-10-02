//
//  tests.h
//  graph-repl
//
//  Created by Alfons Haffmans on 7/11/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_tests_h
#define graph_repl_tests_h

#include <iostream>
#include "graph.h"
#include "regression-test.h"
#include "assertion.h"

extern std::pair<int, std::string> test_stack(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_edges(std::ostream& strm, int argc, const char *argv[]);
extern std::pair<int, std::string> test_edge_compare(std::ostream& strm, int argc, const char *argv[]);
extern std::pair<int, std::string> test_edge_set(std::ostream& strm, int argc, const char *argv[]);
extern std::pair<int, std::string> test_case_1(std::ostream& strm, int argc, const char *argv[]);
extern std::pair<int, std::string> divide_by_zero(std::ostream& strm, int argc, const char *argv[]);
extern std::pair<int, std::string> test_adjacency_list(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_adjacency_list_rm(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_adjacency_matrix(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_directed_graph(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_undirected_random_graph(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_directed_random_graph(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_undirected_dfs(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_components(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_edge_seperability(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_degree(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_bipartite(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_bipartite_negative(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_simple_path(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_vertex_generator(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_adjacency_generator(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_reverse_directed_graph(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_graph(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_directed_graph_dfs(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_transitive_closure(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_transitive_closure_warshall(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_topological_sort_dfs(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_not_dag(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_dag(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_reverse_topological_sort_dfs(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_dfs_property(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_topological_sort_dfs(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_topological_sort_queue(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_kosaraju(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_tarjan(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_gabow(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_transitive_closure_kernel_dag(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_transitive_closure_dag(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_weighted_graph(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_edge_ptr(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_graph_edge_naked_ptr(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_graph_edge_shared_ptr(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_mst_dense_prim(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_priority_queue_base_1(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_priority_queue_base_2(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_priority_queue_1(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_priority_queue_2(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_priority_queue_kv_1(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_priority_queue_kv_2(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_priority_queue_kv_3(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_mst_prim_pfs(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_adjacency_edge_generator(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_assoc_array(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_union_find(std::ostream& strm,int argc, const char *argv[]);
extern std::pair<int, std::string> test_mst_kruskal(std::ostream& strm,int argc, const char *argv[]);
#endif

