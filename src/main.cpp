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

#include <boost/asio.hpp>
#include <bacnet/bvll/controller.hpp>

#include <bacnet/npdu/controller.hpp>

void test_npdu_parser_1() {

  std::string binary;
  binary.push_back(0x01); //version
  binary.push_back(0x04); //control

  binary.push_back(0xDD); //apdu data
  binary.push_back(0xDD);
  binary.push_back(0xDD);
  binary.push_back(0xDD);
  binary.push_back(0xDD);


  auto start = binary.begin();
  auto end = binary.end();


  bacnet::npdu::frame frame_;
  bacnet::npdu::npdu_grammar<decltype(start)> grammar;
  auto has_success = boost::spirit::qi::parse(start, end, grammar, frame_);

  std::cout << "Local BACnet APDU, no addrs, reply expected:" << std::endl;
  std::cout <<  frame_ << std::endl;
  std::cout << "----------------------- " << std::endl;

}

void test_npdu_parser_2() {

  std::string binary;
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

  auto start = binary.begin();
  auto end = binary.end();

  bacnet::npdu::frame frame_;
  bacnet::npdu::npdu_grammar<decltype(start)> grammar;
  auto has_success = boost::spirit::qi::parse(start, end, grammar, frame_);

  std::cout << "Remote BACnet NPDU directed to router prio normale, reply expected:" << std::endl;
  std::cout <<  frame_ << std::endl;
  std::cout << "----------------------- " << std::endl;

}

void test_npdu_parser_3() {

  std::string binary;
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

  auto start = binary.begin();
  auto end = binary.end();

  bacnet::npdu::frame frame_;
  bacnet::npdu::npdu_grammar<decltype(start)> grammar;
  auto has_success = boost::spirit::qi::parse(start, end, grammar, frame_);

  std::cout << "BACnet NPDU passwd between routers prio urgent:" << std::endl;
  std::cout <<  frame_ << std::endl;
  std::cout << "----------------------- " << std::endl;

}


void test_npdu_parser_4() {

  std::string binary;
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

  auto start = binary.begin();
  auto end = binary.end();

  bacnet::npdu::frame frame_;
  bacnet::npdu::npdu_grammar<decltype(start)> grammar;
  auto has_success = boost::spirit::qi::parse(start, end, grammar, frame_);

  std::cout << "Remote BACnet NPDU send from router to final dest prio life_safty:" << std::endl;
  std::cout <<  frame_ << std::endl;
  std::cout << "----------------------- " << std::endl;

}

void test_npdu_parser_5() {

  std::string binary;
  binary.push_back(0x01); //version
  binary.push_back(0x28); //control

  binary.push_back(0xFF); //DNET
  binary.push_back(0xFF); //DNET
  binary.push_back(0x00); //DLEN


  binary.push_back(0x00); //SNET
  binary.push_back(0x01); //SNET
  binary.push_back(0x01); //SLEN
  binary.push_back(0x0F);

  binary.push_back(0x10);

  binary.push_back(0xDD); //apdu data
  binary.push_back(0xDD);
  binary.push_back(0xDD);
  binary.push_back(0xDD);
  binary.push_back(0xDD);

  auto start = binary.begin();
  auto end = binary.end();

  bacnet::npdu::frame frame_;
  bacnet::npdu::npdu_grammar<decltype(start)> grammar;
  auto has_success = boost::spirit::qi::parse(start, end, grammar, frame_);

  std::cout << "Broadcast message by router of prio normal:" << std::endl;
  std::cout <<  frame_ << std::endl;
  std::cout << "----------------------- " << std::endl;

}





int main(int argc, char *argv[]) {
  try {
    test_npdu_parser_1();
    test_npdu_parser_2();
    test_npdu_parser_3();
    test_npdu_parser_4();
    test_npdu_parser_5();


    boost::asio::io_service io_service;
    bacnet::bvll::controller controller(io_service);
    io_service.run();
  }
  catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
