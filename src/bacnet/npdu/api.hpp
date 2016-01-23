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

#include <functional>
#include <boost/asio/ip/udp.hpp>

#include <bacnet/common/protocol/meta_information.hpp>
#include <bacnet/npdu/network_priority.hpp>
#include <bacnet/npdu/address.hpp>

namespace bacnet { namespace npdu {


    namespace config {
      static const bacnet::common::protocol::mac::address DEFAULT_MAC_ADDRESS{bacnet::common::protocol::mac::address_ip{"0.0.0.0", 0}};
      static const constexpr uint16_t  DEFAULT_VENDOR_ID{4242};
    }


    struct configuration {
      uint16_t  vendor_id{config::DEFAULT_VENDOR_ID};
      bacnet::common::protocol::mac::address mac_address{config::DEFAULT_MAC_ADDRESS};

    };

//typedef  std::function<void (bacnet::binary_data&&)> async_receive_broadcast_callback_t;
//typedef  std::function<void (bacnet::binary_data&&)> async_receive_unicast_callback_t;

typedef  std::function<void (bacnet::binary_data&&, bacnet::common::protocol::meta_information&&)> async_received_apdu_callback_t;

}}

#endif //NINJA_WOOKIE_NPDU_API_HPP
