//
//  proto.h
//  graph-repl
//
//  Created by alfons haffmans on 9/15/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_proto_h
#define graph_repl_proto_h
#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <vector>


extern std::vector<std::string> split(const std::string& buff, const std::string& spliton);
extern double string_to_double( const std::string& s );


extern std::ostream& dump_stream(std::ostream& o, std::istream& i);
extern bool   parse_directed(std::istream& i);
extern size_t parse_size(std::istream& i);
extern std::string graphdir();

#endif
