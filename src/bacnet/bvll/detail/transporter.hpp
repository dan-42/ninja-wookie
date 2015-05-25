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


namespace bacnet {   namespace  bvll {  namespace detail {


class transporter {

public:

  const uint16_t DEFAULT_PORT = 0xBAC0;
  const std::string DEFAULT_ADDRESS{"255.255.255.255"};


  transporter(boost::asio::io_service &io_service) : io_service_(io_service), socket_(io_service) {
    init();
  }

  transporter(boost::asio::io_service &io_service, uint16_t port) : io_service_(io_service), socket_(io_service),
                                                                    port_(port) {
    init();
  }

  transporter(boost::asio::io_service &io_service, const std::string multicast_address, uint16_t port) :
      io_service_(io_service), socket_(io_service), port_(port),
      multicast_address_(boost::asio::ip::address::from_string(multicast_address)) {
    init();
  }

  template<typename Buffer, typename Handler>
  void async_receive_from(const Buffer &buffer, boost::asio::ip::udp::endpoint &sender, const Handler &handler) {
    std::cout << "async_receive_from(): " << std::endl;
    socket_.async_receive_from(buffer, sender, handler);
  }

  template<typename Buffer, typename Handler>
  void async_send_to(const Buffer &buffer, boost::asio::ip::udp::endpoint &receiver, const Handler &handler) {
    std::cout << "async_send_to(): " << std::endl;
    socket_.async_send_to(buffer, receiver, handler);
  }


private:
  //xxx to be setable by user for specific interface?
  const boost::asio::ip::address listen_address_ = boost::asio::ip::address::from_string("0.0.0.0");

  void init() {
    std::cout << "init(): " << std::endl;
    listen_endpoint = boost::asio::ip::udp::endpoint(listen_address_, port_);

    socket_.open(listen_endpoint.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(listen_endpoint);


    if (multicast_address_.to_string().compare(DEFAULT_ADDRESS) != 0) {
      socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address_));
    }


  }

  boost::asio::ip::address multicast_address_ = boost::asio::ip::address::from_string(DEFAULT_ADDRESS);
  uint16_t port_ = DEFAULT_PORT;

  boost::asio::io_service &io_service_;
  boost::asio::ip::udp::socket socket_;
  boost::asio::ip::udp::endpoint listen_endpoint;
};


}}}

#endif //NINJA_WOOKIE_TRANSPORTER_HPP