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
#include <bacnet/type/properties.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>

int main(int argc, char *argv[]) {

  try {
    uint16_t    doi{1};
    uint16_t    state{0};
    std::string password{};
    uint16_t    port{0xBAC0};
    std::string ip{"0.0.0.0"};
    uint32_t    object_instance{2};
    std::string object_type_str{""};
    uint32_t      object_type{bacnet::object_type::device};
    uint32_t      property{bacnet::type::property::object_name::value};
    boost::optional<uint32_t>      index;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help", "sending BACnet reinitialize device: e.g.  \n-doi 2  -state 0  -pw 123456")
        ("ip",    po::value<std::string>(&ip)      ->default_value("0.0.0.0"), "listening ip")
        ("port",  po::value<uint16_t>(&port)       ->default_value(0xBAC0),    "listening port")
        ("doi",   po::value<uint16_t>(&doi)                               ,    "device object identifier")
        ("pw",    po::value<std::string>(&password)->default_value(""),        "password")
        ("state", po::value<uint16_t>(&state)                         ,         "state:   coldstart(0)\n  "
                                                                                      "  warmstart(1)\n"
                                                                                      "  startbackup(2)\n"
                                                                                      "  endbackup(3)\n"
                                                                                      "  startrestore(4)\n"
                                                                                      "  endrestore(5)\n"
                                                                                      "  abortrestore(6)\n")

    ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);
/*
    if (vm.count("help") || vm.count("doi") == 0 || vm.count("state") == 0) {
        std::cout << desc << std::endl<< std::endl;
        return 1;
    }
*/
    std::cout
                << "reading property "
                << std::endl
                << " doi: "     << doi
                << " object_type: "   << object_type
                << " object_instance: "   << object_instance
                << " property: "   << property
                << " index: "  ;
                    if(index)
                      std::cout << index.get() ;
                    else
                      std::cout <<  "none";

    std::cout   << " on " << ip << ":"  << port
                << std::endl;


    boost::asio::io_service io_service;
    bacnet::stack::factory<bacnet::stack::ip_v4_client> factory{io_service, ip, port};
    auto &service_controller = factory.controller();

    bacnet::type::object_identifier device_id{bacnet::object_type::device, doi};
    bacnet::type::object_identifier object_id{object_type, object_instance};
    bacnet::service::service::read_property_request request;
    if(index) {
      request = bacnet::service::service::read_property_request{object_id, property, index.get()};
    }
    else {
      request = bacnet::service::service::read_property_request{object_id, property};
    }

    service_controller.start();

    service_controller.async_send(device_id, request, [&io_service](const bacnet::error &ec,  bacnet::service::confirmed::response response) {
                                                          if(ec) {
                                                            std::cout << "error occurred: " << ec <<  std::endl;
                                                          }
                                                          else {
                                                            std::cout << "response: " << pre::json::to_json(response).dump(2) <<  std::endl;
                                                          }
                                                          io_service.stop();
                                                       }
    );

    io_service.run();
  }
  catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw e;
  }
  return 0;
}
