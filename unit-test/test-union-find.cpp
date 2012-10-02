//
//  test-union-find.cpp
//  graph-repl
//
//  Created by alfons haffmans on 9/30/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_union_find);

std::pair<int, std::string> test_union_find(std::ostream& strm,int argc, const char *argv[])
{
      union_find_t<typename simple_edge_t::label_value_type> uf0;
      std::vector<typename simple_edge_t::label_value_type> labels = {2,45,78,90,34,12,29};
      union_find_t<typename simple_edge_t::label_value_type> uf1 = {2,45,78,90,34,12,29};
      union_find_t<typename simple_edge_t::label_value_type> uf2(labels.begin(), labels.end());

      for (auto& val : labels) {
            ASSERT(val == uf0.find(val));
            ASSERT(val == uf1.find(val));
            ASSERT(val == uf2.find(val));
      }
      ASSERT(uf0.count() == labels.size());
      uf0(2,45);
      uf0(2,78);
      uf0(45,34);
      uf0(34,90);
      uf0(90, 12);
      for (auto& v : labels) {
            if (v == 29) continue;
            ASSERT(!uf0.connected(29, v));
      }
      for (auto& v : labels) {
            for (auto& w : labels) {
                  if (v == 29 && w == 29) {
                        ASSERT(uf0.connected(w, v));
                        continue;
                  }
                  if (v == 29 || w == 29) {
                        ASSERT(!uf0.connected(w, v));
                        continue;
                  }
                  ASSERT(uf0.connected(w, v));
            }
      }
      ASSERT(uf0.count() == 2);
      strm << uf0 << std::endl;
      strm << "--------------------------" << std::endl;
      return DONE;
}