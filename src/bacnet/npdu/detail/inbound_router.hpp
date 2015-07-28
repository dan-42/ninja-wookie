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

		callback_manager_.async_received_apdu_callback_(f.apdu_data);
		/*todo: check if not router is better name*/
		/*todo: check if not a reference of the npdu_controller is needed,
			or callbacks in the callback_manager for sending frames back */

		/*todo: include meta data*/


	}

private:
	callback_manager& callback_manager_;

};


}}}



#endif /* SRC_BACNET_NPDU_DETAIL_INBOUND_ROUTER_HPP_ */
