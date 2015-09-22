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

    uint16_t apdu_device_object_id = 1;


    boost::asio::io_service io_service;
    bacnet::bvll::controller bvll_controller(io_service, bvll_listening_ip, bvll_listening_port, bvll_multicast_ip );
    bacnet::npdu::controller<decltype(bvll_controller)> npdu_controller(bvll_controller, npdu_network_number);
    bacnet::apdu::controller<decltype(npdu_controller)> apdu_controller(io_service, npdu_controller, apdu_device_object_id);
    bacnet::service::controller<decltype(apdu_controller)> service_controller(io_service, apdu_controller);

    bacnet::service::who_is who_is_service0(2, 434214);
    service_controller.send(who_is_service0);

    service_controller.async_receive(who_is_service0, [&who_is_service0](){
      std::cout << "async_receive(who_is_service): low " << std::dec <<(int)who_is_service0.device_instance_range_low_limit <<std::endl;
      std::cout << "async_receive(who_is_service): hight " << std::dec <<(int)who_is_service0.device_instance_range_high_limit <<std::endl;
    });


    bacnet::service::i_am i_am_;
    i_am_.max_apdu_length_accepted = 1460;
    i_am_.vendor_id = 0;
    i_am_.segmentation_supported = 0;
    i_am_.i_am_device_identifier = 1;
    service_controller.send(i_am_);


    bacnet::common::object_identifier oi;
    oi.from_native(0x00C0000F);
    std::cout << "oi.instance_number() " << oi.instance_number() << std::endl;
    std::cout << "oi.object_typ() " << oi.object_typ() << std::endl;

    auto generated = bacnet::apdu::type::generate(oi);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;


    //bacnet::binary_data who_is_frame;

    //apdu_controller.send_unconfirmed_request_as_broadcast(0x08, who_is_frame);

    //bacnet::service::who_is who_is_service1;
    //bacnet::service::who_is who_is_service2(42);
    //bacnet::service::who_is who_is_service3(2, 4214);




    io_service.run();


  }
  catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
