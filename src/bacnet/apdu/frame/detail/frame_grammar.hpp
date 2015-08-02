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

#ifndef SRC_BACNET_APDU_FRAME_DETAIL_FRAME_GRAMMAR_HPP_
#define SRC_BACNET_APDU_FRAME_DETAIL_FRAME_GRAMMAR_HPP_



#include <bacnet/apdu/frame/frames.hpp>
#include <bacnet/apdu/frame/detail/confirmed_request_grammar.hpp>
#include <bacnet/apdu/frame/detail/unconfirmed_request_grammar.hpp>
#include <bacnet/apdu/frame/detail/simple_ack_grammar.hpp>
#include <bacnet/apdu/frame/detail/complex_ack_grammar.hpp>
#include <bacnet/apdu/frame/detail/segment_ack_grammar.hpp>
#include <bacnet/apdu/frame/detail/error_grammar.hpp>
#include <bacnet/apdu/frame/detail/reject_grammar.hpp>
#include <bacnet/apdu/frame/detail/abort_grammar.hpp>


namespace bacnet { namespace  apdu { namespace frame { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;

using namespace bacnet::apdu;
using namespace bacnet::apdu::frame;


using boost::spirit::qi::rule;




template<typename Iterator>
struct frame_grammar : grammar<Iterator, possible_frame() >{

  rule<Iterator, possible_frame()>        possible_frame_rule;


  confirmed_request_grammar<Iterator>     confirmed_request_grammar_;
  unconfirmed_request_grammar<Iterator>   unconfirmed_request_grammar_;
  simple_ack_grammar<Iterator>            simple_ack_grammar_;
  complex_ack_grammar<Iterator>           complex_ack_grammar_;
  segment_ack_grammar<Iterator>           segment_ack_grammar_;
  error_grammar<Iterator>                 error_grammar_;
  reject_grammar<Iterator>                reject_grammar_;
  abort_grammar<Iterator>                 abort_grammar_;


  frame_grammar() : frame_grammar::base_type(possible_frame_rule){

    possible_frame_rule  = confirmed_request_grammar_
                         | unconfirmed_request_grammar_
                         | simple_ack_grammar_
                         | complex_ack_grammar_
                         | segment_ack_grammar_
                         | error_grammar_
                         | reject_grammar_
                         | abort_grammar_
                         | eps;

    possible_frame_rule.name("possible_frame_rule");

    /*
       debug(possible_frame_rule);
     */
  }

};

}}}}}





namespace bacnet { namespace  apdu { namespace frame {  namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;

using boost::spirit::karma::rule;

using namespace bacnet::apdu;
using namespace bacnet::apdu::frame;

template<typename Iterator>
struct frame_grammar : grammar<Iterator, possible_frame() >{

  rule<Iterator, possible_frame()>                     possible_frame_rule;


  confirmed_request_grammar<Iterator>     confirmed_request_grammar_;
  unconfirmed_request_grammar<Iterator>   unconfirmed_request_grammar_;
  simple_ack_grammar<Iterator>            simple_ack_grammar_;
  complex_ack_grammar<Iterator>           complex_ack_grammar_;
  segment_ack_grammar<Iterator>           segment_ack_grammar_;
  error_grammar<Iterator>                 error_grammar_;
  reject_grammar<Iterator>                reject_grammar_;
  abort_grammar<Iterator>                 abort_grammar_;


  frame_grammar() : frame_grammar::base_type(possible_frame_rule){

    possible_frame_rule  = confirmed_request_grammar_
                             | unconfirmed_request_grammar_
                             | simple_ack_grammar_
                             | complex_ack_grammar_
                             | segment_ack_grammar_
                             | error_grammar_
                             | reject_grammar_
                             | abort_grammar_
                             | eps;

    possible_frame_rule.name("possible_frame_rule");

    /*
       debug(possible_frame_rule);
     */
  }

};


}}}}}




#endif /* SRC_BACNET_APDU_FRAME_DETAIL_FRAME_GRAMMAR_HPP_ */
