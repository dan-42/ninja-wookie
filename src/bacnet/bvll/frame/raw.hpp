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


#ifndef SRC_BACNET_BVLL_FRAME_RAW_HPP_
#define SRC_BACNET_BVLL_FRAME_RAW_HPP_

#include <string>

#include <boost/fusion/include/define_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/bacnet_ip_address.hpp>

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),raw,
	(bacnet::binary_data, data)
	(bacnet::unused_type, unused)
)


namespace bacnet { namespace bvll { namespace frame { namespace generator {

using namespace ::boost::spirit;
using namespace ::boost::spirit::karma;
using namespace bacnet::bvll::frame;

template<typename Iterator>
struct raw_grammar : grammar<Iterator, raw()> {

	rule<Iterator, raw()> raw_rule;
	rule<Iterator, bacnet::binary_data()> data_rule;

	raw_grammar() : raw_grammar::base_type(raw_rule) {

		raw_rule = data_rule;
		data_rule = *byte_;

		raw_rule.name("raw_rule");
		data_rule.name("data_rule");
	}
};

}}}}


namespace bacnet { namespace bvll { namespace frame { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll::frame;

template<typename Iterator>
struct raw_grammar : grammar<Iterator, raw()> {

	rule<Iterator, raw()> raw_rule;
	rule<Iterator, bacnet::binary_data()> data_rule;

	raw_grammar() : raw_grammar::base_type(raw_rule) {

		raw_rule = data_rule >> attr(0);
		data_rule = *byte_;

		raw_rule.name("raw_rule");
		data_rule.name("data_rule");
	}
};


}}}}

#endif /* SRC_BACNET_BVLL_FRAME_FORWARDED_NPDU_HPP_ */
