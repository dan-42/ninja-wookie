/*
 * test.cpp
 *
 *  Created on: May 14, 2015
 *      Author: schoko
 */




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
#include <bitset>
#include <string>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <bacnet/bacnet.hpp>
#include <bacnet/bvll/frames.hpp>





int main(int argc, char* argv[])
{
  try
  {
	  /**
	   * test if an bacnet ip v4 adress will be proper generated and parsed
	   *
	   * input 192.168.10.10 port 47808
	   */

	  std::string bin_data_to_parse{};
	  std::string bin_data_to_generate{};

	  bin_data_to_parse.push_back(0xC0);
	  bin_data_to_parse.push_back(0xA8);
	  bin_data_to_parse.push_back(0x0A);
	  bin_data_to_parse.push_back(0x0A);

	  bin_data_to_parse.push_back(0xBA);
	  bin_data_to_parse.push_back(0xC0);

	  bacnet::bvll::bvlc::bacnet_ip_address adr{};

	  auto start = bin_data_to_parse.begin();
	  auto end = bin_data_to_parse.end();
	  bacnet::bvll::bvlc::parser::bacnet_ip_address_grammar<decltype(start)> p;

	  bool r = boost::spirit::qi::parse(start, end, p , adr);



	  std::back_insert_iterator<decltype(bin_data_to_generate)> sink(bin_data_to_generate);
	  bacnet::bvll::bvlc::generator::bacnet_ip_address_grammar<decltype(sink)> g;

	  bool r2 = boost::spirit::karma::generate(sink, g, adr);

	  if(bin_data_to_parse.compare(bin_data_to_generate) == 0){
		  std::cout << "juhu!" << std::endl;
	  }







  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
