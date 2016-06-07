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



#ifndef NINJA_WOOKIE_OBJECT_IDENTIFIER_GRAMMAR_HPP
#define NINJA_WOOKIE_OBJECT_IDENTIFIER_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/apdu/type/detail/tag_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive_type.hpp>
#include <bacnet/type/object_identifier.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::phoenix::bind;

using bacnet::apdu::type::tag;
using bacnet::apdu::type::application_tag;
using bacnet::type::object_identifier;


template<typename Iterator>
struct object_identifier_grammar : grammar<Iterator, object_identifier()>, primitive_type {


    rule<Iterator, object_identifier()> start_rule;
    rule<Iterator >                     tag_validation_rule;
    rule<Iterator, object_identifier()> value_rule;

   tag_grammar<Iterator> tag_grammar_;

    object_identifier_grammar() :  object_identifier_grammar::base_type(start_rule),
                                   primitive_type(application_tag::bacnet_object_identifier) {
      setup();
    }

    object_identifier_grammar(uint8_t tag) : object_identifier_grammar::base_type(start_rule),
                                              primitive_type(tag) {
      setup();
    }

private:

    inline void setup() {
      length_value_type_ = 4;

      start_rule  =  tag_validation_rule
                  >> value_rule ;

      tag_validation_rule = tag_grammar_[ boost::phoenix::bind(&object_identifier_grammar::check_tag, this, _1, _pass) ];
      value_rule  = big_dword[ _val = boost::phoenix::bind(&bacnet::type::object_identifier::make_object_identifier, _1) ];
      //
      /*
      start_rule.name("object_identifier_grammar_start_rule");
      tag_validation_rule.name("tag_validation_rule");
      value_rule.name("value_rule");
      debug(start_rule);
      debug(tag_validation_rule);
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
using bacnet::type::object_identifier;


template<typename Iterator>
struct object_identifier_grammar : grammar<Iterator, object_identifier()> {

    rule<Iterator, object_identifier()>   start_rule;
    rule<Iterator, object_identifier()>   extract_rule;
    rule<Iterator>                        tag_rule;
    rule<Iterator>                        value_rule;

    tag_grammar<Iterator> tag_grammar_;

    object_identifier_grammar() : object_identifier_grammar::base_type(start_rule), tag_(application_tag::bacnet_object_identifier) {
      setup();
    }
    object_identifier_grammar(uint8_t tag) : object_identifier_grammar::base_type(start_rule), tag_(tag, true) {
      setup();
    }

private:

    void setup () {

      start_rule    = extract_rule
                    << tag_rule
                    << value_rule;

      extract_rule  = eps[boost::phoenix::bind(&object_identifier_grammar::extract, this, _val)];

      tag_rule      = tag_grammar_[_1 = ref(tag_)];

      value_rule    = big_dword[ _1 = ref(value_)];

      start_rule.name("start_rule");
      tag_rule.name("tag_rule");
      value_rule.name("value_rule");

      /*
      debug(start_rule);
      debug(value_rule);
      debug(tag_rule);
      */
    }

    bool extract(const object_identifier &v) {
      value_ = v.to_native();
      auto size = bacnet::apdu::type::detail::length_helper(value_);
      tag_.length_value_type(size);
      return true;
    }

    uint32_t value_;
    tag tag_;
};

}}}}}


#endif //NINJA_WOOKIE_OBJECT_IDENTIFIER_GRAMMAR_HPP
