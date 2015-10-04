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

#ifndef NINJA_WOOKIE_NPDU_API_HPP
#define NINJA_WOOKIE_NPDU_API_HPP

#include <cstdint>

#include <boost/function.hpp>
#include <boost/asio/ip/udp.hpp>

#include <bacnet/npdu/network_priority.hpp>
#include <bacnet/npdu/address.hpp>

namespace bacnet { namespace npdu {

struct meta_information_t {
  boost::asio::ip::udp::endpoint endpoint;
  bacnet::npdu::network_priority_t network_priority;
  bacnet::npdu::address source;
  uint16_t vendor_id;
};

//typedef  boost::function<void (bacnet::binary_data&&)> async_receive_broadcast_callback_t;
//typedef  boost::function<void (bacnet::binary_data&&)> async_receive_unicast_callback_t;

typedef  boost::function<void (bacnet::binary_data&&, bacnet::npdu::meta_information_t&&)> async_received_apdu_callback_t;

}}

#endif //NINJA_WOOKIE_NPDU_API_HPP
