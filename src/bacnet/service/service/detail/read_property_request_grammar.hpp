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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_READ_PROPERTY_REQUEST_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_READ_PROPERTY_REQUEST_GRAMMAR_HPP


#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/apdu/type/detail/object_identifier_grammar.hpp>
#include <bacnet/apdu/type/detail/unsigned_integer_grammar.hpp>
#include <bacnet/service/service/read_property_request.hpp>



namespace bacnet { namespace service { namespace service { namespace detail { namespace parser {


using namespace boost::spirit;
using namespace boost::spirit::qi;

using namespace bacnet::apdu::type;
using namespace bacnet::apdu::type::detail::parser;

template<typename Iterator>
struct read_property_request_grammar : grammar<Iterator, service::read_property_request()> {
  rule<Iterator, service::read_property_request()>      start_rule;
  rule<Iterator, object_identifier()>           object_identifier_rule;
  rule<Iterator, uint32_t()>                    property_identifier_rule;
  rule<Iterator, boost::optional<uint32_t>()>   property_array_index_rule;

  object_identifier_grammar<Iterator>      tag_0_rule_{0};
  unsigned_integer_grammar<Iterator>       tag_1_rule_{1};
  unsigned_integer_grammar<Iterator>       tag_2_rule_{2};

  read_property_request_grammar() : read_property_request_grammar::base_type(start_rule) {

    start_rule                          =  byte_(service_choice<service::read_property_request>::value)
                                        >> object_identifier_rule
                                        >> property_identifier_rule
                                        >> property_array_index_rule;
    object_identifier_rule              =  tag_0_rule_;
    property_identifier_rule            =  tag_1_rule_;
    property_array_index_rule           = -tag_2_rule_;
  }
};


}}}}}

namespace bacnet { namespace service { namespace service { namespace detail {  namespace generator {


using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::apdu::type;
using namespace bacnet::apdu::type::detail::generator;

template<typename Iterator>
struct read_property_request_grammar : grammar<Iterator, service::read_property_request()> {
  rule<Iterator, service::read_property_request()>      start_rule;
  rule<Iterator, object_identifier()>           object_identifier_rule;
  rule<Iterator, uint32_t()>                    property_identifier_rule;
  rule<Iterator, boost::optional<uint32_t>()>   property_array_index_rule;

  object_identifier_grammar<Iterator>      tag_0_rule_{0};
  unsigned_integer_grammar<Iterator>       tag_1_rule_{1};
  unsigned_integer_grammar<Iterator>       tag_2_rule_{2};

  read_property_request_grammar() : read_property_request_grammar::base_type(start_rule) {

    start_rule                          =  byte_(service_choice<service::read_property_request>::value)
                                        << object_identifier_rule
                                        << property_identifier_rule
                                        << property_array_index_rule;
    object_identifier_rule              =  tag_0_rule_;
    property_identifier_rule            =  tag_1_rule_;
    property_array_index_rule           = -tag_2_rule_;
  }
};


}}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_READ_PROPERTY_REQUEST_GRAMMAR_HPP
