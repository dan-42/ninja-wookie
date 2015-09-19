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

#ifndef NINJA_WOOKIE_BACNET_APDU_API_HPP
#define NINJA_WOOKIE_BACNET_APDU_API_HPP

#include <cstdint>

#include <boost/function.hpp>
#include <boost/asio/ip/udp.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/npdu/api.hpp>

namespace bacnet { namespace apdu {

  struct meta_information_t {
    uint8_t service_choice;
    bacnet::npdu::meta_information_t npdu_meta_information;
  };

  typedef  boost::function<void (const bacnet::apdu::meta_information_t&, const bacnet::binary_data&)> async_received_service_callback_t;

}}

#endif //NINJA_WOOKIE_BACNET_APDU_API_HPP
