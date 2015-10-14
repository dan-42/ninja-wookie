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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_WHO_IS_GRAMMA_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_WHO_IS_GRAMMA_HPP

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/service/who_is.hpp>

#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/apdu/type/unsigned_integer.hpp>
#include <bacnet/apdu/type/unsigned_integer_generator.hpp>
#include <bacnet/apdu/type/detail/helper.hpp>

#include <bacnet/service/service/detail/service_grammar.hpp>




namespace bacnet { namespace service { namespace service { namespace detail {


namespace service = bacnet::service::service;
namespace apdu    = bacnet::apdu::type;

template<>
bacnet::binary_data generate<service::who_is>(const service::who_is& service) {


  constexpr uint32_t device_instance_low_limit = 0;
  constexpr uint32_t device_instance_high_limit = 4194303;

  constexpr uint8_t context_tag_number_0 = 0x00;
  constexpr uint8_t context_tag_number_1 = 0x01;
  constexpr bool is_conext_tag = true;

  bacnet::binary_data binary;

  auto service_choice_command = service_choice<service::who_is>::value;
  binary.push_back(service_choice_command);

  if(service.device_instance_range_low_limit > device_instance_low_limit) {

    apdu::tag tag_low_limit(context_tag_number_0, is_conext_tag, apdu::detail::length_helper(service.device_instance_range_low_limit));
    apdu::tag tag_heigh_limit(context_tag_number_1, is_conext_tag, apdu::detail::length_helper(service.device_instance_range_high_limit));

    apdu::unsigned_integer low_limit(tag_low_limit, service.device_instance_range_low_limit);
    auto low_limit_binary = apdu::generate(low_limit);
    binary.insert(binary.end(), low_limit_binary.begin(), low_limit_binary.end());


    if(service.device_instance_range_high_limit > device_instance_low_limit) {
      apdu::unsigned_integer high_limit(tag_heigh_limit, service.device_instance_range_high_limit);
      auto high_limit_binary = apdu::generate(high_limit);
      binary.insert(binary.end(), high_limit_binary.begin(), high_limit_binary.end());
    }
    else {
      apdu::unsigned_integer high_limit(tag_heigh_limit, service.device_instance_range_low_limit);
      auto high_limit_binary = apdu::generate(high_limit);
      binary.insert(binary.end(), high_limit_binary.begin(), high_limit_binary.end());
    }
  }

  return binary;
}


template<>
bool parse<service::who_is>(bacnet::binary_data& data, service::who_is &service) {


  if(data.empty()) {
    return false;
  }

  /*it's allowed to have now payload*/
  if(data.size() == 1 && data.front() == uncomfirmed_service::who_is) {
    service.device_instance_range_low_limit = 0;
    service.device_instance_range_high_limit = 0;
    return true;
  }

  data.erase(data.begin(), data.begin()+1);

  apdu::unsigned_integer low_limit;
  apdu::unsigned_integer high_limit;
  bool has_succeeded = false;

  has_succeeded = apdu::parse(data, low_limit);
  if(!has_succeeded) {
    std::cout << "parse<service::who_is> fail tag 0" << std::endl;
    return false;
  }

  has_succeeded = apdu::parse(data, high_limit);
  if(!has_succeeded) {
    std::cout << "parse<service::who_is> fail tag 1" << std::endl;
    return false;
  }

  service.device_instance_range_high_limit = high_limit.value_;
  service.device_instance_range_low_limit  = low_limit.value_;

  return true;
}


}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_WHO_IS_GRAMMA_HPP
