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
  rule<Iterator >                                       tag_validation_rule;
  rule<Iterator, tag()>                                 tag_rule;
  rule<Iterator, character_string()>                    value_rule;
  rule<Iterator, string_encoding_type()>                encoding_rule;
  rule<Iterator, std::string()>                         string_rule;

  tag_grammar<Iterator> tag_grammar_;

  character_string_grammar() : character_string_grammar::base_type(start_rule),
                              tag_(application_tag::character_string),
                              size_(0),
                              tag_number_expected_(tag_.number()),
                              is_expecting_context_tag_(tag_.is_context_tag_)  {
    setup();
  }

  character_string_grammar(uint8_t tag) : character_string_grammar::base_type(start_rule),
                                          tag_(tag, true),
                                          size_(0),
                                          tag_number_expected_(tag_.number()),
                                          is_expecting_context_tag_(tag_.is_context_tag_) {
    setup();
  }


private:

  void setup() {
    start_rule  =  tag_validation_rule
                >> value_rule ;


    value_rule  =  encoding_rule
                >> string_rule ;



    tag_validation_rule = omit[tag_rule] >> eps( boost::phoenix::bind(&character_string_grammar::is_as_expected, this) == true );

    tag_rule = tag_grammar_[_val = boost::phoenix::bind(&character_string_grammar::set_size, this, _1)] ;


    encoding_rule =  byte_[ _val = boost::phoenix::bind(&character_string_grammar::to_encoding_type, this, _1)];

    string_rule  = repeat(ref(size_))[byte_];


    start_rule.           name("start_rule");
    tag_validation_rule.  name("tag_validation_rule");
    tag_rule.             name("tag_rule");
    value_rule.           name("value_rule");
    encoding_rule.        name("encoding_rule");
    string_rule.          name("string_rule");


    //
    /*
    debug(start_rule);
    debug(tag_validation_rule);
    debug(tag_rule);
    debug(value_rule);
    debug(encoding_rule);
    debug(string_rule);
    // */
  }

  string_encoding_type to_encoding_type(const uint8_t& underlying_value) {
    string_encoding_type enum_value = static_cast<string_encoding_type>(underlying_value);
    return enum_value;
  }


  /**
   * using separate size value, as  accessing complex type
   * does somehow not work here with spirit
   */
  tag& set_size(tag& t) {
   tag_ = t;
   size_ = t.length_value_type() -1;
   return t;
  }

  bool is_as_expected() {
    if(   tag_.is_context_tag_ == is_expecting_context_tag_
       && tag_.number()  == tag_number_expected_ ) {
     return true;
    }
    else {
      return false;
    }
  }

  tag tag_;
  uint32_t size_{0};
  uint8_t tag_number_expected_{0};
  bool is_expecting_context_tag_{false};

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
