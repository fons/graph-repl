//
//  adjacency_matrix.h
//  graph-repl
//
//  Created by Alfons Haffmans on 3/12/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_adjacency_matrix_h
#define graph_repl_adjacency_matrix_h

#include <iostream>
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>

#include "graph_utils.h"
#include "tuple.h"

class adjacency_matrix {
      
public:
      typedef double edge_weight_t;
      constexpr static const edge_weight_t null_weight = edge_weight_t();
      typedef std::tuple<size_t, size_t, edge_weight_t> edge_tuple_t;
      
      explicit adjacency_matrix(size_t size) : msize(size){init(msize);}
      explicit adjacency_matrix(std::ifstream& strm) ;
      adjacency_matrix(adjacency_matrix&& that) : msize(that.msize), m(std::move(that.m)){}
      
      ~adjacency_matrix() {}
      
      void operator()(size_t row, size_t coll, edge_weight_t w) {
            if (check (row,coll,w)) {
                  m[row][coll] = w;
            }
      }
      
      edge_weight_t operator()(size_t row, size_t coll) const {
            if (check (row,coll, 0)) {
                  return m[row][coll];
            }     
            return 0;    
      }
      
      void rm(size_t row, size_t coll ) {
            m[row][coll] = null_weight;
      }
      
      inline size_t size() const { return msize;}
      inline size_t max_size() const { return msize;}

      class adjacency_matrix_iterator {
            
      public:
            
            adjacency_matrix_iterator (size_t coll, size_t row, const adjacency_matrix& m):iter_state(coll,row),
            m(m), width(m.size()){}
                        
            inline bool operator==(const adjacency_matrix_iterator& that) {
                  return iter_state == that.iter_state;
            }
            
            inline bool operator != (const adjacency_matrix_iterator& that) {
                  return ! (*this == that);
            }
            
            adjacency_matrix::edge_tuple_t operator*() {
                  return edge_tuple_t(iter_state.row, iter_state.coll, m(iter_state.row, iter_state.coll));
            }
            
            std::pair<size_t,size_t> operator()() const {
                  return std::pair<size_t, size_t> (iter_state.row, iter_state.coll);
            }
            
            //std::pair<size_t,size_t> 
            void operator++() {
                  next(m.size(), width, iter_state);           
            }
            
            //std::pair<size_t,size_t> 
            void operator++(int) {                  
                  next(m.size(), width, iter_state); 
            }
                        
      protected:
            //typedef std::pair<size_t, size_t> iter_state_t;
            struct iter_state_struct {
                  iter_state_struct(size_t row, size_t coll) : row(row), coll(coll){}
                  size_t row;
                  size_t coll; 
                  operator std::pair<size_t, size_t>() {
                        return std::pair<size_t, size_t>(row,coll);
                  }
                  bool operator==(const iter_state_struct& that) {
                        return (row == that.row) && (coll == that.coll);
                  }
            };
            typedef iter_state_struct iter_state_t;
          
            static iter_state_struct& next_row (iter_state_struct& i, size_t step = 1) {
                  i.row += step;
                  return i;
            }

            static iter_state_struct& next_coll (iter_state_struct& i, size_t step = 1) {
                  i.coll += step;
                  return i;
            }
            virtual iter_state_t& next(size_t size, size_t width, iter_state_t& i){
                  return i;
            };            
            //this is (row, coll)
            //std::pair<size_t, size_t> iter_state;
                        iter_state_t iter_state;
            const adjacency_matrix&   m ;
            size_t                    width;      
            
            size_t iwidth(const adjacency_matrix& m) {            
                  return m.size() > 1 ? (m.size() - 1) : 0;                 
            }
            
            static size_t row(const iter_state_struct& i) {
                  return i.row;
            }
            
            static size_t coll(const iter_state_struct& i) {
                  return i.coll;
            }

      };

      class row_then_coll_iterator : public adjacency_matrix_iterator {
      public:
            row_then_coll_iterator(size_t coll, size_t row, const adjacency_matrix& m) : adjacency_matrix_iterator(coll, row, m){}
            row_then_coll_iterator(const adjacency_matrix_iterator& that) : adjacency_matrix_iterator(that)  {}            
      private:
            virtual iter_state_t& next(size_t size, size_t width, iter_state_t& i);
            
      };
      
      class coll_then_row_iterator : public adjacency_matrix_iterator {
      public:
            coll_then_row_iterator(size_t coll, size_t row, const adjacency_matrix& m) : adjacency_matrix_iterator(coll, row, m){} 
            coll_then_row_iterator(const adjacency_matrix_iterator& that) : adjacency_matrix_iterator(that)  {}
      private:
            virtual iter_state_t& next(size_t size, size_t width, iter_state_t& i);
            
      };
      
      
      typedef coll_then_row_iterator iterator;
      typedef row_then_coll_iterator iterate_rows_first;
      typedef coll_then_row_iterator iterate_colls_first;
      
      iterator begin() {
            static adjacency_matrix_iterator s(0,0,*this);
            return s;
      }
      
      iterator end() {
            // this going to be called anytime the compare is made..
            static adjacency_matrix_iterator e(msize, msize, *this);
            return e;
      }
      
private:
      
      typedef std::vector <std::vector <edge_weight_t> > coll_t;
      
      size_t msize;
      coll_t m;
      
      void init (size_t s) {            
            m = coll_t (s);
            std::fill(m.begin(), m.begin() + s, std::vector<edge_weight_t>(s, edge_weight_t()));             
      }
      
      inline bool check (size_t x, size_t y, double w) const {
            if ((x < msize) && (y < msize)) {
                  return true;
            }
            return false;
      }
      adjacency_matrix(const adjacency_matrix& that) : msize(that.msize), m(that.m){}
      const adjacency_matrix& operator=(const adjacency_matrix& that) {
            if (this == &that) return *this;
            msize = that.msize;
            m     = that.m;
            return *this;
      }

};

typedef adjacency_matrix adjacency_matrix_t;
extern std::ostream& operator<< (std::ostream &stream, adjacency_matrix_t &m);

#endif
