//
//  graph_utils.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 3/22/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "graph.h"


std::vector<std::string> split(const std::string& buff, const std::string& spliton)
{
      
      std::vector<std::string> slist(1);
      for (std::string::const_iterator it = buff.begin(); it != buff.end(); it++) {  
            if (spliton.find(*it) == std::string::npos) {
                  slist.back().push_back(*it);
            }
            else if (slist.back().length() > 0){
                  slist.push_back(std::string());                      
            }            
      }
      if (slist.back().length() == 0) {
            slist.pop_back();
      }
      return slist;
}

double string_to_double( const std::string& s )
{
      std::istringstream i(s);
      double x;
      if (!(i >> x))
            return 0;
      return x;
} 

std::string graphdir()
{
      const char* userdir = getenv("GRAPHDIR");
      if (userdir) return std::string(userdir);
      const char *home = getenv("HOME");
      if (home) return std::string(home);
      return std::string(".");
}

