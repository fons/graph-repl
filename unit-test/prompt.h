//
//  prompt.h
//  graph-repl
//
//  Created by alfons haffmans on 7/26/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_prompt_h
#define graph_repl_prompt_h

#include <iostream>
#include <string>

class prompt {
public:
      typedef std::pair<int, std::string> response_t;
      enum class response : char { SUCCESS, FAIL};
      prompt() : pr(">"){}
      prompt(const std::string& p) : pr(p){}
      prompt(const prompt&)         = delete;
      void operator=(const prompt&) = delete;
      response_t operator()(std::ostream& strm, const std::string& msg);
      response_t operator()() {
            return operator()(std::cerr);
      }
      response_t operator()(std::ostream& strm)
      {
            return operator()(strm, "please verify the expected results");
      }

protected :
      virtual bool reply_loop(std::ostream& strm, response& r);
      virtual std::pair<int, std::string> test_status(const response& resp)
      {
            if (resp == response::FAIL) {
                  return std::make_pair(0, "failed");
            }
            return std::make_pair(1, "done");
      }
private:
      const std::string pr;
      bool valid_response(const std::string& str);
      response reply_to_response(const std::string& str);
      
};

#endif
