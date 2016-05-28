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

#include <bacnet/stack/factory.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

int main(int argc, char *argv[]) {


  try {
    uint16_t    doi{1};
    uint16_t    port{0xBAC0};
    std::string ip{"0.0.0.0"};


    if(argc == 2 ) {
      doi       = (uint16_t)std::stoi(argv[1]);
    }
    else {
      std::cout
      << "error wrong parameters" << std::endl
      << "usage: " << std::endl
      << "\t" << argv[0] << " [doi] " << std::endl
      << std::endl
      << std::endl;

      return 1;
    }


    std::cout
    << "starting device  "
    << " doi: "     << doi
    << " on " << ip << ":"  << port
    << std::endl;

    boost::asio::io_service io_service;
    bacnet::config config;

    config.device_object_id = doi;
    config.network_number = 1;
    config.send_i_am_frames = true;

    bacnet::stack::factory<bacnet::stack::ip_v4> factory{io_service, ip, port, config};
    auto &service_controller = factory.controller();



    service_controller.async_receive(
      [&](bacnet::service::i_am s, bacnet::error_code ec, bacnet::common::protocol::meta_information mi){
        std::cout << "received i_am" << std::endl;
        // no action needed
      },
      [&](bacnet::service::who_is s, bacnet::error_code ec, bacnet::common::protocol::meta_information mi){
        std::cout << "received who_is" << std::endl;
        //no response needed, done automatically in the service-layer
      },
      [&](bacnet::service::reinitialize_device s, bacnet::error_code ec, bacnet::common::protocol::meta_information mi){
        std::cout << "received reinit" << std::endl;
        //xxx test password and state
        // send answer with OK or Error

        /*
         error
         bacnet::service::error error(class, reason)
         service_controller.response(mi, error);


         success simple
         bacnet::service::ack ack(s) //automatically choose service-choice by template specialization
         service_controller.response(mi, ack);
         */

      },
      [&](bacnet::service::read_property_request s, bacnet::error_code ec, bacnet::common::protocol::meta_information mi){
        std::cout << "received read_property" << std::endl;
        //xxx handle request
        // send answer with OK or Error

        /*
        error
        bacnet::service::error error(class, reason)
        service_controller.response(mi, error);


        success simple
        bacnet::service::ack ack(s) //automatically choose service-choice by template specialization
        service_controller.response(mi, ack);
        */

      }
    );



    service_controller.start();
    io_service.run();
  }
  catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
