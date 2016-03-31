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


namespace bacnet { namespace  npdu { namespace  detail {

using namespace bacnet::npdu;

template<typename CallbackManager>
class inbound_router : public boost::static_visitor<> {

public:
	inbound_router(CallbackManager& cbm) : callback_manager_(cbm) {
	}

	void route(frame f) {

		/* 6.2.2 if control_filed has no network_layer_message, it is an APDU frame for this device*/
		if(!f.control_field.has_network_layer_message_type()) {

      meta_information_.network_priority = f.control_field.network_priority();
      meta_information_.npdu_source = f.source;
      boost::apply_visitor( *this, f.body );
		}

		/*todo: check if not router is better name*/
		/*todo: check if not a reference of the npdu_controller is needed,
			or callbacks in the callback_manager for sending frames back */


	}



	template<typename T>
  void operator()(T npdu_frame_body) const  {
	  callback_manager_.invoke_callback(npdu_frame_body, meta_information_);
  }

	void meta_information(const bacnet::common::protocol::meta_information& mi) {
    meta_information_ = mi;
	}



private:
  CallbackManager& callback_manager_;
  bacnet::common::protocol::meta_information meta_information_;

};


}}}



#endif /* SRC_BACNET_NPDU_DETAIL_INBOUND_ROUTER_HPP_ */
