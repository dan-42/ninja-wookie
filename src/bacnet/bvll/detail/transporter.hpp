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

#ifndef NINJA_WOOKIE_TRANSPORTER_HPP
#define NINJA_WOOKIE_TRANSPORTER_HPP

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <bacnet/bvll/api.hpp>

namespace bacnet {   namespace  bvll {  namespace detail {


class transporter {

public:


  transporter(boost::asio::io_service &io_service) : io_service_(io_service),
                                                     socket_(io_service),
                                                     port_(bacnet::bvll::config::DEFAULT_LISTENING_PORT),
                                                     listen_address_(boost::asio::ip::address::from_string(bacnet::bvll::config::DEFAULT_LISTENING_ADDRESS)),
                                                     multicast_address_(boost::asio::ip::address::from_string(bacnet::bvll::config::DEFAULT_MULTICAST_ADDRESS)),
                                                     listen_endpoint_(listen_address_, port_) {
    init();
  }

  transporter(boost::asio::io_service &io_service, const bacnet::bvll::configuration& config) : io_service_(io_service),
                                                                    socket_(io_service),
                                                                    port_(config.listening_port),
                                                                    listen_address_(boost::asio::ip::address::from_string(config.listening_address)),
                                                                    multicast_address_(boost::asio::ip::address::from_string(config.multicast_address)),
                                                                    listen_endpoint_(listen_address_, port_) {
    init();
  }


  template<typename Buffer, typename Handler>
  void async_receive_from(const Buffer &buffer, boost::asio::ip::udp::endpoint &sender, const Handler &handler) {
   // std::cout << "async_receive_from(): " << std::endl;
    socket_.async_receive_from(buffer, sender, handler);
  }

  template<typename Buffer, typename Handler>
  void async_send_to(const Buffer &buffer, boost::asio::ip::udp::endpoint &receiver, const Handler &handler) {
    //std::cout << "async_send_to(): " << std::endl;
    socket_.async_send_to(buffer, receiver, handler);
  }


  template<typename Buffer, typename Handler>
  void async_send_broadcast(const Buffer &buffer, const Handler &handler) {

    boost::asio::ip::udp::endpoint receiver(multicast_address_, port_);
    //std::cout << "async_send_to(): " << receiver <<  std::endl;
    socket_.async_send_to(buffer, receiver, handler);
  }

private:



  void init() {
    socket_.open(listen_endpoint_.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.set_option(boost::asio::socket_base::broadcast(true));
    socket_.bind(listen_endpoint_);

    if (multicast_address_.to_string().compare(bacnet::bvll::config::DEFAULT_MULTICAST_ADDRESS) != 0) {
      socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address_));
    }


  }


  boost::asio::io_service &io_service_;
  boost::asio::ip::udp::socket socket_;
  uint16_t port_;
  boost::asio::ip::address listen_address_;
  boost::asio::ip::address multicast_address_;
  boost::asio::ip::udp::endpoint listen_endpoint_;


};

}}}

#endif //NINJA_WOOKIE_TRANSPORTER_HPP
