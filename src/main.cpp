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

#include <limits>

#include <boost/asio.hpp>
#include <bacnet/bvll/controller.hpp>
#include <bacnet/npdu/controller.hpp>
#include <bacnet/apdu/controller.hpp>
#include <bacnet/service/controller.hpp>


#include <bacnet/common/object_identifier.hpp>
#include <bacnet/apdu/type/object_identifier_generator.hpp>
#include <bacnet/apdu/type/detail/tag_grammar.hpp>

/*

 I-Am-Request ::= SEQUENCE {
iAmDeviceIdentifier
maxAPDULengthAccepted
segmentationSupported
vendorID
}
BACnetObjectIdentifier,
Unsigned,
BACnetSegmentation,
Unsigned16


 */


void my_handler(const boost::system::error_code& error,  std::size_t bytes_transferred ) { }

class service_receiver {
public:
  void operator()(const bacnet::service::who_is &service) {
    std::cout << "who_is" << std::endl;
  }
  void operator()(const bacnet::service::i_am &service) {
    std::cout << "i_am" << std::endl;
  }
};


int main(int argc, char *argv[]) {


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


    boost::asio::io_service io_service;
    bacnet::bvll::controller bvll_controller(io_service, bvll_listening_ip, bvll_listening_port, bvll_multicast_ip );
    bacnet::npdu::controller<decltype(bvll_controller)> npdu_controller(bvll_controller, npdu_network_number);
    bacnet::apdu::controller<decltype(npdu_controller)> apdu_controller(io_service, npdu_controller);
    bacnet::service::controller<decltype(apdu_controller), service_receiver> service_controller(io_service, apdu_controller);


    bacnet::application::controller<decltype(service_controller)> application_controller(io_service, service_controller);



    bacnet::service::who_is who_is_service0(2, 434214);



    service_controller.async_send(who_is_service0, &my_handler);

    service_controller.async_send(who_is_service0, [](service::error_code ec){

    });
    service_controller.async_send(service::i_am{}, [](service::error_code ec){

    });

    service_controller.async_receive<service::i_am>([](service::error_code ec,service::i_am i_am){

    });

    service_controller.async_receive<service::who_is>([](service::error_code ec, service::who_is who_is) {

    });



    service_receiver sr{};
    service_controller.async_receive_service(sr);



/*
    service_controller.async_receive(who_is_service0, [&who_is_service0](){
      std::cout << "async_receive(who_is_service): low " << std::dec <<(int)who_is_service0.device_instance_range_low_limit <<std::endl;
      std::cout << "async_receive(who_is_service): hight " << std::dec <<(int)who_is_service0.device_instance_range_high_limit <<std::endl;
    });
*/

    bacnet::service::i_am i_am_;
    i_am_.max_apdu_length_accepted = 1460;
    i_am_.vendor_id = 0;
    i_am_.segmentation_supported = 0;
    i_am_.i_am_device_identifier = 1;
    service_controller.async_send(i_am_, &my_handler);

    io_service.run();


  }
  catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
