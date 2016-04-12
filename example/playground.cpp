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



namespace bacnet { namespace id {



namespace object {
  static const constexpr uint32_t analog_input      =  0;
  static const constexpr uint32_t analog_output     =  1;
  static const constexpr uint32_t analog_value      =  2;
  static const constexpr uint32_t binary_input      =  3;
  static const constexpr uint32_t binar_output      =  4;
  static const constexpr uint32_t binary_value      =  5;
  static const constexpr uint32_t calendar          =  6;
  static const constexpr uint32_t command           =  7;
  static const constexpr uint32_t device            =  8;
}


namespace property {
  static const constexpr uint16_t object_name              =  77;
  static const constexpr uint16_t object_identifier        =  77;
  static const constexpr uint16_t present_value            =  85;
}

}

namespace type {

namespace property {

  template<uint32_t object_type, uint16_t property_type, typename Type >
  struct property_type {
    typedef Type type;
  };



    namespace o_id = bacnet::id::object;
    namespace p_id = bacnet::id::property;


    template<> struct property_type<o_id::analog_input, id::property::object_name,         std::string>;
    template<> struct property_type<o_id::analog_input, id::property::object_identifier,   std::string>;
    template<> struct property_type<o_id::analog_input, id::property::present_value,       std::string>;



  }



}

namespace object {

  struct analog_input {
    namespace prop_type = bacnet::type::property;


    ai::object_name::type object_name;
    ai::object_identifier::type object_identifier;
    ai::present_value::type present_value;
  };


}}





int main(int argc, char *argv[]) {


  bacnet::type::analog_input::present_value::type value;










  try {
    uint16_t    doi{1};
    uint16_t    port{0xBAC0};
    std::string ip{"0.0.0.0"};


    std::cout
    << "sending who is to "
    << " doi: "     << doi
    << " on " << ip << ":"  << port
    << std::endl;

    boost::asio::io_service io_service;
    bacnet::stack::factory<bacnet::stack::ip_v4> factory{io_service, ip, port};
    auto &service_controller = factory.controller();

    service_controller.async_receive([](const bacnet::service::i_am &service, const boost::system::error_code &ec, const bacnet::common::protocol::meta_information &mi){
    	//std::cout << service << std::endl;
    });


    //bacnet::common::object_identifier device_id{bacnet::object_type::device, 2};
    bacnet::service::service::who_is wi;

    service_controller.async_send(wi, []
                 (const boost::system::error_code &ec){
                    std::cout << "async_send::who_is " << ec.category().name() << " " << ec.message() <<  std::endl;
                 }
    );


    service_controller.start();

    io_service.run();
  }
  catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
