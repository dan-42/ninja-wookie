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



#ifndef NINJA_WOOKIE_NULL_GRAMMAR_HPP
#define NINJA_WOOKIE_NULL_GRAMMAR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/apdu/type/detail/primitive_type.hpp>
#include <bacnet/apdu/type/detail/util/tag_grammar.hpp>
#include <bacnet/type/null.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::spirit::qi::_pass;
using boost::phoenix::bind;

using bacnet::apdu::type::tag;
using bacnet::apdu::type::application_tag;
using bacnet::type::null;


template<typename Iterator>
struct null_grammar : grammar<Iterator, null()>, primitive_type {

    rule<Iterator, null()>              start_rule;
    rule<Iterator >                     tag_validation_rule;

   tag_grammar<Iterator> tag_grammar_;

    null_grammar() :            null_grammar::base_type(start_rule),
                                primitive_type(application_tag::null) {
      setup();
    }

    null_grammar(uint8_t tag) : null_grammar::base_type(start_rule),
                                primitive_type(tag) {
      setup();
    }

private:

    inline void setup() {
      start_rule          =  tag_validation_rule;
      tag_validation_rule = tag_grammar_[ boost::phoenix::bind(&null_grammar::check_tag, this, _1, _pass) ];
      //
      /*
      start_rule.name("start_rule");
      tag_validation_rule.name("tag_validation_rule");
      debug(start_rule);
      debug(tag_validation_rule);
      //*/
    }
};

}}}}}

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;
using boost::spirit::karma::rule;
using boost::spirit::karma::_1;
using bacnet::apdu::type::tag;
using bacnet::apdu::type::application_tag;
using bacnet::type::null;

template<typename Iterator>
struct null_grammar : grammar<Iterator, null()> {

    rule<Iterator, null()>   start_rule;
    rule<Iterator>           tag_rule;

    tag_grammar<Iterator> tag_grammar_;

    null_grammar() :            null_grammar::base_type(start_rule),
                                tag_(application_tag::null, 0) {
      setup();
    }
    null_grammar(uint8_t tag) : null_grammar::base_type(start_rule),
                                tag_(tag, true, 0) {
      setup();
    }

private:

    void setup () {

      start_rule    =  tag_rule;

      tag_rule      = tag_grammar_[_1 = ref(tag_)];

      start_rule.name("start_rule");
      tag_rule.name("tag_rule");

      /*
      debug(start_rule);
      debug(tag_rule);
     // */
    }
    tag tag_;
};

}}}}}


#endif //NINJA_WOOKIE_NULL_GRAMMAR_HPP
