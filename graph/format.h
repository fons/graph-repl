//
//  format.h
//  graph-repl
//
//  Created by alfons haffmans on 11/4/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_format_h
#define graph_repl_format_h

template<typename T>
std::ostream& column(std::ostream& strm, const T& el, int w)
{
      strm.setf(std::ios::left, std::ios::adjustfield);
      strm << std::setw(w);
      return strm << el;
}


#endif
