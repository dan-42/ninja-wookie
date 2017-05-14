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
    uint16_t    doi{0};
    uint16_t    port{0xBAC0};
    std::string ip{"0.0.0.0"};
    std::string target{argv[1]};
    std::cout
    << "sending who is to " << target  << " on " << ip << ":"  << port
    << std::endl;

    boost::asio::io_service io_service;
    bacnet::common::config config;
    config.send_i_am_frames = false;
    bacnet::stack::factory<bacnet::stack::ip_v4_server> factory{io_service, ip, port, config};
    auto &service_controller = factory.controller();

    service_controller.async_receive([&](const bacnet::service::i_am &service, const bacnet::error &ec, const bacnet::common::protocol::meta_information &mi){
    	std::cout << "i-am from " << mi.address.ip().to_string()  << "  doi: " <<  service.i_am_device_identifier << std::endl;
    });


    service_controller.start();



    auto& apdu_controller = service_controller.underlying_layer();
    auto& npdu_controller = apdu_controller.underlying_layer();


    bacnet::common::protocol::mac::endpoint  ep(bacnet::common::protocol::mac::address_ip{target, 0xBAC0});

    bacnet::service::service::who_is wi;
    auto wi_data =  bacnet::service::service::detail::generate_unconfirmed(wi);

    bacnet::apdu::frame::unconfirmed_request frame;
    frame.pdu_type_and_control_information.pdu_type_ = bacnet::apdu::detail::pdu_type::unconfirmed_request;
    frame.service_data = wi_data;
    auto data = bacnet::apdu::frame::generator::generate(frame);

    npdu_controller.async_send_unicast(ep, std::move(data), []( const bacnet::error& ec) {
                  if(ec) {
                    std::cout << "ERR " << ec << std::endl;
                  }
                  else {
                    std::cout << "OK " << ec << std::endl;
                  }
            });



    io_service.run();
  }
  catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
