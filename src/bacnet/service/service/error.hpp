/**
 * ninja-wooki, is a BACnet stack C++ library
 *
 * Copyright (C) 2015 Daniel Friedrich
 *
 * This file is part of ninja-wooki.
 *
 * ninja-wooki is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * ninja-wooki is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with Mupen64PlusAE. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Daniel Friedrich
 */
#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_ERROR_HPP_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_ERROR_HPP_HPP


#include <cstdint>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <bacnet/service/service/detail/service_choice.hpp>
#include <bacnet/service/service/traits.hpp>

#include <bacnet/type/enumerated.hpp>
//see page 656 chapter 21 Error ::= SEQUENCE {

namespace bacnet { namespace service { namespace service {
struct error {

  error() = default;

  error(uint32_t device_instance) :  device_instance_range_low_limit(device_instance),
                                      device_instance_range_high_limit(device_instance) {
  }

  error(uint32_t device_instance_low, uint32_t device_instance_high) : device_instance_range_low_limit(device_instance_low),
                                                                        device_instance_range_high_limit(device_instance_high) {
  }

  bacnet::type::enumerated error_class;
  bacnet::type::enumerated error_code;

};

}}}


BOOST_FUSION_ADAPT_STRUCT(
  bacnet::service::service::who_is,
  device_instance_range_low_limit,
  device_instance_range_high_limit
)


namespace bacnet { namespace service { namespace service { namespace detail {

  using namespace bacnet::service::service;

  template<>
  struct service_choice<who_is> {
    static constexpr  uint8_t value = 8;
    typedef who_is type;
  };

  template<>
  struct is_broadcast_service<who_is> : std::true_type {
  };

}}}}


namespace bacnet { namespace service { namespace service {    
    
    template<> struct is_unconfirmed<who_is> :  boost::mpl::true_ {};
    
    template<> struct is_request<who_is> :      boost::mpl::true_ {};
    template<> struct is_response<who_is> :     boost::mpl::true_ {};    
    
}}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_ERROR_HPP_HPP
