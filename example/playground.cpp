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

#include <bacnet/type/properties.hpp>
#include <bacnet/stack/factory.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <bacnet/type/bit_string.hpp>
#include <bacnet/type/types.hpp>
#include <bacnet/type/object_property_reference.hpp>
#include <bacnet/type/confirmed_private_transfer_error.hpp>


#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>

#include <boost/system/error_code.hpp>





int main(int argc, char *argv[]) {


  //bacnet::type::property::supported_properties t;

/*
  bacnet::object_ptr_list_t object_list;

  auto ai_ptr = std::make_shared<bacnet::analog_input>();
  auto ao_ptr = std::make_shared<bacnet::analog_output>();
  object_list.push_back(ai_ptr);
  object_list.push_back(ao_ptr);

  uint16_t property_id{0};
  boost::optional<uint16_t> index;
  bacnet::binary_data data{};

  for(auto& o : object_list) {
    o->write_prop(property_id, index, data);
    o->read_prop(property_id, index);
  }
*/
}
