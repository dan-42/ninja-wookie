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


#define BOOST_TEST_MODULE test ninja wookie bacnet transport ipv4 mockup
#include <boost/test/included/unit_test.hpp>

#include <iostream>

#include <bacnet/transport/ip_v4_mockup.hpp>



BOOST_AUTO_TEST_SUITE( test_transport_ipv4_mockup )

  BOOST_AUTO_TEST_CASE( test_case1 ) {

  using namespace bacnet;
  using namespace bacnet::transport;

  bacnet::binary_data data_to_send;
  data_to_send.push_back(0x00);
  data_to_send.push_back(0x01);
  data_to_send.push_back(0x02);
  data_to_send.push_back(0x03);

  ::bacnet::common::protocol::mac::address receiver(::bacnet::common::protocol::mac::address_ip::broadcast());



  receive_callback receive_callback_= [&data_to_send](boost::system::error_code ec, bacnet::common::protocol::mac::address adr, bacnet::binary_data &&data){
    BOOST_ASSERT_MSG(ec == boost::system::errc::argument_list_too_long, "ERROR_CODE WRONG");
    ::bacnet::common::protocol::mac::address expected_adr(::bacnet::common::protocol::mac::address_ip::from_string("192.168.10.1"));

    BOOST_ASSERT_MSG(adr == expected_adr, "WRONG ADDRESS");

    BOOST_ASSERT_MSG(data_to_send.size() == data.size(), "RECEIVED DATA IS NOT THE SAME length");
    for(std::size_t idx = 0; idx < data.size(); ++idx) {
      BOOST_ASSERT_MSG(data_to_send[idx] == data[idx], "RECEIVED DATA IS NOT SAME");
    }

  };
  from_application_callback async_send_from_stack_callback_ = [&data_to_send](boost::asio::ip::udp::endpoint ep,  ::bacnet::binary_data data){
    auto ec = boost::system::errc::make_error_code(boost::system::errc::success);

    BOOST_ASSERT_MSG(data_to_send.size() == data.size(), "SEND DATA IS NOT THE SAME length");
    for(std::size_t idx = 0; idx < data.size(); ++idx) {
      BOOST_ASSERT_MSG(data_to_send[idx] == data[idx], "SEND DATA IS NOT SAME");
    }

    boost::asio::ip::udp::endpoint expected_ep(boost::asio::ip::address_v4::broadcast(), 0xBAC0);
    BOOST_ASSERT_MSG(expected_ep == ep, "ENDPOINT is not the expected one");

    return ec;
  };

  boost::asio::io_service ios;
  ip_v4_mockup transport(ios);
  transport.register_receive_callback(receive_callback_);
  transport.set_from_application_callback(async_send_from_stack_callback_);

  transport.async_send(data_to_send, receiver, [](const boost::system::error_code& ec){
    BOOST_ASSERT_MSG(ec == boost::system::errc::success, "SEND WAS NOT SUCCESSFULL");
  });

  auto ec = boost::system::errc::make_error_code(boost::system::errc::argument_list_too_long);
  ::bacnet::common::protocol::mac::address ep(::bacnet::common::protocol::mac::address_ip::from_string("192.168.10.1"));
    auto d = data_to_send;
  //transport.send_to_application(ec, ep , std::move(d));
    transport.send_to_application(ec, ep , d);

  transport.start();
  ios.run();
}


BOOST_AUTO_TEST_SUITE_END()
