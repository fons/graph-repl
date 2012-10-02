//
//  union-find.h
//  graph-repl
//
//  Created by alfons haffmans on 9/30/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_union_find_h
#define graph_repl_union_find_h
//weighted union find with path compression
template <typename T>
class union_find_t {
public :
      union_find_t() {};
      
      union_find_t(std::initializer_list<T> vals)
      {
            for (auto it = vals.begin(); it != vals.end(); it++) {
                  init(*it);
            }
      }
      
      template <typename C>
      union_find_t(C first, C last)
      {
            for (auto p = first; p != last; p++) {
                  init(*p);
            }
      }
      
      T find (const T& t)
      {
            init(t);
            return root(id[t]);
      }
      void operator()(const T& p, const T& q)
      {
            add_union(p,q);
      }
      
      void add_union (const T& p, const T& q)
      {
            T proot   = root(p);
            T qroot   = root(q);
            if (proot == qroot) {
                  return;
            }
            if (sizes[proot] < sizes[qroot] ) {
                  id[proot] = qroot;
                  sizes[qroot]+= sizes[proot];
                  return;
            }
            id[qroot] = proot;
            sizes[proot]+=sizes[qroot];
            count_--;
      }
      
      bool connected (const T& p, const T& q)
      {
            init(p);
            init(q);
            T rp   = root(p);
            T rq   = root(q);
            return rp == rq;
      }
      
      inline size_t count() const
      {
            return count_;
      }
      
      std::ostream& pp(std::ostream& strm) const
      {
            strm << "components : " << count() << std::endl;
            size_t count = 0;
            for (auto& val : id) {
                  strm << "(" << val.first << " : " << val.second << "), ";
                  if (++count % 10 == 0) {
                        strm << std::endl;
                  }
            }
            strm << std::endl;
            return strm;
      }
private:
      size_t count_ = 0;
      typedef std::unordered_map<T,T> cont_t;
      typedef std::unordered_map<T, size_t> size_cont_t;
      cont_t id;
      size_cont_t sizes;
      T root (const T& p)
      {
            T i = p;
            while ( i != id.at(i) ) {
                  i = id.at(i);
            }
            //path compression
            id[p] = i;
            return i;
      }
      void init (const T& t)
      {
            if (id.find(t) == id.end()) {
                  id[t]    = t;
                  sizes[t] = 1;
                  count_++;
            }
            
      }
};
template<typename T>
std::ostream& operator<<(std::ostream& strm, const union_find_t<T>& uf)
{
      return uf.pp(strm);
}


#endif
