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



#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_ERROR_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_ERROR_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>


#include <bacnet/apdu/type/detail/primitive/enumeration_grammar.hpp>
#include <bacnet/apdu/type/detail/constructed_type.hpp>
#include <bacnet/type/error.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::spirit::qi::_pass;
using boost::phoenix::bind;


template<typename Iterator>
struct error_grammar : grammar<Iterator, bacnet::type::error()>, constructed_type {


    rule<Iterator, bacnet::type::error()>  start_rule;

    rule<Iterator, bacnet::type::error()>  context_rule;
    rule<Iterator, bacnet::type::error()>  error_rule;

    rule<Iterator>                         open_tag_rule;
    rule<Iterator>                         close_tag_rule;

    enumeration_grammar<Iterator>          enumeration_grammar_;
    tag_grammar<Iterator>                  tag_grammar_;

   error_grammar() :  error_grammar::base_type(start_rule) {
      setup();
    }

   error_grammar(uint8_t tag) : error_grammar::base_type(start_rule),
                                constructed_type(tag) {
     setup();
   }

private:

    inline void setup() {
      start_rule    =  context_rule
                    |  error_rule ;

      context_rule  =  open_tag_rule
                    >> error_rule
                    >> close_tag_rule
                    ;

      error_rule  =  enumeration_grammar_
                  >> enumeration_grammar_;

      open_tag_rule   = tag_grammar_[ boost::phoenix::bind(&error_grammar::check_open_tag,  this, _1, _pass) ];
      close_tag_rule  = tag_grammar_[ boost::phoenix::bind(&error_grammar::check_close_tag, this, _1, _pass) ];
      /*
     start_rule.name("start_rule");
           debug(start_rule);
           debug(tag_rule);
           debug(tag_lower_rule);
           debug(value_rule);
     //*/
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

using boost::spirit::repository::karma::big_24word;

using bacnet::apdu::type::tag;
using bacnet::apdu::type::application_tag;



template<typename Iterator>
struct error_grammar : grammar<Iterator, bacnet::type::error()> {


  rule<Iterator, bacnet::type::error()>  start_rule;
  rule<Iterator, bacnet::type::error()>  error_rule;
  rule<Iterator>                         open_tag_rule;
  rule<Iterator>                         close_tag_rule;

  enumeration_grammar<Iterator>          enumeration_grammar_;
  tag_grammar<Iterator> tag_grammar_;


  error_grammar() : error_grammar::base_type(start_rule), add_surrounding_tag_(false) {
    setup();
  }
  error_grammar(uint8_t tag_id) : error_grammar::base_type(start_rule),
                                  add_surrounding_tag_(true),
                                  opening_tag_(tag_id, tag::type::opening),
                                  closing_tag_(tag_id, tag::type::closing) {
    setup();
  }

private:

    void setup () {

      start_rule  =  open_tag_rule
                  << error_rule
                  << close_tag_rule
                  ;

      open_tag_rule  = eps(ref(add_surrounding_tag_) == true)  << tag_grammar_[_1 = ref(opening_tag_)] | eps;
      close_tag_rule = eps(ref(add_surrounding_tag_) == true)  << tag_grammar_[_1 = ref(closing_tag_)] | eps;

      error_rule  =  enumeration_grammar_
                  << enumeration_grammar_;

      start_rule.name("start_rule");

      /*
      debug(start_rule);
      debug(value_rule);
      debug(tag_rule);
      */
    }


    bool add_surrounding_tag_{false};
    tag  opening_tag_;
    tag  closing_tag_;
};

}}}}}


#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_ERROR_GRAMMAR_HPP
