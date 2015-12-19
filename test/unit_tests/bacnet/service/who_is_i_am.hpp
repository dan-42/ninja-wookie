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



#ifndef NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_SERVICE_WHO_IS_I_AM_HPP
#define NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_SERVICE_WHO_IS_I_AM_HPP


#include <iostream>
#include <exception>

#include <limits>

#include <boost/asio.hpp>
#include <boost/format.hpp>

#include <bacnet/transport/api.hpp>
#include <bacnet/transport/ip_v4_mockup.hpp>

#include <bacnet/bvll/controller.hpp>
#include <bacnet/npdu/controller.hpp>
#include <bacnet/apdu/controller.hpp>
#include <bacnet/service/controller.hpp>
#include <bacnet/common/configuration.hpp>

#include <bacnet/common/object_identifier.hpp>
#include <bacnet/service/service/reinitialize_device.hpp>



/*
struct test_who_is_i_am_service {
    boost::asio::io_service& io_service;


    typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;


    bacnet::config config{}; //default config

    bacnet::transport::ip_v4_mockup                                   transporter;
    bacnet::bvll::controller<decltype(transporter)>                   bvll_controller;
    bacnet::npdu::controller<decltype(bvll_controller)>               npdu_controller;
    bacnet::apdu::controller<decltype(npdu_controller),    apdu_size> apdu_controller;
    bacnet::service::controller<decltype(apdu_controller), apdu_size> service_controller;

    test_who_is_i_am_service(boost::asio::io_service& io_s) : io_service(io_s),
                                                           transporter(io_service),
                                                           bvll_controller(io_service, transporter),
                                                           npdu_controller(bvll_controller),
                                                           apdu_controller(io_service, npdu_controller),
                                                           service_controller(io_service, apdu_controller, config) {

    }

    void init() {
      transporter.
    }

    int run() {


      try {

        auto i_am_handler_ = [](boost::system::error_code ec, bacnet::common::protocol::meta_information mi, bacnet::service::i_am i_am) {
        };
        service_controller.async_receive<bacnet::service::i_am, bacnet::service::callback_service_i_am_t>(i_am_handler_);


        auto who_is_handler_ = [this](boost::system::error_code ec, bacnet::common::protocol::meta_information mi, bacnet::service::who_is who_is) {
          std::cout << "async_receive::who_is " << ec.category().name() << " " << ec.message() <<  std::endl;
          if(!ec) {

            bacnet::service::i_am i_am_;
            i_am_.i_am_device_identifier.object_typ(bacnet::object_type::device);
            i_am_.i_am_device_identifier.instance_number(config.device_object_id);
            i_am_.segmentation_supported = config.segmentation;
            i_am_.vendor_id              = config.vendor_id;
            i_am_.max_apdu_length_accepted = apdu_size::size_in_bytes;


            service_controller.async_send(i_am_, [this](boost::system::error_code ec){
              std::cout << "async_send::i_am " << ec.category().name() << " " << ec.message() <<  std::endl;
            });

          } else {

          }
        };
        service_controller.async_receive<bacnet::service::who_is, bacnet::service::callback_service_who_is_t>(who_is_handler_);

      }
      catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << "\n";
        throw;
      }

      return 0;
    }

};


BOOST_AUTO_TEST_SUITE( service_who_is_i_am)

BOOST_AUTO_TEST_CASE( test_case1 )

BOOST_ASSERT_MSG( 1 == 1, "OK");

BOOST_AUTO_TEST_SUITE_END()

*/


#endif //NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_SERVICE_WHO_IS_I_AM_HPP

