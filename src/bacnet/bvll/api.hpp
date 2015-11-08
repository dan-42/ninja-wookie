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

#ifndef NINJA_WOOKIE_BVLL_API_HPP
#define NINJA_WOOKIE_BVLL_API_HPP

#include <boost/function.hpp>
#include <boost/asio/ip/udp.hpp>

#include <bacnet/common/protocol/meta_information.hpp>
namespace bacnet { namespace bvll {


    namespace config {
      static const constexpr char*  DEFAULT_LISTENING_ADDRESS{"0.0.0.0"};
      static const constexpr uint16_t DEFAULT_LISTENING_PORT{0xBAC0};
      static const constexpr char*  DEFAULT_MULTICAST_ADDRESS{"255.255.255.255"};
    }

    struct configuration {

      configuration() : listening_address(config::DEFAULT_LISTENING_ADDRESS),
                        listening_port(config::DEFAULT_LISTENING_PORT),
                        multicast_address(config::DEFAULT_MULTICAST_ADDRESS) {
      }

      configuration(const std::string& l_addr, const uint16_t& l_port, const std::string& m_addr) : listening_address(l_addr),
                                                                                                    listening_port(l_port),
                                                                                                    multicast_address(m_addr) {
      }

      std::string listening_address;
      uint16_t listening_port;
      std::string multicast_address;
    };

typedef  boost::function<void (bacnet::binary_data&&, bacnet::common::protocol::meta_information&& )> async_receive_broadcast_callback_t;
typedef  boost::function<void (bacnet::binary_data&&, bacnet::common::protocol::meta_information&& )> async_receive_unicast_callback_t;

}}

#endif //NINJA_WOOKIE_BVLL_API_HPP
