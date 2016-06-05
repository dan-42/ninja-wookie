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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_I_AM_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_I_AM_HPP



#include <cstdint>
#include <iostream>

#include <boost/fusion/include/define_struct.hpp>
#include <bacnet/service/service/detail/service_choice.hpp>
#include <bacnet/service/service/traits.hpp>

#include <bacnet/type/object_identifier.hpp>
#include <bacnet/common/segment.hpp>


namespace bacnet { namespace service { namespace service {

struct i_am {
    bacnet::type::object_identifier i_am_device_identifier;
    uint32_t                          max_apdu_length_accepted;
    bacnet::common::segmentation      segmentation_supported;
    uint16_t                          vendor_id;
};

static inline std::ostream& operator<<(std::ostream& os, const i_am& s) {
  os << "i_am_device_identifier: " << s.i_am_device_identifier
  << "  max_apdu_length_accepted: " << s.max_apdu_length_accepted
  << "  segmentation_supported: " << s.segmentation_supported
  << "  vendor_id: " << s.vendor_id;
  return os;
}


}}}


BOOST_FUSION_ADAPT_STRUCT(
    bacnet::service::service::i_am,
    i_am_device_identifier,
    max_apdu_length_accepted,
    segmentation_supported,
    vendor_id
)


namespace bacnet { namespace service { namespace service { namespace detail {
  using namespace bacnet::service::service;

  template<>
  struct service_choice<i_am> : std::integral_constant<uint8_t, uncomfirmed_service::i_am> {
    typedef i_am type;
  };

  template<>
  struct is_broadcast_service<i_am> : std::true_type {
  };

}}}}


namespace bacnet { namespace service { namespace service {    
    
    template<> struct is_unconfirmed<i_am> :  boost::mpl::true_ {};
    
    template<> struct is_request<i_am> :      boost::mpl::true_ {};
    template<> struct is_response<i_am> :     boost::mpl::true_ {};    
    
}}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_I_AM_HPP
