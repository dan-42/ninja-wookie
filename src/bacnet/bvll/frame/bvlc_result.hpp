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


#ifndef SRC_BACNET_BVLL_BVLC_RESULT_HPP_
#define SRC_BACNET_BVLL_BVLC_RESULT_HPP_


#include <boost/fusion/include/define_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>


#include <bacnet/bvll/bvlc/result_code.hpp>

#include <bacnet/detail/common/types.hpp>



/*

namespace boost { namespace spirit { namespace traits {
    template <typename Enum, typename RawValue>
    struct assign_to_attribute_from_value<Enum, RawValue, typename enable_if<is_enum<Enum>>::type> {
        static void call(RawValue const& raw, Enum& cat) {
            cat = static_cast<Enum>(raw);
            //cat = boost::phoenix::static_cast_<Enum>(raw);
        }
    };
}}}

*/


BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),bvlc_result,
	(uint16_t, result_code)
	(bacnet::unused_type, unused)
)


namespace bacnet { namespace bvll { namespace frame { namespace generator {

using namespace ::boost::spirit;
using namespace ::boost::spirit::karma;
using namespace bacnet::bvll::bvlc;

template<typename Iterator>
struct bvlc_result_grammar : grammar<Iterator, bvlc_result()> {


	rule<Iterator, bvlc_result()> bvlc_result_rule;
	rule<Iterator, uint16_t()> result_code_rule;

	bvlc_result_grammar() : bvlc_result_grammar::base_type(bvlc_result_rule) {

		bvlc_result_rule = result_code_rule;
		result_code_rule = big_word;

		bvlc_result_rule.name("bvlc_result_rule");
		result_code_rule.name("result_code_rule");
	}
};

}}}}


namespace bacnet { namespace bvll { namespace frame { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll::bvlc;

template<typename Iterator>
struct bvlc_result_grammar : grammar<Iterator, bvlc_result()> {


	rule<Iterator, bvlc_result()> bvlc_result_rule;
	rule<Iterator, uint16_t()> result_code_rule;

	bvlc_result_grammar() : bvlc_result_grammar::base_type(bvlc_result_rule) {

		bvlc_result_rule = result_code_rule >> attr(0);
		result_code_rule = big_word;

		bvlc_result_rule.name("bvlc_result_rule");
		result_code_rule.name("result_code_rule");
	}


};

}}}}

#endif /* SRC_BACNET_BVLL_BVLC_RESULT_HPP_ */
