//
//  regression-tests.h
//  graph-repl
//
//  Created by Alfons Haffmans on 7/9/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_regression_tests_h
#define graph_repl_regression_tests_h
#include <vector>
#include <map>
#include <iomanip>
#include "assertion.h"
#include "prompt.h"
#include "trace.h"

enum class return_t {
      SUCCESS,
      FAILURE,
      NOT_IMPLEMENTED
};

typedef std::pair<int, std::string> (*Func) (std::ostream&, int, const char*[]);
typedef std::tuple<std::string, int,std::string>   test_stack_el_t;
typedef std::vector<test_stack_el_t>  test_stack_t;

static const size_t max_tests = 100;

template<typename T>
static std::ostream& coll(std::ostream& strm, const T& el, int w)
{
      strm.setf(std::ios::left, std::ios::adjustfield);
      strm << std::setw(w);
      return strm << el;
}

static std::ostream& header(std::ostream& strm, const std::string& c1, const std::string& c2, const std::string& c3)
{
      coll(strm, c1, 30);
      coll(strm, c2, 15);
      coll(strm, c3, 30);
      return strm << std::endl;
}

static std::ostream& show(std::ostream& strm, const test_stack_el_t& el) {
      coll(strm, std::get<0>(el), 30);
      coll(strm, std::get<1>(el), 15);
      coll(strm, std::get<2>(el), 40);
      strm << std::endl;
      return strm;
}

template<int n>
struct def {
      def () {}
      def (std::string nm, Func func) {
                       set(nm, func);
      }      
      def (const def& o) = delete;
      const def& operator=(const def& o) = delete;
      static void set (std::string nm, Func func)
      {
            if (state != 0) {
                  def<n-1>::set(nm, func);
                  return;
            }
            func_ptr  = func;
            state     = 1;
            tb(nm.c_str());           
      }

      static void run(std::ostream& strm,int argc, const char* argv[]) 
      {
            run(strm, argc, argv, stack);            
      }
     
      static void run(std::ostream& strm, int argc, const char* argv[], test_stack_t& stack) 
      {
            if (state != 0) {
                  strm << "[" << n << "]***** start test : " << tag << "************" << std::endl << std::endl; 
                  try {
                        auto retval = func_ptr(strm, argc, argv);
                        stack.push_back(test_stack_el_t(std::string(tag), retval.first, retval.second));
                  }
                  catch(assertion& a) {
                        //strm <<  "caught assertion : " << a.what() << std::endl;
                        stack.push_back(test_stack_el_t(std::string(tag), -100, std::string(a.what())));
                  }
                  catch(const std::exception& e) {
                        stack.push_back(test_stack_el_t(std::string(tag), -100, std::string(e.what())));
                  }
                  catch (...) {
                        //strm  <<  "caught unknown exception exception" << std::endl;
                        stack.push_back(test_stack_el_t(std::string(tag), -100, std::string("unkown exception")));
                  }
                  strm << std::endl;
                  strm << "[" << n << "]----- finished test : " << tag << "---------------" << std::endl;
            } //end of if state != 0;           
            def<n-1>::run(strm, argc, argv, stack);            
      }

      static std::ostream& print(std::ostream& strm) {
            if (state != 0) {
                  strm << "[" << n  << "] state " << state << ", test : " << tag << std::endl;
            }
            return def<n-1>::print(strm);
      }
      ~def () {
            cleanup();
      }
      static void cleanup () {
            if (refcount == 1 && tag != nullptr) {
                  delete[] tag;
                  tag      = nullptr;
                  refcount = 0;
            }
            else {
                  refcount--;
            }
            def<n-1>::cleanup();
      }

private:
      
      enum {value = n, maxlen = 200};
      static size_t       state;
      static size_t       refcount;
      static Func         func_ptr;
      static test_stack_t stack;
      static char*        tag;
      static void tb (const char* b) {
            refcount++;
            if (tag != nullptr) {
                  return;
            }
            tag       = new char[maxlen + 1];
            std::fill(tag, tag+maxlen, '\0');
            char *dest = tag;
            const char *p = b;
            size_t l  = maxlen;            
            while (l-- && *p != '\0') {
                  *dest = *p;
                  p++;
                  dest++;
            }
      }
            
};



template<>
struct def <0>
{
      static void set (const std::string& nm, Func func) {
            
      }

      static void run(std::ostream& strm, int argc, const char* argv[], test_stack_t& stack) 
      {
            static  scoreboard_t score_board;
            strm << std::endl;
            strm << std::string(60, '+') << std::endl;
            strm << std::string(5 , '+') << " " << std::endl;
            strm << std::string(5 , '+') << " ";
            strm << "dump of the return values " << std::endl;
            strm << std::string(5 , '+') << " " << std::endl;
            strm << std::string(5 , '+') << " " << std::endl;
            strm << std::string(60, '+') << std::endl << std::endl;

            header(strm, "test case", "return code", "return message");
            header(strm, "--------------", "-----------", "--------------------------->>");
            for (auto& el : stack) {
                  show(strm, el); 
                  score_board = add_score(score_board, el);
            }
            strm << std::endl << std::endl;
         
            strm << std::string(60, '+') << std::endl;
            strm << std::string(5 , '+') << " " << std::endl;
            strm << std::string(5 , '+') << " ";
            strm << "dumping the scoreboard of return values " << std::endl;
            strm << std::string(5 , '+') << " " << std::endl;
            strm << std::string(5 , '+') << " " << std::endl;
            strm << std::string(60, '+') << std::endl << std::endl;
            show_board(strm, score_board);            
            strm << std::endl << std::endl;            
      }
      
      static std::ostream& print(std::ostream& strm) {
            strm << "state " << 0 << std::endl;           
            return strm;
      }
      static void cleanup() {
            
      }
private :
      typedef std::map<int, std::vector<std::pair<std::string, std::string>>> scoreboard_t;
      
      static scoreboard_t& add_score(scoreboard_t& score_board, const test_stack_el_t& el) {
            std::string name;
            int retcode;
            std::string msg;
            std::tie(name, retcode, msg) = el;
            if (score_board.find(retcode) == score_board.end()) {
                  std::vector<std::pair<std::string, std::string>> lst;
                  score_board.insert(std::make_pair(retcode,lst));
            }
            score_board[retcode].push_back(make_pair(name, msg));
            return score_board;
      }
      static std::ostream& show_board(std::ostream& strm, const scoreboard_t& score_board) {
            for (auto& el : score_board) {
                  strm << std::endl << "the following tests have return code : " << el.first << std::endl << std::endl;
                  strm << std::string(5, ' ');
                  coll(strm, "test case", 45);
                  coll(strm, "return message", 45);
                  strm << std::endl;
                  strm << std::string(5, ' ');
                  coll(strm, std::string(24, '-'), 45);
                  coll(strm, std::string(30, '-'), 45);
                  strm << std::endl;
                  
                  for (auto& fn : el.second) {
                        strm << std::string(5, ' ');
                        //strm << "   *) "; 
                        coll(strm, fn.first,  45);
                        coll(strm, fn.second, 45);
                        strm << std::endl;
                  }
            }
            return strm;
      }
};

template<int n>  size_t       def<n>::state      = 0;
template<int n>  Func         def<n>::func_ptr   = nullptr;
template<int n>  test_stack_t def<n>::stack;
template<int n>  char*        def<n>::tag        = nullptr;
template <int n> size_t       def<n>::refcount   = 0;

#define REGISTER_TEST(X) def<max_tests> __ ## X ## __(#X, X); \



extern void run_tests(std::ostream& strm, int argc, const char* argv[]);
extern void run_tests(int argc, const char *argv[]);
extern void run_tests();
extern std::pair<int, std::string> simple_prompt(std::ostream& strm);
extern std::pair<int, std::string> simple_return(return_t state);

#define DONE simple_return(return_t::SUCCESS)
#endif
