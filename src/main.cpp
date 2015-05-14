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















namespace bacnet { namespace  bvll {

const uint16_t DEFAULT_PORT = 0xBAC0;

class controller {

public:

	controller(boost::asio::io_service &ios) : io_service_(ios), socket_(ios) {

		//auto multicast_address = boost::asio::ip::address::from_string("255.255.255.255");
		auto multicast_address = boost::asio::ip::address::from_string("239.255.0.1");


		boost::asio::ip::udp::endpoint multicast_endpoint(multicast_address	, DEFAULT_PORT);


		boost::asio::ip::udp::endpoint listen_endpoint(boost::asio::ip::address::from_string("0.0.0.0")	, DEFAULT_PORT);
		socket_.open(listen_endpoint.protocol());
		socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
		socket_.bind(listen_endpoint);

		//socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address));


		socket_.async_receive_from(
				boost::asio::buffer(data_, max_length), sender_endpoint_,
					boost::bind(&controller::handle_receive_from, this,  boost::asio::placeholders::error,  boost::asio::placeholders::bytes_transferred));






	}


	void handle_receive_from(const boost::system::error_code& error,   size_t bytes_recvd)	  {
	    if (!error)	    {


			for(std::size_t idx = 0; idx < bytes_recvd; idx++){
				std::bitset<8> b(data_[idx]);
				std::cout << b.to_string();
			}
			std::cout << std::endl;


	      socket_.async_receive_from(
	          boost::asio::buffer(data_, max_length), sender_endpoint_,
	          boost::bind(&controller::handle_receive_from, this,
	            boost::asio::placeholders::error,
	            boost::asio::placeholders::bytes_transferred));
	    }
	  }


private:

	boost::asio::io_service &io_service_;
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint sender_endpoint_;
	enum { max_length = std::numeric_limits<uint16_t>::max()};
	char data_[max_length];
};


}}









int main(int argc, char* argv[])
{
  try
  {

	  std::string bin_data_to_parse{};
	  std::string bin_data_to_generate{};

	  bin_data_to_parse.push_back(0xC0);
	  bin_data_to_parse.push_back(0xA8);
	  bin_data_to_parse.push_back(0x0A);
	  bin_data_to_parse.push_back(0x0A);

	  bin_data_to_parse.push_back(0xBA);
	  bin_data_to_parse.push_back(0xC0);


	  bin_data_to_parse.push_back(0xAA);
	  bin_data_to_parse.push_back(0xAA);

	  bin_data_to_parse.push_back(0xDD);
	  bin_data_to_parse.push_back(0xDD);




	  bacnet::bvll::bvlc::foreign_device_table_entry entry{};


	  bacnet::bvll::bvlc::parser::parse(bin_data_to_parse, entry);

	  bacnet::bvll::bvlc::generator::generate(bin_data_to_generate, entry);

	  if(bin_data_to_parse.compare(bin_data_to_generate) == 0){
		  std::cout << "juhu!" << std::endl;
	  }





    boost::asio::io_service io_service;
    bacnet::bvll::controller controller(io_service);

    io_service.run();
  }
  catch (std::exception& e)
  {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
