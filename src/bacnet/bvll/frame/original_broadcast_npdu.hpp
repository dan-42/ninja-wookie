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


#ifndef SRC_BACNET_BVLL_FRAME_ORIGINAL_BROADCAST_NPDU_HPP_
#define SRC_BACNET_BVLL_FRAME_ORIGINAL_BROADCAST_NPDU_HPP_

#include <vector>

#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>



BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),original_broadcast_npdu,
	(bacnet::binary_data, npdu_data)
	(bacnet::unused_type,  unused)
)


namespace bacnet { namespace bvll { namespace frame { namespace generator {

using namespace ::boost::spirit;
using namespace ::boost::spirit::karma;
using namespace bacnet::bvll::frame;

template<typename Iterator>
struct original_broadcast_npdu_grammar : grammar<Iterator, original_broadcast_npdu()> {

	rule<Iterator, original_broadcast_npdu()> original_broadcast_npdu_rule;
	rule<Iterator, bacnet::binary_data()> npdu_data_rule;

	original_broadcast_npdu_grammar() : original_broadcast_npdu_grammar::base_type(original_broadcast_npdu_rule) {

		original_broadcast_npdu_rule = npdu_data_rule;
		npdu_data_rule = *byte_;

		original_broadcast_npdu_rule.name("original_broadcast_npdu_rule");
		npdu_data_rule.name("npdu_data_rule");
	}
};

}}}}


namespace bacnet { namespace bvll { namespace frame { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll::frame;

template<typename Iterator>
struct original_broadcast_npdu_grammar : grammar<Iterator, original_broadcast_npdu()> {

	rule<Iterator, original_broadcast_npdu()> original_broadcast_npdu_rule;
	rule<Iterator, bacnet::binary_data()> npdu_data_rule;


	original_broadcast_npdu_grammar() : original_broadcast_npdu_grammar::base_type(original_broadcast_npdu_rule) {

		original_broadcast_npdu_rule =  npdu_data_rule >> attr(0);
		npdu_data_rule = *byte_;

		original_broadcast_npdu_rule.name("original_broadcast_npdu_rule");
		npdu_data_rule.name("npdu_data_rule");

		debug(original_broadcast_npdu_rule);
		debug(npdu_data_rule);
	}
};


bool parse(const std::string &data_to_parse, original_broadcast_npdu &parsed){
	auto start = data_to_parse.begin();
	auto end = data_to_parse.end();

	original_broadcast_npdu_grammar<decltype(start)> grammar;
	bool result = false;
	try {
		result = boost::spirit::qi::parse(start, end, grammar, parsed);
	}
	catch(std::exception &e) {
		std::cerr << "exception: frames.hpp parse(Container &i, original_broadcast_npdu_grammar &v) " << e.what() << std::endl;
	}
	return result;

}


}}}}



#endif /* SRC_BACNET_BVLL_FRAME_ORIGINAL_BROADCAST_NPDU_HPP_ */
