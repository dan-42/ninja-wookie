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


#ifndef NINJA_WOOKIE_OBJECT_IDENTIFIER_GRAMMAR_HPP_HPP
#define NINJA_WOOKIE_OBJECT_IDENTIFIER_GRAMMAR_HPP_HPP




#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <util/boost/spirit/detail/bit_field_grammar.hpp>
#include <bacnet/apdu/detail/boost/uint24_parser.hpp>
#include <bacnet/apdu/detail/boost/uint24_generator.hpp>

#include <bacnet/apdu/type/object_identifier.hpp>
#include <bacnet/apdu/type/detail/tag_grammar.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::bit_field;
using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::phoenix::bind;

using bacnet::apdu::type::tag;
using bacnet::apdu::type::object_identifier;


template<typename Iterator>
struct object_identifier_grammar : grammar<Iterator, object_identifier()> {


  rule<Iterator, object_identifier()>                   start_rule;
  rule<Iterator, tag()>                                 tag_rule;
  rule<Iterator, bacnet::common::object_identifier()>   value_rule;

    tag_grammar<Iterator> tag_grammar_;

  object_identifier_grammar() : object_identifier_grammar::base_type(start_rule), size_(0) {

    start_rule  = tag_rule >> value_rule ;

    tag_rule = tag_grammar_;

    value_rule  =  big_dword[_val = boost::phoenix::bind(&object_identifier_grammar::create_object_identifier, this, _1)] ;

    start_rule.name("start_rule");
    tag_rule.name("tag_rule");
    value_rule.name("value_rule");
/*
debug(start_rule);
debug(tag_rule);
debug(tag_lower_rule);
debug(value_rule);
*/
  }
private:

  bacnet::common::object_identifier create_object_identifier(const uint32_t & native_value) {
    bacnet::common::object_identifier oi;
    oi.from_native(native_value);
    return oi;
  }

  uint8_t size_;
};

}}}}}

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;

using boost::spirit::karma::bit_field;
using boost::spirit::karma::rule;
using boost::spirit::karma::_1;
using boost::phoenix::bind;

using bacnet::apdu::type::tag;
using bacnet::apdu::type::object_identifier;

template<typename Iterator>
struct object_identifier_grammar : grammar<Iterator, object_identifier()> {

  rule<Iterator, object_identifier()>                   start_rule;
  rule<Iterator, tag()>                                 tag_rule;
  rule<Iterator, bacnet::common::object_identifier()>   value_rule;

    tag_grammar<Iterator> tag_grammar_;

  object_identifier_grammar() : object_identifier_grammar::base_type(start_rule) {

    start_rule  = tag_rule << value_rule ;

    tag_rule = tag_grammar_;

    value_rule  = big_dword[_1 = boost::phoenix::bind(&object_identifier_grammar::get_native_value, this, _val)];

    start_rule.name("start_rule");
    tag_rule.name("tag_rule");
    value_rule.name("value_rule");

    /*
    debug(start_rule);
    debug(value_rule);
    debug(tag_rule);
    */

  }
private:

  uint32_t get_native_value(const bacnet::common::object_identifier &oi) {
    return oi.to_native();
  }

};



}}}}}



#endif //NINJA_WOOKIE_OBJECT_IDENTIFIER_GRAMMAR_HPP_HPP
