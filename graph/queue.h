//
//  queue.h
//  graph-repl
//
//  Created by alfons haffmans on 11/29/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_queue_h
#define graph_repl_queue_h

template <typename T, typename cont_t = std::deque<T>>
struct queue_t {
      queue_t() {}
      explicit queue_t(size_t N) : q(N){};
      queue_t(const queue_t& o) : q(o.q) {}
      const queue_t& operator=(const queue_t& o) {
            if (this != &o) {
                  q = o.q;
            }
            return *this;
      }
      
      void put(const T& el) {
            q.push_back(el);
      }

      T get() {
            T el = q.front();
            q.pop_front();
            return el;
      }
      
      T& operator[](size_t index) {
            return q.at(index);
      }
      
      std::ostream& pp(std::ostream& strm) const {
            size_t count = 1;
            strm << "[";
            for (auto& v : q) {
                  strm << v << ",";
                  if ( (count % 5) == 0) strm << std::endl;
                  if (count > 20) {
                        strm << ".......";
                        break;
                  }
            }
            return strm << "]";            
      }
      
      bool empty() const {
            return q.empty();
      }
      size_t size() const {
            return q.size();
      }

private :
      cont_t q;
};
template <typename T>
std::ostream& operator<<(std::ostream& strm, const queue_t<T>& q)
{
      q.pp(strm);
      return strm;
}
#endif
