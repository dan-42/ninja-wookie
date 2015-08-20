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

#include <iostream>
#include <exception>

#include <boost/asio.hpp>
#include <bacnet/bvll/controller.hpp>
#include <bacnet/npdu/controller.hpp>
#include <bacnet/apdu/controller.hpp>


#include <bacnet/apdu/detail/type/tag_grammar.hpp>


int main(int argc, char *argv[]) {

    //using namespace bacnet::apdu::detail::type;



    std::string bin_data_to_parse{};
    std::string bin_data_to_generate{};

    bin_data_to_parse.push_back(0x11);


    bool bool_ = true;

    auto start = bin_data_to_parse.begin();
    auto end = bin_data_to_parse.end();
    bacnet::apdu::detail::type::parser::boolean_grammar<decltype(start)> p;

    bool r = boost::spirit::qi::parse(start, end, p , bool_);



    if(bool_){
        std::cout << "juhu! true" << std::endl;
    }
    else {
        std::cout << "juhu! false" << std::endl;
    }

return 0;













  try {
/*
    bacnet::config::device device_config;
    device_config.apdu.device_object_id = 1;
    device_config.apdu.support_segmentation = false;
    device_config.apdu.max_segments_accepted= bacnet::apdu::segments::TWO_SEGMENTS;
    device_config.npdu.network_number = 1;

*/

    std::string bvll_listening_ip = "0.0.0.0";
    uint16_t    bvll_listening_port = 0xBAC0;
    std::string bvll_multicast_ip = "255.255.255.255";

    uint16_t npdu_network_number = 1;

    uint16_t apdu_device_object_id = 1;


    boost::asio::io_service io_service;
    bacnet::bvll::controller bvll_controller(io_service, bvll_listening_ip, bvll_listening_port, bvll_multicast_ip );
    bacnet::npdu::controller<> npdu_controller(bvll_controller, npdu_network_number);
    bacnet::apdu::controller<decltype(npdu_controller)> apdu_controller(io_service, npdu_controller, apdu_device_object_id);

   // bacnet::service::controller<decltype(apdu_controller)> service_controller(io_service, apdu_controller);

    //service_controller.create_service("who_is").send();

    //bacnet::apdu::service::who_is who_is_;

    bacnet::binary_data who_is_frame;

    apdu_controller.send_unconfirmed_request_as_broadcast(0x08, who_is_frame);




    io_service.run();


  }
  catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
