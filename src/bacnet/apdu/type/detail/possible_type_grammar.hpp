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
#include <boost/fusion/include/out.hpp>
#include <util/boost/spirit/unused_type.hpp>

#include <bacnet/type/types.hpp>
#include <bacnet/detail/common/types.hpp>

#include <bacnet/apdu/type/detail/primitive/null_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/boolean_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/unsigned_integer_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/signed_integer_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/real_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/double_presision_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/octet_string_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/character_string_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/bit_string_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/enumeration_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/date_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/time_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/object_identifier_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/unsupported_type_grammar.hpp>

#include <bacnet/apdu/type/detail/constructed_type.hpp>

namespace boost { namespace spirit { namespace traits {


  template <>
  struct assign_to_attribute_from_value<uint8_t, bacnet::apdu::type::tag> {
      static void call(bacnet::apdu::type::tag const& val, uint8_t& attr) {
          attr = val.number();
      }
  };

}}}
namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
namespace phoenix = boost::phoenix;
namespace type = bacnet::type;


template<typename Iterator>
struct possible_type_grammar : grammar<Iterator, type::possible_type() > , constructed_type{

    typedef std::vector<type::possible_type>          sequence;
    typedef bacnet::type::constructed_type            constructed;

    rule<Iterator, type::possible_type() >            start_rule;
    rule<Iterator, type::possible_type() >            context_rule;
    rule<Iterator, sequence()>                        sequence_rule;
    rule<Iterator, type::possible_type()>             value_rule;
    rule<Iterator, constructed(),  locals<uint8_t>>   constructed_rule;
    rule<Iterator, type::possible_type()>             primitive_rule;

    rule<Iterator, uint8_t()>                         nested_open_tag_rule;
    rule<Iterator, void(uint8_t)>                     nested_close_tag_rule;
    rule<Iterator>                                    open_tag_rule;
    rule<Iterator>                                    close_tag_rule;

    tag_grammar<Iterator>                             tag_grammar_;

    null_grammar<Iterator>                            null_grammar_;
    boolean_grammar<Iterator>                         boolean_grammar_;
    unsigned_integer_grammar<Iterator>                unsigned_integer_grammar_;
    signed_integer_grammar<Iterator>                  signed_integer_grammar_;
    real_grammar<Iterator>                            real_grammar_;
    double_presision_grammar<Iterator>                double_presision_grammar_;
    octet_string_grammar<Iterator>                    octet_string_grammar_;
    character_string_grammar<Iterator>                character_string_grammar_;
    bit_string_grammar<Iterator>                      bit_string_grammar_;
    enumeration_grammar<Iterator>                     enumeration_grammar_;
    date_grammar<Iterator>                            date_grammar_;
    time_grammar<Iterator>                            time_grammar_;
    object_identifier_grammar<Iterator>               object_identifier_grammar_;

    unsupported_type_grammar<Iterator>                unsupported_type_grammar_;

    possible_type_grammar() :  possible_type_grammar::base_type(start_rule) {
      setup();
    }

    possible_type_grammar(uint8_t tag) :  possible_type_grammar::base_type(context_rule), constructed_type(tag) {
      setup();
    }

private:

    inline void setup() {

      start_rule            %=  value_rule
                             |  sequence_rule
                             ;

      context_rule          %=  open_tag_rule
                            >>  value_rule
                            >>  close_tag_rule
                            ;

      sequence_rule         %= *value_rule;

      value_rule            %=  constructed_rule
                             |  primitive_rule
                             ;

      constructed_rule      %=  nested_open_tag_rule[ _a = _1]
                            >> *value_rule
                            >>  nested_close_tag_rule(_a)
                             ;

      primitive_rule         =  null_grammar_
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

                             |  unsupported_type_grammar_
                             ;

      nested_open_tag_rule   =  tag_grammar_[ _val =  phoenix::bind(&possible_type_grammar::is_context_open_tag, this, _1,      _pass) ];
      nested_close_tag_rule  =  tag_grammar_[         phoenix::bind(&possible_type_grammar::check_nested_tag,    this, _r1, _1, _pass) ];

      open_tag_rule          =  tag_grammar_[ phoenix::bind(&possible_type_grammar::check_open_tag,  this, _1, _pass) ];
      close_tag_rule         =  tag_grammar_[ phoenix::bind(&possible_type_grammar::check_close_tag, this, _1, _pass) ];

      //
      /*
      start_rule            .name("possible_type_grammar_start_rule");
      value_rule            .name("possible_type_grammar_value_rule");
      constructed_rule      .name("possible_type_grammar_constructed_type_rule");
      primitive_rule        .name("possible_type_grammar_primitive_type_rule");
      nested_open_tag_rule  .name("possible_type_grammar_nested_open_tag_rule");
      nested_close_tag_rule .name("possible_type_grammar_nested_close_tag_rule");
      sequence_rule         .name("sequence_rule");
      debug(start_rule);
      debug(value_rule);
      debug(primitive_rule);
      debug(constructed_rule);
      debug(sequence_rule);
      debug(nested_open_tag_rule);
      debug(nested_close_tag_rule);
      // */
    }

    inline void check_nested_tag(const uint8_t& open, const tag& close, bool& pass) {
      if(     close.is_closing_tag()
          &&  open == close.number()  ) {
        pass = true;
      }
      else {
        pass = false;
      }
    }

    inline uint8_t is_context_open_tag(const tag& t, bool& pass) {
      if(t.is_opening_tag()) {
        pass = true;
      }
      else {
        pass = false;
      }
      return t.number();
    }

};

}}}}}

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;

namespace type =  bacnet::type;
using bacnet::apdu::type::application_tag;



template<typename Iterator>
struct possible_type_grammar : grammar<Iterator, type::possible_type()> {

  typedef std::vector<type::possible_type>          sequence;


  rule<Iterator, type::possible_type()>  start_tagged_rule;
  rule<Iterator, type::possible_type()>  start_untagged_rule;

  rule<Iterator, type::possible_type()>  value_rule;
  rule<Iterator, sequence()>             sequence_rule;
  rule<Iterator>                         open_tag_rule;
  rule<Iterator>                         close_tag_rule;

  tag_grammar<Iterator>                  tag_grammar_;

  null_grammar<Iterator>                  null_grammar_;
  boolean_grammar<Iterator>               boolean_grammar_;
  unsigned_integer_grammar<Iterator>      unsigned_integer_grammar_;
  signed_integer_grammar<Iterator>        signed_integer_grammar_;
  real_grammar<Iterator>                  real_grammar_;
  double_presision_grammar<Iterator>      double_presision_grammar_;
  octet_string_grammar<Iterator>          octet_string_grammar_;
  character_string_grammar<Iterator>      character_string_grammar_;
  bit_string_grammar<Iterator>            bit_string_grammar_;
  enumeration_grammar<Iterator>           enumeration_grammar_;
  date_grammar<Iterator>                  date_grammar_;
  time_grammar<Iterator>                  time_grammar_;
  object_identifier_grammar<Iterator>     object_identifier_grammar_;







  possible_type_grammar() : possible_type_grammar::base_type(start_untagged_rule) {
    setup();
  }

  possible_type_grammar(uint8_t tag_id) : possible_type_grammar::base_type(start_tagged_rule),
                                          opening_tag_(tag_id, tag::type::opening),
                                          closing_tag_(tag_id, tag::type::closing) {
    setup();
  }

private:

    void setup () {
      start_untagged_rule %= value_rule;


      start_tagged_rule   %=  open_tag_rule
                          <<  value_rule
                          <<  close_tag_rule
                          ;

      open_tag_rule  =  tag_grammar_[_1 = ref(opening_tag_)]
                     ;

      close_tag_rule = tag_grammar_[_1 = ref(closing_tag_)]
                     ;


      sequence_rule  = repeat(2, inf)[value_rule];

      value_rule  =  null_grammar_
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
                  |  sequence_rule
                  ;


      //
      /*
      start_untagged_rule.name("start_untagged_rule");
      start_tagged_rule.name("start_rule");
      open_tag_rule.name("open_tag_rule");
      close_tag_rule.name("close_tag_rule");
      sequence_rule.name("sequence_rule");
      value_rule.name("value_rule");
      debug(start_untagged_rule);
      debug(start_tagged_rule);
      debug(open_tag_rule);
      debug(close_tag_rule);
      debug(sequence_rule);
      debug(value_rule);
      //*/
    }

    tag  opening_tag_;
    tag  closing_tag_;
};

}}}}}


#endif //NINJA_WOOKIE_ENUMERATION_GRAMMAR_HPP
