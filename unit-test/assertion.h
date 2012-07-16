//
//  assertion.h
//  graph-repl
//
//  Created by Alfons Haffmans on 7/15/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_assertion_h
#define graph_repl_assertion_h
#include <exception>

struct assertion : public std::exception {
      explicit assertion (const char* s) : w(s) {}
      explicit assertion (const std::string& s) : w(s){}
      virtual const char* what() const noexcept {
            return w.c_str();
      }
private:
      const std::string w;
};

struct assert_condition : public assertion {
      assert_condition (const char* c, const char* t) : cond(c), cont(t), assertion(std::string(c + std::string(" | ") + t)){}
      const char* condition () const { return cond.c_str(); }
      const char* context () const { return cont.c_str();}
      
private:
      const std::string cond;
      const std::string cont;
         
};

#define ASSERT(X)                if (! (X) ) { throw assertion (#X); } 
#define ASSERT_CONDITION(C, T)  if (! (T) ) { throw assert_condition (C, #T);}
#endif
