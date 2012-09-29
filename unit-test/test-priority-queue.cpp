//
//  test-priority-queue.cpp
//  graph-repl
//
//  Created by alfons haffmans on 9/23/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_priority_queue_base_1);
REGISTER_TEST(test_priority_queue_base_2);
REGISTER_TEST(test_priority_queue_1);
REGISTER_TEST(test_priority_queue_2);
REGISTER_TEST(test_priority_queue_kv_1);
REGISTER_TEST(test_priority_queue_kv_2);

std::pair<int, std::string> test_priority_queue_base_1(std::ostream& strm,int argc, const char *argv[])
{
      std::vector<double> wt;
      priority_queue_base<double> pq(10, wt);
      strm << "min : " << pq.getmin() << std::endl;
      ASSERT(pq.getmin() == 0);
      ASSERT(pq.empty() == true);
      strm << pq << std::endl;
      
      int w  = 0;
      double P = 0.50;
      wt.push_back(P);
      pq.insert(w);
      
      w = 1;
      P = 0.60;
      wt.push_back(P);
      pq.insert(w);

      w = 2;
      P = 0.7;
      wt.push_back(P);
      pq.insert(w);
      
      w = 3;
      P = 0.3;
      wt.push_back(P);
      pq.insert(w);

      w = 2;
      wt[w] = 0.90;
      pq.lower(w);
      strm << pq << std::endl;
      for (auto& val : wt) {
            strm << val << ",";
      }
      strm << std::endl;
      strm << "--------------------------------" << std::endl;
      ASSERT(pq.empty() == false);
      auto min = pq.getmin();
      strm << "min : " << min << std::endl;
      ASSERT(min == 3);

      min = pq.getmin();
      ASSERT(min == 0);
      ASSERT(pq.empty() == false);
      
      min = pq.getmin();
      strm << "min : " << min << std::endl;
      ASSERT(min == 1);
      ASSERT(pq.empty() == false);

      min = pq.getmin();
      strm << "min : " << min << std::endl;
      ASSERT(min == 2);
      ASSERT(pq.empty() == true);

      return DONE;
}
std::pair<int, std::string> test_priority_queue_base_2(std::ostream& strm,int argc, const char *argv[])
{
      std::vector<double> wt;
      priority_queue_base<double> pq(10, wt);
      std::vector<int> w    = {0,    1,    2,    3,    4,    5,    6,    7,    8,    9   };
      std::vector<double> P = {0.90, 0.80, 0.070, 0.60, 0.50, 0.840, 0.35, 0.30, 0.28, 0.15};
      ASSERT(w.size() == P.size());
      for (size_t i = 0; i < w.size(); i++) {
            wt.push_back(P.at(i));
            pq.insert(w.at(i));
      }
      double old_min_value = -1;
      
      while (! pq.empty()) {
            auto min = pq.getmin();
            double min_value = wt.at(min);
            strm << min << " : " << min_value << std::endl;
            if (old_min_value > -1) {
                  ASSERT(old_min_value < min_value);
            }
            old_min_value = min_value;
      }
      for (size_t i = 0; i < w.size(); i++) {
            wt.push_back(P.at(i));
            pq.insert(w.at(i));
      }

      old_min_value = -1;
      wt[5] = 0.009;
      pq.lower(5);
      wt[8] = 0.002;
      pq.lower(8);
      wt[0] = 0.03;
      pq.lower(0);
      strm << "----------------" << std::endl;
      while (! pq.empty()) {
            auto min = pq.getmin();
            double min_value = wt.at(min);
            strm << min << " : " << min_value << std::endl;
            if (old_min_value > -1) {
                  ASSERT(old_min_value < min_value);
            }
            old_min_value = min_value;
      }

      return DONE;
}


std::pair<int, std::string> test_priority_queue_1(std::ostream& strm,int argc, const char *argv[])
{
      std::vector<double> wt;
      priority_queue<typename simple_edge_t::label_value_type, double> pq(10, wt);
      ASSERT(pq.getmin() == 0);
      ASSERT(pq.empty() == true);
      //strm << pq << std::endl;
      size_t elem_count = 0;
      simple_edge_t::label_value_type w  = 10;
      double P = 0.50;
      wt.push_back(P);
      pq.insert(w);
      elem_count++;
      
      w = 1;
      P = 0.60;
      wt.push_back(P);
      pq.insert(w);
      elem_count++;
      
      w = 2;
      P = 0.7;
      wt.push_back(P);
      pq.insert(w);
      elem_count++;
      
      w = 5;
      P = 0.3;
      wt.push_back(P);
      pq.insert(w);
      elem_count++;
      
      w = 2;
      wt[w] = 0.90;
      pq.lower(w);
      strm << pq << std::endl;
      for (auto& val : wt) {
            strm << val << ",";
      }
      strm << std::endl;
      strm << "--------------------------------" << std::endl;
      ASSERT(pq.empty() == false);
      auto min = pq.getmin();
      elem_count--;
      strm << "min : " << min << " : " << pq(min) << " : " << wt[pq(min)] << std::endl;
      ASSERT(min == 5);
      ASSERT(pq.empty() == false);
      
      min = pq.getmin();
      elem_count--;
      strm << "min : " << min << " : " << pq(min) << " : " << wt[pq(min)] <<std::endl;
      ASSERT(min == 10);
      ASSERT(pq.empty() == false);
      
      min = pq.getmin();
      elem_count--;
      strm << "min : " << min <<  " : " << pq(min) << " : " << wt[pq(min)] <<std::endl;
      ASSERT(min == 1);
      ASSERT(pq.empty() == false);
      
      min = pq.getmin();
      elem_count--;
      strm << "min : " << min <<  " : " << pq(min) << " : " << wt[pq(min)] <<std::endl;
      ASSERT(min == 2);
      ASSERT(pq.empty() == true);
      ASSERT(elem_count == 0);
      return DONE;
}

std::pair<int, std::string> test_priority_queue_2(std::ostream& strm,int argc, const char *argv[])
{
      std::vector<double> wt;
      priority_queue<typename simple_edge_t::label_value_type, double> pq(10, wt);
      std::vector<typename simple_edge_t::label_value_type> w = {10, 78, 56, 23, 12, 49, 81};
      std::vector<double> P = {0.10, 0.78, 0.56, 0.23, 0.12, 0.49, 0.81};
      ASSERT(P.size() == w.size());
      for( size_t i = 0; i < P.size(); i++) {
            wt.push_back(P.at(i));
            pq.insert(w.at(i));
      }
      
      double old_min_value = -1;
      
      while (! pq.empty()) {
            auto min = pq.getmin();
            double min_value = wt.at(pq(min));
            strm << min << " : " << pq(min) << " : " << min_value << std::endl;
            if (old_min_value > -1) {
                  ASSERT(old_min_value < min_value);
            }
            old_min_value = min_value;
      }

      for (size_t i = 0; i < w.size(); i++) {
            //wt.push_back(P.at(i));
            pq.insert(w.at(i));
      }
      

      old_min_value = -1;
      
      wt[pq(81)] = 0.009;
      pq.lower(81);
      
      wt[pq(23)] = 0.002;
      pq.lower(23);
      
      wt[pq(56)] = 0.99;
      pq.lower(56);
      strm << "----------------" << std::endl;
      while (! pq.empty()) {
            auto min = pq.getmin();
            double min_value = wt.at(pq(min));
            strm << min << " : " << pq(min) << " : " << min_value << std::endl;
            if (old_min_value > -1) {
                  ASSERT(old_min_value < min_value);
            }
            old_min_value = min_value;
      }
  
      
      return DONE;
}


std::pair<int, std::string> test_priority_queue_kv_1(std::ostream& strm,int argc, const char *argv[])
{
      
      priority_queue_kv<typename simple_edge_t::label_value_type, double> pq(15);
      //std::vector<typename simple_edge_t::label_value_type> w = {20,21,45,33,1,4,56,78,3,2,90,34,25, 99};
      //std::vector<double> P                                   = {0.20, 0.21, 0.45, 0.33,0.1,0.40,0.56,0.78,0.3,0.2,0.90,0.34,0.25,0.99};
      //ASSERT(w.size() == P.size());
      pq.insert(20);
      pq.push_back(0.20);
      
      pq.insert(40);
      pq.push_back(0.40);

      pq.insert(5);
      pq.push_back(0.05);
      
      pq.insert(10);
      pq.push_back(0.10);
      
      
      auto min = pq.getmin();
      std::cerr << " min : " << min << " : " << pq[min] << std::endl;
      ASSERT(min == 10);
      ASSERT(pq[min] == 0.10);
      
      pq.insert(56);
      pq.push_back(0.90);
      
      pq[56] = 0.01;
      pq.lower(56);
      min = pq.getmin();
      std::cerr << " min : " << min << " : " << pq[min] << std::endl;
      ASSERT(min == 56);
      ASSERT(pq[min] == 0.010);
      
      return DONE;
}

std::pair<int, std::string> test_priority_queue_kv_2(std::ostream& strm,int argc, const char *argv[])
{
      
      priority_queue_kv<typename simple_edge_t::label_value_type, double> pq(25);
      std::vector<typename simple_edge_t::label_value_type> w = {20,21,45,33,1,4,56,78,3,2,90,34,25, 99, 81, 23};
      std::vector<double> P                                   = {0.20, 0.21, 0.45, 0.33,0.1,0.040,0.56,0.78,0.03,0.02,0.90,0.34,0.25,0.99, 0.81, 0.23};
      ASSERT(w.size() == P.size());
      
      
      for( size_t i = 0; i < P.size(); i++) {
            pq.push_back(P.at(i));
            pq.insert(w.at(i));
      }
      double old_min_value = -1;
      
      while (! pq.empty()) {
            auto min = pq.getmin();
            double min_value = pq[min];
            strm << min <<  " :: " << min_value << std::endl;
            if (old_min_value > -1) {
                  //strm << " old : " << old_min_value << " : " << min_value << std::endl;
                  ASSERT(old_min_value < min_value);
            }
            old_min_value = min_value;
      }
      
      for (size_t i = 0; i < w.size(); i++) {
            pq.insert(w.at(i));
      }
      
      
      old_min_value = -1;
      
      pq[81] = 0.009;
      pq.lower(81);
      
      pq[23] = 0.002;
      pq.lower(23);
      
      pq[56] = 0.99111;
      
      pq.lower(56);
      strm << "-------------------------------------------" << std::endl;
      while (! pq.empty()) {
            auto min = pq.getmin();
            double min_value = pq[min];
            strm << min << " : " << min_value << std::endl;
            if (old_min_value > -1) {
                  ASSERT(old_min_value < min_value);
            }
            old_min_value = min_value;
      }
      
      
      return DONE;
}

std::pair<int, std::string> test_priority_queue_kv_3(std::ostream& strm,int argc, const char *argv[])
{
      
      priority_queue_kv<typename simple_edge_t::label_value_type, double> pq(25);
      std::vector<typename simple_edge_t::label_value_type> w = {7,5,6,2,1};
      std::vector<double> P                                   = {0.31,0.60,0.51,0.29,0.32};
      pq.insert(0);
      pq.push_back(10000);
      ASSERT(! pq.empty());
      auto v = pq.getmin();
      ASSERT(v == 0 && pq[v] == 10000);
      
      for( size_t i = 0; i < P.size(); i++) {
            pq.push_back(P.at(i));
            pq.insert(w.at(i));
      }
//      double old_min_value = -1;
//      
//      while (! pq.empty()) {
//            auto min = pq.getmin();
//            double min_value = pq[min];
//            strm << min <<  " :: " << min_value << std::endl;
//            if (old_min_value > -1) {
//                  //strm << " old : " << old_min_value << " : " << min_value << std::endl;
//                  ASSERT(old_min_value < min_value);
//            }
//            old_min_value = min_value;
//      }
      strm << pq << std::endl;
      strm << "----------------------------------------" << std::endl;
      return DONE;
}


