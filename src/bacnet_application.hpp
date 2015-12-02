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

#ifndef NINJA_WOOKIE_BACNET_APPLICATION_HPP
#define NINJA_WOOKIE_BACNET_APPLICATION_HPP



#include <iostream>
#include <exception>

#include <limits>

#include <boost/asio.hpp>
#include <boost/format.hpp>

#include <bacnet/bvll/controller.hpp>
#include <bacnet/npdu/controller.hpp>
#include <bacnet/apdu/controller.hpp>
#include <bacnet/service/controller.hpp>
#include <bacnet/common/configuration.hpp>

#include <bacnet/common/object_identifier.hpp>
#include <bacnet/service/service/reinitialize_device.hpp>



struct config {
 //vendor_id
 //
};


struct my_bacnet_application {
  boost::asio::io_service& io_service;

  uint16_t npdu_network_number = 1;

  std::string bvll_listening_ip = "0.0.0.0";
  uint16_t    bvll_listening_port = 0xBAC0;
  std::string bvll_multicast_ip = "255.255.255.255";

  typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;


  bacnet::config config{};

  bacnet::bvll::controller bvll_controller;
  bacnet::npdu::controller<decltype(bvll_controller)> npdu_controller;
  bacnet::apdu::controller<decltype(npdu_controller), apdu_size > apdu_controller;
  bacnet::service::controller<decltype(apdu_controller), apdu_size> service_controller;

  my_bacnet_application(boost::asio::io_service& io_s) : io_service(io_s),
                                                                                 bvll_controller(io_service, {bvll_listening_ip, bvll_listening_port, bvll_multicast_ip} ),
                                                                                 npdu_controller(bvll_controller, npdu_network_number),
                                                                                 apdu_controller(io_service, npdu_controller),
                                                                                 service_controller(io_service, apdu_controller, config) {

  }

  int run() {


    /**
     * todos
     *
     *  * find a nice way for setting options like:
     *     vendor_id
     *     network
     *     segmentation
     *
     *  * create a managing class, for invoke id's
     *    goal, sending a reinitialize_device and giving a handler which will return the answer, not just when it was send successful.
     *    possible problems, depending on the answer is will be an ACK, Error PDU
     *
     *    So answer could be  SUCCESS, ERROR_password, errror_...
     *    page 573:   16.4.1.3.1 Error Type
     *
     *    how if it is not a simple ack expected?  design for other frames should be consindered
     *
     *    steps:
     *     * write c++11 interface how it should look like
     *     * review
     *     * try to make it work :-)


          * idea: use templates for a uniqe property like
          * uint32 pv_poperty = 80
          *
          * typedef pv bacnet::property<pv_property, float, is_writable>;
          * open questions: how to combine a whole object?
          * how to manage read or write property? and multiple?
          * where is the logic, like cant write pv when not out_of_service
          * so all musst be combined in one object?
          * how to manage reusability and seperation for object specifics but DRY!
     *
     */
    try {




      bacnet::common::object_identifier device_object_id(bacnet::object_type::device, 2);
      bacnet::service::service::reinitialize_device rd;
      rd.reinitialize_state_of_device = 0;
      rd.passowrd = "12345";
      service_controller.async_send(device_object_id, rd, [](boost::system::error_code ec, bacnet::service::possible_service_response response){
        std::cout << "async_send::reinitialize_device " << ec.category().name() << " " << ec.message() <<  std::endl;
      });


      auto i_am_handler_ = [](boost::system::error_code ec, bacnet::common::protocol::meta_information mi, bacnet::service::i_am i_am) {
      };
      service_controller.async_receive<bacnet::service::i_am, bacnet::service::callback_service_i_am_t>(i_am_handler_);


      auto who_is_handler_ = [this](boost::system::error_code ec, bacnet::common::protocol::meta_information mi, bacnet::service::who_is who_is) {
        std::cout << "async_receive::who_is " << ec.category().name() << " " << ec.message() <<  std::endl;
        if(!ec) {

          bacnet::service::i_am i_am_;
          i_am_.i_am_device_identifier.object_typ(bacnet::object_type::device);
          i_am_.i_am_device_identifier.instance_number(config.device_object_id);
          i_am_.segmentation_supported = config.segmentation;
          i_am_.vendor_id              = config.vendor_id;
          i_am_.max_apdu_length_accepted = apdu_size::size_in_bytes;


          service_controller.async_send(i_am_, [this](boost::system::error_code ec){
            std::cout << "async_send::i_am " << ec.category().name() << " " << ec.message() <<  std::endl;
          });

        } else {

        }
      };
      service_controller.async_receive<bacnet::service::who_is, bacnet::service::callback_service_who_is_t>(who_is_handler_);



      //std::cout << formatter_i_am % "device_id" % "endpoint" % "net" % "vendor" % "apdu" % "seg" % "binary source" ;





      //blocking call
      //io_service.run();
    }
    catch (std::exception &e) {
      std::cerr << "Exception: " << e.what() << "\n";
      throw;
    }

    return 0;
  }

};





#endif //NINJA_WOOKIE_BACNET_APPLICATION_HPP
