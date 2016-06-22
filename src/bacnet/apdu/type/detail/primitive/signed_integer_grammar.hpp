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



#ifndef NINJA_WOOKIE_SIGNED_INTEGER_GRAMMAR_HPP
#define NINJA_WOOKIE_SIGNED_INTEGER_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/apdu/detail/boost/uint24_parser.hpp>
#include <bacnet/apdu/detail/boost/uint24_generator.hpp>

#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/apdu/type/detail/util/tag_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive_type.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::bit_field;
using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::phoenix::bind;

using boost::spirit::repository::qi::big_24word;

using bacnet::apdu::type::tag;
using bacnet::apdu::type::application_tag;



template<typename Iterator>
struct signed_integer_grammar : grammar<Iterator, int32_t()>, primitive_type {


    rule<Iterator, int32_t()>          start_rule;
    rule<Iterator >                    tag_validation_rule;
    rule<Iterator, int32_t()>          value_rule;

   tag_grammar<Iterator> tag_grammar_;

    signed_integer_grammar() :  signed_integer_grammar::base_type(start_rule),
                                primitive_type(application_tag::signed_integer) {
      setup();
    }

    signed_integer_grammar(uint8_t tag) : signed_integer_grammar::base_type(start_rule),
                                          primitive_type(tag) {
      setup();
    }

private:

    inline void setup() {
      start_rule   =  tag_validation_rule
                   >> value_rule ;

      tag_validation_rule  = omit[tag_grammar_[ boost::phoenix::bind(&signed_integer_grammar::extract_size_and_check_tag, this, _1, _pass) ] ];

      value_rule  = eps(boost::phoenix::ref(length_value_type_) == (uint32_t)1) >> byte_
                  | eps(boost::phoenix::ref(length_value_type_) == (uint32_t)2) >> big_word
                  | eps(boost::phoenix::ref(length_value_type_) == (uint32_t)3) >> big_24word
                  | eps(boost::phoenix::ref(length_value_type_) == (uint32_t)4) >> big_dword
                  ;
        //
        /*
        start_rule.name("start_rule");
        value_rule.name("value_rule");
        debug(start_rule);
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
struct signed_integer_grammar : grammar<Iterator, int32_t()> {

    rule<Iterator, int32_t()>   start_rule;
    rule<Iterator, int32_t()>   tag_rule;
    rule<Iterator, int32_t()>   value_rule;

    tag_grammar<Iterator> tag_grammar_;

    signed_integer_grammar() : signed_integer_grammar::base_type(start_rule), tag_(application_tag::signed_integer) {
      setup();
    }
    signed_integer_grammar(uint8_t tag) : signed_integer_grammar::base_type(start_rule), tag_(tag) {
      setup();
    }

private:

    void setup () {

      start_rule  = tag_rule[_1 = _val] << value_rule[_1 = _val];


      tag_rule = eps[boost::phoenix::bind(&signed_integer_grammar::extract_size, this, _val)]  << tag_grammar_[_1 = ref(tag_)];
      //tag_rule = tag_grammar_[_1 = ref(tag_)];

      value_rule  =   eps(ref(size_) == 1) << byte_
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

    bool extract_size(const int32_t &signed_value) {
      size_ = bacnet::apdu::type::detail::length_helper(signed_value);
      tag_.length_value_type(size_);
      return true;
    }


    uint8_t size_;
    tag tag_;
};

}}}}}


#endif //NINJA_WOOKIE_SIGNED_INTEGER_GRAMMAR_HPP
