//
//  interactive.cpp
//  graph-repl
//
//  Created by Alfons Haffmans on 7/25/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include <iostream>
#include "interactive.h"

std::pair<int, std::string>interactive (std::ostream& strm, const std::string& msg)
{
      strm << msg << std::endl;
      strm << std::string("-", 45) << std::endl;
            
      return std::make_pair(1, "done");
}