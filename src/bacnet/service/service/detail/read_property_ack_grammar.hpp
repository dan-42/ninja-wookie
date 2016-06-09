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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_read_property_ack_grammar_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_read_property_ack_grammar_HPP


#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/apdu/type/detail/object_identifier_grammar.hpp>
#include <bacnet/apdu/type/detail/unsigned_integer_grammar.hpp>
#include <bacnet/apdu/type/detail/possible_type_grammar.hpp>
#include <bacnet/service/service/read_property_ack.hpp>

/*
 * notes
 * http://stackoverflow.com/questions/23763233/boost-spirit-using-local-variables
 * http://stackoverflow.com/questions/12653407/runtime-value-to-type-mapping
 * http://gpfault.net/posts/mapping-types-to-values.txt.html
 */

namespace bacnet { namespace service { namespace service { namespace detail { namespace parser {


using namespace boost::spirit;
using namespace boost::spirit::qi;

using namespace bacnet::apdu::type;
using namespace bacnet::apdu::type::detail::parser;

template<typename Iterator>
struct read_property_ack_grammar : grammar<Iterator, service::read_property_ack()> {
  rule<Iterator, service::read_property_ack()>      start_rule;
  rule<Iterator, object_identifier()>               object_identifier_rule;
  rule<Iterator, uint32_t()>                        property_identifier_rule;
  rule<Iterator, boost::optional<uint32_t>()>       property_array_index_rule;
  rule<Iterator, bacnet::type::possible_type(object_identifier, uint32_t, boost::optional<uint32_t>)>     possible_type_grammar_rule;

  object_identifier_grammar<Iterator>      tag_0_rule_{0};
  unsigned_integer_grammar<Iterator>       tag_1_rule_{1};
  unsigned_integer_grammar<Iterator>       tag_2_rule_{2};
  possible_type_grammar<Iterator>          tag_3_rule_{3};

  read_property_ack_grammar() : read_property_ack_grammar::base_type(start_rule) {

    start_rule                          %=  byte_(service_choice<service::read_property_ack>::value)
                                        >> object_identifier_rule[ _a = _val]
                                        >> property_identifier_rule[ _b = _val]
                                        >> property_array_index_rule[ _c = _val]
                                        >> possible_type_grammar_rule(_a, _b, _c)
                                        ;

    object_identifier_rule              =  tag_0_rule_;
    property_identifier_rule            =  tag_1_rule_;
    property_array_index_rule           = -tag_2_rule_;
    //possible_type_grammar_rule          =  tag_3_rule_;

    possible_type_grammar_rule          =  tag_3_rule_(_r1, _r2, _r3);

    //
    /*
    start_rule.name("read_property_ack_grammar_start_rule");
    object_identifier_rule.name("object_identifier_rule");
    property_identifier_rule.name("property_identifier_rule");
    property_array_index_rule.name("property_array_index_rule");
    possible_type_grammar_rule.name("possible_type_grammar_rule");

    debug(start_rule);
    debug(object_identifier_rule);
    debug(property_identifier_rule);
    debug(property_array_index_rule);
    debug(possible_type_grammar_rule);
    // */
  }
};


}}}}}

namespace bacnet { namespace service { namespace service { namespace detail {  namespace generator {


using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::apdu::type;
using namespace bacnet::apdu::type::detail::generator;

template<typename Iterator>
struct read_property_ack_grammar : grammar<Iterator, service::read_property_ack()> {
  rule<Iterator, service::read_property_ack()>      start_rule;
  rule<Iterator, object_identifier()>           object_identifier_rule;
  rule<Iterator, uint32_t()>                    property_identifier_rule;
  rule<Iterator, boost::optional<uint32_t>()>   property_array_index_rule;
  rule<Iterator, bacnet::binary_data()>         binary_data_rule;

  object_identifier_grammar<Iterator>      tag_0_rule_{0};
  unsigned_integer_grammar<Iterator>       tag_1_rule_{1};
  unsigned_integer_grammar<Iterator>       tag_2_rule_{2};

  read_property_ack_grammar() : read_property_ack_grammar::base_type(start_rule) {

    start_rule                          =  byte_(service_choice<service::read_property_ack>::value)
                                        << object_identifier_rule
                                        << property_identifier_rule
                                        << property_array_index_rule
                                        ;

    object_identifier_rule              =  tag_0_rule_;
    property_identifier_rule            =  tag_1_rule_;
    property_array_index_rule           = -tag_2_rule_;

  }
};


}}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_read_property_ack_grammar_HPP
