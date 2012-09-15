//
//  digraph-components.h
//  graph-repl
//
//  Created by alfons haffmans on 8/27/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_digraph_components_h
#define graph_repl_digraph_components_h

#include <memory>

template<typename edge_t>
struct component_kosaraju
{
      explicit component_kosaraju(graph_base<edge_t>& G) : R(new graph_impl<adjacency_list, edge_t>(G.V(), direction(G))) {
            _reverse_(G);
            init(G, *R);
      }
      component_kosaraju(const component_kosaraju& o) = delete;
      void operator=(const component_kosaraju& ) = delete;
      
      size_t count() const { return state->scnt;}
      
      bool operator()(typename edge_t::label_value_type f, typename edge_t::label_value_type t) const
      {
            return state->id[f] == state->id[t];
      }
      
      size_t operator[](typename edge_t::label_value_type t) const {
            return state->id.at(t);
      }
      
      std::vector<typename edge_t::label_value_type> operator()(size_t cid) const
      {
            return state->mapI.at(cid);
      }

      std::ostream& pp(std::ostream& strm) {
            strm << "number of components : " << count() << std::endl;
            for (int i = 0; i < count(); i++) {
                  strm << "{ " << i << " ==> [";
                  size_t ms = 10;
                  size_t mi = this->operator()(i).size();
                  mi        = mi > ms ? (mi - ms) : 0;
                  for (auto& val : this->operator()(i)) {
                        strm << val << ",";
                        ms--;
                        if (ms == 0) break;
                  }
                  if (ms == 0) strm << "..(+" << mi <<")";
                  strm << "] }" << std::endl;
            }
            return strm;
      }

private:
      typedef std::map<typename edge_t::label_value_type, size_t> cont_t;
      typedef std::map<size_t, typename edge_t::label_value_type> rev_cont_t;
      typedef std::map<size_t, std::vector<typename edge_t::label_value_type>> comp_map_t;
      typedef std::unique_ptr<graph_impl<adjacency_list_t, edge_t>> graph_ptr_t;
      //typedef graph_impl<adjacency_list_t, edge_t>* graph_ptr_t;
      graph_ptr_t R;

      void _reverse_(graph_base<edge_t>& G) {
            for (typename graph_base<edge_t>::iterator it = G.begin(); it != G.end(); it++) {
                  auto edge = *it;
                  R->insert(typename graph_base<edge_t>::edge_value_type(edge.to, edge.from, edge.weight));
            }
            return;
      }
      
      
      struct dfs_state {
            rev_cont_t postI;
            comp_map_t mapI;
            cont_t id;
            size_t scnt;
            size_t cnt;
            dfs_state() : cnt(0), scnt(0){}

            size_t set_component (typename edge_t::label_value_type v)
            {
                  id[v] = scnt;
                  mapI[scnt].push_back(v);
                  return scnt;
            }

            bool visited (typename edge_t::label_value_type v) const
            {
                  return id.find(v) != id.end();
            }
            
            size_t visited() const {
                  return id.size();
            }

            size_t post_increment(typename edge_t::label_value_type v)
            {                 
                  postI[cnt++] = v;
                  //std::cerr << "incr count : " << cnt << " node :" << v << std::endl;
                  return cnt;
                  
            }
            
            typename edge_t::label_value_type vertex_post_order (size_t index) {
                  return postI[index];
            }
            
            size_t incr_component_count()
            {
                  return scnt++;
            }
      };
      typedef std::unique_ptr<dfs_state> state_ptr_t;
      
      state_ptr_t state;
      
      void init (graph_base<edge_t>& G, graph_base<edge_t>& R)
      {
            state.reset(new dfs_state());
            typename graph_base<edge_t>::vertex_generator vr(R);
            while (! vr.iter_done()) {
                  auto v = vr.yield();
                  if (! state->visited(v)) dfs(R, v);
            }
            int        vcnt = static_cast<int>(state->visited()) - 1;
            state_ptr_t prev_state = std::move(state);
            state.reset(new dfs_state());
            for (int index = vcnt; index >= 0; index--) {
                  typename edge_t::label_value_type v = prev_state->vertex_post_order(index);
                  if (! state->visited(v)) {
                        dfs(G,v);
                        state->incr_component_count();
                  }
            }
      }
      
      void dfs (graph_base<edge_t>& G, typename edge_t::label_value_type w)
      {
            state->set_component (w);
            typename graph_base<edge_t>::adjacency_generator adj(G, w);
            while (! adj.iter_done()) {
                  auto t = adj.yield();
                  if (! state->visited (t) ) dfs(G, t);
            }
            state->post_increment(w);
      }
            
     
};

template <typename edge_t>
struct component_tarjan
{
      explicit component_tarjan(graph_base<edge_t>& G) {
            init (G);
      }

      size_t count() const {
            return scnt;
      }
      
      size_t operator[](typename edge_t::label_value_type t) const {
            return id.at(t);
      }
      
      bool operator()(typename edge_t::label_value_type f, typename edge_t::label_value_type t )
      {
            return id[f] == id[t];
      }
      std::vector<typename edge_t::label_value_type> operator()(size_t cid) const
      {
            return mapI.at(cid);
      }

      std::ostream& pp(std::ostream& strm) {
            strm << "number of components : " << count() << std::endl;
            for (int i = 0; i < count(); i++) {
                  strm << "{ " << i << " ==> [";
                  size_t ms = 10;
                  size_t mi = this->operator()(i).size();
                  mi        = mi > ms ? (mi - ms) : 0;
                  for (auto& val : this->operator()(i)) {
                        strm << val << ",";
                        ms--;
                        if (ms == 0) break;
                  }
                  if (ms == 0) strm << "..(+" << mi <<")";
                  strm << "] }" << std::endl;
            }

            return strm;
      }

protected :

      
      typedef std::map<typename edge_t::label_value_type, size_t> cont_t;
      typedef std::map<size_t, std::vector<typename edge_t::label_value_type>> comp_map_t;
      typedef stack<typename edge_t::label_value_type> stack_t;

      cont_t id;
      cont_t pre;
      cont_t low;
      comp_map_t mapI;
      stack_t S;
      size_t cnt  = 0;
      size_t scnt = 0;
      
      bool visited (typename edge_t::label_value_type v) const
      {
            return pre.find(v) != pre.end();
      }
      
      void init (graph_base<edge_t>& G)
      {
            typename graph_base<edge_t>::vertex_generator vg(G);
            while (!vg.iter_done()) {
                  auto v = vg.yield();
                  if (!visited(v)) scR(G, v);
            }
      }
      
      void scR(graph_base<edge_t>& G, typename edge_t::label_value_type w)
      {
            
            pre[w]     = cnt; // preorder
            low[w]     = cnt; // lowest preorder number encountered
            size_t min = cnt; // temporary smallest pre-order encountered
            cnt++;
            S.push(w);
            typename graph_base<edge_t>::adjacency_generator adj(G, w);
            while (! adj.iter_done()) {
                  auto t = adj.yield();
                  if (! visited(t)) scR(G, t);
                  if (low[t] < min) min = low[t];
            }
            if (min < low[w]) {
                  low[w] = min;
                  return;
            }
            // pre[w] == low[w] at this point
            //std::cerr << "we are going to pop : " << w << std::endl;
            {
                  typename edge_t::label_value_type t;
                  do {
                        t = S.pop();
                        id[t] = scnt;
                        mapI[scnt].push_back(t);
                        low[t] = G.V();
                  } while (t != w);
                  scnt++;
            }
      }
      
      
};

//same as tarjan except for scR
template <typename edge_t>
struct component_gabow
{
      explicit component_gabow(graph_base<edge_t>& G) {
            init (G);
      }
      
      size_t count() const {
            return scnt;
      }

      size_t operator[](typename edge_t::label_value_type t) const {
            return id.at(t);
      }
      
      bool operator()(typename edge_t::label_value_type f, typename edge_t::label_value_type t )
      {
            return id[f] == id[t];
      }
      std::vector<typename edge_t::label_value_type> operator()(size_t cid) const
      {
            return mapI.at(cid);
      }
      
      std::ostream& pp(std::ostream& strm) {
            strm << "number of components : " << count() << std::endl;
            for (int i = 0; i < count(); i++) {
                  strm << "{ " << i << " ==> [";
                  size_t ms = 10;
                  size_t mi = this->operator()(i).size();
                  mi        = mi > ms ? (mi - ms) : 0;
                  for (auto& val : this->operator()(i)) {
                        strm << val << ",";
                        ms--;
                        if (ms == 0) break;
                  }
                  if (ms == 0) strm << "..(+" << mi <<")";
                  strm << "] }" << std::endl;
            }
            
            return strm;
      }
      
      protected :
      
      
      typedef std::map<typename edge_t::label_value_type, size_t> cont_t;
      typedef std::map<size_t, std::vector<typename edge_t::label_value_type>> comp_map_t;
      typedef stack<typename edge_t::label_value_type> stack_t;
      
      cont_t id;
      cont_t pre;
      cont_t low;
      comp_map_t mapI;
      stack_t S;
      stack_t path;
      size_t cnt  = 0;
      size_t scnt = 0;
      
      bool visited (typename edge_t::label_value_type v) const
      {
            return pre.find(v) != pre.end();
      }
      
      bool in_component (typename edge_t::label_value_type v) const {
            return id.find(v) != id.end();
      }
      
      void init (graph_base<edge_t>& G)
      {
            typename graph_base<edge_t>::vertex_generator vg(G);
            while (!vg.iter_done()) {
                  auto v = vg.yield();
                  if (!visited(v)) scR(G, v);
            }
      }
      
      void scR(graph_base<edge_t>& G, typename edge_t::label_value_type w)
      {
            
            pre[w]     = cnt; // preorder
            cnt++;
            S.push(w);
            path.push(w);
            typename graph_base<edge_t>::adjacency_generator adj(G, w);
            while (! adj.iter_done()) {
                  auto t = adj.yield();
                  if (! visited(t)){
                        scR(G, t);
                  }
                  else if (! in_component(t)){
                        // we are on a back edge...
                        // pop all the preceding vertices..
                        while (pre[path.top()] > pre[t]) {
                              path.pop();
                        }
                  }
            }
            if (path.top() == w) {
                  path.pop();
            }
            else {
                  return;
            }
            
            {
                  typename edge_t::label_value_type t;
                  do {
                        t = S.pop();
                        id[t] = scnt;
                        mapI[scnt].push_back(t);
                        low[t] = G.V();
                  } while (t != w);
                  scnt++;
            }
      }
      
      
};

template <typename edge_t, typename algo_t=component_gabow<edge_t>>
class strong_components {
      
public:
      typedef typename edge_t::label_value_type label_t;
      strong_components(graph_base<edge_t>& G) : algo(G) {}
            
      std::ostream& pp(std::ostream& strm) {
            return algo.pp(strm);
      }
      
      strong_components(const strong_components&) = delete;
      void operator=(const strong_components&)   = delete;
      
      size_t count() const {
            return algo.count();
      }
      
      size_t operator[](label_t t) const {
            return algo.operator[](t);
      }
      
      size_t id(label_t t) const {
            return algo.operator[](t);
      }
      
      bool operator()(label_t f, label_t t)
      {
            return algo.operator()(f,t);
      }

      std::vector<label_t> operator()(size_t cid) const
      {
            return algo.operator()(cid);
      }
      
      
private:
      algo_t algo;
};


//template <typename edge_t>


template<typename graph_t, typename algo_t>
std::ostream& operator<<(std::ostream& strm, strong_components<graph_t, algo_t>& v)
{
      return v.pp(strm);
}


#endif
