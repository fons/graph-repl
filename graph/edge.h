//
//  edge.h
//  graph-repl
//
//  Created by Alfons Haffmans on 3/26/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_edge_h
#define graph_repl_edge_h

#include <iostream>
#include <bitset>

#include "graph_utils.h"

template <typename label_t, typename weight_t>
struct edge_t {
      explicit edge_t(const label_t& from = label_t(), const label_t& to = label_t(), const weight_t& weight = weight_t()) : from(from),
            to(to), weight(weight){}
      label_t  from;
      label_t  to;
      weight_t weight;
      
      typedef label_t  label_value_type;
      typedef weight_t weight_value_type;

      static std::vector<edge_t<label_t, weight_t> > from_string(const std::string& s)
      {            
            std::vector<std::string> splits = split(s, "() ");
            std::vector<edge_t<label_t, weight_t> > edges;
            for (std::vector<std::string>::iterator it = splits.begin(); it != splits.end(); it = it + 3) {
                  edges.push_back(edge_t(std::stoi(*it), std::stoi(*(it + 1)), std::stod(*(it + 2))));
            }
            return edges;
      }

      static std::vector<edge_t<label_t, weight_t> >& from_string(const std::string& s, std::vector< edge_t<label_t, weight_t> >& edges)
      {            
            std::vector<std::string> splits = split(s, "() ");           
            for (std::vector<std::string>::iterator it = splits.begin(); it != splits.end(); it = it + 3) {
                  edges.push_back(edge_t(std::stoi(*it), std::stoi(*(it + 1)), std::stod(*(it + 2))));
            }
            return edges;
      }

      static std::ostream& graphviz (std::ostream& strm, const edge_t<label_t, weight_t>& edge, bool directed_edge)
      {
            
            strm << "n" << edge.from;
            if (directed_edge) {
                  strm << "->";
            }
            else {
                  strm << "--";
            }
            strm << "n" << edge.to; 
            
            if (edge.weight != 1) {
                  strm << "[label= \"w:" << edge.weight << "\"]";  
            } 
            strm << ";";            
            return strm;
            
      }
      
      static std::ostream& serialize(std::ostream& strm, const edge_t<label_t, weight_t>& edge)
      {     
            return strm << "(" << edge.from << " " << edge.to << " " << edge.weight << ")";
      }
      
      static std::vector<edge_t<label_t, weight_t> > deserialize(std::istream& strm)
      {
            std::vector<std::string> coll;
            std::vector< edge_t<label_t, weight_t> > edges;
            //std::copy(std::istream_iterator<std::string>(strm), std::istream_iterator<std::string>(), std::back_inserter(coll));
            std::string s;
            while (std::getline(strm, s)) {
                  coll.push_back(s);
            }
            
            for (std::vector<std::string>::iterator it = coll.begin(); it != coll.end(); it++){
                  edges = from_string(*it, edges);                                      
            }
            
            return edges;
      }
      
      bool operator==(const edge_t& e) const
      {
            return (from == e.from) && (to == e.to) && (weight == e.weight);
      }
      
      bool operator!=(const edge_t& e) const
      {
            return ! (*this == e);
      }
      
      bool operator<(const edge_t& e) const
      {
            if (*this == e) return false;
            return (from < e.from) || (to < e.to) || (weight < e.weight);
      }
      
      bool operator<=(const edge_t& e) const
      {
            if (*this == e) return true;
            return *this < e;
      }
      
      bool operator>(const edge_t& e) const
      {
            if (*this == e) return false;
            return !(*this < e);

      }
      
      bool operator>=(const edge_t& e) const
      {
            if (*this == e) return true;
            return !(*this < e);
            
      }
      bool is_self_loop() const
      {
            return to == from;
      }
      edge_t reverse() {
            return edge_t(to, from, weight);
      }
};

template<typename label_t, typename weight_t>
edge_t<label_t, weight_t> reverse(const edge_t<label_t, weight_t>& e)
{
      return edge_t<label_t, weight_t>(e.to, e.from, e.weight);
}

template<typename label_t, typename weight_t>
bool operator<(const edge_t<label_t, weight_t>& lhs, const edge_t<label_t, weight_t>& rhs)
{
      return lhs.operator<(rhs); // be aware of recursion 
}

template<typename label_t, typename weight_t>
std::ostream& operator<< (std::ostream &stream, const edge_t<label_t, weight_t> &edge)
{
      stream << "[" << edge.from << "," << edge.to << "," << edge.weight << "]"; 
      return stream;     
      
}


#endif
