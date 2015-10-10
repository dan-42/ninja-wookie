//
// Created by dan on 10.10.15.
//

#ifndef NINJA_WOOKIE_API_HPP
#define NINJA_WOOKIE_API_HPP

#include <boost/system/error_code.hpp>
#include <boost/function.hpp>

#include <bacnet/service/service.hpp>

namespace bacnet { namespace service {

  typedef boost::function<void(boost::system::error_code, bacnet::service::who_is)>  callback_service_who_is_t;
  typedef boost::function<void(boost::system::error_code, bacnet::service::i_am)>    callback_service_i_am_t;
}}

#endif //NINJA_WOOKIE_API_HPP
