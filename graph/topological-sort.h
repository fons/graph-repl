//
//  topological-sort.h
//  graph-repl
//
//  Created by alfons haffmans on 8/9/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_topological_sort_h
#define graph_repl_topological_sort_h

#include <iostream>
#include <deque>


template<typename edge_t>
struct topological_sort_base {
      typedef std::map<typename edge_t::label_value_type, size_t> topological_sort_t;
      
      topological_sort_t operator()() const
      {
            return order;
      }

      size_t operator()(const typename edge_t::label_value_type& v)
      {
            return order[v];
      }
                 
      std::ostream& pp(std::ostream& strm)
      {
            for (typename topological_sort_t::iterator it = order.begin(); it != order.end(); it++) {
                  strm << it->first << " : " << it->second << std::endl;
            }
            
            return strm;
      }
      
protected :
      typename topological_sort_base<edge_t>::topological_sort_t order;
};

template<typename edge_t>
std::ostream& operator<<(std::ostream& strm, topological_sort_base<edge_t>& v)
{
      return v.pp(strm);
}

template <typename edge_t>
struct rev_top_sort_dfs : public topological_sort_base<edge_t>
{
public:
      rev_top_sort_dfs (graph_base<edge_t>& G)
      {
            init(G);
      }
      
private:
      
      void init(graph_base<edge_t>& g)
      {
            dfs<edge_t> dfs(g);
            dfs();
            sparse_graph_t::vertex_generator s(g);
            while (! s.iter_done()){
                  auto v = s.yield();
                  //size_t post_order = dfs.post_order(v);
                  size_t post_order = property<simple_edge_t, postorder_t>(dfs, v);
                  topological_sort_base<edge_t>::order[v] = post_order;
            }
      }
      
};

template <typename edge_t>
struct top_sort_dfs : public topological_sort_base<edge_t>
{
public:
      top_sort_dfs (graph_base<edge_t>& G)
      {
            init(G);
      }
      
private:
      
      void init(graph_base<edge_t>& g)
      {
            size_t n = g.V();
            dfs<edge_t> dfs(g);
            dfs();
            sparse_graph_t::vertex_generator s(g);
            while (! s.iter_done()){
                  auto v = s.yield();
                  //size_t post_order = dfs.post_order(v);
                  size_t post_order = property<simple_edge_t, postorder_t>(dfs, v);
                  topological_sort_base<edge_t>::order[v] = n - post_order - 1;
            }
      }
      
};

template <typename edge_t>
struct top_sort_queue : topological_sort_base<edge_t> {
public:
      top_sort_queue (graph_base<edge_t>& G)
      {
            init(G);
      }
      
private:
      typedef std::map<typename edge_t::label_value_type, size_t> cont_t;
      typedef std::deque<typename edge_t::label_value_type> queue_t;
      
      cont_t  indegree;
      queue_t Q;
      
      static cont_t& indegree_init(graph_base<edge_t>& g, cont_t& in)
      {
            typename graph_base<edge_t>::vertex_generator gen(g);
            while (!gen.iter_done()) {
                  in[gen.yield()] = 0;
            }
            for (typename graph_base<edge_t>::iterator it = g.begin(); it != g.end(); it++) {
                  //skip self loops
                  if ((*it).from == (*it).to) continue;
                  //std::cerr << *it << std::endl;
                  in[(*it).to]++;
            }
            return in;
      }
            
      void init(graph_base<edge_t>& g)
      {
            indegree = indegree_init(g, indegree);
            
            for (auto& val : indegree) {
                  if (val.second == 0) {
                        Q.push_back(val.first);
                  }
            }
            size_t guard = g.E() + 10;
            size_t order = 0;
            while (! Q.empty()) {
                  auto v = Q.front();
                  Q.pop_front();
                  topological_sort_base<edge_t>::order[v] = order;
                  order++;
                  typename graph_base<edge_t>::adjacency_generator adj(g, v);
                  while (! adj.iter_done()) {
                        auto v = adj.yield();

                        if (indegree[v] == 1) {
                              Q.push_back(v);
                              indegree[v]--;
                        }
                        
                        if (indegree[v] > 1) {
                              indegree[v]--;
                        }
                  }
                  if (order > guard) return;
            }
      }
};

template <typename graph_t, typename algo_t=top_sort_dfs<typename graph_t::edge_value_type>>
class topological_sort {
     
public:
      typedef typename algo_t::topological_sort_t container_t;
      
      topological_sort(graph_base<typename graph_t::edge_value_type>& G) : algo(new algo_t(G)) {}
      
      
      container_t operator()() const
      {
            return algo->operator()();
      }

      size_t operator()(const typename graph_t::edge_value_type::label_value_type& v)
      {
            return algo->operator()(v);
      }
      
      std::ostream& pp(std::ostream& strm) {
            return algo->pp(strm);
      }
      
      topological_sort(const topological_sort&) = delete;
      void operator=(const topological_sort&)   = delete;

private:
      std::unique_ptr<topological_sort_base<typename graph_t::edge_value_type>> algo;
};


template<typename graph_t, typename algo_t>
std::ostream& operator<<(std::ostream& strm, topological_sort<graph_t, algo_t>& v)
{
      return v.pp(strm);
}

#endif
