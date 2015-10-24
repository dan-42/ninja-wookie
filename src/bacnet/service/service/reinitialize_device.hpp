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
#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_REINITIALIZE_DEVICE_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_REINITIALIZE_DEVICE_HPP


#include <cstdint>

#include <boost/fusion/include/define_struct.hpp>
#include <bacnet/service/service/detail/service_choice.hpp>

BOOST_FUSION_DEFINE_STRUCT(
  (bacnet)(service)(service), reinitialize_device,
  (uint32_t, reinitialize_state_of_device)
  (std::string, passowrd)
)


namespace bacnet { namespace service { namespace service {
  namespace reinitialized_state_of_device {
      uint32_t coldstart    = 0;
      uint32_t warmstart    = 1;
      uint32_t startbackup  = 2;
      uint32_t endbackup    = 3;
      uint32_t startrestore = 4;
      uint32_t endrestore   = 5;
      uint32_t abortrestore = 6;
  }
}}}

namespace bacnet { namespace service { namespace service { namespace detail {

  using namespace bacnet::service::service;

  template<>
  struct service_choice<reinitialize_device> {
    static constexpr  uint8_t value = 20;
    typedef reinitialize_device type;
  };

  template<>
  struct is_broadcast_service<reinitialize_device> : std::false_type {
  };

}}}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_REINITIALIZE_DEVICE_HPP
