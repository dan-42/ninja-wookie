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


#define BOOST_TEST_MODULE test ninja wookie bacnet service services who-is-i-am
#include <boost/test/included/unit_test.hpp>

#include <iostream>

#include <bacnet/transport/ip_v4_mockup.hpp>
#include <bacnet/bvll/controller.hpp>
#include <bacnet/npdu/controller.hpp>
#include <bacnet/apdu/controller.hpp>


BOOST_AUTO_TEST_SUITE( test_services_who_is_i_am )

  BOOST_AUTO_TEST_CASE( test_send_who_is ) {

    using namespace bacnet;
    using namespace bacnet::transport;


    async_send_from_stack_callback async_send_from_stack_callback_ = [](boost::asio::ip::udp::endpoint ep,  ::bacnet::binary_data data){
      auto ec = boost::system::errc::make_error_code(boost::system::errc::success);

      bacnet::binary_data expected_data;
      //bvll
      expected_data.push_back(0x81); //bacnet ipv4
      expected_data.push_back(0x0b); //original broadcast
      expected_data.push_back(0x00); //
      expected_data.push_back(0x0c); // 2byte length
      //npdu
      expected_data.push_back(0x01); //version
      expected_data.push_back(0x20); //control info
      expected_data.push_back(0xff); //network number
      expected_data.push_back(0xff);
      expected_data.push_back(0x00); //MAX
      expected_data.push_back(0xff); //hop count
      //apdu
      expected_data.push_back(0x10); //unconfirmed service
      expected_data.push_back(0x08); //who is


      BOOST_ASSERT_MSG(expected_data.size() == data.size(), "SEND DATA IS NOT THE SAME length");
      for(std::size_t idx = 0; idx < data.size(); ++idx) {
        BOOST_ASSERT_MSG(expected_data[idx] == data[idx], "SEND DATA IS NOT SAME");
      }

      boost::asio::ip::udp::endpoint expected_ep(boost::asio::ip::address_v4::from_string("255.255.255.255"), 0xBAC0);
      BOOST_ASSERT_MSG(expected_ep == ep, "ENDPOINT is not the expected one");

      return ec;
    };


    boost::asio::io_service ios;
    ip_v4_mockup transport_(ios);
    transport_.set_async_send_from_stack_callback(async_send_from_stack_callback_);
    transport_.set_async_receive_callback([](boost::system::error_code ec, bacnet::common::protocol::mac::address adr, bacnet::binary_data data){

    });


    bvll::controller<decltype(transport_)> bvll_controller_(ios, transport_);
    npdu::controller<decltype(bvll_controller_)> npdu_controller_(bvll_controller_);

    transport_.set_async_send_from_stack_callback(async_send_from_stack_callback_);

    bacnet::binary_data data_to_send;
    data_to_send.push_back(0x10); //unconfirmed service
    data_to_send.push_back(0x08); //who is
    npdu_controller_.async_send_broadcast(data_to_send, [](const boost::system::error_code &ec) {
    });

    ios.run();
  }


////////////////////////////////////////////////////////////////////////////////////////////////////




BOOST_AUTO_TEST_SUITE_END()