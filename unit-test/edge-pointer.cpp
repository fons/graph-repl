//
//  edge-pointer.cpp
//  graph-repl
//
//  Created by alfons haffmans on 9/11/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#include "tests.h"

REGISTER_TEST(test_edge_ptr);

//template <typename T>
//static typename T::retval_t test_func(const T& val) {
//      std::cerr << edge_trait_t<T>::from(val) << std::endl;
//      return val;
//}

template <typename T>
static typename edge_trait_t<T>::value_type test_func(const T& val) {
      std::cerr << edge_trait_t<T>::from(val) << std::endl;
      return val;
}

template <typename edge_t, typename traits_t=edge_trait_t<edge_t>>
struct edge_class {
      
      void add (const edge_t& e) {
            edges.push_back(e);
            nodes.push_back(traits_t::from(e));
            if (nset.find(traits_t::to(e)) == nset.end()) {
                  nset.insert(traits_t::to(e));
            }
      }
      std::ostream& pp(std::ostream& strm) {
            for (auto& e: edges) {
                  strm << traits_t::deref(e) << std::endl;
            }
            return strm;
      }
      std::vector<edge_t> edges;
      std::vector<typename traits_t::label_value_type> nodes;
      std::set<typename traits_t::label_value_type> nset;
};

template <typename edge_t>
std::ostream& operator<<(std::ostream& strm, edge_class<edge_t>& ec)
{
      return ec.pp(strm);
}
std::pair<int, std::string> test_edge_ptr(std::ostream& strm,int argc, const char *argv[])
{
      simple_edge_t e (0,1,1);
      std::cerr << e << std::endl;
      std::cerr << "from : " <<  edge_trait_t<simple_edge_t>::from(e) << std::endl;
      ASSERT(edge_trait_t<simple_edge_t>::from(e) == 0);
      ASSERT(edge_trait_t<simple_edge_t>::to(e) == 1);
      ASSERT(edge_trait_t<simple_edge_t>::weight(e) == 1);

      simple_edge_t* ep = new simple_edge_t(2,3,1);
      std::cerr << *ep << std::endl;
      std::cerr << "from : " <<  edge_trait_t<simple_edge_t*>::from(ep) << std::endl;
      ASSERT(edge_trait_t<simple_edge_t*>::from(ep) == 2);
      ASSERT(edge_trait_t<simple_edge_t*>::to(ep) == 3);
      ASSERT(edge_trait_t<simple_edge_t*>::weight(ep) == 1);
      
      std::shared_ptr<simple_edge_t> eps (new simple_edge_t(7,8,1));
      std::cerr << *eps << std::endl;
      std::cerr << "from : " <<  edge_trait_t<std::shared_ptr<simple_edge_t>>::from(eps) << std::endl;
      std::shared_ptr<simple_edge_t> eps2;
      eps2 = test_func(eps);
      std::cerr << *eps << std::endl;
      ASSERT(edge_trait_t<std::shared_ptr<simple_edge_t>>::from(eps) == 7);
      ASSERT(edge_trait_t<std::shared_ptr<simple_edge_t>>::to(eps2) == 8);
      ASSERT(edge_trait_t<std::shared_ptr<simple_edge_t>>::weight(eps2) == 1);
      std::vector<simple_edge_t> V;
      V.push_back(simple_edge_t(1,2,1));
      edge_class<simple_edge_t> es;
      
      es.add(simple_edge_t(0,3,4));
      es.add(simple_edge_t(2,3,4));
      es.add(simple_edge_t(1,3,4));
      
      std::cerr << es << std::endl;
      
      edge_class<simple_edge_t*> ecsep;
      ecsep.add(new simple_edge_t(2,3,1));
      ecsep.add(new simple_edge_t(2,3,1));
      ecsep.add(new simple_edge_t(6,7,1));
      ecsep.add(new simple_edge_t(9,3,1));
      std::cerr << ecsep << std::endl;
      
      edge_class<std::shared_ptr<simple_edge_t>> ecseshp;
      ecseshp.add(std::shared_ptr<simple_edge_t>(new simple_edge_t(2,3,1)));
      ecseshp.add(std::shared_ptr<simple_edge_t>(new simple_edge_t(2,3,1)));
      ecseshp.add(std::shared_ptr<simple_edge_t>(new simple_edge_t(6,7,1)));
      ecseshp.add(std::shared_ptr<simple_edge_t>(new simple_edge_t(9,3,1)));
      std::cerr << ecseshp << std::endl;

      return DONE;
}
