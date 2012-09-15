//
//  graph_gen.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 5/15/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include <iostream>
#include "graph.h"
#include "graph_gen.h"

#include <random>
#include <vector>
#include <map>

size_t random_number(size_t max)
{
      
      std::default_random_engine dre(static_cast<int>(time(0)));
      std::uniform_int_distribution<size_t> di (0, 10);      
      return di(dre);     
}
typedef std::pair<size_t,size_t> point_t;

static size_t safediff(size_t a, size_t b)
{
      return (a > b) ? a - b : b - a;
}
static size_t m_dist(const point_t& l, const point_t& r)
{      
      return (safediff(l.first, r.first) + safediff(l.second, r.second));
}

std::vector <simple_edge_t> random_plane_edges(size_t R, size_t N)
{
      std::default_random_engine dre(static_cast<int>(time(0)));
      std::uniform_int_distribution<size_t> di (0, N);  
      size_t count = 0;
      std::set<point_t> points;
      std::map<point_t, size_t> index;
      while (count < N) {
            auto p = std::make_pair(di(dre), di(dre));
            if (points.find(p) == points.end()) {
                  points.insert(p);
                  index.insert(std::make_pair(p, count));
                  count++;
            }
      }
      std::map<std::pair<size_t, size_t>, std::vector<point_t>> M;
      for( auto point : points ) {
            if (M.find(point) == M.end()) {
                  M.insert(std::make_pair(point, std::vector<point_t>()));
            }
            for (auto mip = M.begin(); mip != M.end(); mip++) {                  
                  if ((mip->first != point) && (m_dist(point, mip->first) < R)) {                       
                        mip->second.push_back(point);
                  }
            }
      }
      std::vector<simple_edge_t> edges;
      for (auto mip = index.begin(); mip != index.end(); mip++) {            
            std::vector<point_t>& points = M.at(mip->first);
            for (auto pip = points.begin(); pip != points.end(); pip++) {
                  size_t val = index.at(*pip);
                  edges.push_back(simple_edge_t(mip->second, val, 1));
            }
      }
      return edges;
}

