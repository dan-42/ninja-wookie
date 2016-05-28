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

#include <bacnet/error/error.hpp>
#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/detail/pdu_type.hpp>
#include <bacnet/apdu/frame/frames.hpp>
#include <bacnet/apdu/frame/grammar.hpp>

#include <bacnet/apdu/detail/inbound_router.hpp>
#include <bacnet/apdu/detail/request_manager.hpp>

#include <bacnet/npdu/api.hpp>



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

template<class UnderlyingLayerController, typename ApduSize>
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
    underlying_controller_.async_send_broadcast(std::move(data), handler);
  }

  /*
   * handler is called if:
   *  * the message could not be send(internal error)
   *  * answer received  for the confirmed message, including answer payload
   */
  void async_send_confirmed_request(const bacnet::common::protocol::mac::address& adr, const bacnet::binary_data& payload, confirmed_request_handler_type handler) {
    bacnet::common::protocol::mac::endpoint ep{adr};

    frame::confirmed_request                            frame;
    bacnet::apdu::detail::header::segmentation_t        seg;
    auto invoke_id                                    = request_manager_.get_next_invoke_id(adr);
    seg.max_accepted_apdu_                            = ApduSize::size_as_enum;
    frame.invoke_id                                   = invoke_id;
    frame.segmentation                                = seg;
    frame.pdu_type_and_control_information.pdu_type_  = detail::pdu_type::confirmed_request;
    frame.service_data                                = payload;
    frame.proposed_window_size                        = 1;
    auto data                                         = frame::generator::generate(frame);


    // xxx don't forget timeout!
    underlying_controller_.async_send_unicast(ep, std::move(data), [this, adr, invoke_id, handler]( const bacnet::error_code& ec) {
            if(ec) {
              this->request_manager_.purge_invoke_id(adr, invoke_id);
              handler(ec, frame::possible_confirmed_respons(), bacnet::common::protocol::meta_information());
            }
            else {
              this->request_manager_.store_handler(adr, invoke_id, handler);
            }
      });
  }


  void async_received_apdu_handler(bacnet::npdu::frame_body::apdu apdu, bacnet::common::protocol::meta_information meta_info) {
    auto data = apdu.data;
    frame::possible_frame f = frame::parser::parse(std::move(data));
    inbound_router_.meta_information(std::move(meta_info));
    f.apply_visitor(inbound_router_);
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
