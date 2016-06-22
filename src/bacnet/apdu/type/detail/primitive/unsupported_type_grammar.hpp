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



#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_UNKNOWN_DATA_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_UNKNOWN_DATA_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/detail/util/tag_grammar.hpp>
#include <bacnet/apdu/type/detail/constructed_type.hpp>
#include <bacnet/apdu/type/detail/primitive_type.hpp>
#include <bacnet/type/unsupported_type.hpp>
#include <boost/fusion/include/out.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::spirit::qi::_pass;
using boost::phoenix::bind;


template<typename Iterator>
struct unsupported_type_grammar : grammar<Iterator, bacnet::type::unsupported_type()> {

    rule<Iterator, bacnet::type::unsupported_type()>  start_rule;
    rule<Iterator>                                    tag_rule;
    rule<Iterator, uint8_t()>                         tag_number_rule;
    rule<Iterator, bacnet::binary_data()>             data_rule;
    tag_grammar<Iterator>                             tag_grammar_;

    uint32_t    data_length_{0};
    uint8_t     tag_number_{0};

    unsupported_type_grammar() :  unsupported_type_grammar::base_type(start_rule) {
      setup();
    }

private:
    uint_parser<uint8_t, 16, 2, 2> hex8;
    inline void setup() {

      start_rule       =   tag_rule
                       >>  tag_number_rule
                       >>  data_rule
                        ;

      tag_rule          =  tag_grammar_[ boost::phoenix::bind(&unsupported_type_grammar::extract_tag, this,  _1, _pass) ]
                        ;

      tag_number_rule   = attr( ref(tag_number_));

      data_rule         = repeat( ref(data_length_) )[byte_];

      //
      /*
      start_rule        .name("unknown_data_grammar_start_rule");
      data_rule         .name("data_rule");
      tag_number_rule   .name("tag_number_rule");
      debug(start_rule);
      debug(data_rule);
      debug(tag_number_rule);
     // */
    }

    inline void extract_tag(const tag& t, bool& pass) {
      if(t.is_context_tag() ) {
        pass         = true;
        data_length_ = t.length_value_type();
        tag_number_  = t.number();
      }
      else {
        pass = false;
      }
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



template<typename Iterator>
struct error_grammar : grammar<Iterator, bacnet::type::unknown_data()> {


  rule<Iterator, bacnet::type::unknown_data()>  start_rule;
  rule<Iterator, bacnet::type::unknown_data()>  error_rule;
  rule<Iterator>                         open_tag_rule;
  rule<Iterator>                         close_tag_rule;

  enumeration_grammar<Iterator>          enumeration_grammar_;
  tag_grammar<Iterator> tag_grammar_;


  error_grammar() : error_grammar::base_type(start_rule), add_surrounding_tag_(false) {
    setup();
  }
  error_grammar(uint8_t tag_id) : error_grammar::base_type(start_rule),
                                  add_surrounding_tag_(true),
                                  opening_tag_(tag_id, true, tag::opening_tag_indication),
                                  closing_tag_(tag_id, true, tag::closing_tag_indication) {
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

      /  *
      debug(start_rule);
      debug(value_rule);
      debug(tag_rule);
      *  /
    }


    bool add_surrounding_tag_{false};
    tag  opening_tag_;
    tag  closing_tag_;
};


}}}}}
*/

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DETAIL_UNKNOWN_DATA_GRAMMAR_HPP
