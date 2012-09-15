//
//  prompt.cpp
//  graph-repl
//
//  Created by alfons haffmans on 7/27/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//


#include "prompt.h"
bool prompt::valid_response(const std::string& str)
{
      
      if (str[0] == '\n') {
            return true;
      }

      if (str[0] == 'Y' || str[0] == 'y') {
            return true;
      }

      if (str[0] == 'N' || str[0] == 'n') {
            return true;
      }

      return false;
}

prompt::response prompt::reply_to_response(const std::string& str)
{
      if (str[0] == '\n') {
            return response::SUCCESS;
      }
      
      if (str[0] == 'Y' || str[0] == 'y') {
            return response::SUCCESS;
      }
      
      if (str[0] == 'N' || str[0] == 'n') {
            return response::FAIL;
      }
      return response::FAIL;
}

bool prompt::reply_loop(std::ostream& strm, prompt::response& resp)
{
      std::string line;
      static size_t count = 1;
      
      strm << count << " please respond Yy/Nn >> ";
      std::cin >> line;
      strm << "++ " << line << std::endl;
      count++;
      if (valid_response(line)) {
            resp = reply_to_response(line);
            return false;
      }
      if (count > 40) {
            resp = prompt::response::FAIL;
            return false;
      }
      return true;
}

prompt::response_t prompt::operator()(std::ostream& strm, const std::string& msg)
{
      prompt::response response;
      do {
            strm << msg << std::endl;
      } while (reply_loop(strm, response));
      return test_status(response);
}
