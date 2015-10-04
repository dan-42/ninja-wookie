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

#ifndef NINJA_WOOKIE_NPDU_CONTROLLER_HPP
#define NINJA_WOOKIE_NPDU_CONTROLLER_HPP

#include <bitset>

#include <boost/fusion/include/define_struct.hpp>

#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>


#include <bacnet/npdu/frame.hpp>
#include <bacnet/npdu/grammar.hpp>
#include <bacnet/npdu/api.hpp>
#include <bacnet/npdu/detail/callback_manager.hpp>
#include <bacnet/npdu/detail/inbound_router.hpp>

namespace bacnet { namespace npdu {


constexpr uint8_t  NPDU_PROTOCOL_VERSION = 1;
constexpr uint16_t DEFAULT_NETWORK_NUMBER = 1;
constexpr uint16_t BROADCAST_NETWORK_NUMBER = 0xFFFF;
constexpr uint8_t  BROADCAST_HOP_COUNT = 0xFF;

template<class Underlying_layer>
class controller {

public:
  controller(Underlying_layer &underlying_layer) : underlying_layer_(underlying_layer), inbound_router_(callback_manager_) {
    init();
  }

  controller(Underlying_layer &underlying_layer, const uint16_t & network_number) : underlying_layer_(underlying_layer), inbound_router_(callback_manager_), network_number_(network_number) {
    init();
  }

  /** callback to upper layer*/
  void register_async_received_apdu_callback(const async_received_apdu_callback_t &callback){
    callback_manager_.async_received_apdu_callback_ = callback;
  }


  template<typename Handler>
  void async_send_broadcast(const bacnet::binary_data & payload, const Handler &handler){

    npdu::frame frame;
    frame.protocol_version = NPDU_PROTOCOL_VERSION;
    frame.control_field.has_destination_specifier_ = true;
    frame.destination.network_number = BROADCAST_NETWORK_NUMBER;
    frame.hop_count = BROADCAST_HOP_COUNT;
    frame.apdu_data = payload;

    bacnet::binary_data binary_frame = npdu::generator::generate(frame);

    underlying_layer_.async_send_broadcast(binary_frame, handler);
  }

  void async_receive_broadcast_handler(bacnet::binary_data&& data, boost::asio::ip::udp::endpoint&& sender_endpoint) {
    std::cout << "npdu_controller " << "async_receive_broadcast_handler" << std::endl;

    auto frame = npdu::parser::parse(data);
    //std::cout << "bacnet::npdu::parser::parse parsed "   << std::endl;
    inbound_router_.sender_endpoint(sender_endpoint);
    inbound_router_.route(std::move(frame));
  }

  void async_receive_broadcast_handler2(bacnet::binary_data data, boost::asio::ip::udp::endpoint sender_endpoint) {
      std::cout << "async_receive_broadcast_handler2 npdu_controller " << "async_receive_broadcast_handler" << std::endl;

    auto frame = npdu::parser::parse(data);
    //std::cout << "bacnet::npdu::parser::parse parsed "   << std::endl;
    inbound_router_.sender_endpoint(sender_endpoint);
    inbound_router_.route(std::move(frame));
  }

  void async_receive_broadcast_handler3(const bacnet::binary_data& data, const boost::asio::ip::udp::endpoint& sender_endpoint) {
      std::cout << " async_receive_broadcast_handler3 npdu_controller " << "async_receive_broadcast_handler" << std::endl;

    auto frame = npdu::parser::parse(data);
    //std::cout << "bacnet::npdu::parser::parse parsed "   << std::endl;
    inbound_router_.sender_endpoint(sender_endpoint);
    inbound_router_.route(std::move(frame));
  }


private:

  void init() {
    underlying_layer_.register_async_receive_broadcast_callback(boost::bind(&controller::async_receive_broadcast_handler3, this, _1, _2));
  }

  Underlying_layer &underlying_layer_;
  detail::callback_manager callback_manager_;
  detail::inbound_router inbound_router_;
  uint16_t network_number_ = DEFAULT_NETWORK_NUMBER;

};

}}

#endif /* NINJA_WOOKIE_NPDU_CONTROLLER_HPP */
