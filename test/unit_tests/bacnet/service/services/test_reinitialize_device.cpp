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


#define BOOST_TEST_MODULE test ninja wookie bacnet service services reinitialize_device
#include <boost/test/included/unit_test.hpp>

#include <iostream>

#include <utils/utils.hpp>

#include <bacnet/transport/ip_v4_mockup.hpp>
#include <bacnet/bvll/controller.hpp>
#include <bacnet/npdu/controller.hpp>
#include <bacnet/apdu/controller.hpp>
#include <bacnet/service/controller.hpp>
#include <bacnet/common/configuration.hpp>

BOOST_AUTO_TEST_SUITE( test_services_reinitialize_device )

  BOOST_AUTO_TEST_CASE( test_send_reinitialize_device_doi ) {

    using namespace bacnet;
    using namespace bacnet::transport;

    /**
     * expected data
     */
    bacnet::binary_data expected_data;
    //bvll
    expected_data.push_back(0x81); //bacnet ipv4
    expected_data.push_back(0x0b); //original broadcast
    expected_data.push_back(0x00); //
    expected_data.push_back(0xc); // 2byte length
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

    boost::asio::ip::udp::endpoint expected_ep(boost::asio::ip::address_v4::from_string("255.255.255.255"), 0xBAC0);

    auto ec_succsess = boost::system::errc::make_error_code(boost::system::errc::success);

    /*
     * actual test function
     */
    auto async_send_from_stack_callback_ = [&](boost::asio::ip::udp::endpoint ep,  ::bacnet::binary_data data) {
      bacnet::print(data);
      bacnet::print(expected_data);
      BOOST_ASSERT_MSG(test::utils::compare_binary_data(expected_data, data), "SEND DATA IS NOT THE SAME ");
      BOOST_ASSERT_MSG(expected_ep == ep, "ENDPOINT is not the expected one");

      return ec_succsess;
    };


    boost::asio::io_service ios;
    ip_v4_mockup transport_mockup(ios);
    transport_mockup.set_async_send_from_stack_callback(async_send_from_stack_callback_);
    transport_mockup.set_async_receive_callback([](boost::system::error_code ec, bacnet::common::protocol::mac::address adr, bacnet::binary_data data) {
    });


    /**
     * test mockup
     */
    bvll::controller<decltype(transport_mockup)> bvll_controller_(ios, transport_mockup);
    transport_mockup.set_async_send_from_stack_callback(async_send_from_stack_callback_);


    /**
     * setup default stack
     */
    typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;
    bacnet::config config{}; //default config

    npdu::controller<decltype(bvll_controller_)> npdu_controller_(bvll_controller_);
    bacnet::apdu::controller<decltype(npdu_controller_),    apdu_size> apdu_controller(ios, npdu_controller_);
    bacnet::service::controller<decltype(apdu_controller), apdu_size> service_controller(ios, apdu_controller, config);


    /**
     * sending who is with no limits
     */
    bacnet::service::who_is who_is_service{};

    service_controller.async_send(who_is_service, [](const boost::system::error_code &ec){

    });


    ios.run();
  }


////////////////////////////////////////////////////////////////////////////////////////////////////



  BOOST_AUTO_TEST_CASE( test_send_who_is_with_limits ) {

    using namespace bacnet;
    using namespace bacnet::transport;

    /**
     * expected data
     */
    bacnet::binary_data expected_data;
    //bvll
    expected_data.push_back(0x81); //bacnet ipv4
    expected_data.push_back(0x0b); //original broadcast
    expected_data.push_back(0x00); //
    expected_data.push_back(0x10); // 2byte length
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

    //TAG 0
    expected_data.push_back(0x09);
    expected_data.push_back(0x01);
    //TAG 1
    expected_data.push_back(0x19);
    expected_data.push_back(0x01);


    boost::asio::ip::udp::endpoint expected_ep(boost::asio::ip::address_v4::from_string("255.255.255.255"), 0xBAC0);

    auto ec_succsess = boost::system::errc::make_error_code(boost::system::errc::success);

    /*
     * actual test function
     */
    auto async_send_from_stack_callback_ = [&](boost::asio::ip::udp::endpoint ep,  ::bacnet::binary_data data) {

      bacnet::print(data);
      bacnet::print(expected_data);
      BOOST_ASSERT_MSG(test::utils::compare_binary_data(expected_data, data), "SEND DATA IS NOT THE SAME ");
      BOOST_ASSERT_MSG(expected_ep == ep, "ENDPOINT is not the expected one");

      return ec_succsess;
    };


    boost::asio::io_service ios;
    ip_v4_mockup transport_mockup(ios);
    transport_mockup.set_async_send_from_stack_callback(async_send_from_stack_callback_);
    transport_mockup.set_async_receive_callback([](boost::system::error_code ec, bacnet::common::protocol::mac::address adr, bacnet::binary_data data) {
    });


    /**
     * test mockup
     */
    bvll::controller<decltype(transport_mockup)> bvll_controller_(ios, transport_mockup);
    transport_mockup.set_async_send_from_stack_callback(async_send_from_stack_callback_);


    /**
     * setup default stack
     */
    typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;
    bacnet::config config{}; //default config

    npdu::controller<decltype(bvll_controller_)> npdu_controller_(bvll_controller_);
    bacnet::apdu::controller<decltype(npdu_controller_),    apdu_size> apdu_controller(ios, npdu_controller_);
    bacnet::service::controller<decltype(apdu_controller), apdu_size> service_controller(ios, apdu_controller, config);


    /**
     * sending who is with no limits
     */

    bacnet::service::who_is who_is_service{1,1};
    service_controller.async_send(who_is_service, [](const boost::system::error_code &ec){

    });


    ios.run();
  }


  ////////////////////////////////////////////////////////////////////////////////////////////////////



  BOOST_AUTO_TEST_CASE( test_receive_who_is ) {

    using namespace bacnet;
    using namespace bacnet::transport;

    /**
     * expected data
     */
    bacnet::binary_data send_data;
    //bvll
    send_data.push_back(0x81); //bacnet ipv4
    send_data.push_back(0x0b); //original broadcast
    send_data.push_back(0x00); //
    send_data.push_back(0x0c); // 2byte length
    //npdu
    send_data.push_back(0x01); //version
    send_data.push_back(0x20); //control info
    send_data.push_back(0xff); //network number
    send_data.push_back(0xff);
    send_data.push_back(0x00); //MAX
    send_data.push_back(0xff); //hop count
    //apdu
    send_data.push_back(0x10); //unconfirmed service
    send_data.push_back(0x08); //who is

    boost::asio::ip::udp::endpoint send_ep(boost::asio::ip::address_v4::from_string("255.255.255.255"), 0xBAC0);
    ::bacnet::common::protocol::mac::address send_adr(::bacnet::common::protocol::mac::address_ip::from_native(send_ep));

    auto send_ec = boost::system::errc::make_error_code(boost::system::errc::success);



    /**
     * test mockup
     */
    boost::asio::io_service ios;
    ip_v4_mockup transport_mockup(ios);
    transport_mockup.set_async_send_from_stack_callback([](boost::asio::ip::udp::endpoint ep,  ::bacnet::binary_data data) {
     return boost::system::errc::make_error_code(boost::system::errc::success);
    });

    /**
     * setup default stack
     */
    typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;
    bacnet::config config{}; //default config
    bvll::controller<decltype(transport_mockup)> bvll_controller_(ios, transport_mockup);
    npdu::controller<decltype(bvll_controller_)> npdu_controller_(bvll_controller_);
    bacnet::apdu::controller<decltype(npdu_controller_),    apdu_size> apdu_controller(ios, npdu_controller_);
    bacnet::service::controller<decltype(apdu_controller), apdu_size> service_controller(ios, apdu_controller, config);


    /**
     * receiving who_is
     */
    service_controller.async_receive([&](boost::system::error_code ec, bacnet::common::protocol::meta_information mi, bacnet::service::who_is service) {

      boost::system::error_code expected_ec{bacnet::service::error::errc::success, bacnet::service::error::get_error_category()};
      BOOST_ASSERT_MSG(ec == expected_ec, " Error code is wrong ");

      boost::asio::ip::udp::endpoint expected_ep(boost::asio::ip::address_v4::from_string("255.255.255.255"), 0xBAC0);
      ::bacnet::common::protocol::mac::address expected_adr(::bacnet::common::protocol::mac::address_ip::from_native(send_ep));
      BOOST_ASSERT_MSG(mi.address == expected_adr, " Error mac address  wrong");

      BOOST_ASSERT_MSG(service.device_instance_range_high_limit == 0 , "Error range must be 0");
      BOOST_ASSERT_MSG(service.device_instance_range_low_limit == 0 , "Error range must be 0");

    });

    transport_mockup.async_send_to_stack(send_ec, send_adr, send_data);



    ios.run();
  }


  ////////////////////////////////////////////////////////////////////////////////////////////////////



  BOOST_AUTO_TEST_CASE( test_receive_who_is_with_limits ) {

    using namespace bacnet;
    using namespace bacnet::transport;

    /**
     * expected data
     */
    bacnet::binary_data expected_data;
    //bvll
    expected_data.push_back(0x81); //bacnet ipv4
    expected_data.push_back(0x0b); //original broadcast
    expected_data.push_back(0x00); //
    expected_data.push_back(0x10); // 2byte length
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

    //TAG 0
    expected_data.push_back(0x09);
    expected_data.push_back(0x01);
    //TAG 1
    expected_data.push_back(0x19);
    expected_data.push_back(0x01);


    boost::asio::ip::udp::endpoint expected_ep(boost::asio::ip::address_v4::from_string("255.255.255.255"), 0xBAC0);

    auto ec_succsess = boost::system::errc::make_error_code(boost::system::errc::success);

    /*
     * actual test function
     */
    auto async_send_from_stack_callback_ = [&](boost::asio::ip::udp::endpoint ep,  ::bacnet::binary_data data) {

      bacnet::print(data);
      bacnet::print(expected_data);
      BOOST_ASSERT_MSG(test::utils::compare_binary_data(expected_data, data), "SEND DATA IS NOT THE SAME ");
      BOOST_ASSERT_MSG(expected_ep == ep, "ENDPOINT is not the expected one");

      return ec_succsess;
    };


    boost::asio::io_service ios;
    ip_v4_mockup transport_mockup(ios);
    transport_mockup.set_async_send_from_stack_callback(async_send_from_stack_callback_);
    transport_mockup.set_async_receive_callback([](boost::system::error_code ec, bacnet::common::protocol::mac::address adr, bacnet::binary_data data) {
    });


    /**
     * test mockup
     */
    bvll::controller<decltype(transport_mockup)> bvll_controller_(ios, transport_mockup);
    transport_mockup.set_async_send_from_stack_callback(async_send_from_stack_callback_);


    /**
     * setup default stack
     */
    typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;
    bacnet::config config{}; //default config

    npdu::controller<decltype(bvll_controller_)> npdu_controller_(bvll_controller_);
    bacnet::apdu::controller<decltype(npdu_controller_),    apdu_size> apdu_controller(ios, npdu_controller_);
    bacnet::service::controller<decltype(apdu_controller), apdu_size> service_controller(ios, apdu_controller, config);


    /**
     * sending who is with no limits
     */

    bacnet::service::who_is who_is_service{1,1};
    service_controller.async_send(who_is_service, [](const boost::system::error_code &ec){

    });


    ios.run();
  }

BOOST_AUTO_TEST_SUITE_END()