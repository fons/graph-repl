//
//  test-queue.cpp
//  graph-repl
//
//  Created by alfons haffmans on 11/29/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//


#include "tests.h"

REGISTER_TEST(test_queue);

std::pair<int, std::string> test_queue(std::ostream& strm,int argc, const char *argv[])
{
      
      queue_t<int> s;
      
      s.put(1);
      s.put(2);
      queue_t<int> p(s);
      queue_t<int> t;
      t = s;
      strm << s << std::endl;
//      
      ASSERT(s[0] == p[0] && s[1] == p[1]);
      ASSERT(s[0] == t[0] && s[1] == t[1]);
      ASSERT(s.size() ==2);
      ASSERT(!s.empty());
      ASSERT(s.get() == 1);
      ASSERT(s.get() == 2);
      ASSERT(s.empty());
      ASSERT(s.size() == 0);
      ASSERT(!p.empty() && ! t.empty());
      return DONE;
}
