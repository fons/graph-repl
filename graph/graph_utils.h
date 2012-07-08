//
//  graph_utils.h
//  graph-repl
//
//  Created by Alfons Haffmans on 3/22/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_graph_utils_h
#define graph_repl_graph_utils_h


#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& buff, const std::string& spliton);
double string_to_double( const std::string& s );


#endif
