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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_REINITIALIZE_DEVICE_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_REINITIALIZE_DEVICE_GRAMMAR_HPP

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/service/reinitialize_device.hpp>

#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/apdu/type/unsigned_integer.hpp>
#include <bacnet/apdu/type/unsigned_integer_generator.hpp>
#include <bacnet/apdu/type/character_string.hpp>
#include <bacnet/apdu/type/character_string_generator.hpp>
#include <bacnet/apdu/type/detail/helper.hpp>

#include <bacnet/service/service/detail/service_grammar.hpp>

/*
 *
 F.4.4 Encoding for Example E.4.4 - ReinitializeDevice Service
X'00'
X'01'
X'02'
X'14'
PDU Type=0 (BACnet-Confirmed-Request-PDU, SEG=0, MOR=0, SA=0)
Maximum APDU Size Accepted=128 octets
Invoke ID=2
Service Choice=20 (ReinitializeDevice-Request)
X'09'
X'01'
X'1D'
X'09'
X'00'
X'4162436445664768'
SD Context Tag 0 (Reinitialized State Of Device, L=1)
1 (WARMSTART)
SD Context Tag 1 (Password, L>4)
Extended Length=9
ISO 10646 (UTF-8) Encoding
"AbCdEfGh"
Assuming this service procedure executes correctly, a simple acknowledgment is returned:
X'20'
X'02'
X'14'
PDU Type=2 (BACnet-SimpleACK-PDU)
Invoke ID=2
Service ACK Choice=20 (ReinitializeDevice)



 */


namespace bacnet { namespace service { namespace service { namespace detail {


namespace service = bacnet::service::service;
namespace apdu    = bacnet::apdu::type;

template<>
bacnet::binary_data generate<service::reinitialize_device>(const service::reinitialize_device& service) {


  constexpr decltype(service.passowrd)::size_type password_string_max_length = 20;

  constexpr uint8_t context_tag_number_0 = 0x00;
  constexpr uint8_t context_tag_number_1 = 0x01;
  constexpr bool is_conext_tag = true;
  auto service_choice_command = service_choice<service::reinitialize_device>::value;

  bacnet::binary_data binary;

  binary.push_back(service_choice_command);

  apdu::tag tag_reinitialized_state_of_device(context_tag_number_0, is_conext_tag, apdu::detail::length_helper(service.reinitialize_state_of_device));
  apdu::unsigned_integer reinitialized_state_of_device(tag_reinitialized_state_of_device, service.reinitialize_state_of_device);
  auto reinitialized_state_of_device_binary = apdu::generate(reinitialized_state_of_device);
  binary.insert(binary.end(), reinitialized_state_of_device_binary.begin(), reinitialized_state_of_device_binary.end());


  if(!service.passowrd.empty() && service.passowrd.size() <= password_string_max_length) {

    apdu::tag tag_password(context_tag_number_1, is_conext_tag, service.passowrd.size() + 1);

    apdu::character_string password(tag_password, apdu::string_encoding_type::iso_10646_utf_8, service.passowrd);
    auto password_binary = apdu::generate(password);
    binary.insert(binary.end(), password_binary.begin(), password_binary.end());

  }

  return binary;
}


template<>
bool parse<service::reinitialize_device>(bacnet::binary_data& data, service::reinitialize_device &service) {


  if(data.empty()) {
    return false;
  }
/*

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
*/
  return true;
}


}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_REINITIALIZE_DEVICE_GRAMMAR_HPP
