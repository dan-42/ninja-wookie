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

#include <boost/fusion/include/define_struct.hpp>

#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/error/error.hpp>
#include <bacnet/bvll/api.hpp>
#include <bacnet/detail/common/types.hpp>
#include <util/callback_manager.hpp>
#include <bacnet/common/protocol/meta_information.hpp>

#include <bacnet/npdu/frame.hpp>
#include <bacnet/npdu/detail/grammar.hpp>
#include <bacnet/npdu/api.hpp>
#include <bacnet/npdu/detail/inbound_router.hpp>

namespace bacnet { namespace npdu {


constexpr uint8_t  NPDU_PROTOCOL_VERSION    = 0x01;
constexpr uint16_t DEFAULT_NETWORK_NUMBER   = 0x0001;
constexpr uint16_t BROADCAST_NETWORK_NUMBER = 0xFFFF;
constexpr uint8_t  BROADCAST_HOP_COUNT      = 0xFF;


    namespace  detail {
      typedef boost::fusion::map<
          boost::fusion::pair<frame_body::apdu, receive_apdu_callback_t>,
          boost::fusion::pair<frame_body::raw, receive_raw_callback_t>
      > callback_map_type;
    }

template<class Underlying_layer>
class controller {

public:
  controller(Underlying_layer &underlying_layer) : underlying_layer_(underlying_layer), inbound_router_(callback_manager_) {

  }

  controller(Underlying_layer &underlying_layer, const uint16_t & network_number) :
                                                        underlying_layer_(underlying_layer),
                                                        inbound_router_(callback_manager_),
                                                        network_number_(network_number) {

  }

  template<typename... Callbacks>
  void register_callbacks(Callbacks... callbacks) {
    callback_manager_.set_callbacks(callbacks...);
  }


  /**
   * handler is called when
   *  * Successfully send message
   *  * error while sending
   */
  template<typename Handler>
  void async_send_broadcast(const bacnet::binary_data & payload, const Handler &handler){

    npdu::frame frame;
    frame_body::apdu body;
    body.data = payload;
    frame.protocol_version = NPDU_PROTOCOL_VERSION;
    frame.control_field.has_destination_specifier_ = true;
    frame.destination.network_number = BROADCAST_NETWORK_NUMBER;
    frame.hop_count = BROADCAST_HOP_COUNT;
    frame.body = body;

    bacnet::binary_data binary_frame = npdu::detail::generator::generate(std::move(frame));

    underlying_layer_.async_send_broadcast(binary_frame, handler);
  }

  /**
   * handler is called when
   *  * Successfully send message
   *  * error while sending
   * It will not be waited for an answer, thats job of a upper layer
   */
  template<typename Handler>
  void async_send_unicast(bacnet::common::protocol::mac::endpoint endpoint, const bacnet::binary_data & payload, Handler handler){

    endpoint.network(network_number_);
    /**
     * simple BACnet messages have a simple NPDU-Header without any src or dst information
     * xxx use kind of a router if we want to send to a different BACnet network
     *     then we need a more complex NPDU-header
     */
    npdu::frame frame;
    frame.protocol_version                          = NPDU_PROTOCOL_VERSION;
    frame.control_field.has_network_layer_message_  = false;
    frame.control_field.priority_                   = npdu::priority::normal_message;
    frame.hop_count                                 = 0;

    /*because of single-element-fusion-sequence*/
    frame_body::apdu  body;
    body.data       = payload;
    frame.body      = body;

    bacnet::binary_data binary_frame = npdu::detail::generator::generate(std::move(frame));
    underlying_layer_.async_send(binary_frame, endpoint.address(), handler);
  }

  void start() {
    underlying_layer_.register_callbacks([this](bacnet::bvll::frame::original_broadcast_npdu&& data, const bacnet::common::protocol::meta_information& mi) {
                                            received_broadcast(std::move(data), mi);
                                         },
                                         [this](bacnet::bvll::frame::original_unicast_npdu&& data, const bacnet::common::protocol::meta_information& mi) {
                                            received_unicast(std::move(data), mi);
                                         });
    underlying_layer_.start();
  }

private:

  /**
   * called when a underlying layer received a broadcast message
   */
  void received_broadcast(bacnet::bvll::frame::original_broadcast_npdu&& data, const bacnet::common::protocol::meta_information& mi) {
    //std::cout << "npdu::controller::received_broadcast()" << std::endl;
    auto frame = npdu::detail::parser::parse(std::move(data.npdu_data));
    inbound_router_.meta_information(mi);
    inbound_router_.route(std::move(frame));
  }

  /**
   * called when a underlying layer received a unicast message
   */
  void received_unicast(bacnet::bvll::frame::original_unicast_npdu&& data, const bacnet::common::protocol::meta_information& mi) {
    //std::cout << "npdu::controller::received_unicast()" << std::endl;
    auto frame = npdu::detail::parser::parse(std::move(data.npdu_data));
    inbound_router_.meta_information(mi);
    inbound_router_.route(std::move(frame));
  }



  Underlying_layer &underlying_layer_;
  util::callback::callback_manager<detail::callback_map_type> callback_manager_;
  detail::inbound_router<decltype(callback_manager_)> inbound_router_;
  uint16_t network_number_ = DEFAULT_NETWORK_NUMBER;

};

}}

#endif /* NINJA_WOOKIE_NPDU_CONTROLLER_HPP */
