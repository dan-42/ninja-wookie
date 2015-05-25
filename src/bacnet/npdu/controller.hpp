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



#ifndef NINJA_WOOKIE_CONTROLLER_HPP
#define NINJA_WOOKIE_CONTROLLER_HPP

#include <bitset>

#include <boost/fusion/include/define_struct.hpp>
#include <bacnet/detail/common/types.hpp>

namespace bacnet { namespace  npdu {

static constexpr uint8_t  protocol_version = 0x01;

//xxx to a more gloabl namespace?
enum class network_priority : uint8_t {
  normal_message             = 0b00000000,
  urgent_message             = 0b00000001,
  critical_equitment_message = 0b00000010,
  life_safety_message        = 0b00000011
};

namespace message_type {

static constexpr who_is_router_to_network         = 0x00;
static constexpr i_am_router_to_network           = 0x01;
static constexpr i_could_be_route_to_network      = 0x02;
static constexpr reject_message_to_network        = 0x03;
static constexpr router_busy_to_network           = 0x04;
static constexpr router_available_to_network      = 0x05;
static constexpr initialize_routing_table         = 0x06;
static constexpr initialize_routing_table_ack     = 0x07;
static constexpr establish_connection_to_network  = 0x08;
static constexpr disconnect_connection_to_network = 0x09;
static constexpr challenge_request                = 0x0A;
static constexpr security_payload                 = 0x0B;
static constexpr security_response                = 0x0C;
static constexpr request_key_update               = 0x0D;
static constexpr update_key_set                   = 0x0E;
static constexpr update_distribution_key          = 0x0F;
static constexpr request_master_key               = 0x10;
static constexpr set_master_key                   = 0x11;
static constexpr what_is_network_number           = 0x12;
static constexpr network_number_is                = 0x13;

//xxx stream operator to string
}




}}



namespace bacnet { namespace  npdu { namespace detail {

enum control_information_position {
  has_network_layer_message = 7,
  bit6_unused = 6,
  has_destination_specifier = 5,
  bit4_unused = 4,
  has_source_specifier = 3,
  has_confirmedReq_or_ComplxAck_or_expectingReply = 2,
  priority_hiBit = 1,
  priority_loBit = 0
};



static inline bool has_network_layer_message_type(uint8_t control_information){
  std:bitset<8> ci(control_information);
  return ci.test(control_information_position::has_network_layer_message);
}

static inline bool has_destination_specifier(uint8_t control_information){
  std:bitset<8> ci(control_information);
  return ci.test(control_information_position::has_destination_specifier);
}

static inline bool has_source_specifier(uint8_t control_information){
  std:bitset<8> ci(control_information);
  return ci.test(control_information_position::has_source_specifier);
}

static inline bool has_confirmedReq_or_ComplxAck_or_expectingReply(uint8_t control_information){
  std:bitset<8> ci(control_information);
  return ci.test(control_information_position::has_confirmedReq_or_ComplxAck_or_expectingReply);
}

static inline network_priority get_network_priority(uint8_t control_information) {
  uint8_t LOWEST_TWO_BITS = 0b00000011;
  uint8_t value_lowest_two_bits = LOWEST_TWO_BITS & control_information;
  return static_cast<network_priority>(value_lowest_two_bits);
}


}}}


BOOST_FUSION_DEFINE_STRUCT(
  (bacnet)(npdu), frame,
  (uint8_t, protocol_version)
 // (uint8_t, control_information)
  (uint16_t, destination_network_number)
//  (uint8_t, destination_length)
  (bacnet::binary_data, destination_address)
  (uint16_t, source_network_number)
//  (uint8_t, source_length)
  (bacnet::binary_data, source_address)
  (uint8_t, hop_count)
  (uint8_t, message_type)
  (uint16_t, vendor_id)
  (bacnet::binary_data, apdu_data)
)

namespace bacnet { namespace  npdu {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using namespace bacnet::npdu::frame;

template<typename Iterator>
struct npdu_grammar : grammar<Iterator, frame() >{

  rule<Iterator, frame()> frame_rule;
  rule<Iterator, bacnet::binary_data()> destination_address_rule;
  rule<Iterator, bacnet::binary_data()> source_address_rule;
  rule<Iterator, bacnet::binary_data()> apdu_data_rule;

  npdu_grammar() : npdu_grammar::base_type(frame_rule){

    frame_rule = byte_(protocol_version) > byte_[ref(control_information) = _1] >

                 ( (eps(has_destination_specifier(ref(control_information))) > big_word > byte_[ref(destination_length) = _1] >  destination_address_rule  ) | ( attr(uint16_t{0} > destination_address_rule) ) )
              >  ( (eps(has_source_specifier(ref(control_information)))      > big_word > byte_[ref(source_length) = _1]      >  source_address_rule  )      | ( attr(uint16_t{0} > source_address_rule) ) )
              >  ( (eps(has_destination_specifier(ref(control_information))) > byte_) | (attr(uint8_t{0})) )
              >  ( (eps(has_network_layer_message_type(ref(control_information))) > byte_) | (attr(uint8_t{0})) )
      //xxx vendor id
              > repeare[byte_]
        ;




    destination_address_rule = repeate(ref(destination_length))[byte_];
    source_address_rule = repeate(ref(source_length))[byte_];

  }


  uint8_t control_information = 0;
  uint8_t destination_length = 0;
  uint8_t source_length = 0;

};


}}