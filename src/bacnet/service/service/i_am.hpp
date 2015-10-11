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

#include <boost/fusion/include/define_struct.hpp>
#include <bacnet/service/service/detail/service_choice.hpp>


#include <bacnet/common/object_identifier.hpp>
#include <bacnet/common/segment.hpp>



BOOST_FUSION_DEFINE_STRUCT(
    (bacnet)(service)(service), i_am,
    (bacnet::common::object_identifier, i_am_device_identifier)
    (uint32_t, max_apdu_length_accepted)
    (bacnet::common::segmentation, segmentation_supported)
    (uint16_t, vendor_id)
)

namespace bacnet { namespace service { namespace service { namespace detail {
  using namespace bacnet::service::service;

  template<>
  struct service_choice<i_am> {
    static constexpr uint8_t value = 0x00;
    typedef i_am type;
  };

  template<>
  struct is_broadcast_service<i_am> : std::true_type {
  };

}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_I_AM_HPP
