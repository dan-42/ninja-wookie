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

#ifndef SRC_BACNET_APDU_FRAME_DETAIL_SIMPLE_ACK_GRAMMAR_HPP_
#define SRC_BACNET_APDU_FRAME_DETAIL_SIMPLE_ACK_GRAMMAR_HPP_


#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>

#include <bacnet/apdu/frame/simple_ack.hpp>
#include <bacnet/apdu/detail/pdu_type.hpp>


namespace bacnet { namespace  apdu { namespace frame { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::bit_field;
using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::phoenix::bind;

using namespace bacnet::apdu;
using namespace bacnet::apdu::frame;
using namespace bacnet::apdu::detail;
using namespace bacnet::apdu::detail::header;


template<typename Iterator>
struct simple_ack_grammar : grammar<Iterator, simple_ack() >{

  rule<Iterator, simple_ack()>                            simple_ack_rule;
  rule<Iterator, pdu_type_and_control_information_t()>    pdu_header_rule;
  rule<Iterator, uint8_t()>                               original_invoke_id_rule;
  rule<Iterator, uint8_t()>                               service_ack_choice_rule;

  rule<Iterator>                                          pdu_type_check_rule;


  bit_field<Iterator, pdu_type_and_control_information_t> pdu_type_and_control_information_grammar;

  simple_ack_grammar() : simple_ack_grammar::base_type(simple_ack_rule){

    simple_ack_rule  = pdu_header_rule
                     >> original_invoke_id_rule
                     >> service_ack_choice_rule;


    pdu_header_rule           = (pdu_type_and_control_information_grammar[ref(pdu_header_) = _1])[_val = _1]  >> pdu_type_check_rule;

    original_invoke_id_rule   = byte_;

    service_ack_choice_rule   = byte_;


    pdu_type_check_rule       = ( eps(boost::phoenix::bind(&pdu_type_and_control_information_t::pdu_type, ref(pdu_header_)) == pdu_type::simple_ack)
                              >>  eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_segmented, ref(pdu_header_))                   == false)
                              >>  eps(boost::phoenix::bind(&pdu_type_and_control_information_t::has_more_segments_following, ref(pdu_header_))     == false)
                              >>  eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_segmented_response_accepted, ref(pdu_header_))  == false)
                              >>  eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_send_by_server, ref(pdu_header_))               == false)
                              );
    /*
    simple_ack_rule.name("service_ack_choice_rule");
    pdu_header_rule.name("pdu_header_rule");
    original_invoke_id_rule.name("original_invoke_id_rule");
    service_ack_choice_rule.name("service_ack_choice_rule");
    pdu_type_check_rule.name("pdu_type_check_rule");
    debug(simple_ack_rule);
    debug(pdu_header_rule);
    debug(original_invoke_id_rule);
    debug(service_ack_choice_rule);
    debug(pdu_type_check_rule);
     */
  }


  pdu_type_and_control_information_t pdu_header_;
};

}}}}}





namespace bacnet { namespace  apdu { namespace frame {  namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;

using boost::spirit::karma::bit_field;
using boost::spirit::karma::rule;
using boost::spirit::karma::_1;


using namespace bacnet::apdu;
using namespace bacnet::apdu::frame;
using namespace bacnet::apdu::detail;
using namespace bacnet::apdu::detail::header;



template<typename Iterator>
struct simple_ack_grammar : grammar<Iterator, simple_ack() >{

  rule<Iterator, simple_ack()>                            simple_ack_rule;
  rule<Iterator, pdu_type_and_control_information_t()>    pdu_header_rule;
  rule<Iterator, uint8_t()>                               original_invoke_id_rule;
  rule<Iterator, uint8_t()>                               service_ack_choice_rule;

  rule<Iterator>                                          pdu_type_check_rule;


  bit_field<Iterator, pdu_type_and_control_information_t> pdu_type_and_control_information_grammar;

  simple_ack_grammar() : simple_ack_grammar::base_type(simple_ack_rule){

    simple_ack_rule  = pdu_header_rule
                     << original_invoke_id_rule
                     << service_ack_choice_rule;


    pdu_header_rule           = (pdu_type_and_control_information_grammar[ref(pdu_header_) = _val])[_1 = _val]  << pdu_type_check_rule;

    original_invoke_id_rule   = byte_;

    service_ack_choice_rule   = byte_;


    pdu_type_check_rule       = ( eps(boost::phoenix::bind(&pdu_type_and_control_information_t::pdu_type, ref(pdu_header_)) == pdu_type::simple_ack)
                              <<  eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_segmented, ref(pdu_header_))                   == false)
                              <<  eps(boost::phoenix::bind(&pdu_type_and_control_information_t::has_more_segments_following, ref(pdu_header_))     == false)
                              <<  eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_segmented_response_accepted, ref(pdu_header_))  == false)
                              <<  eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_send_by_server, ref(pdu_header_))               == false)
                              );


    simple_ack_rule.name("service_ack_choice_rule");
    pdu_header_rule.name("pdu_header_rule");
    original_invoke_id_rule.name("original_invoke_id_rule");
    service_ack_choice_rule.name("service_ack_choice_rule");
    pdu_type_check_rule.name("pdu_type_check_rule");

    /*
       debug(simple_ack_rule);
       debug(pdu_header_rule);
       debug(original_invoke_id_rule);
       debug(service_ack_choice_rule);
       debug(pdu_type_check_rule);
     */
  }


  pdu_type_and_control_information_t pdu_header_;
};



}}}}}


#endif /* SRC_BACNET_APDU_FRAME_DETAIL_SIMPLE_ACK_GRAMMAR_HPP_ */
