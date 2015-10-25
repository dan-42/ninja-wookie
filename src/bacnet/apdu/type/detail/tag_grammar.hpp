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



#ifndef NINJA_WOOKIE_TAG_GRAMMAR_HPP
#define NINJA_WOOKIE_TAG_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/apdu/type/tag.hpp>


/*

 possibilities of tags
  simple 1 byte
    length between 2 and 5 OK
    tag_number 0 to 15.
       7             4    3    2            0
    +----+----+----+----+----+----+----+----+
    | tag number        | C  | length       |
    +----+----+----+----+----+----+----+----+


  extended tag_number
    the 4-bit tag_number in the first byte are all one, and indicating one byte following containing the extendet tag_number
    from 0 to 254 decoded,  value 255 is reserved.

         7             4    3    2          0
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
    | 1    1    1    1  | C  | length       |  |  uint8_t extended_tag_number          |
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+

 extended length value
    for data length bigger then 4 bytes, e.g. double or BACnet-bit-Strings and so on
    the length is encoded as bx101 indicating one following byte
    if the following byte contains 254 then it indicates two following bytes
    if the following byte contains 255 then it indicates four following bytes


    length from 15 to 254

       7             4    3    2           0    7                                    0
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
    |  tag_number       | C  |  1    0    1 |  |  uint8_t extended_length_value        |
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+


    length from 254 to 65535
     7             4    3    2           0      7                                    0      15                                  8   7                                    0
    +----+----+----+----+----+----+----+----+ +----+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
    |  tag_number       | C  |  1    0    1 | |  1    1    1    1   1    1    1    0  |   |    uint16_t extended_length_value                                            |
    +----+----+----+----+----+----+----+----+ +----+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+


    length from 65535 to 2^32-1
      7             4    3    2           0      7                                    0      32                                  [...]                                   0
    +----+----+----+----+----+----+----+----+ +----+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+---[...]+----+----+----+----+----+----+----+
    |  tag_number       | C  |  1    0    1 | |  1    1    1    1   1    1    1    1  |   |    uint32_t extended_length_value    [...]                                   |
    +----+----+----+----+----+----+----+----+ +----+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+---[...]+----+----+----+----+----+----+----+

 combinations

    if the tag_number is extended and the length, then the extended_tag_number comes bevore the extended_length

        7             4    3    2          0     7                                     0    7                                     0
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
    | 1    1    1    1  | C  |  1    0    1 |  |  uint8_t extended_tag_number          |  |   uint8_t extended_length_value       |
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+


 summary, the tag_part can be of size between 1 byte and 7 bytes


 */





namespace bacnet { namespace apdu {  namespace type {

struct simple_tag {

    static constexpr uint8_t extended_tag_number_indication   = 0b1111;
    static constexpr uint8_t extended_length_value_0_byte_min = 0b101; //stored in tag


    uint8_t length_value_type_         : 3;
    uint8_t is_context_tag_            : 1; //also called: class in the standard
    uint8_t number_                    : 4;

    simple_tag() :   length_value_type_(0), is_context_tag_(0), number_(0) {
    }

    simple_tag(const uint8_t &n) : length_value_type_(0), is_context_tag_(0), number_(n) {
    }

    simple_tag(const uint8_t &n, const bool &is_app) : length_value_type_(0), is_context_tag_(is_app), number_(n) {
    }

    simple_tag(const uint8_t &n, const bool &is_app, const uint8_t &v) : length_value_type_(v), is_context_tag_(is_app), number_(n) {
    }

    simple_tag(const tag& t) :   length_value_type_(t.length_value_type()), is_context_tag_(t.is_context_tag()), number_(t.number()) {
      if(t.number() >= extended_tag_number_indication)
        number_ = extended_tag_number_indication;

      if(t.length_value_type() >= extended_length_value_0_byte_min) {
        length_value_type_ = extended_length_value_0_byte_min;
      }
    }

    inline uint8_t number() const { return number_; }

    inline bool is_context_tag() const { return is_context_tag_ == 1; }

    inline uint8_t length_value_type() const { return length_value_type_; }

    inline void number(uint8_t v) { number_ = v; }

    inline void is_context_tag(bool v) { v ? is_context_tag_ = 0 : is_context_tag_ = 1; }

    inline void length_value_type(uint8_t v) { length_value_type_ = v; }



};


}}}

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::bit_field;
using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::phoenix::bind;
using boost::phoenix::ref;

using bacnet::apdu::type::tag;


template<typename Iterator>
struct tag_grammar : grammar<Iterator, tag()> {


    rule<Iterator, tag()>               start_rule;

    rule<Iterator, tag()>               tag_rule;

    rule<Iterator>                      simple_tag_rule;

    rule<Iterator, uint8_t()>           tag_number_rule;
    rule<Iterator, bool()>              is_context_tag_rule;
    rule<Iterator, uint32_t()>          length_value_rule;

    rule<Iterator, uint32_t()>          extendet_length_value_rule;

    bit_field<Iterator, simple_tag> simple_tag_grammar;

    tag_grammar() : tag_grammar::base_type(start_rule) {

      static const constexpr uint8_t extended_2_bytes_length_value_indication = 0b11111110;
      static const constexpr uint8_t extended_4_bytes_length_value_indication = 0b11111111;

      start_rule  = simple_tag_rule  >> tag_number_rule >>  is_context_tag_rule >> length_value_rule;

      simple_tag_rule = simple_tag_grammar[ref(simple_tag_) = _1];

      tag_number_rule = (eps(boost::phoenix::bind(&simple_tag::number, ref(simple_tag_)) == 0b1111) >> byte_ )
                      | attr(boost::phoenix::bind(&simple_tag::number, ref(simple_tag_)));

      is_context_tag_rule = attr(boost::phoenix::bind(&simple_tag::is_context_tag, ref(simple_tag_)));

      length_value_rule = (eps(boost::phoenix::bind(&simple_tag::length_value_type, ref(simple_tag_)) == 0b101) >> extendet_length_value_rule)
                        |  attr(boost::phoenix::bind(&simple_tag::length_value_type, ref(simple_tag_)));


      extendet_length_value_rule = (omit[byte_(254)] >> big_word)
                                 | (omit[byte_(255)] >> big_dword)
                                 | byte_;


      start_rule.name("start_rule");
      simple_tag_rule.name("simple_tag_rule");
      tag_number_rule.name("tag_number_rule");
      is_context_tag_rule.name("is_context_tag_rule");
      length_value_rule.name("length_value_rule");
      extendet_length_value_rule.name("extendet_length_value_rule");

     //
     /*
      debug(start_rule);
      debug(simple_tag_rule);
      debug(tag_number_rule);
      debug(is_context_tag_rule);
      debug(length_value_rule);
      debug(extendet_length_value_rule);
      //*/

    }
private:



    void extract_value(const tag &tag_) {
      simple_tag_ = simple_tag(tag_);
      tag_number_ = tag_.number();
      tag_length_ = tag_.length_value_type();
      is_context_tag_ = tag_.is_context_tag();
    }

    void get_simple_tag(simple_tag& st) {
      st = simple_tag_;
    }

    bool is_extended_tag_number() {
      static constexpr uint8_t extended_tag_number_indication = 0b1111;
      return (tag_number_ >= extended_tag_number_indication);
    }

    bool is_length_extendend_by_1_byte() {
      static constexpr uint32_t min_value = 5;
      static constexpr uint32_t max_value = 253;
      return (tag_length_ >= min_value && tag_length_ <= max_value);
    }

    bool is_length_extendend_by_2_byte() {
      static constexpr uint32_t min_value = 254;
      static constexpr uint32_t max_value = 65535;
      return (tag_length_ >= min_value && tag_length_ <= max_value);
    }

    bool is_length_extendend_by_4_byte() {
      static constexpr uint32_t min_value = 65536;
      return (tag_length_ >= min_value );
    }


    uint8_t tag_number_ = 0;
    uint32_t tag_length_ = 0;
    bool is_context_tag_ = false;
    simple_tag simple_tag_;
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
using boost::phoenix::ref;


using bacnet::apdu::type::tag;
using bacnet::apdu::type::simple_tag;


template<typename Iterator>
struct tag_grammar : grammar<Iterator, tag()> {


    rule<Iterator, tag()>               start_rule;

    rule<Iterator, tag()>               tag_rule;

    rule<Iterator>                      simple_tag_rule;

    rule<Iterator, uint8_t()>           tag_number_rule;
    rule<Iterator, bool()>              is_context_tag_rule;
    rule<Iterator, uint32_t()>          length_value_rule;

    rule<Iterator, uint32_t()>          extendet_length_value_rule;

    bit_field<Iterator, simple_tag> simple_tag_grammar;

    tag_grammar() : tag_grammar::base_type(start_rule) {

      static const constexpr uint8_t extended_2_bytes_length_value_indication = 0b11111110;
      static const constexpr uint8_t extended_4_bytes_length_value_indication = 0b11111111;

      start_rule = eps[boost::phoenix::bind(&tag_grammar::extract_value, this, _val)] << tag_rule[_1 = _val];

      tag_rule  = simple_tag_rule  << tag_number_rule <<  is_context_tag_rule << length_value_rule;

      simple_tag_rule = simple_tag_grammar[ _1 = ref(simple_tag_)];

      is_context_tag_rule = eps;

      tag_number_rule = eps( boost::phoenix::bind(&tag_grammar::is_extended_tag_number, this) == true) << byte_
                      | eps;


      length_value_rule = ( eps( boost::phoenix::bind(&tag_grammar::is_length_extendend_by_1_byte, this) == true) << byte_ )
                        | ( eps( boost::phoenix::bind(&tag_grammar::is_length_extendend_by_2_byte, this) == true) << byte_(extended_2_bytes_length_value_indication) << big_word )
                        | ( eps( boost::phoenix::bind(&tag_grammar::is_length_extendend_by_4_byte, this) == true) << byte_(extended_4_bytes_length_value_indication) << big_dword )
                        |  eps;


      /**
       * to do
       * [] tag grammar generator testing
       * [] debug
       * [] parser
       * [] test parser
       * [] replace by old bitfield tag_grammar
       */
      start_rule.name("start_rule");
      simple_tag_rule.name("simple_tag_rule");
      tag_number_rule.name("tag_number_rule");
      is_context_tag_rule.name("is_context_tag_rule");
      length_value_rule.name("length_value_rule");
      extendet_length_value_rule.name("extendet_length_value_rule");

      /*
      debug(start_rule);
      debug(simple_tag_rule);
      debug(tag_number_rule);
      debug(is_context_tag_rule);
      debug(length_value_rule);
      debug(extendet_length_value_rule);
      */

    }
private:



    void extract_value(const tag &tag_) {
      simple_tag_ = simple_tag(tag_);
      tag_number_ = tag_.number();
      tag_length_ = tag_.length_value_type();
      is_context_tag_ = tag_.is_context_tag();
    }

    void get_simple_tag(simple_tag& st) {
     st = simple_tag_;
    }

    bool is_extended_tag_number() {
      static constexpr uint8_t extended_tag_number_indication = 0b1111;
      return (tag_number_ >= extended_tag_number_indication);
    }

    bool is_length_extendend_by_1_byte() {
      static constexpr uint32_t min_value = 5;
      static constexpr uint32_t max_value = 253;
      return (tag_length_ >= min_value && tag_length_ <= max_value);
    }

    bool is_length_extendend_by_2_byte() {
      static constexpr uint32_t min_value = 254;
      static constexpr uint32_t max_value = 65535;
      return (tag_length_ >= min_value && tag_length_ <= max_value);
    }

    bool is_length_extendend_by_4_byte() {
      static constexpr uint32_t min_value = 65536;
      return (tag_length_ >= min_value );
    }


    uint8_t tag_number_ = 0;
    uint32_t tag_length_ = 0;
    bool is_context_tag_ = false;
    simple_tag simple_tag_;
};

}}}}}


#endif //NINJA_WOOKIE_TAG_GRAMMAR_HPP