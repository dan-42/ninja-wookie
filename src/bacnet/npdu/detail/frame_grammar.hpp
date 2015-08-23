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

#ifndef SRC_BACNET_NPDU_DETAIL_FRAME_GRAMMAR_HPP_
#define SRC_BACNET_NPDU_DETAIL_FRAME_GRAMMAR_HPP_




#include <bitset>

#include <boost/fusion/include/define_struct.hpp>


#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>



#include <bacnet/npdu/network_priority.hpp>
#include <bacnet/npdu/protocol_version.hpp>
#include <bacnet/npdu/vendor_specific_message_type_adr.hpp>
#include <bacnet/npdu/message_type.hpp>
#include <bacnet/npdu/address.hpp>

#include <bacnet/npdu/frame.hpp>

#include <bacnet/npdu/detail/address_grammar.hpp>

namespace bacnet { namespace  npdu { namespace detail { namespace parser {

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
struct npdu_grammar : grammar<Iterator, frame() >{

  rule<Iterator, frame()>               frame_rule;
  rule<Iterator, uint8_t()>             protocol_version_rule;
  rule<Iterator, control_information_t()> controle_information_rule;
  rule<Iterator, address()>             destination_rule;
  rule<Iterator, address()>             source_rule;
  rule<Iterator, uint8_t()>             hop_count_rule;
  rule<Iterator, uint8_t()>             message_type_rule;
  rule<Iterator, uint16_t()>            vendor_id_rule;
  rule<Iterator, bacnet::binary_data()> apdu_data_rule;

  address_grammar<Iterator>             address_grammar_;

  bit_field<Iterator, control_information_t> control_information_grammar;

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

    destination_rule  = ( (eps(boost::phoenix::bind(&control_information_t::has_destination_specifier, ref(control_field)) == true) >>  address_grammar_ )
                      | ( attr(empty_address)) );

    source_rule       = ( (eps(boost::phoenix::bind(&control_information_t::has_source_specifier, ref(control_field)) == true) >> address_grammar_ )
                      | ( attr(empty_address)) );

    hop_count_rule    = ( (eps(boost::phoenix::bind(&control_information_t::has_destination_specifier, ref(control_field)) == true) >> byte_            )
                      | ( attr(uint8_t{0})) );

    message_type_rule = ( (eps(boost::phoenix::bind(&control_information_t::has_network_layer_message_type, ref(control_field)) == true) >> byte_[ref(message_type) = _1]  )[_val = _1]
                      | ( attr(uint8_t{0})) );

    vendor_id_rule    = ( (eps(boost::phoenix::bind(&control_information_t::has_network_layer_message_type, ref(control_field)) == true) >> eps(ref(message_type) >= vendor_specific_message_type_adr) >> big_word   )
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
  control_information_t control_field;
  uint8_t message_type = 0;
};

}}}}





namespace boost { namespace spirit { namespace traits {
template <>
struct transform_attribute<bacnet::binary_data const, uint8_t, boost::spirit::karma::domain>
{
  typedef uint8_t type;
  static uint8_t pre(bacnet::binary_data const& d) { return static_cast<uint8_t>(d.size()); }
};
}}}

namespace bacnet { namespace  npdu { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;

using namespace bacnet::npdu::detail;
using namespace bacnet::npdu;

using boost::spirit::karma::bit_field;
using boost::spirit::karma::rule;
using boost::spirit::karma::_1;



template<typename Iterator>
struct npdu_grammar : grammar<Iterator, frame() >{

  rule<Iterator, frame()>               frame_rule;
  rule<Iterator, uint8_t()>             protocol_version_rule;
  rule<Iterator, control_information_t()> controle_information_rule;
  rule<Iterator, address()>             destination_rule;
  rule<Iterator, address()>             source_rule;
  rule<Iterator, uint8_t()>             hop_count_rule;
  rule<Iterator, uint8_t()>             message_type_rule;
  rule<Iterator, uint16_t()>            vendor_id_rule;
  rule<Iterator, bacnet::binary_data()> apdu_data_rule;

  address_grammar<Iterator>             address_grammar_;

  bit_field<Iterator, control_information_t> control_information_grammar;

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

    destination_rule  = ( (eps(boost::phoenix::bind(&control_information_t::has_destination_specifier, ref(control_field)) == true)
                            <<  address_grammar_ )
                      | eps );

    source_rule       = ( (eps(boost::phoenix::bind(&control_information_t::has_source_specifier, ref(control_field)) == true)
                            << address_grammar_ )
                       | eps );

    hop_count_rule    = ( (eps(boost::phoenix::bind(&control_information_t::has_destination_specifier, ref(control_field)) == true)
                           << byte_            )
                       | eps );

    message_type_rule = ( (eps(boost::phoenix::bind(&control_information_t::has_network_layer_message_type, ref(control_field)) == true)
                           << byte_[ref(message_type) = _val]  )[_1 = _val]
                      | eps  );

    vendor_id_rule    = ( (eps(boost::phoenix::bind(&control_information_t::has_network_layer_message_type, ref(control_field)) == true)
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
  control_information_t control_field;
  uint8_t message_type = 0;
};

}}}}






#endif /* SRC_BACNET_NPDU_DETAIL_FRAME_GRAMMAR_HPP_ */
