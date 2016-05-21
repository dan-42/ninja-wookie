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


#include <bacnet/apdu/type/detail/enumeration_grammar.hpp>
#include <bacnet/type/error.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::phoenix::bind;


template<typename Iterator>
struct error_grammar : grammar<Iterator, bacnet::type::error()> {


    rule<Iterator, bacnet::type::error()>  start_rule;

    rule<Iterator, bacnet::type::error()>  context_rule;
    rule<Iterator, bacnet::type::error()>  error_rule;

    rule<Iterator>                         open_tag_rule;
    rule<Iterator>                         close_tag_rule;

    enumeration_grammar<Iterator>          enumeration_grammar_;

   tag_grammar<Iterator> tag_grammar_;

   error_grammar() :  error_grammar::base_type(start_rule) {
      setup();
    }

   error_grammar(uint8_t tag) : error_grammar::base_type(start_rule),
                                                                  size_(0),
                                                                  tag_number_expected_(tag),
                                                                  is_expecting_context_tag_(true) {
      setup();
    }

private:

    inline void setup() {
      start_rule    =  context_rule
                    | error_rule ;

      context_rule  =  open_tag_rule
                    >> error_rule
                    >> close_tag_rule
                    ;

      error_rule  =  enumeration_grammar_
                  >> enumeration_grammar_;

           tag_validation_rule = tag_grammar_[ boost::phoenix::bind(&enumeration_grammar::check_tag, this, _1) == true ];

           value_rule  = eps(boost::phoenix::ref(size_) == (uint32_t)1) >> byte_
                       | eps(boost::phoenix::ref(size_) == (uint32_t)2) >> big_word
                       | eps(boost::phoenix::ref(size_) == (uint32_t)3) >> big_24word
                       | eps(boost::phoenix::ref(size_) == (uint32_t)4) >> big_dword;


           start_rule.name("start_rule");
           value_rule.name("value_rule");

     /*
           debug(start_rule);
           debug(tag_rule);
           debug(tag_lower_rule);
           debug(value_rule);
     //*/
    }

    bool check_tag(tag& t) {
      size_ = t.length_value_type();
      if(   t.is_context_tag() == is_expecting_context_tag_
         && t.number()         == tag_number_expected_ ) {
        return true;
      }
      else {
        return false;
      }
    }
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

using boost::spirit::repository::karma::big_24word;

using bacnet::apdu::type::tag;
using bacnet::apdu::type::application_tag;



template<typename Iterator>
struct enumeration_grammar : grammar<Iterator, uint32_t()> {

    rule<Iterator, uint32_t()>   start_rule;
    rule<Iterator, uint32_t()>   tag_rule;
    rule<Iterator, uint32_t()>   value_rule;

    tag_grammar<Iterator> tag_grammar_;

    enumeration_grammar() : enumeration_grammar::base_type(start_rule), tag_(application_tag::unsigned_integer) {
      setup();
    }
    enumeration_grammar(uint8_t tag) : enumeration_grammar::base_type(start_rule), tag_(tag, true) {
      setup();
    }

private:

    void setup () {

      start_rule  = tag_rule[_1 = _val] << value_rule[_1 = _val];


      tag_rule = eps[boost::phoenix::bind(&enumeration_grammar::extract_size, this, _val)]  << tag_grammar_[_1 = ref(tag_)];
      //tag_rule = tag_grammar_[_1 = ref(tag_)];

      value_rule  = eps(ref(size_) == 1) << byte_
                    | eps(ref(size_) == 2) << big_word
                    | eps(ref(size_) == 3) << big_24word
                    | eps(ref(size_) == 4) << big_dword;

      start_rule.name("start_rule");
      tag_rule.name("tag_rule");
      value_rule.name("value_rule");

      /*
      debug(start_rule);
      debug(value_rule);
      debug(tag_rule);
      */
    }

    bool extract_size(const uint32_t &unsigned_value) {
      size_ = bacnet::apdu::type::detail::length_helper(unsigned_value);
      tag_.length_value_type(size_);
      return true;
    }


    uint8_t size_;
    tag tag_;
};

}}}}}


#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_ERROR_GRAMMAR_HPP
