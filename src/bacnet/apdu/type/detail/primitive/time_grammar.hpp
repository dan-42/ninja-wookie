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


#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_time_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_time_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/apdu/type/detail/util/tag_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive_type.hpp>
#include <bacnet/type/time.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;
using boost::spirit::qi::_1;
using bacnet::apdu::type::tag;
using bacnet::type::time;

template<typename Iterator>
struct time_grammar : grammar<Iterator, time()>, primitive_type {


  rule<Iterator, time()>      start_rule;
  rule<Iterator>              tag_validation_rule;
  rule<Iterator>              tag_rule;
  rule<Iterator, time()>      value_rule;
  tag_grammar<Iterator>       tag_grammar_;


  time_grammar()            : time_grammar::base_type(start_rule),
                              primitive_type(application_tag::time) {
    setup();
  }
  time_grammar(uint8_t tag) : time_grammar::base_type(start_rule),
                              primitive_type(tag) {
    setup();
  }

private:

  void setup() {
    length_value_type_  =  4;
    start_rule          =  tag_validation_rule
                        >> value_rule ;
    value_rule          =  byte_
                        >> byte_
                        >> byte_
                        >> byte_;

    tag_validation_rule = tag_grammar_[ boost::phoenix::bind(&time_grammar::check_tag, this, _1, _pass) ];
    /*
    start_rule.           name("start_rule");
    tag_validation_rule.  name("tag_validation_rule");
    value_rule.           name("value_rule");
    debug(start_rule);
    debug(tag_validation_rule);
    debug(value_rule);
    // */
  }
};

}}}}}

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;
using boost::spirit::karma::_1;
using bacnet::apdu::type::tag;
using bacnet::type::time;

template<typename Iterator>
struct time_grammar : grammar<Iterator, time()> {

  rule<Iterator, time()>      start_rule;
  rule<Iterator>              tag_rule;
  rule<Iterator, time()>      value_rule;
  tag_grammar<Iterator>       tag_grammar_;

  time_grammar()             : time_grammar::base_type(start_rule),
                               tag_(application_tag::time, 4) {
    setup();
  }

  time_grammar(uint8_t tag)  : time_grammar::base_type(start_rule),
                               tag_(tag, 4) {
    setup();
  }

private:

  void setup() {
    start_rule    =  tag_rule
                  << value_rule;
    tag_rule      =  tag_grammar_[ _1 = boost::phoenix::bind(&time_grammar::get_tag, this)];
    value_rule    =  byte_
                  << byte_
                  << byte_
                  << byte_;


    start_rule.   name("start_rule");
    tag_rule.     name("tag_rule");
    value_rule.   name("value_rule");
  }

  tag get_tag() {
     return tag_;
  }
  tag tag_;
};

}}}}}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_time_grammar_HPP
