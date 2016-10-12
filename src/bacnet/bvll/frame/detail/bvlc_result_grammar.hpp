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

#ifndef SRC_BACNET_BVLL_BVLC_RESULT_GRAMMAR_HPP_
#define SRC_BACNET_BVLL_BVLC_RESULT_GRAMMAR_HPP_

#include <mapbox/boost_spirit_karma.hpp>
#include <mapbox/boost_spirit_qi.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/bvll/frame/bvlc_result.hpp>
#include <bacnet/bvll/result_code.hpp>
#include <util/boost/spirit/unused_type.hpp>



namespace bacnet { namespace bvll { namespace frame { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll;

template<typename Iterator>
struct bvlc_result_grammar : grammar<Iterator, bvlc_result()> {

  rule<Iterator, bvlc_result()> bvlc_result_rule;
  rule<Iterator, uint16_t()> result_code_rule;

 // unused_grammar<Iterator> unused_grammar_;

  bvlc_result_grammar() : bvlc_result_grammar::base_type(bvlc_result_rule) {

    bvlc_result_rule = result_code_rule;// << unused_grammar_;
    result_code_rule = big_word;

    bvlc_result_rule.name("bvlc_result_rule");
    result_code_rule.name("result_code_rule");
  }
};


}}}}} /* namespaces */


namespace bacnet { namespace bvll { namespace frame { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll;

template<typename Iterator>
struct bvlc_result_grammar : grammar<Iterator, bvlc_result()> {

  rule<Iterator, bvlc_result()> bvlc_result_rule;
  rule<Iterator, uint16_t()> result_code_rule;

  //unused_grammar<Iterator> unused_grammar_;

  bvlc_result_grammar() : bvlc_result_grammar::base_type(bvlc_result_rule) {

    bvlc_result_rule = result_code_rule;// >> unused_grammar_;
    result_code_rule = big_word;

    bvlc_result_rule.name("bvlc_result_rule");
    result_code_rule.name("result_code_rule");
  }
};

}}}}} /* namespaces */

#endif /* SRC_BACNET_BVLL_BVLC_RESULT_GRAMMAR_HPP_ */
