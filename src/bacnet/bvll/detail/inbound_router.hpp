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

#ifndef NINJA_WOOKIE_INBOUND_ROUTER_HPP
#define NINJA_WOOKIE_INBOUND_ROUTER_HPP

#include <iostream>
//#include <boost/variant/static_visitor.hpp>


#include <bacnet/common/protocol/meta_information.hpp>
#include <bacnet/bvll/frames.hpp>

#include <bacnet/bvll/controller.hpp>


namespace bacnet { namespace  bvll { namespace  detail {

template<typename CallbackManager>
class inbound_router /* : public boost::static_visitor<> */ {

public:

  inbound_router(CallbackManager& cm) : callback_manager_(cm) {
  }

  template<typename T>
  void operator()(T t) {
      bacnet::common::protocol::meta_information mi;
      mi.address = sender_endpoint_;
      callback_manager_.invoke_callback(std::move(t), std::move(mi));
  }

  void sender_endpoint(const bacnet::common::protocol::mac::address& sender_endpoint) {
    sender_endpoint_ = sender_endpoint;
  }

private:
  CallbackManager&  callback_manager_;
  bacnet::common::protocol::mac::address sender_endpoint_;
};


}}}



#endif //NINJA_WOOKIE_INBOUND_ROUTER_HPP
