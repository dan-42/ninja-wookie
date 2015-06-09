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
#include <iostream>
#include <iomanip>
#include <bitset>

#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include <bacnet/bvll/frames.hpp>

#include <bacnet/bvll/detail/inbound_router.hpp>
#include <bacnet/bvll/detail/transporter.hpp>


namespace bacnet { namespace  bvll {

class controller {

public:

  controller(boost::asio::io_service &ios) : io_service_(ios), transporter_(ios), inbound_router_(transporter_) {
    start();
  }

  controller(boost::asio::io_service &ios, uint16_t port) : io_service_(ios), transporter_(ios, port), inbound_router_(transporter_)  {
    start();
  }

  void start() {
    data_.reserve(std::numeric_limits<uint16_t>::max());

    auto callback = boost::bind(&controller::handle_receive_from, this, boost::asio::placeholders::error,
                                boost::asio::placeholders::bytes_transferred);
    transporter_.async_receive_from(boost::asio::buffer(data_, std::numeric_limits<uint16_t>::max()), sender_endpoint_, callback);
  }

  void handle_receive_from(const boost::system::error_code &error, size_t bytes_recvd) {
    if (!error) {
      std::cout << "received from: " << sender_endpoint_.address().to_string()
      << ":" << (int) sender_endpoint_.port() << std::endl;
      bacnet::binary_data input(data_.begin(), data_.begin()+bytes_recvd);

      for(auto c : data_){
        //std::bitset<8> b(c);
        //std::cout << b.to_string();
        std::cout << " 0x" << std::setw(2) << std::setfill('0') << std::hex << (int) c ;
      }
      std::cout << std::endl;

      frame::possible_bvll_frame f = parser::parse(input);
      boost::apply_visitor(inbound_router_, f);

      data_.clear();
      data_.reserve(std::numeric_limits<uint16_t>::max());
      auto callback = boost::bind(&controller::handle_receive_from, this, boost::asio::placeholders::error,
                                  boost::asio::placeholders::bytes_transferred);
      transporter_.async_receive_from(boost::asio::buffer(data_, std::numeric_limits<uint16_t>::max()), sender_endpoint_, callback);
    }
  }

  template<typename Handler>
  void async_send_broadcast(const bacnet::binary_data &payload, const Handler &handler){

    frame::original_broadcast_npdu frame;
    frame.npdu_data = payload;
    frame::possible_bvll_frame f(frame);

    bacnet::binary_data binary_frame = generator::generate(f);
    transporter_.async_send_broadcast(boost::asio::buffer(binary_frame), handler);
  }


private:

  boost::asio::io_service &io_service_;
  boost::asio::ip::udp::endpoint sender_endpoint_;

  std::vector<uint8_t> data_;

  bacnet::bvll::detail::transporter transporter_;
  bacnet::bvll::detail::inbound_router inbound_router_;
};


}}

#endif //NINJA_WOOKIE_CONTROLLER_HPP
