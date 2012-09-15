//
//  degree.h
//  graph-repl
//
//  Created by Alfons Haffmans on 5/14/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_degree_h
#define graph_repl_degree_h

#include <vector>
#include <map>
#include "graph_base.h"


template<typename edge_t>
struct degree {
private:
      typedef typename edge_t::label_value_type edge_value_t;
      typedef std::vector<typename edge_t::label_value_type> cont_t;
      typedef typename std::vector<typename edge_t::label_value_type>::iterator cont_iter_t;
public:      
      degree(graph_base<edge_t>& g) :graph(g),deg(g.V(), typename edge_t::label_value_type()) {
            construct();
      }
      size_t operator[](size_t n) {
            if (n > size) return 0;
            return deg[n];
      }
      std::ostream& pp(std::ostream& strm) const {
            size_t count = 0;
            strm << "index :degree" << std::endl;
            for (auto it =deg.begin() ;it != deg.end(); it++) {
                  strm << count << " : " <<  *it << std::endl;
                  count++;
            }
            return strm;
      }
      
      class iterator_p {
            public :
            iterator_p(){}
            iterator_p(cont_iter_t itt) : it(itt){}
            iterator_p(const iterator_p& obj) : it(obj.it){}
            iterator_p& operator=(const iterator_p& obj) {
                  if (this != &obj) {
                        it = obj.it;
                  }
                  return *this;
            }
            void operator++() {
                  it++;
            }
            void operator++(int v) {
                  ++it;
            }
            bool operator==(const iterator_p& obj) {
                  return it == obj.it;
            }
            bool operator!=(const iterator_p& obj) {
                  return ! (*this == obj);
            }
            edge_value_t operator*() {
                  return *it;
            }
            private :
                  cont_iter_t it;                  
      };
      iterator_p begin() {            
            return iterator_p(deg.begin());;
      }      
      degree::iterator_p end() {            
            return iterator_p(deg.end());
      }
      friend class iterator_p;
      
private:
      cont_t deg;
      size_t size;
      graph_base<edge_t>& graph;
      void construct() {
            for (typename graph_base<edge_t>::iterator it = graph.begin(); it != graph.end(); it++) {
                  deg[(*it).from]++;
                  if (graph.is_directed()) {
                        deg[(*it).to]++;
                  }
            }           
      }
};
template <typename edge_t>
std::ostream& operator<<(std::ostream& strm, const degree<edge_t>& d) {
      return d.pp(strm);
}
//typedef typename std::map<typename edge_t::label_value_type, size_t> degree_distribution_t;

template <typename edge_t>
struct degree_distribution  {
private :
      degree<edge_t>& D;
      typename std::map<typename edge_t::label_value_type, size_t> cont_t;
public :
      degree_distribution(degree<edge_t>& d) : D(d) {
            construct();
      }
      size_t operator[](typename edge_t::label_value_type& val) {
            return M[val];
      }
      std::ostream& pp(std::ostream& strm) const {
            strm << "degree : count" << std::endl;
            for (auto it =M.begin() ;it != M.end(); it++) {
                  strm << it->first << " : " <<  it->second << std::endl;
            }
            return strm;
      }

private :
      std::map<typename edge_t::label_value_type, size_t> M;
      void construct() {
            for (auto it = D.begin(); it != D.end(); it++) {
                  if (M.find(*it) == M.end() ) {
                        M.insert(std::make_pair(*it, 0));
                  }
                  M[*it]++;
            }
      }
};

template<typename edge_t>
std::ostream& operator<<(std::ostream& strm, const degree_distribution<edge_t>& ds) {
      return ds.pp(strm);
}

#endif
