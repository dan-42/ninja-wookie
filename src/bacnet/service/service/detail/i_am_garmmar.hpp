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


#include <bacnet/apdu/type/detail/enumeration_grammar.hpp>
#include <bacnet/apdu/type/detail/object_identifier_grammar.hpp>
#include <bacnet/apdu/type/detail/unsigned_integer_grammar.hpp>

namespace bacnet { namespace service { namespace service { namespace detail {


namespace service = bacnet::service::service;
namespace apdu    = bacnet::apdu::type;

namespace parser {


using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::rule;
using boost::phoenix::bind;

using namespace bacnet::apdu::type::detail::parser;
using namespace bacnet::apdu::type;
using namespace bacnet::common;

template<typename Iterator>
struct i_am_grammar : grammar<Iterator, service::i_am()> {


  rule<Iterator, service::i_am()>       start_rule;

  rule<Iterator, object_identifier()>   object_identifier_rule;
  rule<Iterator, uint32_t()>            max_apdu_length_accepted_rule;
  rule<Iterator, segmentation()>        segmentation_supported_rule;
  rule<Iterator, uint16_t()>            vendor_id_rule;

  object_identifier_grammar<Iterator>  object_identifier_grammar_;
  unsigned_integer_grammar<Iterator>   unsigned_integer_grammar_;
  enumeration_grammar<Iterator>        enumeration_grammar_;


  i_am_grammar() : i_am_grammar::base_type(start_rule) {

    start_rule                    =
                                    byte_(service::detail::service_choice<service::i_am>::value)
                                  >> object_identifier_rule
                                  >> max_apdu_length_accepted_rule
                                  >> segmentation_supported_rule
                                  >> vendor_id_rule;


    object_identifier_rule        = object_identifier_grammar_;
    max_apdu_length_accepted_rule = unsigned_integer_grammar_;
    segmentation_supported_rule   = enumeration_grammar_[_val = boost::phoenix::bind(segmentation::from_enumerated, _1)];
    vendor_id_rule                = unsigned_integer_grammar_;

    start_rule.name("start_rule");
    object_identifier_rule.name("object_identifier_rule");
    max_apdu_length_accepted_rule.name("max_apdu_length_accepted_rule");
    segmentation_supported_rule.name("segmentation_supported_rule");
    vendor_id_rule.name("vendor_id_rule");
   /* debug(start_rule);
    debug(object_identifier_rule);
    debug(max_apdu_length_accepted_rule);
    debug(segmentation_supported_rule);
    debug(vendor_id_rule);*/
  }
};


}

namespace generator {


using namespace boost::spirit;
using namespace boost::spirit::karma;

using boost::spirit::karma::rule;
using boost::spirit::karma::_1;


using namespace bacnet::apdu::type::detail::generator;
using namespace bacnet::apdu::type;
using namespace bacnet::common;

template<typename Iterator>
struct i_am_grammar : grammar<Iterator, service::i_am()> {


  rule<Iterator, service::i_am()>       start_rule;

  rule<Iterator, object_identifier()>   object_identifier_rule;
  rule<Iterator, uint32_t()>            max_apdu_length_accepted_rule;
  rule<Iterator, segmentation()>        segmentation_supported_rule;
  rule<Iterator, uint16_t()>            vendor_id_rule;

  object_identifier_grammar<Iterator>  object_identifier_grammar_;
  unsigned_integer_grammar<Iterator>   unsigned_integer_grammar_;
  enumeration_grammar<Iterator>        enumeration_grammar_;


  i_am_grammar() : i_am_grammar::base_type(start_rule) {

    start_rule                    =
                                     byte_(service::detail::service_choice<service::i_am>::value)
                                  << object_identifier_rule
                                  << max_apdu_length_accepted_rule
                                  << segmentation_supported_rule
                                  << vendor_id_rule;


    object_identifier_rule        = object_identifier_grammar_;
    max_apdu_length_accepted_rule = unsigned_integer_grammar_;
    segmentation_supported_rule   = enumeration_grammar_[_1 = boost::phoenix::bind(segmentation::to_native, _val)];
    vendor_id_rule                = unsigned_integer_grammar_;
  }
};


}


}}}}



#endif //NINJA_WOOKIE_BACNET_SERVICE_DETAIL_I_AM_GRAMMAR_HPP
