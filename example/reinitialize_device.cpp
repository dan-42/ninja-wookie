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
    uint16_t    state{0};
    std::string password{};
    uint16_t    port{0xBAC0};
    std::string ip{"0.0.0.0"};


    if(argc == 3 ) {
      doi       = (uint16_t)std::stoi(argv[1]);
      state     = (uint16_t)std::stoi(argv[2]);
    }
    else if(argc == 4 ) {
      doi       = (uint16_t)std::stoi(argv[1]);
      state     = (uint16_t)std::stoi(argv[2]);
      password  = std::string{argv[3]};
    }
    else if(argc == 5 ) {
      doi       = (uint16_t)std::stoi(argv[1]);
      state     = (uint16_t)std::stoi(argv[2]);
      password  = std::string{argv[3]};
      port      = (uint16_t)std::stoi(argv[4]);
    }
    else if(argc == 6 ) {
      doi       = (uint16_t)std::stoi(argv[1]);
      state     = (uint16_t)std::stoi(argv[2]);
      password  = std::string{argv[3]};
      port      = (uint16_t)std::stoi(argv[4]);
      ip        = std::string{argv[5]};
    }
    else {
      std::cout
      << "error wrong parameters" << std::endl
      << "usage: " << std::endl
      << "\t" << argv[0] << " [doi] [state] " << std::endl
      << "\t" << argv[0] << " [doi] [state] [password]" << std::endl
      << "\t" << argv[0] << " [doi] [state] [password] [port]" << std::endl
      << "\t" << argv[0] << " [doi] [state] [password] [port] [ip_address]" << std::endl
      << std::endl
      << "example:" << std::endl
      << "\t" << argv[0] << " 1 \"12345\" 47808 \"0.0.0.0\" " << std::endl
      << std::endl;

      return 1;
    }


    std::cout
    << "sending reinitialize_device to "
    << " doi: "     << doi
    << " state: "   << state
    << " with password: "   << password
    << " on " << ip << ":"  << port
    << std::endl;

    boost::asio::io_service io_service;
    bacnet::config config;
    config.send_i_am_frames = false;
    bacnet::stack::factory<bacnet::stack::ip_v4> factory{io_service, ip, port, config};
    auto &service_controller = factory.controller();

    bacnet::common::object_identifier device_id{bacnet::object_type::device, 2};
    bacnet::service::service::reinitialize_device reinitd{state, password};

    service_controller.start();


    service_controller.async_send(device_id, reinitd, [&]
                 (const boost::system::error_code &ec, bacnet::service::possible_service_response response){
                    std::cout << "async_send::reinitialize_device " << ec.category().name() << " " << ec.message() <<  std::endl;
                  }
    );


    io_service.run();
  }
  catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
