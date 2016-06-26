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
#include <bacnet/type/types.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>


int main(int argc, char *argv[]) {
  namespace prop = bacnet::type::property;

    uint16_t    port{0xBAC0};
    std::string ip{"0.0.0.0"};

    uint16_t                    doi;
    uint32_t                    object_instance;
    uint32_t                    object_type;
    uint32_t                    property;
    boost::optional<uint32_t>   index;

    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help",                "sending BACnet read property: e.g.  \n")
        ("ip",                  po::value<std::string>(&ip)             ->default_value("0.0.0.0"),                     "listening ip")
        ("port",                po::value<uint16_t>(&port)              ->default_value(0xBAC0),                        "listening port")
        ("doi",                 po::value<uint16_t>(&doi)               ->default_value(2),                             "device object identifier")
        ("object_instance",     po::value<uint32_t>(&object_instance)   ->default_value(2),                             "object_instance")
        ("object_type",         po::value<uint32_t>(&object_type)       ->default_value(bacnet::type::object_type::type{bacnet::type::object_type::device}),   "object_type")
        ("property",            po::value<uint32_t>(&property)          ->default_value(prop::object_name::value),      "property")
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
                << " doi: "               << doi
                << " object_type: "       << object_type
                << " object_instance: "   << object_instance
                << " property: "          << property
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

    //bacnet::type::object_identifier device_id{bacnet::type::object_type::type{bacnet::type::object_type::device}, doi};
    bacnet::type::object_identifier device_id{bacnet::type::object_type::device, doi};
    bacnet::type::object_identifier object_id{object_type, object_instance};
    bacnet::service::service::read_property_request request;
    if(index) {
      request = bacnet::service::service::read_property_request{object_id, property, index.get()};
    }
    else {
      request = bacnet::service::service::read_property_request{object_id, property};
    }

    service_controller.start();

    service_controller.async_send(device_id, request, [&io_service](const bacnet::error &ec,  bacnet::service::service::read_property_ack response) {
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

  return 0;
}
