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
namespace  bacnet { namespace apdu { namespace type {
static bacnet::binary_data generate(const bacnet::apdu::type::tag &tag_) {
  using namespace bacnet::apdu;
  bacnet::binary_data binary;

  std::back_insert_iterator<bacnet::binary_data> sink(binary);
  type::detail::generator::tag_grammar<decltype(sink)> generator;
  bool result = false;
  try {
    result = boost::spirit::karma::generate(sink, generator, tag_);
  }
  catch (std::exception &e) {
    std::cerr << "exception: apdu generate  unsigned_integer" << e.what() << std::endl;
  }
  if (!result) {
    return bacnet::binary_data();
  }

  return binary;
}


static bool parse(bacnet::binary_data& data, bacnet::apdu::type::tag &tag_) {
  using namespace bacnet::apdu;

  using namespace bacnet::apdu;

  auto start = data.begin();
  auto end = data.end();

  type::detail::parser::tag_grammar<decltype(start)> parser;
  bool has_succeeded = false;
  try {
    has_succeeded = boost::spirit::qi::parse(start, end, parser, tag_);
  }
  catch (std::exception &e) {
    std::cerr << "exception: cant parse tag" << e.what() << std::endl;
  }
  if (has_succeeded) {
    data.erase(data.begin(), start);
    return true;
  }
  return false;
}


}}}




int main(int argc, char *argv[]) {


  try {
/*
    bacnet::config::device device_config;
    device_config.apdu.device_object_id = 1;
    device_config.apdu.support_segmentation = false;
    device_config.apdu.max_segments_accepted= bacnet::apdu::segments::TWO_SEGMENTS;
    device_config.npdu.network_number = 1;

*/

    /*

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

       bacnet::apdu::type::object_identifier aoi;
*/


    bacnet::apdu::type::tag tag_simple;
    bacnet::apdu::type::tag tag_parsed;
    tag_simple.is_context_tag(false);
    tag_simple.number(12);
    tag_simple.length_value_type(4);

    std::cout << std::endl;
    std::cout << "-----simple-----------------"  << std::endl;
    std::cout << "TAG: " << tag_simple << std::endl;

    auto generated = bacnet::apdu::type::generate(tag_simple);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;


    bacnet::apdu::type::tag tag_extended_number;
    tag_extended_number.is_context_tag(false);
    tag_extended_number.number(15);
    tag_extended_number.length_value_type(4);

    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "-----tag_extended_number---15--------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;

    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;



    tag_extended_number.number(16);
    tag_extended_number.length_value_type(4);

    std::cout << std::endl;
    std::cout << "-----tag_extended_number----16-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;

    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;

    tag_extended_number.number(17);
    tag_extended_number.length_value_type(4);

    std::cout << std::endl;
    std::cout << "-----tag_extended_number----17-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;

    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;

    tag_extended_number.number(254);
    tag_extended_number.length_value_type(4);
    std::cout << std::endl;
    std::cout << "-----tag_extended_number----254-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;

    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;



    std::cout << std::endl;
    tag_extended_number.number(12);
    tag_extended_number.length_value_type(4);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----4-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;

    tag_extended_number.number(12);
    tag_extended_number.length_value_type(5);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----5-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;

    tag_extended_number.number(12);
    tag_extended_number.length_value_type(6);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----6-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;


    tag_extended_number.number(12);
    tag_extended_number.length_value_type(253);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----253-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;

    tag_extended_number.number(12);
    tag_extended_number.length_value_type(254);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----254-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;



    tag_extended_number.number(12);
    tag_extended_number.length_value_type(255);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----255-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;


    tag_extended_number.number(12);
    tag_extended_number.length_value_type( 65534 );
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----65534-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;


    tag_extended_number.number(12);
    tag_extended_number.length_value_type(65535);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----65535-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;

    tag_extended_number.number(12);
    tag_extended_number.length_value_type(65536);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----65536-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;

    tag_extended_number.number(12);
    tag_extended_number.length_value_type(65537);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----65537-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;





    tag_extended_number.number(12);
    tag_extended_number.length_value_type(4294967294);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----4294967294-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;


    tag_extended_number.number(12);
    tag_extended_number.length_value_type(4294967295);
    std::cout << std::endl;
    std::cout << "-----tag_extended_length----4294967295-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;




    std::cout << std::endl;
    std::cout << std::endl;
    tag_extended_number.number(254);
    tag_extended_number.length_value_type(4294967295);
    std::cout << std::endl;
    std::cout << "--tag_extended_number 254---tag_extended_length----4294967295-------------"  << std::endl;
    std::cout << "TAG: " << tag_extended_number << std::endl;
    generated = bacnet::apdu::type::generate(tag_extended_number);
    for(auto &c : generated){
      std::cout << " 0x" << std::hex << (int)c ;
    }
    std::cout << std::endl;
    tag_parsed = bacnet::apdu::type::tag{};
    if( bacnet::apdu::type::parse(generated, tag_parsed)) {
      std::cout << " parsed successfull " << tag_parsed << std::endl;
    }
    else
      std::cout << " parsed failed " << std::endl;






    //bacnet::binary_data who_is_frame;

    //apdu_controller.send_unconfirmed_request_as_broadcast(0x08, who_is_frame);

    //bacnet::service::who_is who_is_service1;
    //bacnet::service::who_is who_is_service2(42);
    //bacnet::service::who_is who_is_service3(2, 4214);




   // io_service.run();


  }
  catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
