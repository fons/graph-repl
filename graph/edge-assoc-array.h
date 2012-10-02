//
//  assoc-array.h
//  graph-repl
//
//  Created by alfons haffmans on 9/29/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_edge_assoc_array_h
#define graph_repl_edge_assoc_array_h

//see josuttis : the c++ standard library : section 7.9.2
template <typename T>
inline void hash_combine (size_t& seed, const T& val)
{
      seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

template<typename T>
inline void hash_val(size_t& seed, const T& val)
{
      hash_combine(seed, val);
}
template <typename T, typename... Types>
inline void hash_val(size_t& seed, const T& val, const Types&... args )
{
      hash_combine(seed, val);
      hash_val(seed, args...);
}
template<typename... Types>
inline size_t hash_val (const Types&... args)
{
      size_t seed = 0;
      hash_val(seed, args...);
      return seed;
}
template <typename edge_t, typename traits = edge_trait_t<edge_t>>
struct edge_hash_t
{
      std::size_t operator()(const edge_t& e) const
      {
            return hash_val(traits::from(e), traits::to(e), traits::weight(e), traits::salt);
      }
};

template<typename edge_t, typename traits = edge_trait_t<edge_t>>
class edge_set_t {
public :
      edge_set_t() : set(new set_t()) {}
      
      edge_set_t(const edge_set_t& obj) {
            set = obj.set;
      }

      edge_set_t operator=(const edge_set_t& obj)
      {
            if (&obj == this) return this;
            set = obj.set;
      }
      
      ~edge_set_t() {}
      
      
      
private :
      typedef std::unordered_set<edge_t, edge_hash_t<edge_t, traits>> set_t;
      std::shared_ptr<set_t> set;
};

#endif
