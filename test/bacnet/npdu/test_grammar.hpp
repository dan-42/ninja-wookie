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

#ifndef NINJA_WOOKIE_GRAMMAR_HPP
#define NINJA_WOOKIE_GRAMMAR_HPP

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include <bacnet/npdu/controller.hpp>

bool is_equal(const bacnet::binary_data& a, const bacnet::binary_data& b) {

  if(a.size() != b.size()) {
    return false;
  }

  for(bacnet::binary_data::size_type idx = 0; idx < a.size(); ++idx){
    if(a[idx] != b[idx]) {
      return false;
    }
  }
  return true;

}

BOOST_AUTO_TEST_SUITE( npdu_grammar )

  BOOST_AUTO_TEST_CASE( test_case1 ) {

    bacnet::binary_data binary;
    binary.push_back(0x01); //version
    binary.push_back(0x04); //control

    binary.push_back(0xDD); //apdu data
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);



    auto frame_parsed = bacnet::npdu::parser::parse(binary);
    bacnet::binary_data frame_generated =  bacnet::npdu::generator::generate(frame_parsed);

    BOOST_TEST(is_equal(binary, frame_generated), "Local BACnet APDU, no addrs, reply expected");


  }

  BOOST_AUTO_TEST_CASE( test_case2 ){

    bacnet::binary_data binary;
    binary.push_back(0x01); //version
    binary.push_back(0x24); //control

    binary.push_back(0x00); //DNET
    binary.push_back(0x01); //DNET
    binary.push_back(0x04); //DLEN
    binary.push_back(0x01);
    binary.push_back(0x01);
    binary.push_back(0x01);
    binary.push_back(0x01);

    /*no source*/

    binary.push_back(0x10); //hop count

    binary.push_back(0xDD); //apdu data
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);


    auto frame_parsed = bacnet::npdu::parser::parse(binary);
    bacnet::binary_data frame_generated =  bacnet::npdu::generator::generate(frame_parsed);

    BOOST_TEST(is_equal(binary, frame_generated),  "Remote BACnet NPDU directed to router prio normale, reply expected");

  }

  BOOST_AUTO_TEST_CASE( test_case3 ) {

    bacnet::binary_data binary;
    binary.push_back(0x01); //version
    binary.push_back(0x29); //control

    binary.push_back(0x00); //DNET
    binary.push_back(0x01); //DNET
    binary.push_back(0x01); //DLEN
    binary.push_back(0x01);


    binary.push_back(0x00); //SNET
    binary.push_back(0x01); //SNET
    binary.push_back(0x06); //SLEN
    binary.push_back(0x0F);
    binary.push_back(0x0F);
    binary.push_back(0x0F);
    binary.push_back(0x0F);
    binary.push_back(0xBA);
    binary.push_back(0xC0);

    binary.push_back(0x10); //hop count

    binary.push_back(0xDD); //apdu data
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);

    auto frame_parsed = bacnet::npdu::parser::parse(binary);
    bacnet::binary_data frame_generated =  bacnet::npdu::generator::generate(frame_parsed);

    BOOST_TEST(is_equal(binary, frame_generated),  "BACnet NPDU passwd between routers prio urgent");
  }


  BOOST_AUTO_TEST_CASE( test_case4 ) {

    bacnet::binary_data binary;
    binary.push_back(0x01); //version
    binary.push_back(0x0B); //control

    /* no destination -> BROADCAST*/

    binary.push_back(0x00); //SNET
    binary.push_back(0x01); //SNET
    binary.push_back(0x06); //SLEN
    binary.push_back(0x0F);
    binary.push_back(0x0F);
    binary.push_back(0x0F);
    binary.push_back(0x0F);
    binary.push_back(0xBA);
    binary.push_back(0xC0);

    /* no HOP COUNT*/

    binary.push_back(0xDD); //apdu data
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);


    auto frame_parsed = bacnet::npdu::parser::parse(binary);
    bacnet::binary_data frame_generated =  bacnet::npdu::generator::generate(frame_parsed);

    BOOST_TEST(is_equal(binary, frame_generated), "Remote BACnet NPDU send from router to final dest prio life_safty");

  }

  BOOST_AUTO_TEST_CASE( test_case5 ) {

    bacnet::binary_data binary;
    binary.push_back(0x01); //version
    binary.push_back(0x28); //control

    binary.push_back(0xFF); //DNET
    binary.push_back(0xFF); //DNET
    binary.push_back(0x00); //DLEN


    binary.push_back(0x00); //SNET
    binary.push_back(0x01); //SNET
    binary.push_back(0x01); //SLEN
    binary.push_back(0x0F);

    binary.push_back(0x10); //hop

    binary.push_back(0xDD); //apdu data
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);
    binary.push_back(0xDD);


    auto frame_parsed = bacnet::npdu::parser::parse(binary);
    bacnet::binary_data frame_generated =  bacnet::npdu::generator::generate(frame_parsed);

    BOOST_TEST(is_equal(binary, frame_generated),  "Broadcast message by router of prio normal");
  }


BOOST_AUTO_TEST_SUITE_END()

#endif //NINJA_WOOKIE_GRAMMAR_HPP
