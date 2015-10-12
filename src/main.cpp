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
    bacnet::service::controller<decltype(apdu_controller)> service_controller(io_service, apdu_controller);


   // bacnet::application::controller<decltype(service_controller)> application_controller(io_service, service_controller);


    service_controller.async_send(bacnet::service::who_is{2, 434214}, [](boost::system::error_code ec) {
        std::cout << "async_send::who_is " << ec.category().name() << " " << ec.message() <<  std::endl;
    });


    bacnet::service::i_am i_am_;
    i_am_.i_am_device_identifier.object_typ(bacnet::object_type::device);
    i_am_.i_am_device_identifier.instance_number(1);
    i_am_.segmentation_supported.segmented(bacnet::common::segmentation::segment::both);
    i_am_.vendor_id = 1;
    i_am_.max_apdu_length_accepted = 1460;

    service_controller.async_send(i_am_, [](boost::system::error_code ec){
      std::cout << "async_send::i_am " << ec.category().name() << " " << ec.message() <<  std::endl;
    });


    auto i_am_handler_ = [](boost::system::error_code ec, bacnet::service::i_am i_am) {
      std::cout << "async_receive::i_am " << ec.category().name() << " " << ec.message() <<  std::endl;

      std::cout << "i_am_device_identifier:\t" << i_am.i_am_device_identifier << std::endl;
      std::cout << "max_apdu_length_accepted:\t" << i_am.max_apdu_length_accepted << std::endl;
      std::cout << "segmentation_supported:\t" << i_am.segmentation_supported << std::endl;
      std::cout << "vendor_id:\t" << (uint32_t)i_am.vendor_id << std::endl;
    };
    service_controller.async_receive<bacnet::service::i_am, bacnet::service::callback_service_i_am_t>(i_am_handler_);


    auto who_is_handler_ = [](boost::system::error_code ec, bacnet::service::who_is who_is) {
      std::cout << "async_receive::who_is " << ec.category().name() << " " << ec.message() <<  std::endl;
      if(!ec) {
        std::cout << "async_receive(who_is_service): low " << std::dec << (int) who_is.device_instance_range_low_limit << std::endl;
        std::cout << "async_receive(who_is_service): hight " << std::dec << (int) who_is.device_instance_range_high_limit << std::endl;
      } else {

      }
    };
    service_controller.async_receive<bacnet::service::who_is, bacnet::service::callback_service_who_is_t>(who_is_handler_);


    //blocking call
    io_service.run();
  }
  catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
