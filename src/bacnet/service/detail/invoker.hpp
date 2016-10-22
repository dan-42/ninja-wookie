/*
 * invoker.hpp
 *
 *  Created on: Oct 22, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_SERVICE_DETAIL_INVOKER_HPP_
#define SRC_BACNET_SERVICE_DETAIL_INVOKER_HPP_

#include <cstdint>
#include <type_traits>

#include <bacnet/error/error.hpp>

#include <bacnet/service/service/traits.hpp>

namespace bacnet { namespace service { namespace detail {

using namespace bacnet::service;

template<class Service, class Enable = void>
struct invoke_handler_ {

  static constexpr bool expect_complex_response = false;

  template<typename Handler, typename T>
  static inline void invoke(Handler &&handler, bacnet::error ec, T response ) {
      handler(std::move(ec));
  }
  template<typename Handler>
  static inline void invoke(Handler &&handler, bacnet::error ec) {
    handler(std::move(ec));
  }
};


template<class Service>
struct invoke_handler_<Service, typename std::enable_if<  service::has_complex_response<typename std::decay<Service>::type >::value  >::type> {

  static constexpr bool expect_complex_response = true;

  template<typename Handler>
  static inline void invoke(Handler &&handler, bacnet::error ec ) {
    typedef pre::type_traits::function_traits<typename std::decay<Handler>::type > callback_traits;
    typedef typename callback_traits::template arg<1> arg_1_t;
    typedef typename std::decay<arg_1_t>::type service_response_type;
    service_response_type empty_resp{};
    handler(ec, empty_resp);
  }

  template<typename Handler, typename T>
  static inline void invoke(Handler &&handler, bacnet::error ec, T response ) {
    typedef pre::type_traits::function_traits<typename std::decay<Handler>::type > callback_traits;
    typedef typename callback_traits::template arg<1> arg_1_t;
    typedef typename std::decay<arg_1_t>::type service_response_type;
    auto ff = mapbox::util::get<service_response_type>(response);

    handler(ec, ff);
  }

};

}}}



#endif /* SRC_BACNET_SERVICE_DETAIL_INVOKER_HPP_ */
