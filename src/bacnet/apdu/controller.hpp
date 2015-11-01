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

namespace bacnet { namespace apdu {


    namespace detail {

      //   20.1.2.4   max-segments-accepted
      enum class number_of_max_segments_accepted : uint8_t {
        unspecified = 0b000,
        segments_2 = 0b001,
        segments_4 = 0b010,
        segments_8 = 0b011,
        segments_16 = 0b100,
        segments_32 = 0b101,
        segments_64 = 0b110,
        segments_more_then_64 = 0b111
      };


      //20.1.2.5  max-APDU-length-accepted
      enum class max_apdu_length_accepted : uint8_t {
        up_to_50_bytes = 0b0000, //minimum
        up_to_128_bytes = 0b0001,
        up_to_206_bytes = 0b0010, //(fits in a LonTalk frame)
        up_to_480_bytes = 0b0011, //(fits in an ARCNET frame)
        up_to_1024_bytes = 0b0100,
        up_to_1476_bytes = 0b0101, //(fits in an ISO 8802-3 frame)
        reserved_value_07 = 0b0110,
        reserved_value_08 = 0b0111,
        reserved_value_09 = 0b1001,
        reserved_value_10 = 0b1010,
        reserved_value_11 = 0b1011,
        reserved_value_12 = 0b1100,
        reserved_value_13 = 0b1101,
        reserved_value_14 = 0b1110,
        reserved_value_15 = 0b1111
      };

    }


    namespace settings {

      namespace apdu_size {
        static const constexpr auto minimal = static_cast<typename std::underlying_type<decltype(detail::max_apdu_length_accepted::up_to_50_bytes)>::type>(
                                                                                                            detail::max_apdu_length_accepted::up_to_50_bytes);
        static const constexpr auto ip = static_cast<typename std::underlying_type<decltype(detail::max_apdu_length_accepted::up_to_1476_bytes)>::type>(
                                                                                                            detail::max_apdu_length_accepted::up_to_1476_bytes);
      }

    }

}}








namespace bacnet { namespace apdu {



template<class UnderlyingLayerController>
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
  void async_send_confirmed_request(const bacnet::binary_data& payload, Handler handler) {
    frame::confirmed_request frame;
    bacnet::apdu::detail::header::segmentation_t seg;
    seg.max_accepted_apdu_ = 1;
    frame.pdu_type_and_control_information.pdu_type_ = detail::pdu_type::confirmed_request;
    frame.invoke_id = 0;
    frame.segmentation = seg;

    frame.service_data = payload;
    auto data = frame::generator::generate(frame);
    std::cout << "send async_send_confirmed_request " << std::endl;
    bacnet::print(data);
    underlying_controller_.async_send_broadcast(std::move(data), handler);
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
