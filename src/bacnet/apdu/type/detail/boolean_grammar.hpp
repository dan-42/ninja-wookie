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



#ifndef NINJA_WOOKIE_BOOLEAN_GRAMMAR_HPP
#define NINJA_WOOKIE_BOOLEAN_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/apdu/type/detail/tag_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive_type.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::phoenix::bind;
using bacnet::apdu::type::tag;
using bacnet::apdu::type::application_tag;



template<typename Iterator>
struct boolean_grammar : grammar<Iterator, bool()>, primitive_type {


    rule<Iterator, bool()>          start_rule;
    rule<Iterator >                 tag_validation_rule;
    rule<Iterator, bool()>          value_rule;

   tag_grammar<Iterator> tag_grammar_;

    boolean_grammar() :  boolean_grammar::base_type(start_rule),
                         primitive_type(application_tag::boolean) {
      setup();
    }

    boolean_grammar(uint8_t tag) : boolean_grammar::base_type(start_rule),
                                   primitive_type(tag) {
      setup();
    }

private:

    inline void setup() {
      start_rule           =  tag_validation_rule
                           >> value_rule ;

      tag_validation_rule  = omit[tag_grammar_[ boost::phoenix::bind(&boolean_grammar::extract_size_and_check_tag, this, _1, _pass) ]];

      value_rule           = ( eps(boost::phoenix::ref(is_expecting_context_tag_) == true)
                               >> byte_
                             )
                           | attr(boost::phoenix::ref(length_value_type_))
                           ;
      //
      /*
      start_rule.name("start_rule");
      value_rule.name("value_rule");
      tag_validation_rule.name("tag_validation_rule");
      debug(start_rule);
      debug(value_rule);
      debug(tag_validation_rule);
      // */
    }
};

}}}}}

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;

using boost::spirit::karma::rule;
using boost::spirit::karma::_1;
using boost::phoenix::bind;

using bacnet::apdu::type::tag;
using bacnet::apdu::type::application_tag;



template<typename Iterator>
struct boolean_grammar : grammar<Iterator, bool()> {

    rule<Iterator, bool()>   start_rule;
    rule<Iterator, bool()>   tag_rule;
    rule<Iterator, bool()>   value_rule;

    tag_grammar<Iterator> tag_grammar_;

    boolean_grammar()             : boolean_grammar::base_type(start_rule),
                                    tag_(application_tag::boolean) {
      setup();
    }
    boolean_grammar(uint8_t tag)  : boolean_grammar::base_type(start_rule),
                                    tag_(tag, true) {
      setup();
    }

private:

    void setup () {

      start_rule  = tag_rule[_1 = _val] << value_rule[_1 = _val];


      tag_rule     =  eps[boost::phoenix::bind(&boolean_grammar::extract_value, this, _val)]
                   << tag_grammar_[_1 = ref(tag_)];


      value_rule  =  (     eps(boost::phoenix::bind(&tag::is_context_tag, tag_) == true )
                        << byte_(boost::phoenix::ref(value_))
                     )
                     | eps
                 ;
      start_rule.name("start_rule");
      tag_rule.name("tag_rule");
      value_rule.name("value_rule");

      //
      /*
      debug(start_rule);
      debug(value_rule);
      debug(tag_rule);
      // */
    }

    bool extract_value(const bool &value) {
      value_ = value;
      if(tag_.is_context_tag()) {
        tag_.length_value_type(1);
      }
      else {
        tag_.length_value_type(value ? 1 : 0);
      }
      return true;
    }

    bool value_{false};
    tag tag_;
};

}}}}}


#endif //NINJA_WOOKIE_BOOLEAN_GRAMMAR_HPP
