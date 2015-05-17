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
#include <iomanip>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <bacnet/bacnet.hpp>
#include <bacnet/bvll/frames.hpp>






namespace bacnet { namespace  bvll { namespace detail {


class transporter {

public:

	const uint16_t DEFAULT_PORT = 0xBAC0;
	const std::string DEFAULT_ADDRESS{"255.255.255.255"};


	transporter(boost::asio::io_service &io_service) : io_service_(io_service), socket_(io_service) {
		init();
	}

	transporter(boost::asio::io_service &io_service, uint16_t port) : io_service_(io_service), socket_(io_service), port_(port) {
		init();
	}

	transporter(boost::asio::io_service &io_service, const std::string multicast_address, uint16_t port) :
		io_service_(io_service), socket_(io_service), port_(port), multicast_address_(boost::asio::ip::address::from_string(multicast_address)) {
		init();
	}

	template<typename Buffer,typename Handler>
	void async_receive_from(const Buffer &buffer, boost::asio::ip::udp::endpoint &sender, const Handler &handler) {
		std::cout << "async_receive_from(): " << std::endl;
		socket_.async_receive_from( buffer, sender, handler);
	}

private:
	//xxx to be setable by user for specific interface?
	const boost::asio::ip::address listen_address_ = boost::asio::ip::address::from_string("0.0.0.0");

	void init() {
		std::cout << "init(): " << std::endl;
		listen_endpoint = boost::asio::ip::udp::endpoint(listen_address_, port_);

		socket_.open(listen_endpoint.protocol());
		socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
		socket_.bind(listen_endpoint);


		if(multicast_address_.to_string().compare(DEFAULT_ADDRESS) != 0) {
			socket_.set_option(boost::asio::ip::multicast::join_group(multicast_address_));
		}


	}

	boost::asio::ip::address multicast_address_= boost::asio::ip::address::from_string(DEFAULT_ADDRESS);
	uint16_t port_ = DEFAULT_PORT;

	boost::asio::io_service &io_service_;
	boost::asio::ip::udp::socket socket_;
	boost::asio::ip::udp::endpoint listen_endpoint;
};



}}}




namespace bacnet { namespace  bvll {

class inbound_router : public boost::static_visitor<> {

public:
	void operator()(frame::bvlc_result request) {
		std::cout << "inbound_router bvlc_result" << std::endl;
	}
	void operator()(frame::write_broadcast_distribution_table request) {
			std::cout << "inbound_router write_broadcast_distribution_table" << std::endl;
	}
/*	void operator()(frame::read_broadcast_distribution_table request) {
			std::cout << "inbound_router read_broadcast_distribution_table" << std::endl;
	}
*/
	void operator()(frame::read_broadcast_distribution_table_ack request) {
			std::cout << "inbound_router read_broadcast_distribution_table" << std::endl;
	}
	void operator()(frame::forwarded_npdu request) {
			std::cout << "inbound_router forwarded_npdu" << std::endl;
	}
	void operator()(frame::register_foreign_device request) {
			std::cout << "inbound_router register_foreign_device" << std::endl;
	}
/*	void operator()(frame::read_foreign_device_table request) {
			std::cout << "inbound_router read_foreign_device_table" << std::endl;
	}
*/
/*	void operator()(frame::read_foreign_device_table_ack request) {
				std::cout << "inbound_router read_foreign_device_table_ack" << std::endl;
	}
*/
/*	void operator()(frame::delete_foreign_device_table_entry request) {
			std::cout << "inbound_router delete_foreign_device_table_entry" << std::endl;
	}
*/
	void operator()(frame::distribute_broadcast_to_network request) {
			std::cout << "inbound_router distribute_broadcast_to_network" << std::endl;
	}
	void operator()(frame::original_unicast_npdu request) {
				std::cout << "inbound_router original_unicast_npdu" << std::endl;
	}
	void operator()(frame::original_broadcast_npdu request) {
				std::cout << "inbound_router original_broadcast_npdu" << std::endl;
	}
/*	void operator()(frame::original_secure_bvll request) {
				std::cout << "inbound_router original_secure_bvll" << std::endl;
	}
*/

};



class controller {

public:

	controller(boost::asio::io_service &ios) : io_service_(ios), transporter_(ios) {
		auto callback = boost::bind(&controller::handle_receive_from, this,  boost::asio::placeholders::error,     boost::asio::placeholders::bytes_transferred);
		transporter_.async_receive_from( boost::asio::buffer(data_, max_length), sender_endpoint_, callback);
	}

	controller(boost::asio::io_service &ios, uint16_t port) : io_service_(ios), transporter_(ios, port) {
			auto callback = boost::bind(&controller::handle_receive_from, this,  boost::asio::placeholders::error,     boost::asio::placeholders::bytes_transferred);
			transporter_.async_receive_from( boost::asio::buffer(data_, max_length), sender_endpoint_, callback);
	}

	void handle_receive_from(const boost::system::error_code& error,   size_t bytes_recvd)	  {
	    if (!error) {
	    	std::cout << "received from: " << sender_endpoint_.address().to_string() << ":" << sender_endpoint_.port() << std::endl;
	    	std::string input;
			for(std::size_t idx = 0; idx < bytes_recvd; idx++){
				std::bitset<8> b(data_[idx]);
				std::cout << b.to_string();
				input.push_back(data_[idx]);
			}
			std::cout << std::endl;
			for(std::size_t idx = 0; idx < bytes_recvd; idx++){
				std::cout  << std::hex << (int)data_[idx] << " ";
			}
			std::cout << std::endl;

			//std::string input(data_, bytes_recvd);
			frame::possible_bvll_frame f = parser::parse(input);
			boost::apply_visitor(inbound_router_, f);

			auto callback = boost::bind(&controller::handle_receive_from, this,  boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred);
			transporter_.async_receive_from( boost::asio::buffer(data_, max_length), sender_endpoint_, callback);
	    }
	  }


private:

	boost::asio::io_service &io_service_;
	boost::asio::ip::udp::endpoint sender_endpoint_;
	enum { max_length = std::numeric_limits<uint16_t>::max()};
	char data_[max_length];

	bacnet::bvll::detail::transporter transporter_;
	inbound_router inbound_router_;
};


}}





void received(){
	std::cout << "received()" << std::endl;
}


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
