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

#ifndef NINJA_WOOKIE_APDU_CONTROLLER_HPP
#define NINJA_WOOKIE_APDU_CONTROLLER_HPP

#include <iostream>

#include <boost/asio.hpp>
#include <boost/variant.hpp>
#include <boost/bind.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/detail/pdu_type.hpp>
#include <bacnet/apdu/frame/frames.hpp>
#include <bacnet/apdu/frame/grammar.hpp>

#include <bacnet/apdu/detail/inbound_router.hpp>
#include <bacnet/apdu/detail/callback_manager.hpp>

namespace bacnet { namespace apdu { namespace detail {

/**
 *
    key is   endpoint + invoke id
    idea: for each endpoint one transmissionmanager?

 *
 */

  struct transmission_identifier {
      bacnet::common::protocol::mac::address mac;
      uint8_t invoke_id_counter = 0;
  };


  struct device_transmission_manager {



  private:
      static uint8_t invoke_id_counter;
  };



}}}








namespace bacnet { namespace apdu {



template<class UnderlyingLayerController, typename ApduSize>
struct controller {

  controller(boost::asio::io_service &io_service, UnderlyingLayerController &underlying_controller) :
                          io_service_(io_service),
                          underlying_controller_(underlying_controller),
                          inbound_router_(callback_manager_) {
	  init();
  }

  controller(boost::asio::io_service &io_service, UnderlyingLayerController &underlying_controller, const uint16_t &device_object_id) :
                          io_service_(io_service),
                          underlying_controller_(underlying_controller),
                          inbound_router_(callback_manager_) {
    init();
  }

  void register_async_received_service_callback(const async_received_service_callback_t &callback){
    callback_manager_.async_received_service_callback_ = callback;
  }

  template<typename Handler>
  void async_send_unconfirmed_request_as_broadcast(const bacnet::binary_data& payload, Handler handler) {
    frame::unconfirmed_request frame;
    frame.pdu_type_and_control_information.pdu_type_ = detail::pdu_type::unconfirmed_request;
    frame.service_data = payload;
    auto data = frame::generator::generate(frame);
    underlying_controller_.async_send_broadcast(std::move(data), handler);
  }

  template<typename Handler>
  void async_send_confirmed_request(const bacnet::common::protocol::mac::address& adr, const bacnet::binary_data& payload, Handler handler) {
    frame::confirmed_request frame;
    bacnet::apdu::detail::header::segmentation_t seg;
    frame.pdu_type_and_control_information.pdu_type_ = detail::pdu_type::confirmed_request;

    seg.max_accepted_apdu_ = ApduSize::size_as_enum;
    frame.invoke_id       = 0;
    frame.segmentation = seg;

    frame.service_data = payload;
    auto data = frame::generator::generate(frame);
    //std::cout << "send async_send_confirmed_request " << std::endl;
    //bacnet::print(data);
    // set lambda as callback, and on success sending, store handler in a "handlerManager" with endpoint and invoke id as key
    // don't forget timeout!
    bacnet::common::protocol::mac::endpoint ep{adr};
    underlying_controller_.async_send_unicast(ep, std::move(data), [this, handler]( const boost::system::error_code& ec){
          handler(ec);
      });
  }


  void async_received_apdu_handler(bacnet::binary_data data, bacnet::common::protocol::meta_information meta_info) {
    frame::possible_frame f = frame::parser::parse(std::move(data));
    inbound_router_.meta_information(std::move(meta_info));
    f.apply_visitor(inbound_router_);

  }

private:

  void init() {
    underlying_controller_.register_async_received_apdu_callback(boost::bind(&controller::async_received_apdu_handler, this, _1, _2));
  }

  boost::asio::io_service &io_service_;
  UnderlyingLayerController& underlying_controller_;
  detail::inbound_router  inbound_router_;
  detail::callback_manager callback_manager_;
};

}}

#endif //NINJA_WOOKIE_APDU_CONTROLLER_HPP
