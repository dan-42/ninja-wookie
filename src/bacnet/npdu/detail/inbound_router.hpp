/*
 * inbound_router.hpp
 *
 *  Created on: Jul 25, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_NPDU_DETAIL_INBOUND_ROUTER_HPP_
#define SRC_BACNET_NPDU_DETAIL_INBOUND_ROUTER_HPP_

// #include <boost/noncopyable.hpp>

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
