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



int main(int argc, char *argv[]) {
  try {
/*
	  std::string binary;
	  binary.push_back(0x81);
	  binary.push_back(0x0b);
	  binary.push_back(0x00);
	  binary.push_back(0x0c);
	  binary.push_back(0x01);
	  binary.push_back(0x20);
	  binary.push_back(0xff);
	  binary.push_back(0xff);


	  //bacnet::bvll::frame::original_broadcast_npdu_grammar frame;

	  //bacnet::bvll::frame::parser::parse(binary, frame);

	  bacnet::bvll::frame::possible_bvll_frame f ;
	  bool r = bacnet::bvll::parser::parse(binary, f);
*/
    boost::asio::io_service io_service;
    bacnet::bvll::controller controller(io_service);
    io_service.run();
  }
  catch (std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
