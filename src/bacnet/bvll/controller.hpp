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

#include <util/callback_manager.hpp>
#include <bacnet/transport/api.hpp>
#include <bacnet/bvll/frames.hpp>
#include <bacnet/bvll/api.hpp>

#include <bacnet/bvll/detail/inbound_router.hpp>
#include <bacnet/error/error.hpp>

namespace bacnet { namespace  bvll {

    namespace  detail {
      typedef boost::fusion::map<
          boost::fusion::pair<frame::bvlc_result, receive_bvlc_result_callback_t>,
          boost::fusion::pair<frame::write_broadcast_distribution_table, receive_write_broadcast_distribution_table_callback_t>,
          boost::fusion::pair<frame::read_broadcast_distribution_table, receive_read_broadcast_distribution_table_callback_t>,
          boost::fusion::pair<frame::read_broadcast_distribution_table_ack, receive_read_broadcast_distribution_table_ack_callback_t>,
          boost::fusion::pair<frame::forwarded_npdu, receive_forwarded_npdu_callback_t>,
          boost::fusion::pair<frame::register_foreign_device, receive_register_foreign_device_callback_t>,
          boost::fusion::pair<frame::read_foreign_device_table, receive_read_foreign_device_table_callback_t>,
          boost::fusion::pair<frame::read_foreign_device_table_ack, receive_read_foreign_device_table_ack_callback_t>,
          boost::fusion::pair<frame::delete_foreign_device_table_entry, receive_delete_foreign_device_table_entry_callback_t>,
          boost::fusion::pair<frame::distribute_broadcast_to_network, receive_distribute_broadcast_to_network_callback_t>,
          boost::fusion::pair<frame::original_unicast_npdu, receive_original_unicast_npdu_callback_t>,
          boost::fusion::pair<frame::original_broadcast_npdu, receive_original_broadcast_npdu_callback_t>,
          boost::fusion::pair<frame::original_secure_bvll, receive_original_secure_bvll_callback_t>,
          boost::fusion::pair<frame::raw, receive_raw_callback_t>
      > callback_map_type;
    }

template<typename Transporter>
class controller {

public:

  controller(boost::asio::io_service &ios, Transporter &transporter) :
                                          io_service_(ios),
                                          transporter_(transporter),
                                          inbound_router_(callback_manager_) {
  }



  template<typename... Callbacks>
  void register_callbacks(Callbacks... callbacks) {
    callback_manager_.set_callbacks(callbacks...);
  }


  void start() {
    //transporter_.register_receive_callback(boost::bind(&controller::handle_async_receive, this, boost::asio::placeholders::error, _2, _3));
    transporter_.register_receive_callback([this](bacnet::error &&error, bacnet::common::protocol::mac::address &&sender, bacnet::binary_data&& data) {
      handle_async_receive(std::move(error), std::move(sender), std::move(data));
    });
    transporter_.start();
  }

  template<typename Handler>
  void async_send(const bacnet::binary_data &payload, const bacnet::common::protocol::mac::address& address, const Handler &handler){

    frame::original_unicast_npdu frame;
    frame.npdu_data = payload;
    frame::possible_bvll_frame f(frame);

    bacnet::binary_data binary_frame = generator::generate(f);
    transporter_.async_send(binary_frame, address,  handler);
  }

  template<typename Handler>
  void async_send_broadcast(const bacnet::binary_data &payload, Handler handler){
    //todo here we need a broadcast address AND PORT or access to the global config? or get a broadcast address from underlying types?
    auto address = bacnet::common::protocol::mac::address(bacnet::common::protocol::mac::address_ip::broadcast());
    frame::original_broadcast_npdu frame;
    frame.npdu_data = payload;
    frame::possible_bvll_frame f(frame);

    bacnet::binary_data binary_frame = generator::generate(f);
    transporter_.async_send(binary_frame, address, handler);
  }

private:

  void handle_async_receive(bacnet::error &&error, bacnet::common::protocol::mac::address &&sender, bacnet::binary_data&& data) {
    if (!error) {
      //std::cout << "bvll::controller::handle_async_receive()" << std::endl;
      frame::possible_bvll_frame f = parser::parse(std::move(data));
      inbound_router_.sender_endpoint(sender);
      //boost::apply_visitor(inbound_router_, f);
      mapbox::util::apply_visitor( inbound_router_, f );
    }
  }

  boost::asio::io_service &io_service_;
  Transporter &transporter_;
  util::callback::callback_manager<detail::callback_map_type> callback_manager_;
  bacnet::bvll::detail::inbound_router<decltype(callback_manager_)> inbound_router_;

};

}}

#endif //NINJA_WOOKIE_CONTROLLER_HPP
