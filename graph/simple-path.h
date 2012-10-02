//
//  simple-path.h
//  graph-repl
//
//  Created by alfons haffmans on 8/1/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_simple_path_h
#define graph_repl_simple_path_h

#include <vector>
#include <map>
#include <deque>

#include "graph_base.h"
#include "degree.h"
#include "edge.h"

template<typename edge_t>
struct paths {
      typedef typename edge_t::label_value_type value_t;
      typedef std::vector<value_t>              path_t;

      paths(value_t f, value_t t, path_t pp): from_(f), to_(t), p(pp){}
      
      value_t from() const {return from_;}
      value_t to()   const {return to_;}
      std::vector<value_t> operator()() const {
            return p;
      }

      operator bool() {
            return (p.size() > 0);
      }
private:
      const std::vector<value_t> p;
      const value_t from_;
      const value_t to_;
};

template<typename edge_t>
class simple_path {
public:
      typedef typename edge_t::label_value_type Value;
      
      simple_path(graph_base<edge_t>& g) : G(g){}

      paths<edge_t> operator()(Value f, Value t) {
            visited.clear();
            paths_coll.clear();
            search(f, t);
            return paths<edge_t>(f, t, paths_coll);
      }
      
           
private:
      graph_base<edge_t> &G;
      std::unordered_map<Value, bool> visited;
      std::vector<Value> paths_coll;
      bool  search (Value& from, Value& to) {
            paths_coll.push_back(from);
            if (from == to) return true;
            visited.insert(std::make_pair(from, true));
            typename graph_base<edge_t>::adjacency_generator adjacent(G, from);
            while (! adjacent.iter_done()) {
                  Value next = adjacent.yield();
                  if (visited.find(next) == visited.end()) {
                        if (search (next, to)) return true;
                  }
            }
            paths_coll.pop_back();
            return false;
      }
};


#endif
