//
//  test-stack.cpp
//  graph-repl
//
//  Created by alfons haffmans on 9/2/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_stack);

std::pair<int, std::string> test_stack(std::ostream& strm,int argc, const char *argv[])
{

      stack<int> s;
     
      s.push(1);
      s.push(2);
      stack<int> p(s);
      stack<int> t;
      t = s;
      strm << s << std::endl;
      
      ASSERT(s[0] == p[0] && s[1] == p[1]);
      ASSERT(s[0] == t[0] && s[1] == t[1]);
      ASSERT(s.size() ==2);
      ASSERT(!s.empty());
      ASSERT(s.pop() == 2);
      ASSERT(s.pop() == 1);
      ASSERT(s.empty());
      ASSERT(s.size() == 0);
      ASSERT(!p.empty() && ! t.empty());
      return DONE;
}