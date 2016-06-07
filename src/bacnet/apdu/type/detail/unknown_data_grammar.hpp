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
#include <bacnet/apdu/type/detail/tag_grammar.hpp>
#include <bacnet/apdu/type/detail/constructed_type.hpp>
#include <bacnet/apdu/type/detail/primitive_type.hpp>
#include <bacnet/type/unknown_data.hpp>
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
struct unknown_data_grammar : grammar<Iterator, bacnet::type::unknown_data()> {


    rule<Iterator, bacnet::type::unknown_data()>  start_rule;

    rule<Iterator, bacnet::type::unknown_data()>  context_rule;
    rule<Iterator, bacnet::type::unknown_data()>  primitive_rule;
    rule<Iterator, bacnet::binary_data()>         unknown_data_rule;
    rule<Iterator, bacnet::binary_data()>         fixed_data_rule;


    rule<Iterator>                         open_tag_rule;
    rule<Iterator>                         close_tag_rule;
    tag_grammar<Iterator>                  tag_grammar_;

    unknown_data_grammar() :  unknown_data_grammar::base_type(start_rule) {
      setup();
    }


private:

    inline void setup() {
      /*
      start_rule        =  open_tag_rule
                        >>
                          (    primitive_rule
                            |  context_rule
                          )
                        ;
*/

      start_rule        =  open_tag_rule
                        >> primitive_rule
                        ;

      primitive_rule    =  eps(    boost::phoenix::bind(&tag::is_primitive_context_tag,  ref(open_tag_)) == true)
                        >> attr(   ref(open_tag_.number_))
                        >> fixed_data_rule
                        ;

      context_rule      =  eps(    boost::phoenix::bind(&tag::is_opening_tag,            ref(open_tag_)) == true)
                        >> attr(   ref(open_tag_.number_))
                        >> unknown_data_rule
                        >> close_tag_rule
                        ;

      fixed_data_rule   = repeat( ref(open_tag_.length_value_type_) )[byte_];

      unknown_data_rule = *(byte_  -byte_( ref( closing_tag_matcher) )  );


      open_tag_rule    = tag_grammar_[ boost::phoenix::bind(&unknown_data_grammar::extract_tag,  this, _1, _pass) ];
      close_tag_rule   = tag_grammar_[ boost::phoenix::bind(&unknown_data_grammar::check_close_tag, this, _1, _pass) ];
      ///*
      start_rule        .name("unknown_data_grammar_start_rule");
      primitive_rule    .name("unknown_data_grammar_primitive_rule");
      context_rule      .name("unknown_data_grammar_context_rule");
      fixed_data_rule   .name("unknown_data_grammar_fixed_data_rule");
      unknown_data_rule .name("unknown_data_grammar_unknown_data_rule");
      open_tag_rule     .name("unknown_data_grammar_open_tag_rule");
      close_tag_rule    .name("unknown_data_grammar_close_tag_rule");
      debug(start_rule);
      debug(start_rule);
      debug(context_rule);
      debug(fixed_data_rule);
      debug(unknown_data_rule);
      debug(open_tag_rule);
      debug(close_tag_rule);
     //*/
    }

    inline void extract_tag(tag& t, bool& pass) {
      std::cout << "extract_tag(): " << t << std::endl;
      if(t.is_context_tag()) {
        pass                = true;
        open_tag_           = t;
        close_tag_          = t;
        close_tag_.length_value_type_  = tag::closing_tag_indication;
        simple_tag st{t};
        closing_tag_matcher = st.to_binary();
        std::cerr << "extract_tag(): closing_tag_matcher:" << std::hex << (int)closing_tag_matcher << std::endl;
      }
      else {
        pass = false;
      }
    }

    inline void check_close_tag(tag& t, bool& pass) {
      if(    t.is_closing_tag()
          && t.is_context_tag()
          && t.number() == open_tag_.number() ) {
        pass = true;
      }
      else {
        pass = false;
      }
    }

    tag open_tag_;
    tag close_tag_;
    uint8_t closing_tag_matcher{0x00};



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
