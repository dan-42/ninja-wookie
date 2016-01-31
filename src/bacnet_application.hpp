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

#ifndef NINJA_WOOKIE_BACNET_APPLICATION_HPP
#define NINJA_WOOKIE_BACNET_APPLICATION_HPP

#include <iostream>
#include <exception>

#include <limits>

#include <boost/asio.hpp>
#include <boost/format.hpp>

#include <bacnet/transport/api.hpp>
#include <bacnet/transport/ip_v4.hpp>

#include <bacnet/bvll/controller.hpp>
#include <bacnet/npdu/controller.hpp>
#include <bacnet/apdu/controller.hpp>
#include <bacnet/service/controller.hpp>
#include <bacnet/common/configuration.hpp>

#include <bacnet/common/object_identifier.hpp>
#include <bacnet/service/service/reinitialize_device.hpp>

struct my_bacnet_application {


  my_bacnet_application(boost::asio::io_service& io_s) : io_service(io_s),
                                                         transporter(io_service, {bvll_listening_ip, bvll_listening_port} ),
                                                                                 bvll_controller(io_service, transporter),
                                                                                 npdu_controller(bvll_controller),
                                                                                 apdu_controller(io_service, npdu_controller),
                                                                                 service_controller(io_service, apdu_controller, config) {

  }

  int run() {

    try {


      auto i_am_handler_ = [](boost::system::error_code ec, bacnet::common::protocol::meta_information mi, bacnet::service::i_am service) {

      };
      auto who_is_handler_ = [](boost::system::error_code ec, bacnet::common::protocol::meta_information mi, bacnet::service::who_is service) {

      };

      service_controller.async_receive(i_am_handler_, who_is_handler_);

      /**
       * sending a reinitialize device to device with DOI 2
       */
      bacnet::common::object_identifier doi{bacnet::object_type::device, 2};
      std::cout << "call reinit on doi: " << doi << std::endl;
      bacnet::service::service::reinitialize_device reinitd{0, "12345"};
      service_controller.async_send(doi, reinitd, [](const boost::system::error_code &ec, bacnet::service::possible_service_response response){
        std::cout << "async_send::reinitialize_device " << ec.category().name() << " " << ec.message() <<  std::endl;
      });



      io_service.run();
    }
    catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << "\n";
      throw;
    }


    return 0;
  }


    boost::asio::io_service& io_service;

    std::string bvll_listening_ip = "0.0.0.0";
    uint16_t    bvll_listening_port = 0xBAC0;

    typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;


    bacnet::config config{}; //default config

    bacnet::transport::ip_v4                                          transporter;
    bacnet::bvll::controller<decltype(transporter)>                   bvll_controller;
    bacnet::npdu::controller<decltype(bvll_controller)>               npdu_controller;
    bacnet::apdu::controller<decltype(npdu_controller),    apdu_size> apdu_controller;
    bacnet::service::controller<decltype(apdu_controller), apdu_size> service_controller;

};





#endif //NINJA_WOOKIE_BACNET_APPLICATION_HPP
