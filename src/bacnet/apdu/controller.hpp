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
#include <bacnet/apdu/service/services.hpp>
#include <bacnet/apdu/detail/pdu_type.hpp>
#include <bacnet/apdu/frame/frames.hpp>
#include <bacnet/apdu/frame/grammar.hpp>

#include <bacnet/apdu/detail/inbound_router.hpp>


void handler(const boost::system::error_code& error_code, const std::size_t &bytes_transfered){
  std::cout << "handler " <<  error_code.message() << std::endl;
}



namespace bacnet { namespace apdu {

constexpr uint16_t DEFAULT_DEVICE_OBJECT_ID = 1;

template<class UnderlyingLayerController>
struct controller {

  controller(boost::asio::io_service &io_service, UnderlyingLayerController &underlying_controller) :
                          io_service_(io_service),
                          underlying_controller_(underlying_controller) {
	  init();
  }

  controller(boost::asio::io_service &io_service, UnderlyingLayerController &underlying_controller, const uint16_t &device_object_id) :
                          io_service_(io_service),
                          underlying_controller_(underlying_controller),
                          device_object_id_(device_object_id) {
    init();
  }


  void send_unconfirmed_request_as_broadcast(const uint8_t &service_choice, const bacnet::binary_data& payload) {
    frame::unconfirmed_request frame;
    frame.pdu_type_and_control_information.pdu_type_ = detail::pdu_type::unconfirmed_request;
    frame.service_choice = service_choice;
    frame.service_data = payload;
    auto data = frame::generator::generate(frame);
    underlying_controller_.async_send_broadcast(data, &handler);
  }

  void service(const service::possible_service& service_) {
    service::generate_frame gf;
    auto data = service_.apply_visitor(gf);
    underlying_controller_.async_send_broadcast(data, &handler);
  }

  void async_received_apdu_handler(bacnet::binary_data data) {
    std::cout << "apdu::controller::async_received_apdu_handler()" << std::endl;
    frame::possible_frame f = frame::parser::parse(data);
    boost::apply_visitor(inbound_router_, f);

  }

private:

  void init() {
    underlying_controller_.register_async_received_apdu_callback(boost::bind(&controller::async_received_apdu_handler, this, _1));
  }

  boost::asio::io_service &io_service_;
  UnderlyingLayerController& underlying_controller_;
  detail::inbound_router  inbound_router_;
  uint16_t device_object_id_ = DEFAULT_DEVICE_OBJECT_ID;
};

}}

#endif //NINJA_WOOKIE_APDU_CONTROLLER_HPP
