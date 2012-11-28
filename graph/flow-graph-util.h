//
//  flow-graph-util.h
//  graph-repl
//
//  Created by alfons haffmans on 11/22/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef __graph_repl__flow_graph_util__
#define __graph_repl__flow_graph_util__

typedef capacity_flow_t<long>                                     simple_capacity_flow_t;
typedef std::shared_ptr<simple_capacity_flow_t>                   simple_capacity_flow_ptr_t;
typedef edge_t<size_t, simple_capacity_flow_ptr_t>                simple_flow_edge_t;
typedef std::shared_ptr<simple_flow_edge_t>                       simple_flow_edge_ptr_t;

typedef adjacency_list<simple_capacity_flow_ptr_t>                flow_adjacency_list_t;
typedef graph_impl<flow_adjacency_list_t, simple_flow_edge_ptr_t> flow_graph_t;

template<typename T>
std::shared_ptr<capacity_flow_t<T>> make_capacity_flow(const T& capacity)
{
      return std::shared_ptr<capacity_flow_t<T>>(new capacity_flow_t<T>(capacity));
}


template <>
struct weight_traits_t<std::shared_ptr<simple_capacity_flow_t>>
{
      typedef long value_type;
      
      static const simple_capacity_flow_t& deref(const std::shared_ptr<simple_capacity_flow_t>& e) {
            return *e;
      }
};

extern simple_flow_edge_ptr_t make_simple_flow_edge(const size_t& from, const size_t& to, const long& capacity);

extern bool change_flow(flow_graph_t& F, size_t from, size_t to, long flow);
struct flow_edge
{
private:
      typedef edge_trait_t<simple_flow_edge_ptr_t> traits;
      typedef typename traits::label_value_type label_t;
      typedef typename weight_traits_t<traits::weight_value_type>::value_type weight_t;
      //typedef typename weight_t::flow_value_type flow_t;
      typedef long flow_t;
      
public:
      flow_edge() : e(nullptr) {}
      explicit flow_edge (const simple_flow_edge_ptr_t& e) : e(e){};
      flow_edge (const flow_edge& obj) {
            e = obj.e;
      }
      const flow_edge& operator=(const flow_edge& o) {
            if (this != &o) {
                  e=o.e;
            }
            return *this;
      };
      ~flow_edge() {
            e = 0;
      }
      simple_flow_edge_ptr_t& operator->() {
            return e;
      }
      
      bool null() const {
            return e == nullptr;
      }
      
      label_t from() const { return traits::from(e); }
      label_t to() const { return traits::to(e); }
      
      flow_t cap() const {
            auto weight = traits::weight(e);
            return weight->capacity();
      }
      
      flow_t flow() const {
            auto weight = traits::weight(e);
            return weight->flow();
      }
      
      bool from (const label_t& v) const {
            return traits::is_from(e, v);
      }
      
      label_t other(const label_t& v) const {
            return from(v) ? traits::to(e) : traits::from(e);
      }
      // residual capacity into v
      flow_t capRto (int v) const {
            return from(v) ? flow() : cap() - flow();
      }
      
      //add flow to the residual graph
      
      void addflowRto(int v, flow_t d){
            auto add = from(v) ? -d : d;
            auto newflow = traits::weight(e)->flow() + add;
            traits::weight(e)->flow(newflow);
      }
      std::ostream& pp(std::ostream& strm) const {
            if (null()) {
                  return strm << "null";
            }
            return strm << *e;
      }
      private :
      simple_flow_edge_ptr_t e;
};

extern std::ostream& operator<<(std::ostream& strm, const flow_edge& fe);

#endif /* defined(__graph_repl__flow_graph_util__) */
