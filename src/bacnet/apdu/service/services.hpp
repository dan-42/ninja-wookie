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

#ifndef NINJA_WOOKIE_SERVICES_HPP
#define NINJA_WOOKIE_SERVICES_HPP


#include <vector>
#include <boost/variant.hpp>
#include <bacnet/detail/common/types.hpp>

namespace  bacnet { namespace apdu { namespace service {

struct who_is {

  bacnet::binary_data generate() {
    bacnet::binary_data who_is_frame;
    who_is_frame.push_back(0x08);
    return who_is_frame;
  }

};

struct i_am {

  bacnet::binary_data generate() {
    bacnet::binary_data whoi_is_frame;
    whoi_is_frame.push_back(0x00);
    whoi_is_frame.push_back(0x00);
    return whoi_is_frame;
  }

};

typedef boost::variant<who_is, i_am> possible_service;


struct generate_frame : public boost::static_visitor<bacnet::binary_data> {
  template<typename T>
  bacnet::binary_data operator()( T op){
    return op.generate();
  }
};

}}}


#endif //NINJA_WOOKIE_SERVICES_HPP
