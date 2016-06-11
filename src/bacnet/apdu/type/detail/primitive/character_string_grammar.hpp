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


#include <bacnet/type/character_string.hpp>
#include <bacnet/apdu/type/detail/util/tag_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive_type.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::bit_field;
using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::phoenix::bind;

using bacnet::apdu::type::tag;
using bacnet::type::character_string;
using bacnet::type::string_encoding_type;

template<typename Iterator>
struct character_string_grammar : grammar<Iterator, character_string()>, primitive_type {


  rule<Iterator, character_string()>                    start_rule;
  rule<Iterator >                                       tag_validation_rule;
  rule<Iterator, character_string()>                    value_rule;
  rule<Iterator, string_encoding_type()>                encoding_rule;
  rule<Iterator, std::string()>                         string_rule;

  tag_grammar<Iterator> tag_grammar_;

  character_string_grammar() : character_string_grammar::base_type(start_rule),
                                primitive_type(application_tag::character_string) {
    setup();
  }

  character_string_grammar(uint8_t tag) : character_string_grammar::base_type(start_rule),
                                          primitive_type(tag) {
    setup();
  }


private:

  void setup() {
    start_rule  =  tag_validation_rule
                >> value_rule ;

    value_rule  =  encoding_rule
                >> string_rule ;

    tag_validation_rule  = omit[tag_grammar_[ boost::phoenix::bind(&character_string_grammar::extract_size_and_check_tag, this, _1, _pass, -1) ] ];

    encoding_rule =  byte_[ _val = boost::phoenix::bind(&character_string_grammar::to_encoding_type, this, _1)];

    string_rule  = repeat(ref(length_value_type_ ))[byte_];

    //
    /*
    start_rule.           name("start_rule");
    tag_validation_rule.  name("tag_validation_rule");
    value_rule.           name("value_rule");
    encoding_rule.        name("encoding_rule");
    string_rule.          name("string_rule");
    debug(start_rule);
    debug(tag_validation_rule);
    debug(value_rule);
    debug(encoding_rule);
    debug(string_rule);
    // */
  }
  string_encoding_type to_encoding_type(const uint8_t& underlying_value) {
    string_encoding_type enum_value = static_cast<string_encoding_type>(underlying_value);
    return enum_value;
  }
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
using bacnet::type::character_string;
using bacnet::type::string_encoding_type;

template<typename Iterator>
struct character_string_grammar : grammar<Iterator, character_string()> {

  rule<Iterator, character_string()>                    start_rule;
  rule<Iterator, character_string()>                    tag_rule;
  rule<Iterator, character_string()>                    value_rule;
  rule<Iterator, string_encoding_type()>                encoding_rule;
  rule<Iterator, std::string()>                         string_rule;

  tag_grammar<Iterator> tag_grammar_;

  character_string_grammar() : character_string_grammar::base_type(start_rule),
                              size_(0),
                              tag_(application_tag::character_string) {
    setup();
  }

  character_string_grammar(uint8_t tag) : character_string_grammar::base_type(start_rule),
                                        size_(0),
                                        tag_(tag, true) {
    setup();
  }
private:

  void setup() {
    start_rule  =  tag_rule[_1 = _val]
                << value_rule[_1 = _val];

    tag_rule = tag_grammar_[ _1 = boost::phoenix::bind(&character_string_grammar::get_tag, this, _val)];


    value_rule =  encoding_rule
               << string_rule;

    encoding_rule = byte_[ _1 = boost::phoenix::bind(&character_string_grammar::from_encoding_type, this, _val)];

    string_rule  = repeat(ref(size_))[byte_];

    start_rule.name("start_rule");
    tag_rule.name("tag_rule");
    encoding_rule.name("encoding_rule");
    string_rule.name("string_rule");
    //
    /*
    debug(start_rule);
    debug(tag_rule);
    debug(encoding_rule);
    debug(string_rule);
    // */
  }

  tag get_tag(const character_string &char_string) {
     size_ = char_string.value.size();
     tag_.length_value_type(size_+1);
     return tag_;
   }

  uint8_t from_encoding_type(const string_encoding_type& enum_value) {
    return static_cast<uint8_t>(enum_value);
  }

  uint8_t size_;
  tag tag_;
};

}}}}}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_CHARACTER_STRING_GRAMMAR_HPP
