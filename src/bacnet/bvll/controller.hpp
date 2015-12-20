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


#ifndef NINJA_WOOKIE_CONTROLLER_HPP
#define NINJA_WOOKIE_CONTROLLER_HPP

#include <vector>
#include <array>
#include <iostream>
#include <iomanip>
#include <bitset>

#include <boost/bind.hpp>

#include <bacnet/transport/api.hpp>

#include <bacnet/bvll/frames.hpp>
#include <bacnet/bvll/api.hpp>

#include <bacnet/bvll/detail/inbound_router.hpp>
#include <bacnet/bvll/detail/callback_manager.hpp>





namespace bacnet { namespace  bvll {

template<typename Transporter>
class controller {

public:

  controller(boost::asio::io_service &ios, Transporter &transporter) :
                                          io_service_(ios),
                                          transporter_(transporter),
                                          inbound_router_(callback_manager_) {
    start();
  }


  void register_async_receive_broadcast_callback(const async_receive_broadcast_callback_t &callback){
    callback_manager_.async_receive_broadcast_callback_ = callback;
  }

  void register_async_receive_unicast_callback(const async_receive_unicast_callback_t &callback){
    callback_manager_.async_receive_unicast_callback_ = callback;
  }

  void start() {
    transporter_.set_async_receive_callback(boost::bind(&controller::handle_async_receive, this, boost::asio::placeholders::error, _2, _3));
    transporter_.start();
  }

  void handle_async_receive(boost::system::error_code error, bacnet::common::protocol::mac::address sender, bacnet::binary_data data) {

    if (!error) {
      frame::possible_bvll_frame f = parser::parse(std::move(data));
      inbound_router_.sender_endpoint(sender);
      f.apply_visitor(inbound_router_);

    }
  }


  template<typename Handler>
  void async_send(const bacnet::binary_data &payload, const bacnet::common::protocol::mac::address_ip& address, const Handler &handler){

    frame::original_unicast_npdu frame;
    frame.npdu_data = payload;
    frame::possible_bvll_frame f(frame);

    bacnet::binary_data binary_frame = generator::generate(f);
    transporter_.async_send(binary_frame, address,  handler);
  }
  template<typename Handler>
  void async_send_broadcast(const bacnet::binary_data &payload, const Handler &handler){
    //todo here we need a broadcast address or access to the global config? or get a broadcast address from underlying type?
    auto address = bacnet::common::protocol::mac::address(bacnet::common::protocol::mac::address_ip::broadcast());
    frame::original_broadcast_npdu frame;
    frame.npdu_data = payload;
    frame::possible_bvll_frame f(frame);

    bacnet::binary_data binary_frame = generator::generate(f);
    transporter_.async_send(binary_frame, address,  [handler](const boost::system::error_code &error){});
  }

private:

  boost::asio::io_service &io_service_;
  Transporter &transporter_;

  bacnet::bvll::detail::inbound_router inbound_router_;
  bacnet::bvll::detail::callback_manager callback_manager_;

};

}}

#endif //NINJA_WOOKIE_CONTROLLER_HPP
