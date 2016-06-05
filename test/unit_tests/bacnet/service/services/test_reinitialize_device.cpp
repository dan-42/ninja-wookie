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

  using namespace bacnet;
  using namespace bacnet::transport;

  bacnet::type::object_identifier device_doi{2};
  auto who_is_2_request           = bacnet::make_binary<bacnet::hex_string>("81 0b 00 10 01 20 ff ff 00 ff 10 08  09 02  19 02");
  auto i_am_answer                = bacnet::make_binary<bacnet::hex_string>("81 0b 00 19 01 20 ff ff 00 ff 10 00 c4 02 00 00 02 22 05 c4 91 03 22 01 04");
  // id 0  pw 12345
  auto reinitialize_request_pw_12345 = bacnet::make_binary<bacnet::hex_string>("81 0a 00 14 01 00 00 05 03 14 09 00 1d 06 00 31 32 33 34 35");
  auto reinitialize_request          = bacnet::make_binary<bacnet::hex_string>("81 0a 00 0c 01 00 00 05 00 14 09 00 ");
  auto reinitialize_device_ack       = bacnet::make_binary<bacnet::hex_string>("81 0a 00 09 01 00 20 05 14");
  //class security  nr password_failure
  auto reinitialize_device_error  = bacnet::make_binary<bacnet::hex_string>("81 0a 00 0d 01 00 05 03 14 91 04 91 1a 00 00 00");

  boost::asio::ip::udp::endpoint broadcast_endpoint(boost::asio::ip::address_v4::from_string("255.255.255.255"), 0xBAC0);
  boost::asio::ip::udp::endpoint unicast_endpoint_device(boost::asio::ip::address_v4::from_string("192.168.10.1"), 0xBAC0);
  boost::asio::ip::udp::endpoint unicast_endpoint_client(boost::asio::ip::address_v4::from_string("192.168.10.2"), 0xBAC0);
  auto ec_succsess = boost::system::errc::make_error_code(boost::system::errc::success);
  auto bacnet_ec_succsess = bacnet::error(ec_succsess);



  BOOST_AUTO_TEST_CASE( test_send_reinitialize_device_doi ) {

    enum class test_state {
      who_is,
      reinitialize_device
    };

    test_state state = test_state::who_is;

    boost::asio::io_service ios;
    ip_v4_mockup transport_mockup(ios);

    /*
     * first we expect a who_is -> send I-Am
     * second we expect a reinitialdevice and send success
     */
    auto from_application_callback_ = [&](boost::asio::ip::udp::endpoint ep,  ::bacnet::binary_data data) {

      if(state == test_state::who_is) {
        std::cout << "data ";  bacnet::print(data);
        std::cout << "expt ";  bacnet::print(who_is_2_request);

        BOOST_TEST(test::utils::compare_binary_data(who_is_2_request, data), "SEND DATA IS NOT THE SAME as who_is_2_request");
        BOOST_TEST(broadcast_endpoint == ep, "ENDPOINT is not the expected broadcast_endpoint ");
        state = test_state::reinitialize_device;
        transport_mockup.send_to_application(ec_succsess, unicast_endpoint_device, i_am_answer);
      }
      else if(state == test_state::reinitialize_device) {
        std::cout << "data ";  bacnet::print(data);
        std::cout << "expt ";  bacnet::print(reinitialize_request);
        BOOST_TEST(test::utils::compare_binary_data(reinitialize_request, data), "SEND DATA IS NOT THE SAME as reinitialize_request");
        BOOST_TEST(unicast_endpoint_device == ep, "ENDPOINT is not the expected unicast_endpoint_device ");
        transport_mockup.send_to_application(ec_succsess, unicast_endpoint_device, reinitialize_device_ack);
      }
      return ec_succsess;
    };

    transport_mockup.set_from_application_callback(from_application_callback_);

    /**   *    */
    typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;
    bacnet::config config{};
    config.send_i_am_frames = false;
    bvll::controller<decltype(transport_mockup)> bvll_controller_(ios, transport_mockup);
    npdu::controller<decltype(bvll_controller_)> npdu_controller_(bvll_controller_);
    bacnet::apdu::controller<decltype(npdu_controller_),    apdu_size> apdu_controller(ios, npdu_controller_);
    bacnet::service::controller<decltype(apdu_controller), apdu_size> service_controller(ios, apdu_controller, config);
    service_controller.start();

    bacnet::service::reinitialize_device reinitialize_device_{bacnet::service::reinitialized_state_of_device::coldstart};
    service_controller.async_send(device_doi, reinitialize_device_, []
                 (const bacnet::error &ec){
                    std::cout << "async_send::reinitialize_device " << ec <<  std::endl;
                    BOOST_TEST( !ec, "Expected successful");
                 }
    );

    ios.run();
  }


////////////////////////////////////////////////////////////////////////////////////////////////////

  BOOST_AUTO_TEST_CASE( test_send_reinitialize_device_doi_wrong_pw ) {

    enum class test_state {
      who_is,
      reinitialize_device
    };

    test_state state = test_state::who_is;

    boost::asio::io_service ios;
    ip_v4_mockup transport_mockup(ios);

    /*
     * first we expect a who_is -> send I-Am
     * second we expect a reinitialdevice and send an error back
     */
    auto from_application_callback_ = [&](boost::asio::ip::udp::endpoint ep,  ::bacnet::binary_data data) {

      std::cout << "from_application_callback_ data: -> ";  bacnet::print(data);
      if(state == test_state::who_is) {
        BOOST_TEST(test::utils::compare_binary_data(who_is_2_request, data), "SEND DATA IS NOT THE SAME as who_is_2_request");
        BOOST_TEST(broadcast_endpoint == ep, "ENDPOINT is not the expected broadcast_endpoint ");
        state = test_state::reinitialize_device;
        std::cout << "from_application_callback_ data: <- ";  bacnet::print(i_am_answer);
        transport_mockup.send_to_application(ec_succsess, unicast_endpoint_device, i_am_answer);
      }
      else if(state == test_state::reinitialize_device) {
        BOOST_TEST(test::utils::compare_binary_data(reinitialize_request, data), "SEND DATA IS NOT THE SAME as reinitialize_request");
        BOOST_TEST(unicast_endpoint_device == ep, "ENDPOINT is not the expected unicast_endpoint_device ");
        std::cout << "from_application_callback_ data: <- ";  bacnet::print(reinitialize_device_ack);
        transport_mockup.send_to_application(ec_succsess, unicast_endpoint_device, reinitialize_device_ack);
      }
      return ec_succsess;
    };

    transport_mockup.set_from_application_callback(from_application_callback_);

    /**   *    */
    typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;
    bacnet::config config{};
    config.send_i_am_frames = false;
    bvll::controller<decltype(transport_mockup)> bvll_controller_(ios, transport_mockup);
    npdu::controller<decltype(bvll_controller_)> npdu_controller_(bvll_controller_);
    bacnet::apdu::controller<decltype(npdu_controller_),    apdu_size> apdu_controller(ios, npdu_controller_);
    bacnet::service::controller<decltype(apdu_controller), apdu_size> service_controller(ios, apdu_controller, config);
    service_controller.start();

    bacnet::service::reinitialize_device reinitialize_device_{bacnet::service::reinitialized_state_of_device::coldstart};
    service_controller.async_send(device_doi, reinitialize_device_, []
                 (const bacnet::error &ec){
                    std::cout << "async_send::reinitialize_device " << ec <<  std::endl;
                    BOOST_TEST( !ec , "Expected successful");
                 }
    );

    ios.run();
  }


////////////////////////////////////////////////////////////////////////////////////////////////////



BOOST_AUTO_TEST_SUITE_END()
