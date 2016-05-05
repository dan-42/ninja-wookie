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


#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_double_presision_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_double_presision_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/apdu/type/detail/tag_grammar.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using bacnet::apdu::type::tag;

template<typename Iterator>
struct double_presision_grammar : grammar<Iterator, double()> {


  rule<Iterator, double()>   start_rule;
  rule<Iterator >           tag_validation_rule;
  rule<Iterator, tag()>     tag_rule;
  rule<Iterator, double()>   value_rule;

  tag_grammar<Iterator>     tag_grammar_;



  double_presision_grammar() : double_presision_grammar::base_type(start_rule),
                              tag_(application_tag::double_presision),
                              tag_number_expected_(tag_.number()),
                              is_expecting_context_tag_(tag_.is_context_tag_)  {
    setup();
  }

  double_presision_grammar(uint8_t tag) : double_presision_grammar::base_type(start_rule),
                                          tag_(tag, true),
                                          tag_number_expected_(tag_.number()),
                                          is_expecting_context_tag_(tag_.is_context_tag_) {
    setup();
  }


private:

  void setup() {
    start_rule          =  tag_validation_rule
                        >> value_rule ;

    value_rule          =  big_bin_double;
    tag_validation_rule =  omit[tag_rule]
                        >> eps( boost::phoenix::bind(&double_presision_grammar::is_as_expected, this) == true );
    tag_rule            = tag_grammar_[_val = boost::phoenix::bind(&double_presision_grammar::extract_tag, this, _1)] ;

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
   tag_ = t;
   return t;
  }

  bool is_as_expected() {
    if(   tag_.is_context_tag_     == is_expecting_context_tag_
       && tag_.number()            == tag_number_expected_
       && tag_.length_value_type() == size) {
     return true;
    }
    else {
      return false;
    }
  }
  static const constexpr uint32_t size{8};
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
struct double_presision_grammar : grammar<Iterator, double()> {

  rule<Iterator, double()>                    start_rule;
  rule<Iterator>                              tag_rule;
  rule<Iterator, double()>                    value_rule;
  tag_grammar<Iterator> tag_grammar_;

  double_presision_grammar()             : double_presision_grammar::base_type(start_rule),
                                tag_(application_tag::double_presision, size) {
    setup();
  }

  double_presision_grammar(uint8_t tag)  : double_presision_grammar::base_type(start_rule),
                                tag_(tag, true, size) {
    setup();
  }

private:

  void setup() {
    start_rule    =  tag_rule
                  << value_rule;

    tag_rule      =  tag_grammar_[ _1 = boost::phoenix::bind(&double_presision_grammar::get_tag, this)];
    value_rule    =  big_bin_double;

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

  tag get_tag() {//(const double &/*value*/) {
     return tag_;
  }

  static const constexpr uint32_t size{8};
  tag tag_;
};

}}}}}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_double_presision_grammar_HPP
