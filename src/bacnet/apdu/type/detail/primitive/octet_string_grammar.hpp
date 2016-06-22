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

#include <bacnet/apdu/type/detail/util/tag_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive_type.hpp>
#include <bacnet/type/octet_string.hpp>
#include <bacnet/detail/common/types.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using bacnet::apdu::type::tag;

template<typename Iterator>
struct octet_string_grammar : grammar<Iterator, bacnet::binary_data()>, primitive_type {

  rule<Iterator, bacnet::binary_data()>   start_rule;
  rule<Iterator >                         tag_validation_rule;
  rule<Iterator, bacnet::binary_data()>   value_rule;

  tag_grammar<Iterator>     tag_grammar_;

  octet_string_grammar()            : octet_string_grammar::base_type(start_rule),
                                      primitive_type(application_tag::octet_string) {
    setup();
  }

  octet_string_grammar(uint8_t tag) : octet_string_grammar::base_type(start_rule),
                                      primitive_type(tag) {
    setup();
  }


private:

  void setup() {
    start_rule          =  tag_validation_rule
                        >> value_rule ;

    value_rule          =  repeat(ref(length_value_type_))[byte_];
    tag_validation_rule  = omit[tag_grammar_[ boost::phoenix::bind(&octet_string_grammar::extract_size_and_check_tag, this, _1, _pass) ] ];
    //
    /*
    start_rule.           name("start_rule");
    tag_validation_rule.  name("tag_validation_rule");
    tag_rule.             name("tag_rule");
    value_rule.           name("value_rule");

    debug(start_rule);
    debug(tag_validation_rule);
    debug(tag_rule);
    debug(value_rule);
    // */
  }
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
                                        tag_(tag) {
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
