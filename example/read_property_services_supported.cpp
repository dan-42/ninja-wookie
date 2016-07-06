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

    uint16_t                    doi{2};
    uint32_t                    object_instance{doi};
    uint32_t                    object_type{bacnet::type::object_type::device};
    uint32_t                    property{bacnet::type::property::protocol_services_supported::value};
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help",                "sending BACnet read property: e.g.  \n")
        ("ip",                  po::value<std::string>(&ip)             ->default_value("0.0.0.0"),                     "listening ip")
        ("port",                po::value<uint16_t>(&port)              ->default_value(0xBAC0),                        "listening port")
        ("doi",                 po::value<uint16_t>(&doi)               ->default_value(2),                             "device object identifier")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || vm.count("doi") == 0 ) {
        std::cout << desc << std::endl<< std::endl;
        return 1;
    }

    object_instance = doi;

    std::cout
                << "reading property "
                << std::endl
                << " doi: "               << doi
                << " object_type: "       << object_type
                << " object_instance: "   << object_instance
                << " property: "          << property;

    std::cout   << " on " << ip << ":"  << port
                << std::endl;


    boost::asio::io_service io_service;
    bacnet::stack::factory<bacnet::stack::ip_v4_client> factory{io_service, ip, port};
    auto &service_controller = factory.controller();

    bacnet::type::object_identifier device_id{bacnet::type::object_type::device, doi};
    bacnet::type::object_identifier object_id{object_type, object_instance};
    bacnet::service::service::read_property_request request;

    request = bacnet::service::service::read_property_request{object_id, property};

    service_controller.start();

    service_controller.async_send(device_id, request, [&io_service](const bacnet::error &ec,  bacnet::service::service::read_property_ack response) {
                                                          if(ec) {
                                                            std::cout << "error occurred: " << ec <<  std::endl;
                                                          }
                                                          else {
                                                            try {
                                                              bacnet::type::services_supported ss{boost::get<bacnet::type::bit_string>(response.property_value)};
                                                              std::cout << "response: " << ss <<  std::endl;
                                                     //         std::cout << "response: " << pre::json::to_json(response.property_value).dump(2) <<  std::endl;
                                                            }
                                                            catch(const std::exception &e) {
                                                              std::cout << "exception: " << e.what() <<  std::endl;
                                                            }

                                                          }
                                                          io_service.stop();
                                                       }
    );

    io_service.run();

  return 0;
}
