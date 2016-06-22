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


#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_bit_string_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_bit_string_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/apdu/type/detail/util/tag_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive_type.hpp>
#include <bacnet/type/bit_string.hpp>
#include <bacnet/detail/common/types.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using bacnet::apdu::type::tag;
using bacnet::type::bit_string;

template<typename Iterator>
struct bit_string_grammar : grammar<Iterator, bit_string()> , primitive_type{

  rule<Iterator, bit_string()>   start_rule;
  rule<Iterator>                 tag_rule;
  rule<Iterator>                 tag_validation_rule;
  rule<Iterator>                 unused_bits_rule;
  rule<Iterator, bit_string()>   value_rule;
  rule<Iterator>                 extract_bit_string_rule;
  tag_grammar<Iterator>          tag_grammar_;


  bit_string_grammar()            : bit_string_grammar::base_type(start_rule),
                                    primitive_type(application_tag::bit_string) {
    setup();
  }

  bit_string_grammar(uint8_t tag) : bit_string_grammar::base_type(start_rule),
                                    primitive_type(tag) {
    setup();
  }

private:

  void setup() {
    start_rule              = tag_validation_rule
                            >> unused_bits_rule
                            >> value_rule ;

    tag_validation_rule     =  omit[tag_grammar_[ boost::phoenix::bind(&bit_string_grammar::extract_size_and_check_tag,   this, _1, _pass) ] ];

    unused_bits_rule        =  byte_[             boost::phoenix::bind(&bit_string_grammar::extract_num_of_expected_bits, this, _1) ];

    value_rule              =  repeat(ref(length_value_type_))[extract_bit_string_rule]
                            >> attr(ref(bit_string_));

    extract_bit_string_rule =  byte_[             boost::phoenix::bind(&bit_string_grammar::extract_bit_string,           this, _1)];
    //
    /*
    start_rule.             name("start_rule");
    tag_validation_rule.    name("tag_validation_rule");
    unused_bits_rule.       name("unused_bits_rule");
    value_rule.             name("value_rule");
    extract_bit_string_rule.name("first_bytes_rule");
    debug(start_rule);
    debug(tag_validation_rule);
    debug(tag_rule);
    debug(value_rule);
    debug(unused_bits_rule);
    debug(first_bytes_rule);
    // */
  }

  bool extract_bit_string(uint8_t bits) {
    for(int idx = 7; idx >= 0; --idx) {
      bool value = bits & (1 << idx);
      bit_string_.push_back(std::move(value));
      expected_bits_--;
      if(expected_bits_ == 0) {
        break;
      }
    }
    return true;
  }

  void extract_num_of_expected_bits(const uint8_t &num_of_unused_bits) {
    bit_string_.clear();
    --length_value_type_;
    expected_bits_ = ((length_value_type_) * 8) - num_of_unused_bits;
  }

  bit_string bit_string_;
  uint32_t   expected_bits_{0};
};

}}}}}


namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;
using bacnet::apdu::type::tag;
using bacnet::type::bit_string;

template<typename Iterator>
struct bit_string_grammar : grammar<Iterator, bit_string()> {

  rule<Iterator, bit_string()>          start_rule;
  rule<Iterator, bit_string()>          tag_rule;
  rule<Iterator>                        unused_bits_rule;
  rule<Iterator>                        value_rule;
  rule<Iterator>                        pack_bit_rule;
  rule<Iterator>                        packed_bits_rule;
  tag_grammar<Iterator> tag_grammar_;

  bit_string_grammar()              : bit_string_grammar::base_type(start_rule),
                                      tag_(application_tag::bit_string) {
    setup();
  }

  bit_string_grammar(uint8_t tag)   : bit_string_grammar::base_type(start_rule),
                                      tag_(tag) {
    setup();
  }

private:

  void setup() {
    start_rule    =  tag_rule         [_1 = _val]
                  << unused_bits_rule
                  << value_rule;

    tag_rule          =  tag_grammar_ [ _1 = boost::phoenix::bind(&bit_string_grammar::get_tag, this, _val)];
    unused_bits_rule  =  byte_[_1 = ref(unused_bits_)];
    value_rule        =  repeat(ref(num_of_bytes_))[pack_bit_rule];
    pack_bit_rule     =  byte_[_1 = boost::phoenix::bind(&bit_string_grammar::get_packed_bits, this)];

    start_rule. name("start_rule");
    tag_rule.   name("tag_rule");
    value_rule. name("value_rule");
  }

  uint8_t get_packed_bits() {
    uint8_t  packed_bits_{0};
    for(int idx = 7; idx >= 0; --idx ) {
      uint8_t value = bit_string_[bit_index_] ? 1 : 0;
      packed_bits_ |= value << idx;
      bit_index_++;
      if(bit_index_ >= bit_string_.size()) {
        break;
      }
    }
    return packed_bits_;
  }

  tag get_tag(const bit_string &value) {
    bit_string_    = value;
    uint32_t size  = value.size();
    bit_index_     = 0;
    if(size == 0) {
      unused_bits_   = 0;
      num_of_bytes_  = 0;
      tag_.length_value_type(1);
    }
    else {
      unused_bits_   = 8 - (size  % 8);
      num_of_bytes_  = (uint32_t) (size  / 8);
      num_of_bytes_ += (unused_bits_ > 0) ? 1 : 0;
      tag_.length_value_type(num_of_bytes_ + 1);
    }
    return tag_;
  }

  uint32_t   num_of_bytes_{0};
  uint32_t   bit_index_{0};
  uint8_t    unused_bits_{0};
  tag        tag_;
  bit_string bit_string_;
};

}}}}}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_bit_string_grammar_HPP
