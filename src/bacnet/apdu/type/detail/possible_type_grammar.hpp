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



#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_POSSIBLE_TYPE_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_POSSIBLE_TYPE_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>

#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/include/phoenix_fusion.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <util/boost/spirit/unused_type.hpp>
#include <bacnet/type/types.hpp>

#include <bacnet/apdu/type/detail/null_grammar.hpp>
#include <bacnet/apdu/type/detail/boolean_grammar.hpp>
#include <bacnet/apdu/type/detail/unsigned_integer_grammar.hpp>
#include <bacnet/apdu/type/detail/signed_integer_grammar.hpp>
#include <bacnet/apdu/type/detail/real_grammar.hpp>
#include <bacnet/apdu/type/detail/double_presision_grammar.hpp>
#include <bacnet/apdu/type/detail/octet_string_grammar.hpp>
#include <bacnet/apdu/type/detail/character_string_grammar.hpp>
#include <bacnet/apdu/type/detail/bit_string_grammar.hpp>
#include <bacnet/apdu/type/detail/enumeration_grammar.hpp>
#include <bacnet/apdu/type/detail/date_grammar.hpp>
#include <bacnet/apdu/type/detail/time_grammar.hpp>
#include <bacnet/apdu/type/detail/object_identifier_grammar.hpp>

#include <bacnet/apdu/type/detail/constructed_type.hpp>


namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

namespace fusion = boost::fusion;
namespace phoenix = boost::phoenix;


using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::type;
using namespace bacnet::apdu::type::detail::parser;
using phoenix::at_c;
using phoenix::push_back;

template<typename Iterator>
struct possible_type_grammar : grammar<Iterator, possible_type()>, constructed_type {


    rule<Iterator, possible_type()>           start_rule;
    rule<Iterator, possible_type()>           context_rule;
    rule<Iterator, possible_type()>           primitive_type_rule;
    rule<Iterator, sequence()>                constructed_type_rule;
    rule<Iterator, possible_type()>           value_rule;


    rule<Iterator>                            open_tag_rule;
    rule<Iterator>                            close_tag_rule;
    tag_grammar<Iterator>                     tag_grammar_;


    null_grammar<Iterator>                    null_grammar_;
    boolean_grammar<Iterator>                 boolean_grammar_;
    unsigned_integer_grammar<Iterator>        unsigned_integer_grammar_;
    signed_integer_grammar<Iterator>          signed_integer_grammar_;
    real_grammar<Iterator>                    real_grammar_;
    double_presision_grammar<Iterator>        double_presision_grammar_;
    octet_string_grammar<Iterator>            octet_string_grammar_;
    character_string_grammar<Iterator>        character_string_grammar_;
    bit_string_grammar<Iterator>              bit_string_grammar_;
    enumeration_grammar<Iterator>             enumeration_grammar_;
    date_grammar<Iterator>                    date_grammar_;
    time_grammar<Iterator>                    time_grammar_;
    object_identifier_grammar<Iterator>       object_identifier_grammar_;

    unused_grammar<Iterator> unused_grammar_;
    possible_type_grammar() :  possible_type_grammar::base_type(start_rule) {
      setup();
    }

    possible_type_grammar(uint8_t tag) :  possible_type_grammar::base_type(start_rule),
                                          constructed_type(tag) {
      setup();
    }

private:

    inline void setup() {
      start_rule            = context_rule
                            | value_rule
                            ;


      context_rule          =  open_tag_rule
                            >> value_rule
                            >> close_tag_rule
                            ;

      value_rule            = constructed_type_rule
                            | primitive_type_rule
                            ;

      constructed_type_rule =  repeat(2, inf)[ primitive_type_rule ]
                            >> unused_grammar_;

      primitive_type_rule   =  null_grammar_
                            |  boolean_grammar_
                            |  unsigned_integer_grammar_
                            |  signed_integer_grammar_
                            |  real_grammar_
                            |  double_presision_grammar_
                            |  octet_string_grammar_
                            |  character_string_grammar_
                            |  bit_string_grammar_
                            |  enumeration_grammar_
                            |  date_grammar_
                            |  time_grammar_
                            |  object_identifier_grammar_
                          //  |  value_rule
                            ;

      open_tag_rule   = tag_grammar_[ boost::phoenix::bind(&possible_type_grammar::check_open_tag,  this, _1, _pass) ];
      close_tag_rule  = tag_grammar_[ boost::phoenix::bind(&possible_type_grammar::check_close_tag, this, _1, _pass) ];

      //
      /*
      start_rule            .name("start_rule");
      context_rule          .name("context_rule");
      value_rule            .name("value_rule");
      constructed_type_rule .name("constructed_type_rule");
      primitive_type_rule   .name("primitive_type_rule");
      open_tag_rule         .name("open_tag_rule");
      close_tag_rule        .name("close_tag_rule");
      debug(start_rule);
      debug(context_rule);
      debug(value_rule);
      debug(constructed_type_rule);
      debug(primitive_type_rule);
      debug(open_tag_rule);
      debug(close_tag_rule);
      // */
    }
};

}}}}}
/*
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
using bacnet::type::enumerated;


template<typename Iterator>
struct enumeration_grammar : grammar<Iterator, enumerated()> {

    rule<Iterator, enumerated()>    start_rule;
    rule<Iterator, enumerated()>    tag_rule;
    rule<Iterator, enumerated::e()> type_rule;
    rule<Iterator, enumerated()>    value_rule;

    tag_grammar<Iterator> tag_grammar_;

    enumeration_grammar() : enumeration_grammar::base_type(start_rule), tag_(application_tag::enumerated) {
      setup();
    }
    enumeration_grammar(uint8_t tag) : enumeration_grammar::base_type(start_rule), tag_(tag, true) {
      setup();
    }

private:

    void setup () {

      start_rule  = tag_rule[_1 = _val] << value_rule[_1 = _val];


      tag_rule    =  eps[boost::phoenix::bind(&enumeration_grammar::extract_size, this, _val)]
                  << tag_grammar_[_1 = ref(tag_)];


      value_rule  = type_rule << (
                        eps(ref(size_) == 1) << byte_
                      | eps(ref(size_) == 2) << big_word
                      | eps(ref(size_) == 3) << big_24word
                      | eps(ref(size_) == 4) << big_dword
                    )
                  ;

      type_rule   = eps;

      start_rule.name("start_rule");
      tag_rule.name("tag_rule");
      value_rule.name("value_rule");

    }

    bool extract_size(const enumerated &enumerated_value) {
      size_ = bacnet::apdu::type::detail::length_helper(enumerated_value.value);
      tag_.length_value_type(size_);
      return true;
    }


    uint8_t size_;
    tag tag_;
};

}}}}}
*/

#endif //NINJA_WOOKIE_ENUMERATION_GRAMMAR_HPP
