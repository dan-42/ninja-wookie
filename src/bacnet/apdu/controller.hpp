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
#include <limits>
#include <functional>

#include <boost/asio.hpp>
#include <boost/variant.hpp>
#include <boost/bind.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/detail/pdu_type.hpp>
#include <bacnet/apdu/frame/frames.hpp>
#include <bacnet/apdu/frame/grammar.hpp>

#include <bacnet/apdu/detail/inbound_router.hpp>
#include <bacnet/apdu/detail/request_manager.hpp>
#include <bacnet/error/error.hpp>
#include <bacnet/npdu/api.hpp>
#include <bacnet/service/detail/invoker.hpp>


namespace bacnet { namespace apdu {


/**
 * SCOPE OF THIS LAYER
 *  * layer decodes static part of apdu messages(apdu-types...)
 *  * fully decodes simple_ack, reject and abort frame as the payload is only a uint8_t simple enums
 *  * [NOT YET] Concatenates segmented messages into one, before sending to upperLayer
 *  * [NOT YET] slices message into segments and sends to lowerLayer
 *  * manage confirmed requests
 *    * manages invoke_ids
 *    * stores callbacks for each request, calles them on receiving answer
 *    * [NOT YET] takes care of timeouts
 *  * unconfirmed messages, are more or less just passed trough
 *
 *
 */
namespace detail {

using namespace bacnet::apdu;

typedef boost::fusion::map<
    boost::fusion::pair<frame::unconfirmed_request, received_unconfirmed_callback_t>,
    boost::fusion::pair<frame::confirmed_request,   received_confirmed_callback_t  >
> callback_map_type;

}

template<class UnderlyingLayerController, typename Config>
struct controller {

  controller(boost::asio::io_service &io_service, UnderlyingLayerController &underlying_controller) :
                          io_service_(io_service),
                          underlying_controller_(underlying_controller),
                          inbound_router_(callback_manager_, request_manager_) {

  }

  controller(boost::asio::io_service &io_service, UnderlyingLayerController &underlying_controller, const uint16_t &device_object_id) :
                          io_service_(io_service),
                          underlying_controller_(underlying_controller),
                          inbound_router_(callback_manager_, request_manager_) {

  }

  void start() {
    underlying_controller_.register_callbacks([this](bacnet::npdu::frame_body::apdu apdu, bacnet::common::protocol::meta_information meta_info) {
                                                        this->async_received_apdu_handler(apdu, meta_info);
                                                      });
    underlying_controller_.start();
  }

  template<typename ...Callbacks>
  void register_callbacks(Callbacks... callbacks) {
    callback_manager_.set_callbacks(callbacks...);
  }


  /**
   * handler is called when sending was successful/failed, as this is a unconfirmed message,
   * so no response can be expected
   */
  template<typename Handler>
  void async_send_unconfirmed_request_as_broadcast(const bacnet::binary_data& payload, Handler handler) {
    frame::unconfirmed_request frame;
    frame.pdu_type_and_control_information.pdu_type_ = detail::pdu_type::unconfirmed_request;
    frame.service_data = payload;
    auto data = frame::generator::generate(frame);
    std::cout << "async_send_unconfirmed_request_as_broadcast() ";
    print(data);
    underlying_controller_.async_send_broadcast(std::move(data), handler);
  }

  /*
   * handler is called if:
   *  * the message could not be send(internal error)
   *  * answer received  for the confirmed message, including answer payload
   */
  void async_send_confirmed_request(const bacnet::common::protocol::mac::endpoint& ep, const bacnet::binary_data& payload, confirmed_request_handler_type handler) {


    if(payload.size() > Config::apdu_size::size_in_bytes || payload.size() > ep.apdu_size() ) {
      if(Config::segmentation_config::segment_supported == bacnet::common::segmentation::segment::none) {
        auto e = bacnet::make_error(bacnet::err::error_code::segmentation_support_none, bacnet::err::error_class::internal);
        handler(e, frame::complex_ack(), bacnet::common::protocol::meta_information());
        return;
      }







    }
    else {

      frame::confirmed_request                            frame;
      bacnet::apdu::detail::header::segmentation_t        seg;

      auto invoke_id                                    = request_manager_.get_next_invoke_id(ep.address());
      seg.max_accepted_apdu_                            = Config::apdu_size::size_as_enum;
      frame.invoke_id                                   = invoke_id;
      frame.segmentation                                = seg;
      frame.pdu_type_and_control_information.pdu_type_  = detail::pdu_type::confirmed_request;
      frame.service_data                                = payload;
      frame.proposed_window_size                        = 1;//Config::segmentation_config::number_of_segments;
      auto data                                         = frame::generator::generate(frame);


      // xxx don't forget timeout!
      underlying_controller_.async_send_unicast(ep, std::move(data), [this, ep, invoke_id, handler]( const bacnet::error& ec) {
              if(ec) {
                this->request_manager_.purge_invoke_id(ep.address(), invoke_id);
                handler(ec, frame::complex_ack(), bacnet::common::protocol::meta_information());
              }
              else {
                this->request_manager_.store_handler(ep.address(), invoke_id, handler);
              }
        });
    }
  }


  void async_received_apdu_handler(bacnet::npdu::frame_body::apdu apdu, bacnet::common::protocol::meta_information meta_info) {
    auto data = apdu.data;
    frame::possible_frame f = frame::parser::parse(std::move(data));
    inbound_router_.meta_information(std::move(meta_info));
    mapbox::util::apply_visitor(inbound_router_, f);
  }

  void async_send_confirmed_response(bacnet::binary_data payload, bacnet::common::protocol::meta_information meta_info, unconfirmed_response_handler_type handler) {
       bacnet::common::protocol::mac::endpoint             ep{meta_info.address};

       frame::complex_ack                                  frame;
       bacnet::apdu::detail::header::segmentation_t        seg;
       seg.max_accepted_apdu_                            = Config::apdu_size::size_as_enum;
       frame.pdu_type_and_control_information.pdu_type_  = detail::pdu_type::complex_ack;
       frame.original_invoke_id                          = meta_info.invoke_id;
       frame.sequence_number                             = 0;
       frame.proposed_window_size                        = 1;
       frame.service_ack_data                            = payload;

       auto data                                         = frame::generator::generate(frame);
       underlying_controller_.async_send_unicast(ep, std::move(data), handler);
  }

  void async_send_confirmed_response(bacnet::error error, bacnet::common::protocol::meta_information meta_info, unconfirmed_response_handler_type handler) {
    bacnet::common::protocol::mac::endpoint ep{meta_info.address};
    bacnet::binary_data data;
    if(error.category == bacnet::err::cat::error) {
      frame::error                    frame;
      frame.pdu_type_and_control_information.pdu_type_ = detail::pdu_type::error;
      frame.original_invoke_id      = meta_info.invoke_id;
      frame.error_choice            = meta_info.service_choice;
      frame.error_                  = bacnet::type::error(error);
      data                          = frame::generator::generate(frame);
      underlying_controller_.async_send_unicast(ep, std::move(data), handler);
    }
    else if(error.category == bacnet::err::cat::abort) {
      frame::abort                  frame;
      frame.pdu_type_and_control_information.pdu_type_ = detail::pdu_type::abort;
      frame.original_invoke_id      = meta_info.invoke_id;
      frame.abort_reason            = static_cast<uint8_t>(error.value);
      data                          = frame::generator::generate(frame);
      underlying_controller_.async_send_unicast(ep, std::move(data), handler);
    }
    else if(error.category == bacnet::err::cat::reject) {
      frame::reject                   frame;
      frame.pdu_type_and_control_information.pdu_type_ = detail::pdu_type::reject;
      frame.original_invoke_id      = meta_info.invoke_id;
      frame.reject_reason           = static_cast<uint8_t>(error.value);
      data                          = frame::generator::generate(frame);
      underlying_controller_.async_send_unicast(ep, std::move(data), handler);
    }
    else if(!error) {
      frame::simple_ack                   frame;
      frame.pdu_type_and_control_information.pdu_type_ = detail::pdu_type::simple_ack;
      frame.original_invoke_id      = meta_info.invoke_id;
      frame.service_ack_choice      = meta_info.service_choice;
      data                          = frame::generator::generate(frame);
      underlying_controller_.async_send_unicast(ep, std::move(data), handler);
    }
    else {
      bacnet::error e(boost::system::errc::bad_message);
      handler(e);
    }
  }

private:



  boost::asio::io_service &io_service_;
  UnderlyingLayerController& underlying_controller_;
  util::callback::callback_manager<detail::callback_map_type>  callback_manager_;
  detail::request_manager request_manager_;
  detail::inbound_router<decltype(callback_manager_), decltype(request_manager_)>  inbound_router_;

};

}}

#endif //NINJA_WOOKIE_APDU_CONTROLLER_HPP
