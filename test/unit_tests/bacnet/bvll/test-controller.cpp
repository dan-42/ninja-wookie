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


#define BOOST_TEST_MODULE test ninja wookie bacnet bvll controller
#include <boost/test/included/unit_test.hpp>

#include <iostream>

#include <bacnet/transport/ip_v4_mockup.hpp>
#include <bacnet/bvll/controller.hpp>



BOOST_AUTO_TEST_SUITE( test_bvll_controller )

BOOST_AUTO_TEST_CASE( test_case1 ) {

  using namespace bacnet;
  using namespace bacnet::transport;
  using namespace bacnet::bvll;

  bacnet::binary_data data_to_send;
  data_to_send.push_back(0x00);
  data_to_send.push_back(0x01);
  data_to_send.push_back(0x02);
  data_to_send.push_back(0x03);

  async_send_from_stack_callback async_send_from_stack_callback_ = [](boost::asio::ip::udp::endpoint ep,  ::bacnet::binary_data data){
    auto ec = boost::system::errc::make_error_code(boost::system::errc::success);

    bacnet::binary_data expected_data;
    expected_data.push_back(0x81); //bacnet ipv4
    expected_data.push_back(0x0a); //original unicast
    expected_data.push_back(0x00); //
    expected_data.push_back(0x08); // 2byte length


    expected_data.push_back(0x00); //payload
    expected_data.push_back(0x01);
    expected_data.push_back(0x02);
    expected_data.push_back(0x03);

    BOOST_ASSERT_MSG(expected_data.size() == data.size(), "SEND DATA IS NOT THE SAME length");
    for(std::size_t idx = 0; idx < data.size(); ++idx) {
      BOOST_ASSERT_MSG(expected_data[idx] == data[idx], "SEND DATA IS NOT SAME");
    }

    boost::asio::ip::udp::endpoint expected_ep(boost::asio::ip::address_v4::broadcast(), 0xBAC0);
    //BOOST_ASSERT_MSG(expected_ep == ep, "ENDPOINT is not the expected one");

    return ec;
  };

  boost::asio::io_service ios;
  ip_v4_mockup transport(ios);
  transport.set_async_send_from_stack_callback(async_send_from_stack_callback_);





  bacnet::common::protocol::mac::address_ip address  = bacnet::common::protocol::mac::address_ip::from_string("192.168.10.1", 0xBAC0);

  controller<decltype(transport)> controller_(ios, transport);
  controller_.async_send(data_to_send, address, [](const boost::system::error_code &ec) {

  });


  ios.run();
}


BOOST_AUTO_TEST_SUITE_END()