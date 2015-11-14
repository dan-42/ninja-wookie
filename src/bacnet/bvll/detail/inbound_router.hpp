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

#ifndef NINJA_WOOKIE_INBOUND_ROUTER_HPP
#define NINJA_WOOKIE_INBOUND_ROUTER_HPP

#include <iostream>
#include <boost/variant/static_visitor.hpp>


#include <bacnet/common/protocol/meta_information.hpp>
#include <bacnet/bvll/frames.hpp>
#include <bacnet/bvll/detail/transporter.hpp>
#include <bacnet/bvll/detail/callback_manager.hpp>
#include <bacnet/bvll/controller.hpp>


namespace bacnet { namespace  bvll { namespace  detail {


class inbound_router : public boost::static_visitor<> {

public:

  inbound_router(bacnet::bvll::detail::callback_manager& cm) : callback_manager_(cm) {

  }

  void operator()(frame::bvlc_result request) {
    std::cout << "inbound_router bvlc_result" << std::endl;
  }

  void operator()(frame::write_broadcast_distribution_table request) {
    std::cout << "inbound_router write_broadcast_distribution_table" << std::endl;
  }

  void operator()(frame::read_broadcast_distribution_table request) {
    std::cout << "inbound_router read_broadcast_distribution_table" << std::endl;
  }

  void operator()(frame::read_broadcast_distribution_table_ack request) {
    std::cout << "inbound_router read_broadcast_distribution_table" << std::endl;
  }

  void operator()(frame::register_foreign_device request) {
    std::cout << "inbound_router register_foreign_device" << std::endl;
  }
  void operator()(frame::read_foreign_device_table request) {
    std::cout << "inbound_router read_foreign_device_table" << std::endl;
  }

  void operator()(frame::read_foreign_device_table_ack request) {
    std::cout << "inbound_router read_foreign_device_table_ack" << std::endl;
  }

  void operator()(frame::delete_foreign_device_table_entry request) {
    std::cout << "inbound_router delete_foreign_device_table_entry" << std::endl;
  }

  void operator()(frame::distribute_broadcast_to_network request) {
    std::cout << "inbound_router distribute_broadcast_to_network" << std::endl;
  }

  void operator()(frame::forwarded_npdu request) {
    std::cout << "inbound_router forwarded_npdu" << std::endl;
  }

  void operator()(frame::original_unicast_npdu request) {
    if(!callback_manager_.async_receive_unicast_callback_.empty()){
      bacnet::common::protocol::meta_information mi;
      mi.address = bacnet::common::protocol::mac::address_ip(sender_endpoint_.address().to_v4(), sender_endpoint_.port());

      callback_manager_.async_receive_unicast_callback_(std::move(request.npdu_data), std::move(mi));
    }
  }

  void operator()(frame::original_broadcast_npdu request) {
    if(!callback_manager_.async_receive_broadcast_callback_.empty()) {
      bacnet::common::protocol::meta_information mi;
      mi.address = bacnet::common::protocol::mac::address_ip(sender_endpoint_.address().to_v4(), sender_endpoint_.port());

      callback_manager_.async_receive_broadcast_callback_(std::move(request.npdu_data), std::move(mi));
    }
  }

  void operator()(frame::original_secure_bvll request) {
    std::cout << "inbound_router original_secure_bvll" << std::endl;
  }
  void operator()(frame::raw request) {
    std::cout << "inbound_router raw data" << std::endl;
  }

  void sender_endpoint(const boost::asio::ip::udp::endpoint& sender_endpoint) {
    sender_endpoint_ = sender_endpoint;
  }

private:
  bacnet::bvll::detail::callback_manager&  callback_manager_;
  boost::asio::ip::udp::endpoint sender_endpoint_;
};


}}}



#endif //NINJA_WOOKIE_INBOUND_ROUTER_HPP
