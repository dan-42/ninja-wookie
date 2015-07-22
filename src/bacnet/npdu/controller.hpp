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



#ifndef NINJA_WOOKIE_NPDU_CONTROLLER_HPP
#define NINJA_WOOKIE_NPDU_CONTROLLER_HPP

#include <bitset>

#include <boost/fusion/include/define_struct.hpp>

//#include <boost/phoenix/bind/bind_member_function.hpp>
#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>


#include <bacnet/npdu/frame.hpp>
#include <bacnet/npdu/grammar.hpp>

namespace bacnet { namespace npdu {


template<class Underlying_layer = bacnet::bvll::controller>
class controller {

public:
  controller(Underlying_layer &underlying_layer) : underlying_layer_(underlying_layer) {

    underlying_layer_.register_async_receive_broadcast_callback(boost::bind(&controller::async_receive_broadcast_handler, this, _1));

  }

  template<typename Handler>
  void async_send_broadcast(const bacnet::binary_data & payload, const Handler &handler){

    npdu::frame frame;
    frame.protocol_version = 1;
    frame.control_field.has_destination_specifier_ = 1;
    frame.destination.network_number = 65535;
    frame.hop_count = 255;
    frame.apdu_data = payload;

    bacnet::binary_data binary_frame = npdu::generator::generate(frame);

    underlying_layer_.async_send_broadcast(binary_frame, handler);
  }

  void async_receive_broadcast_handler(const bacnet::binary_data& data) {
    std::cout << "npdu_controller " << "async_receive_broadcast_handler" << std::endl;

    auto frame = npdu::parser::parse(data);

    std::cout << "bacnet::npdu::parser::parse parsed "   << std::endl;
  }


private:
  Underlying_layer &underlying_layer_;

};

}}

#endif /* NINJA_WOOKIE_NPDU_CONTROLLER_HPP */
