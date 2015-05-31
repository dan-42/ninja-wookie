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

#include <boost/phoenix/bind/bind_member_function.hpp>
#include <bacnet/npdu/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>

namespace bacnet { namespace  npdu {

static constexpr uint8_t  protocol_version = 0x01;

static constexpr uint8_t  vendor_specific_message_type_adr = 0x80;

//xxx to a more gloabl namespace?
enum class network_priority : uint8_t {
  normal_message             = 0b00000000,
  urgent_message             = 0b00000001,
  critical_equitment_message = 0b00000010,
  life_safety_message        = 0b00000011
};

namespace message_type {

static constexpr uint8_t who_is_router_to_network         = 0x00;
static constexpr uint8_t i_am_router_to_network           = 0x01;
static constexpr uint8_t i_could_be_route_to_network      = 0x02;
static constexpr uint8_t reject_message_to_network        = 0x03;
static constexpr uint8_t router_busy_to_network           = 0x04;
static constexpr uint8_t router_available_to_network      = 0x05;
static constexpr uint8_t initialize_routing_table         = 0x06;
static constexpr uint8_t initialize_routing_table_ack     = 0x07;
static constexpr uint8_t establish_connection_to_network  = 0x08;
static constexpr uint8_t disconnect_connection_to_network = 0x09;
static constexpr uint8_t challenge_request                = 0x0A;
static constexpr uint8_t security_payload                 = 0x0B;
static constexpr uint8_t security_response                = 0x0C;
static constexpr uint8_t request_key_update               = 0x0D;
static constexpr uint8_t update_key_set                   = 0x0E;
static constexpr uint8_t update_distribution_key          = 0x0F;
static constexpr uint8_t request_master_key               = 0x10;
static constexpr uint8_t set_master_key                   = 0x11;
static constexpr uint8_t what_is_network_number           = 0x12;
static constexpr uint8_t network_number_is                = 0x13;

//xxx stream operator to string
}

}}



namespace bacnet { namespace  npdu { namespace detail {

enum control_information_position {
  position_has_network_layer_message = 7,
  position_bit6_unused = 6,
  position_has_destination_specifier = 5,
  position_bit4_unused = 4,
  position_has_source_specifier = 3,
  position_has_confirmedReq_or_ComplxAck_or_expectingReply = 2,
  position_priority_hiBit = 1,
  position_priority_loBit = 0
};



}}}


BOOST_FUSION_DEFINE_STRUCT(
    (bacnet)(npdu), address,
    (uint16_t, network_number)
    (bacnet::binary_data, binary_address)
)


std::ostream &operator<<(std::ostream &os, const bacnet::npdu::address &a) {
  os << "bacnet::npdu::address " << (int)a.network_number << ":";
  for(auto &b : a.binary_address){
    os <<  std::setfill ('0') << std::setw(2) << std::hex << (int)b << " ";
  }
  return os;
}

namespace  bacnet { namespace npdu {
struct alignas(1) control_information {
  uint8_t priority_                  : 2;
  uint8_t has_confirmedReq_or_ComplxAck_or_expectingReply_ : 1;
  uint8_t has_source_specifier_      : 1;
  uint8_t bit4_unused_               : 1;
  uint8_t has_destination_specifier_ : 1;
  uint8_t bit6_unused_               : 1;
  uint8_t has_network_layer_message_ : 1;

  control_information() : priority_(0), has_confirmedReq_or_ComplxAck_or_expectingReply_(0),
                          has_source_specifier_(0), bit4_unused_(0), has_destination_specifier_(0),
                          bit6_unused_(0), has_network_layer_message_(0) {
  }

  bool has_confirmedReq_or_ComplxAck_or_expectingReply(){
    return has_confirmedReq_or_ComplxAck_or_expectingReply_==true;
  }
  bool has_source_specifier(){
    return has_source_specifier_==true;
  }
  bool has_destination_specifier(){
    return has_destination_specifier_==true;
  }
  bool has_network_layer_message_type(){
    return has_network_layer_message_==true;
  }
};

std::ostream &operator<<(std::ostream &os, const bacnet::npdu::control_information &ci) {
  os << "\thas_network_layer_message: ";
  if(ci.has_network_layer_message_) { os << "true";  }
  else { os << "false" ;  }
  os << "\n";

  os << "\t  has_destination_specifier: ";
  if(ci.has_destination_specifier_) { os << "true";  }
  else { os << "false" ;  }
  os << "\n";

  os << "\t  has_source_specifier: ";
  if(ci.has_source_specifier_) { os << "true";  }
  else { os << "false" ;  }
  os << "\n";

  os << "\t  has_confirmedReq_or_ComplxAck_or_expectingReply: ";
  if(ci.has_confirmedReq_or_ComplxAck_or_expectingReply_) { os << "true";  }
  else { os << "false" ;  }
  os << "\n";

  os << "\t  priority: ";
  os << std::to_string((int) ci.priority_) ;
  os << "\n";

  return os;
}

}}

BOOST_FUSION_DEFINE_STRUCT(
  (bacnet)(npdu), frame,
  (uint8_t, protocol_version)
  (bacnet::npdu::control_information, control_field)
  (bacnet::npdu::address, destination)
  (bacnet::npdu::address, source)
  (uint8_t, hop_count)
  (uint8_t, message_type)
  (uint16_t, vendor_id)
  (bacnet::binary_data, apdu_data)
)


std::ostream &operator<<(std::ostream &os, const bacnet::npdu::frame &f) {

  os << "bacnet::npdu::frame version: " <<  std::setfill ('0') << std::setw(2) << std::hex << (int)f.protocol_version << "\n";
  os << "\t control_information: " << f.control_field << "\n";
  os << "\t destination: " << f.destination << "\n";
  os << "\t source: " << f.source << "\n";
  os << "\t hop_count: " <<  std::setfill ('0') << std::setw(2) << std::hex << (int)f.hop_count << "\n";
  os << "\t message_type: " <<  std::setfill ('0') << std::setw(2) << std::hex << (int)f.message_type << "\n";
  os << "\t vendor_id: " <<  std::setfill ('0') << std::setw(2) << std::hex << (int)f.vendor_id << "\n";
  os << "\t apdu_data: ";

  for(auto &b : f.apdu_data){
    os <<  std::setfill ('0') << std::setw(2) << std::hex << (int)b << " ";
  }
  os << "\n";

  return os;
}


namespace bacnet { namespace  npdu { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using namespace bacnet::npdu::detail;
using boost::spirit::qi::bit_field;

using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::spirit::qi::_2;
using boost::spirit::qi::_3;
using boost::phoenix::bind;

template<typename Iterator>
struct address_grammar : grammar<Iterator, address() > {

  rule<Iterator, address()>             address_rule;
  rule<Iterator, uint16_t()>            network_number_rule;
  rule <Iterator>                       length_rule;
  rule<Iterator, bacnet::binary_data()> binary_address_rule;

  address_grammar() : address_grammar::base_type(address_rule) {

    address_rule = (network_number_rule >> length_rule >> binary_address_rule);

    network_number_rule = big_word;
    length_rule = byte_[ref(length) = _1];
    binary_address_rule = repeat(ref(length))[byte_];

    address_rule.name("address_rule");
    network_number_rule.name("network_number_rule");
    binary_address_rule.name("binary_address_rule");

    //debug(address_rule);
    //debug(network_number_rule);
    //debug(binary_address_rule);
  }

  uint8_t length = 0;
};



template<typename Iterator>
struct npdu_grammar : grammar<Iterator, frame() >{

  rule<Iterator, frame()>               frame_rule;
  rule<Iterator, uint8_t()>             protocol_version_rule;
  rule<Iterator, control_information()> controle_information_rule;
  rule<Iterator, address()>             destination_rule;
  rule<Iterator, address()>             source_rule;
  rule<Iterator, uint8_t()>             hop_count_rule;
  rule<Iterator, uint8_t()>             message_type_rule;
  rule<Iterator, uint16_t()>            vendor_id_rule;
  rule<Iterator, bacnet::binary_data()> apdu_data_rule;

  address_grammar<Iterator>             address_grammar_;

  bit_field<Iterator, control_information> control_information_grammar;

  npdu_grammar() : npdu_grammar::base_type(frame_rule){

    frame_rule = protocol_version_rule
                 >> controle_information_rule
                 >>  destination_rule
                 >> source_rule
                 >> hop_count_rule
                 >> message_type_rule
                 >> vendor_id_rule
                 >> apdu_data_rule;


    protocol_version_rule = byte_(bacnet::npdu::protocol_version);
    controle_information_rule = (control_information_grammar[ref(control_field) = _1])[_val = _1];

    destination_rule  = ( (eps(boost::phoenix::bind(&control_information::has_destination_specifier, ref(control_field)) == true) >>  address_grammar_ )
                      | ( attr(empty_address)) );

    source_rule       = ( (eps(boost::phoenix::bind(&control_information::has_source_specifier, ref(control_field)) == true) >> address_grammar_ )
                      | ( attr(empty_address)) );

    hop_count_rule    = ( (eps(boost::phoenix::bind(&control_information::has_destination_specifier, ref(control_field)) == true) >> byte_            )
                      | ( attr(uint8_t{0})) );

    message_type_rule = ( (eps(boost::phoenix::bind(&control_information::has_network_layer_message_type, ref(control_field)) == true) >> byte_[ref(message_type) = _1]  )[_val = _1]
                      | ( attr(uint8_t{0})) );

    vendor_id_rule    = ( (eps(boost::phoenix::bind(&control_information::has_network_layer_message_type, ref(control_field)) == true) >> eps(ref(message_type) >= vendor_specific_message_type_adr) >> big_word   )
                      | ( attr(uint16_t{0})) );

    apdu_data_rule    = repeat[byte_];


    frame_rule.name("frame_rule");
    protocol_version_rule.name("protocol_version_rule");
    controle_information_rule.name("controle_information_rule");
    destination_rule.name("destination_rule");
    source_rule.name("source_rule");
    hop_count_rule.name("hop_count_rule");

    /*
       debug(destination_rule);
       debug(source_rule);
       debug(frame_rule);
       debug(controle_information_rule);
       debug(source_rule);
       debug(frame_rule);
       debug(frame_rule);
     */
  }

  address empty_address;
  control_information control_field;
  uint8_t message_type = 0;
};

}}}





namespace boost { namespace spirit { namespace traits {
template <>
struct transform_attribute<bacnet::binary_data const, uint8_t, boost::spirit::karma::domain>
{
  typedef uint8_t type;
  static uint8_t pre(bacnet::binary_data const& d) { return static_cast<uint8_t>(d.size()); }
};
}}}

namespace bacnet { namespace  npdu { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;

using namespace bacnet::npdu::detail;
using namespace bacnet::npdu;

using boost::spirit::karma::bit_field;
using boost::spirit::karma::rule;
using boost::spirit::karma::_1;

template<typename Iterator>
struct address_grammar : grammar<Iterator, address() > {

  rule<Iterator, address()>             address_rule;
  rule<Iterator, uint16_t()>            network_number_rule;
  rule<Iterator, bacnet::binary_data()> length_rule;
  rule<Iterator, bacnet::binary_data()> binary_address_rule;

  address_grammar() : address_grammar::base_type(address_rule) {

    address_rule = (network_number_rule <<  binary_address_rule);

    network_number_rule = big_word;
    length_rule = attr_cast(byte_);
    binary_address_rule =  length_rule[_1 = _val] << (repeat[byte_])[_1 = _val];

    address_rule.name("address_rule");
    network_number_rule.name("network_number_rule");
    binary_address_rule.name("binary_address_rule");

    //debug(address_rule);
    //debug(network_number_rule);
    //debug(binary_address_rule);
  }
};



template<typename Iterator>
struct npdu_grammar : grammar<Iterator, frame() >{

  rule<Iterator, frame()>               frame_rule;
  rule<Iterator, uint8_t()>             protocol_version_rule;
  rule<Iterator, control_information()> controle_information_rule;
  rule<Iterator, address()>             destination_rule;
  rule<Iterator, address()>             source_rule;
  rule<Iterator, uint8_t()>             hop_count_rule;
  rule<Iterator, uint8_t()>             message_type_rule;
  rule<Iterator, uint16_t()>            vendor_id_rule;
  rule<Iterator, bacnet::binary_data()> apdu_data_rule;

  address_grammar<Iterator>             address_grammar_;

  bit_field<Iterator, control_information> control_information_grammar;

  npdu_grammar() : npdu_grammar::base_type(frame_rule){

    frame_rule = protocol_version_rule
                 << controle_information_rule
                 <<  destination_rule
                 << source_rule
                 << hop_count_rule
                 << message_type_rule
                 << vendor_id_rule
                 << apdu_data_rule;


    protocol_version_rule = byte_(bacnet::npdu::protocol_version);
    controle_information_rule = (control_information_grammar[ref(control_field) = _val])[_1 = _val];

    destination_rule  = ( (eps(boost::phoenix::bind(&control_information::has_destination_specifier, ref(control_field)) == true)
                            <<  address_grammar_ )
                      | eps );

    source_rule       = ( (eps(boost::phoenix::bind(&control_information::has_source_specifier, ref(control_field)) == true)
                            << address_grammar_ )
                       | eps );

    hop_count_rule    = ( (eps(boost::phoenix::bind(&control_information::has_destination_specifier, ref(control_field)) == true)
                           << byte_            )
                       | eps );

    message_type_rule = ( (eps(boost::phoenix::bind(&control_information::has_network_layer_message_type, ref(control_field)) == true)
                           << byte_[ref(message_type) = _val]  )[_1 = _val]
                      | eps  );

    vendor_id_rule    = ( (eps(boost::phoenix::bind(&control_information::has_network_layer_message_type, ref(control_field)) == true)
                           << eps(ref(message_type) >= vendor_specific_message_type_adr) << big_word   )
                      | eps   );

    apdu_data_rule    = repeat[byte_];


    frame_rule.name("frame_rule");
    protocol_version_rule.name("protocol_version_rule");
    controle_information_rule.name("controle_information_rule");
    destination_rule.name("destination_rule");
    source_rule.name("source_rule");
    hop_count_rule.name("hop_count_rule");

     /*
       debug(destination_rule);
       debug(source_rule);
       debug(frame_rule);
       debug(controle_information_rule);
       debug(source_rule);
       debug(frame_rule);
       debug(frame_rule);
     */
  }
  control_information control_field;
  uint8_t message_type = 0;
};

}}}

#endif /* NINJA_WOOKIE_NPDU_CONTROLLER_HPP */