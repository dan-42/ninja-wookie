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

#ifndef SRC_BACNET_NPDU_DETAIL_INBOUND_ROUTER_HPP_
#define SRC_BACNET_NPDU_DETAIL_INBOUND_ROUTER_HPP_


#include <bacnet/npdu/frame.hpp>
#include <bacnet/npdu/detail/callback_manager.hpp>

namespace bacnet { namespace  npdu { namespace  detail {

using namespace bacnet::npdu;

class inbound_router {

public:
	inbound_router(callback_manager& cbm) : callback_manager_(cbm) {
	}

	void route(const frame& f) {
		std::cout << "npdu::detail::inbound_router::route() "  << std::endl;


		/* 6.2.2 if control_filed has no network_layer_message, it is an APDU frame for this device*/
		if(!f.control_field.has_network_layer_message_type()) {
		  meta_information_t meta_information;
		  meta_information.endpoint = sender_endpoint_;
		  meta_information.network_priority = f.control_field.network_priority();
		  // is this needed?
		  meta_information.source = f.source;
		  callback_manager_.async_received_apdu_callback_(f.apdu_data, meta_information);
		}

		/*todo: check if not router is better name*/
		/*todo: check if not a reference of the npdu_controller is needed,
			or callbacks in the callback_manager for sending frames back */


	}

	void sender_endpoint(const boost::asio::ip::udp::endpoint& sender_endpoint) {
	  sender_endpoint_ = sender_endpoint;
	}



private:
	callback_manager& callback_manager_;
	boost::asio::ip::udp::endpoint sender_endpoint_;

};


}}}



#endif /* SRC_BACNET_NPDU_DETAIL_INBOUND_ROUTER_HPP_ */