//
//  graph_impl.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 4/17/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//


#include <iostream>
#include <algorithm>

#include "proto.h"

bool parse_directed(std::istream& i)
{
      std::string s;      
      if (! std::getline(i, s)) {
            return 0;
      }
      size_t spos = s.find("directed");
      size_t ln   = strlen("directed");
      if (spos == std::string::npos) {
            return 0;
      }
      std::string e = s.substr(spos + ln + 1);              
      size_t epos   = e.find(")");
      if (epos != std::string::npos) {
            e.erase(epos);
      }
      s.erase(std::remove_if(s.begin(), s.end(), isspace), s.end());
      bool state = false;
      if (s == "t") {
            return true;
      }
      return state;
}

size_t parse_size(std::istream& i)
{
      std::string s;      
      if (! std::getline(i, s)) {
            return 0;
      }
      size_t spos = s.find("vertices");
      size_t ln   = strlen("vertices");
      if (spos == std::string::npos) {
            return 0;
      }
      std::string e = s.substr(spos + ln + 1);              
      size_t epos   = e.find(")");
      if (epos != std::string::npos) {
            e.erase(epos);
      }
      size_t v = std::stoi(e);
      return v;
}

std::ostream& dump_stream(std::ostream& o, std::istream& i)
{
      std::string s;
      
                  
      while (std::getline(i, s)) {
            o << s << std::endl;
      }
      
      return o;
}
