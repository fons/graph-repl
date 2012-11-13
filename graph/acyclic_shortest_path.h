//
//  acyclic_shortest_path.h
//  graph-repl
//
//  Created by alfons haffmans on 11/2/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_acyclic_shortest_path_h
#define graph_repl_acyclic_shortest_path_h

template<typename traits>
struct longest_path
{
      static bool update(const typename traits::weight_value_type& lhs, const typename traits::weight_value_type& rhs) {
            std::cerr << lhs << ":" << rhs << std::endl;
            return lhs < rhs;
      }
      
      static const typename traits::weight_value_type sentinel; 
};

template<typename traits>
const typename traits::weight_value_type longest_path<traits>::sentinel = typename traits::weight_value_type();
//template<typename traits>
//const typename traits::weight_value_type longest_path<traits>::sentinel = std::numeric_limits<typename traits::weight_value_type>::max();
//

template<typename edge_t, typename calc_t, typename traits=edge_trait_t<edge_t>>
struct dag_all_paths
{
private:
      typedef graph_base<edge_t,traits>                      graph_t;
      typedef typename traits::label_value_type              label_t;
      typedef typename traits::weight_value_type             weight_t;
      typedef typename std::unordered_map<label_t, label_t>  label_cont_t;
      typedef typename std::unordered_map<label_t, weight_t> value_cont_t;
      
public:
      dag_all_paths(graph_base<edge_t, traits>& G) : G(G), initial(weight_t()) {
            init(G);
      }
      
      std::ostream& pp(std::ostream& strm) {
            column(strm, "vertex ,",   8);
            column(strm, "distance ,", 10);
            column(strm, "predecessor", 12);
            strm << std::endl;
            for (auto& v : vert) {
                  column(strm, v, 7);
                  strm <<",";
                  column(strm, mdist[v], 9);
                  strm << ",";
                  column(strm, mpred[v], 12);
                  strm << std::endl;
            }
            return strm;
      }
      std::pair<weight_t, bool> dist(const label_t& to) {
            auto it = mdist.find(to);
            if (it == mdist.end()) return std::make_pair(weight_t(), false);
            return std::make_pair(it->second, true);
      }
      
      std::pair<label_t, bool> pred(const label_t& to) {
            auto it = mpred.find(to);
            if (it == mpred.end()) return std::make_pair(label_t(), false);
            return std::make_pair(it->second, true);
      }

private:
      const weight_t initial;
      label_cont_t   mpred;
      value_cont_t   mdist;
      graph_base<edge_t, traits>& G;
      std::vector<label_t> vert;
      void init(graph_base<edge_t, traits>& G)
      {
            typename graph_t::vertex_generator wg(G);
            while (! wg.iter_done()) {
                  auto v = wg.yield();
                  mdist[v] = 0; //calc_t::sentinel;
                  mpred[v] = v;
            }
            
            topological_sort<sparse_graph_t> rts(G);
            vert = rts.order();
            for (auto& v : vert){
                  typename graph_t::adjacency_edge_generator adj(G, v);
                  while (! adj.iter_done()) {
                        auto n = adj.yield();
                        auto from   = traits::from(n);
                        auto to     = traits::to(n);
                        auto w      = traits::weight(n);
                        if (mdist[from] == calc_t::sentinel) {
                              mdist[from] = initial;
                        }
                        auto newlen = mdist[from] + w;
                        
                        if (calc_t::update(mdist[to], newlen)) {
                              mdist[to] = newlen;
                              mpred[to] = from;
                        }
                  }
            }
      }
};
template<typename edge_t, typename traits=edge_trait_t<edge_t>>
struct dag_all_longest_paths : public dag_all_paths<edge_t, longest_path<edge_trait_t<edge_t>>, traits>
{
      dag_all_longest_paths(graph_base<edge_t>& G) : dag_all_paths<edge_t, longest_path<edge_trait_t<edge_t>>, traits>(G) {}
};
//---------

//template<typename edge_t, typename traits=edge_trait_t<edge_t>>
//struct dag_all_longest_paths
//{
//private:
//      typedef graph_base<edge_t,traits>                      graph_t;
//      typedef typename traits::label_value_type              label_t;
//      typedef typename traits::weight_value_type             weight_t;
//      typedef typename std::unordered_map<label_t, label_t>  label_cont_t;
//      typedef typename std::unordered_map<label_t, weight_t> value_cont_t;
//
//public:
//      dag_all_longest_paths(graph_base<edge_t, traits>& G ) : G(G){
//            init(G);
//      }
//      
//      std::ostream& pp(std::ostream& strm) {
//            for (auto& v : mdist) {
//                  strm << v << std::endl;
//            }
//            
//            for (auto& v : mpred) {
//                  strm << v << std::endl;
//            }
//            return strm;
//      }
//      
//private:
//      
//      label_cont_t  mpred;
//      value_cont_t mdist;
//      graph_base<edge_t, traits>& G;
//
//      void init(graph_base<edge_t, traits>& G)
//      {
//            typename graph_t::vertex_generator wg(G);
//            while (! wg.iter_done()) {
//                  auto v = wg.yield();
//                  mdist[v] = weight_t(); //std::numeric_limits<double>::max();
//                  mpred[v] = v;
//            }
//            
//            topological_sort<sparse_graph_t> rts(G);
//            auto vert = rts.order();
//            for (auto& v : vert){
//                  typename graph_t::adjacency_edge_generator adj(G, v);
//                  while (! adj.iter_done()) {
//                        auto n = adj.yield();
//                        auto from   = traits::from(n);
//                        auto to     = traits::to(n);
//                        auto w      = traits::weight(n);
//                        auto newlen = mdist[from] + w;
//                        if (mdist[to] < newlen) {
//                              mdist[to] = newlen;
//                              mpred[to] = from;
//                        }
//                  }
//            }
//      }
//};

template<typename edge_t, typename traits=edge_trait_t<edge_t>>
struct dag_all_shortest_paths
{
private:
      typedef graph_base<edge_t,traits>                      graph_t;
      typedef typename traits::label_value_type              label_t;
      typedef typename traits::weight_value_type             weight_t;
      typedef typename std::unordered_map<label_t, label_t>  label_cont_t;
      typedef typename std::unordered_map<label_t, weight_t> value_cont_t;
      
public:
      dag_all_shortest_paths(graph_base<edge_t, traits>& G ) : G(G){
            init(G);
      }
      
      std::ostream& pp(std::ostream& strm) {
            for (auto& v : mdist) {
                  strm << v << std::endl;
            }
            
            for (auto& v : mpred) {
                  strm << v << std::endl;
            }
            return strm;
      }
      
private:
      
      label_cont_t  mpred;
      value_cont_t mdist;
      graph_base<edge_t, traits>& G;
      
      void init(graph_base<edge_t, traits>& G)
      {
            typename graph_t::vertex_generator wg(G);
            while (! wg.iter_done()) {
                  auto v = wg.yield();
                  mdist[v] = std::numeric_limits<weight_t>::max();
                  mpred[v] = v;
            }
            
            topological_sort<sparse_graph_t> rts(G);
            auto vert = rts.order();
            for (auto& v : vert){
                  typename graph_t::adjacency_edge_generator adj(G, v);
                  while (! adj.iter_done()) {
                        auto n = adj.yield();
                        auto from   = traits::from(n);
                        auto to     = traits::to(n);
                        auto w      = traits::weight(n);
                        if (mdist[from] == std::numeric_limits<double>::max()) {
                              mdist[from] = weight_t();
                        }
                        auto newlen = mdist[from] + w;
                        if (mdist[to] > newlen) {
                              mdist[to] = newlen;
                              mpred[to] = from;
                        }
                  }
            }
      }
};


#endif
