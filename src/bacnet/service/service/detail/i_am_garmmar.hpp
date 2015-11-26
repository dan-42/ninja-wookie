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
#include <bacnet/apdu/type/object_identifier.hpp>
#include <bacnet/apdu/type/enumeration.hpp>
#include <bacnet/apdu/type/unsigned_integer_generator.hpp>
#include <bacnet/apdu/type/object_identifier_generator.hpp>
#include <bacnet/apdu/type/enumaration_grammar.hpp>
#include <bacnet/apdu/type/detail/helper.hpp>




namespace bacnet { namespace service { namespace service { namespace detail {

template<>
bacnet::binary_data generate<i_am>(const i_am& i_am_service) {

  namespace service = bacnet::service::service;
  namespace apdu    = bacnet::apdu::type;


  bacnet::binary_data binary;
  auto service_choice_command = service_choice<service::i_am>::value;
  binary.push_back(service_choice_command);

  auto max_apdu_length_accepted = i_am_service.max_apdu_length_accepted;

  constexpr bool is_application_tag = false;
  apdu::tag tag_object_identifier(apdu::application_tag_number::bacnet_object_identifier, is_application_tag, 4);
  apdu::tag tag_max_apdu_accepted(apdu::application_tag_number::unsigned_interger, is_application_tag, apdu::detail::length_helper(max_apdu_length_accepted));
  apdu::tag tag_segmentation_supported(apdu::application_tag_number::enumerated, is_application_tag, apdu::detail::length_helper(i_am_service.segmentation_supported.to_native()));
  apdu::tag tag_vendor_id(apdu::application_tag_number::unsigned_interger, is_application_tag, apdu::detail::length_helper(i_am_service.vendor_id));


  apdu::object_identifier oi(tag_object_identifier, i_am_service.i_am_device_identifier);
  auto oi_binary = apdu::generate(oi);
  binary.insert(binary.end(), oi_binary.begin(), oi_binary.end());


  apdu::unsigned_integer max_apdu_accepted(tag_max_apdu_accepted, max_apdu_length_accepted);
  auto max_apdu_accepted_binary = apdu::generate(max_apdu_accepted);
  binary.insert(binary.end(), max_apdu_accepted_binary.begin(), max_apdu_accepted_binary.end());

  apdu::enumeration segmentation_supported(tag_segmentation_supported, i_am_service.segmentation_supported.to_native());
  auto segmentation_supported_binary = apdu::generate(segmentation_supported);
  binary.insert(binary.end(), segmentation_supported_binary.begin(), segmentation_supported_binary.end());

  apdu::unsigned_integer vendor_id(tag_vendor_id, i_am_service.vendor_id);
  auto vendor_id_binary = apdu::generate(vendor_id);
  binary.insert(binary.end(), vendor_id_binary.begin(), vendor_id_binary.end());



  return binary;
}


template<>
bool parse<i_am>(bacnet::binary_data& data, i_am &service) {
/*

    (bacnet)(service)(service), i_am,
    (bacnet::common::object_identifier, i_am_device_identifier)
    (uint32_t, max_apdu_length_accepted)
    (bacnet::common::segmentation, segmentation_supported)
    (uint16_t, vendor_id)


X'00'       Service Choice=0 (I-Am-Request)

X'C4'       Application Tag 12 (Object Identifier, L=4) (I-Am Device Identifier)
X'02000001' Device, Instance Number=1

X'22'       Application Tag 2 (Unsigned Integer, L=2) (Max APDU Length Accepted)
X'01E0'     480

X'91'       Application Tag 9 (Enumerated, L=1) (Segmentation Supported)
X'01'1      (SEGMENTED_TRANSMIT)

X'21'       Application Tag 2 (Unsigned Integer, L=1) (Vendor ID)
X'63'       99
 */

  if(data.empty()) {
    return false;
  }
  data.erase(data.begin(), data.begin()+1);

  apdu::unsigned_integer tmp_unsigned;
  apdu::object_identifier tmp_oi;
  apdu::enumeration tmp_enumeration;
  bool has_succeeded = false;

  has_succeeded = apdu::parse(data, tmp_oi);
  if(!has_succeeded) {
    std::cout << "parse<service::i_am> fail tag 0" << std::endl;
    return false;
  }
  service.i_am_device_identifier = tmp_oi.object_identifier_;
  service.i_am_device_identifier.object_typ(bacnet::object_type::device);

  has_succeeded = apdu::parse(data, tmp_unsigned);
  if(!has_succeeded) {
    std::cout << "parse<service::i_am> fail tag 1" << std::endl;
    return false;
  }
  service.max_apdu_length_accepted = tmp_unsigned.value_;


  has_succeeded = apdu::parse(data, tmp_enumeration);
  if(!has_succeeded) {
    std::cout << "parse<service::i_am> fail tag 2" << std::endl;
    return false;
  }
  service.segmentation_supported.from_native(tmp_enumeration.value_);

  has_succeeded = apdu::parse(data, tmp_unsigned);
  if(!has_succeeded) {
    std::cout << "parse<service::i_am> fail tag 3" << std::endl;
    return false;
  }
  service.vendor_id = tmp_unsigned.value_;

  return true;
}


}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_DETAIL_I_AM_GRAMMAR_HPP
