//
//  priority-queue.h
//  graph-repl
//
//  Created by alfons haffmans on 9/22/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_priority_queue_h
#define graph_repl_priority_queue_h
template <typename elem_t, typename key_t>
struct priority_queue_t
{
      virtual bool empty() const              = 0;
      virtual void insert(const elem_t& )     = 0;
      virtual elem_t getmin()                 = 0;
      virtual void lower(const elem_t& )      = 0;
      virtual void clear()                    = 0;
      virtual std::ostream& pp(std::ostream&) const = 0;
      virtual ~priority_queue_t() {};
};

template <typename key_t>
class priority_queue_base : public priority_queue_t<int, key_t>
{
public :
      explicit priority_queue_base(size_t NN, const std::vector<key_t>& a, int d=3) : a(a), pq(NN+1,0), qp(NN+1, 0), N(0), d(d) {}
      
      bool empty() const {return N == 0;}
      
      void insert (const int& v)
      {
            pq[++N] = v;
            qp[v]   = N;
            fix_up(N);
      }
      
      int getmin()
      {
            exch(1,N);
            fix_down(1, N-1);
            if (N > 0) {
                  return pq[N--];
            }
            return pq[0];
      }
      
      void lower (const int& k)
      {
            fix_up(qp[k]);
      }

      std::ostream& pp(std::ostream& strm) const
      {
            size_t line = 0;
            size_t sz = a.size();
            sz = (sz > 10) ? sz - 10: sz;
            strm << "[ ";
            for (auto& v: a)
            {
                  strm << v << ",";
                  line++;
                  if (line % 10 == 0 && line < sz) strm << std::endl;
            }
            strm << " ]" << std::endl;

            line = 0;
            sz = pq.size();
            sz = (sz > 10) ? sz - 10: sz;
            strm << "[ ";
            for (auto& v: pq)
            {
                  strm << v << ",";
                  line++;
                  if (line % 10 == 0 && line < sz) strm << std::endl;
            }
            strm << " ]" << std::endl;
            return strm;
      }
      
      void clear() {
            pq.clear();
            qp.clear();
            N = 0;
      }
      
private:
      int d;
      int N;
      std::vector<int> pq;
      std::vector<int> qp;
      const std::vector<key_t>& a;

      void exch(int i, int j)
      {
            int t     = pq[i];
            pq[i]     = pq[j];
            pq[j]     = t;
            qp[pq[i]] = i;
            qp[pq[j]] = j;
      }
      
      void fix_up(int k)
      {
            while (k > 1 && a[pq[(k+d-2)/d]] > a[pq[k]]) {
                  exch(k, (k+d-2)/d);
                  k = (k + d - 2)/d;
            }
      }
      
      void fix_down (int k, int N)
      {
            int j = 0;
            while ( (j = d*(k-1) + 2) <= N) {
                  for (int i = j + 1; (i < (j + d)) && (i <= N); i++) {
                        if (a[pq[j]] > a[pq[i]]) j = i;
                  }
                  if (! (a[pq[k]] > a[pq[j]]) ) break;
                  exch(k,j);
                  k = j;
            }
      }
};

template<typename elem_t, typename key_t>
class priority_queue : public priority_queue_t<elem_t, key_t>{

public:
      explicit priority_queue(size_t NN, const std::vector<key_t>& a, int d=3) : Q(new priority_queue_base<key_t> (NN,a,d)),I(0),Rm(NN + 1,elem_t()) {}
      
      bool empty() const { return Q->empty();}
      
      size_t operator()(const elem_t& e) {
            return get_index(e);
      }
      
      elem_t rev(const size_t e) {
            return get_revindex(e);
      }

      void insert (const elem_t& e)
      {
            Q->insert(get_index(e));
      }
      
      elem_t getmin () 
      {
            return get_revindex(Q->getmin());
      }
      
      void lower (const elem_t& e)
      {
            Q->lower(get_index(e));
      }
      std::ostream& pp(std::ostream& strm) const
      {
            strm << "elem  =>  index " << std::endl;
            for (auto& val : M) {
                  strm << " " << val.first << "   =>   " << val.second << std::endl;
            }
            strm << "index  <=  elem " << std::endl;
            size_t count = 0;
            for (auto& val : Rm) {
                  strm << " " << count << " <= " << val << std::endl;
                  count++;
                  if (count >= I) break;
                  
            }
            Q->pp(strm);
            return strm;
      }
      
      void clear()
      {
            Q->clear();
            M.clear();
            Rm.clear();
            I = zero;
      }
      
private:
      typedef int index_t;
      std::unique_ptr<priority_queue_base<key_t>> Q;
      std::map<elem_t, int> M;
      std::vector<elem_t> Rm;
      index_t I;
      const index_t zero = index_t();
      int get_index(const elem_t& e)
      {
            if (M.end() == M.find(e)) {
                  M[e]  = I;
                  Rm[I] = e;
                  I++;
            }
            return M[e];
      }
      
      elem_t get_revindex(int i)
      {
            return Rm.at(i);
      }
};

template<typename elem_t, typename key_t>
class priority_queue_kv : public priority_queue_t<elem_t, key_t>{
      
public:
      explicit priority_queue_kv(size_t NN, int d=3) : Q(new priority_queue_base<key_t> (NN,a,d)),I(0),Rm(NN + 1,elem_t()) {}
      
      bool empty() const { return Q->empty();}
      
      void insert (const elem_t& e)
      {
            Q->insert(get_index(e));
      }
      
      void push_back(const key_t v)
      {
            a.push_back(v);
      }
      
      key_t& operator[](const elem_t& e) {
            return a.at(get_index(e));
      }
      
      elem_t getmin ()
      {
            if (a.size() == 0 && M.size() == 1) {
                  return M.begin()->first;
            }
            return get_revindex(Q->getmin());
      }
      
      void lower (const elem_t& e)
      {
            Q->lower(get_index(e));
      }
      std::ostream& pp(std::ostream& strm) const
      {
            strm << "elem  =>  index " << std::endl;
            for (auto& val : M) {
                  strm << " " << val.first << "   =>   " << val.second << std::endl;
            }
            strm << "index  <=  elem " << std::endl;
            size_t count = 0;
            for (auto& val : Rm) {
                  strm << " " << count << " <= " << val << std::endl;
                  count++;
                  if (count >= I) break;
                  
            }
            Q->pp(strm);
            return strm;
      }
      
      void clear()
      {
            Q->clear();
            M.clear();
            Rm.clear();
            I = zero;
      }
      
private:
            typedef int index_t;
            std::unique_ptr<priority_queue_base<key_t>> Q;
            std::map<elem_t, int> M;
            std::vector<elem_t> Rm;
            std::vector<key_t>  a;
            index_t I;
            const index_t zero = index_t();
            int get_index(const elem_t& e)
            {
                  if (M.end() == M.find(e)) {
                        M[e]  = I;
                        Rm[I] = e;
                        I++;
                  }
                  return M[e];
            }
            
            elem_t get_revindex(int i)
            {
                  return Rm.at(i);
            }
};
template <typename key_t, typename value_t>
class priority_queue_stl {
      typedef std::pair<key_t, value_t>                 value_type;
      typedef std::shared_ptr<value_type>               value_type_ptr;
      typedef std::vector<value_type_ptr>               container_t;
      typedef std::unordered_map<key_t, value_type_ptr> map_t;
      struct sorter {
            bool operator()(const value_type_ptr& l, const value_type_ptr& r) {
                  return l->second > r->second;
            }
      };
      
      
public:
      priority_queue_stl() {}
      priority_queue_stl(const priority_queue_stl& ) = delete;
      void operator=(const priority_queue_stl& ) = delete;
      ~priority_queue_stl() {}
      
      key_t insert(const key_t k, const value_t& v)
      {
            auto p = value_type_ptr (new value_type(k, v));
            M[k]   = p;
            L.push_back(p);
            dirty  = true;
            return k;
      }
      
      value_t update(const key_t k, const value_t& v)
      {
            auto p = M[k];
            auto o = p->second;
            if (p->second != v) dirty = true;
            p->second = v;
            return o;
      }
      
      value_type getmin()
      {
            lazy_heap();
            pop_heap(L.begin(), L.end(), sorter());
            auto e = *L.back();
            L.pop_back();
            M[e.first] = std::nullptr_t();
            return e;
      }
      
      const bool empty()
      {
            return L.empty();
      }

      std::ostream& pp(std::ostream& strm) const
      {
            //lazy_heap();
            for (auto& val : L) {
                  value_type v = *val;
                  strm << "[" << v.first << " : " << v.second << "]" << std::endl;
            }
            return strm;
      }
private:
      container_t L;
      map_t  M;
      bool dirty = false;
      void lazy_heap()
      {
            if (dirty) {
                  std::make_heap(L.begin(), L.end(), sorter());
                  dirty = false;
            }
            
      }
};

template<typename elem_t, typename key_t>
std::ostream& operator<<(std::ostream& strm, const priority_queue_t<elem_t, key_t>& pq)
{
      return pq.pp(strm);
}

template<typename elem_t, typename key_t>
std::ostream& operator<<(std::ostream& strm, const priority_queue_stl<elem_t, key_t>& pq)
{
      return pq.pp(strm);
}

#endif
