/*
 * callback_manager.hpp
 *
 *  Created on: Mar 5, 2016
 *      Author: dan
 */

#ifndef SRC_UTIL_CALLBACK_MANAGER_HPP_
#define SRC_UTIL_CALLBACK_MANAGER_HPP_


#include <vector>
#include <functional>

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/algorithm.hpp>

#include <pre/type_traits/function_traits.hpp>
#include <util/for_each.hpp>

namespace util { namespace callback {

template<typename CallbackFusionMap>
  struct callback_manager {

    template<typename... Callbacks>
    void set_callbacks(Callbacks... callbacks) {
      ::util::for_each_args([this](auto callback ) {
        typedef pre::type_traits::function_traits<decltype(callback)> callback_traits;
        typedef typename callback_traits::template arg<0> arg_0_t;
        typedef typename std::decay<arg_0_t>::type key;
        boost::fusion::at_key<key>(callback_map) = callback;
      }, callbacks...);
    }

    template<typename Type, typename... Args>
    void invoke_callback(Type t, Args... args) {
      typedef typename std::decay<Type>::type key;
      if(boost::fusion::at_key<key>(callback_map)) {
        boost::fusion::at_key<key>(callback_map)(t, args...);
      }
    }

  private:
    CallbackFusionMap callback_map;
  };

}}
#endif /* SRC_UTIL_CALLBACK_MANAGER_HPP_ */
