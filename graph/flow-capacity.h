//
//  flow-capacity.h
//  graph-repl
//
//  Created by alfons haffmans on 11/13/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_flow_capacity_h
#define garaph_repl_flow_capacity_h
template <typename T>
struct capacity_flow_t {
public :
      capacity_flow_t(const T& capacity) : v_capacity (capacity), v_flow(T()){}
      capacity_flow_t() : v_capacity(T()), v_flow(T()){}
      T flow() const {
            return v_flow;
      }
      T capacity() const {
            return v_capacity;
      }
      T& flow (const T& v) {
            auto s = flow();
            v_flow = v;
            return s;
      }
      T& capacity(const T& v){
            auto s = capacity();
            v_capacity = v;
            return s;
      }
      
      bool operator==(const capacity_flow_t& rhs)
      {
            return ((capacity() == rhs.capacity()) && (flow() == rhs.flow()));
      }
      
      bool operator!=(const capacity_flow_t& rhs)
      {
            return ! operator==(rhs);
      }

private :
      T v_capacity;
      T v_flow;
};

template<typename T>

std::ostream& operator<< (std::ostream &stream, const capacity_flow_t<T>& p)
{
      stream << "[capacity : " << p.capacity() << ", flow : " << p.flow() << "]";
      return stream;
}

#endif
