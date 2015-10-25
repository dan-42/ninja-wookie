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


#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_CHARACTER_STRING_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_CHARACTER_STRING_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <util/boost/spirit/detail/bit_field_grammar.hpp>
#include <bacnet/apdu/detail/boost/uint24_parser.hpp>
#include <bacnet/apdu/detail/boost/uint24_generator.hpp>

#include <bacnet/apdu/type/character_string.hpp>
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
using bacnet::apdu::type::character_string;
using bacnet::apdu::type::string_encoding_type;

template<typename Iterator>
struct character_string_grammar : grammar<Iterator, character_string()> {


  rule<Iterator, character_string()>                    start_rule;
  rule<Iterator, tag()>                                 tag_rule;
  rule<Iterator, string_encoding_type()>                encoding_rule;
  rule<Iterator, std::string()>                         string_rule;

  tag_grammar<Iterator> tag_grammar_;

  character_string_grammar() : character_string_grammar::base_type(start_rule), size_(0) {

    start_rule  = tag_rule >> encoding_rule >> string_rule ;

    tag_rule = tag_grammar_[_val = boost::phoenix::bind(&character_string_grammar::set_size, this, _1)];

    encoding_rule = byte_;

    string_rule  =  repeate[ref(size_](byte_);

    start_rule.name("start_rule");
    tag_rule.name("tag_rule");
    string_encoding_type.name("string_encoding_type");
    string_rule.name("string_rule");
/*
debug(start_rule);
debug(tag_rule);
debug(tag_lower_rule);
debug(string_rule);
*/
  }
private:

  tag& set_size(tag& t) {
    size_ = t.length_value_type();
    return t;
  }

  uint32_t size_;

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
using bacnet::apdu::type::character_string;

template<typename Iterator>
struct character_string_grammar : grammar<Iterator, character_string()> {

  rule<Iterator, character_string()>                    start_rule;
  rule<Iterator, tag()>                                 tag_rule;
  rule<Iterator, string_encoding_type()>                encoding_rule;
  rule<Iterator, std::string()>                         string_rule;

  tag_grammar<Iterator> tag_grammar_;

  character_string_grammar() : character_string_grammar::base_type(start_rule) {

    start_rule  = tag_rule << encoding_rule << value_rule ;

    tag_rule = eps[boost::phoenix::bind(&character_string_grammar::extract_size, this, _val)] << tag_grammar_[_1 = _val];

    string_rule  = repeate[ref(size_)](byte_);

    start_rule.name("start_rule");
    tag_rule.name("tag_rule");
    string_rule.name("string_rule");

    /*
    debug(start_rule);
    debug(value_rule);
    debug(tag_rule);
    */

  }
private:

  void extract_size(const tag &tag_) {
    size_ = tag_.length_value_type();
  }

  uint8_t size_;
};

}}}}}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_CHARACTER_STRING_GRAMMAR_HPP
