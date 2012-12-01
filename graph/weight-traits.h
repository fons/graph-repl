//
//  weigth-traits.h
//  graph-repl
//
//  Created by alfons haffmans on 11/22/12.
//  Copyright (c) 2012 mohegan skunk works. All rights reserved.
//

#ifndef graph_repl_weight_traits_h
#define graph_repl_weight_traits_h

template <typename weight_t>
struct weight_traits_t
{
      typedef weight_t value_type;
      static const weight_t& deref(const weight_t& w) {
            return w;
      }
      static value_type make_weight (const weight_t& w) {
            return w;
      }

};

//template <typename weight_t>
//struct weight_traits_t<std::shared_ptr<weight_t>>
//{
//      typedef weight_t value_type;
//      
//      static const weight_t& deref(const std::shared_ptr<weight_t>& e) {
//            return *e;
//      }
//};

#endif
