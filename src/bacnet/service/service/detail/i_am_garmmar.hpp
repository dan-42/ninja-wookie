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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_DETAIL_I_AM_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_DETAIL_I_AM_GRAMMAR_HPP

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/service/i_am.hpp>

#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/apdu/type/unsigned_integer.hpp>
#include <bacnet/apdu/type/unsigned_integer_generator.hpp>
#include <bacnet/apdu/type/detail/helper.hpp>



namespace bacnet { namespace service { namespace service { namespace detail {

namespace service = bacnet::service::service;
namespace apdu    = bacnet::apdu::type;


template<>
bacnet::binary_data generate<i_am>(const i_am& service) {


  constexpr uint32_t device_instance_low_limit = 0;
  constexpr uint32_t device_instance_high_limit = 4194303;

  constexpr uint8_t context_tag_number_0 = 0x00;
  constexpr uint8_t context_tag_number_1 = 0x01;
  constexpr bool is_conext_tag = false;



  bacnet::binary_data binary;

  /* todo generate */

  return binary;
}

/*
template<>
bool parse<i_am>(bacnet::binary_data& data, who_is &service) {


  // it's allowed to have now payload
  if(data.empty()) {
    service.device_instance_range_low_limit = 0;
    service.device_instance_range_high_limit = 0;
    return true;
  }

  apdu::unsigned_integer low_limit;
  apdu::unsigned_integer high_limit;
  bool has_succeeded = false;

  has_succeeded= apdu::parse(data, low_limit);
  if(!has_succeeded) {
    return false;
  }

  has_succeeded = apdu::parse(data, high_limit);
  if(!has_succeeded) {
    return false;
  }

  service.device_instance_range_high_limit = high_limit.value_;
  service.device_instance_range_low_limit  = low_limit.value_;

  return true;
}
*/

}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_DETAIL_I_AM_GRAMMAR_HPP
