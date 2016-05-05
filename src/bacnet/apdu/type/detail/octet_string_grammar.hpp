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


#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_octet_string_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_octet_string_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/apdu/type/detail/tag_grammar.hpp>
#include <bacnet/detail/common/types.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using bacnet::apdu::type::tag;

template<typename Iterator>
struct octet_string_grammar : grammar<Iterator, bacnet::binary_data()> {


  rule<Iterator, bacnet::binary_data()>   start_rule;
  rule<Iterator >                         tag_validation_rule;
  rule<Iterator, tag()>                   tag_rule;
  rule<Iterator, bacnet::binary_data()>   value_rule;

  tag_grammar<Iterator>     tag_grammar_;



  octet_string_grammar()            : octet_string_grammar::base_type(start_rule),
                                      tag_(application_tag::octet_string),
                                      tag_number_expected_(tag_.number()),
                                      is_expecting_context_tag_(tag_.is_context_tag_)  {
    setup();
  }

  octet_string_grammar(uint8_t tag) : octet_string_grammar::base_type(start_rule),
                                      tag_(tag, true),
                                      tag_number_expected_(tag_.number()),
                                      is_expecting_context_tag_(tag_.is_context_tag_) {
    setup();
  }


private:

  void setup() {
    start_rule          =  tag_validation_rule
                        >> value_rule ;

    value_rule          =  repeat(ref(size_))[byte_];
    tag_validation_rule =  omit[tag_rule]
                        >> eps( boost::phoenix::bind(&octet_string_grammar::is_as_expected, this) == true );
    tag_rule            = tag_grammar_[_val = boost::phoenix::bind(&octet_string_grammar::extract_tag, this, _1)] ;

    start_rule.           name("start_rule");
    tag_validation_rule.  name("tag_validation_rule");
    tag_rule.             name("tag_rule");
    value_rule.           name("value_rule");


    //
    /*
    debug(start_rule);
    debug(tag_validation_rule);
    debug(tag_rule);
    debug(value_rule);
    // */
  }


  tag& extract_tag(tag& t) {
   tag_  = t;
   size_ = t.length_value_type();
   return t;
  }

  bool is_as_expected() {
    if(   tag_.is_context_tag_     == is_expecting_context_tag_
       && tag_.number()            == tag_number_expected_ ) {
     return true;
    }
    else {
      return false;
    }
  }
  uint32_t size_{0};
  tag tag_;
  uint8_t tag_number_expected_{0};
  bool is_expecting_context_tag_{false};

};

}}}}}

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;
using bacnet::apdu::type::tag;

template<typename Iterator>
struct octet_string_grammar : grammar<Iterator, bacnet::binary_data()> {

  rule<Iterator, bacnet::binary_data()>       start_rule;
  rule<Iterator, bacnet::binary_data()>       tag_rule;
  rule<Iterator, bacnet::binary_data()>       value_rule;
  tag_grammar<Iterator> tag_grammar_;

  octet_string_grammar()              : octet_string_grammar::base_type(start_rule),
                                        size_(0),
                                        tag_(application_tag::octet_string) {
    setup();
  }

  octet_string_grammar(uint8_t tag)   : octet_string_grammar::base_type(start_rule),
                                        size_(0),
                                        tag_(tag, true) {
    setup();
  }

private:

  void setup() {
    start_rule    =  tag_rule   [_1 = _val]
                  << value_rule [_1 = _val];

    tag_rule      =  tag_grammar_[ _1 = boost::phoenix::bind(&octet_string_grammar::get_tag, this, _val)];
    value_rule    =  repeat(ref(size_))[byte_];

    start_rule.name("start_rule");
    tag_rule.name("tag_rule");
    value_rule.name("value_rule");
    //
    /*
    debug(start_rule);
    debug(tag_rule);
    debug(value_rule);
    // */
  }

  tag get_tag(const bacnet::binary_data &value) {
    size_ = value.size();
    tag_.length_value_type(size_);
    return tag_;
  }

  uint32_t size_;
  tag tag_;
};

}}}}}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_octet_string_grammar_HPP
