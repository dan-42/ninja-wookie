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


#ifndef SRC_BACNET_BVLL_FRAME_WRITE_BROADCAST_DISTRIBUTION_TABLE_HPP_
#define SRC_BACNET_BVLL_FRAME_WRITE_BROADCAST_DISTRIBUTION_TABLE_HPP_


#include <boost/fusion/include/define_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/broadcast_distribution_table.hpp>

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),write_broadcast_distribution_table,
	(bacnet::bvll::bvlc::broadcast_distribution_table, broadcast_distribution_table_)
	(bacnet::unused_type,  unused)
)

namespace bacnet { namespace bvll { namespace frame { namespace generator {

using namespace ::boost::spirit;
using namespace ::boost::spirit::karma;
using namespace bacnet::bvll::frame;
using namespace bacnet::bvll::bvlc::generator;

template<typename Iterator>
struct write_broadcast_distribution_table_grammar : grammar<Iterator, write_broadcast_distribution_table()> {

	rule<Iterator, write_broadcast_distribution_table()> write_broadcast_distribution_table_rule;
	rule<Iterator, broadcast_distribution_table()> broadcast_distribution_table_rule;

	broadcast_distribution_table_grammar<Iterator> broadcast_distribution_table_grammar_;

	write_broadcast_distribution_table_grammar() : write_broadcast_distribution_table_grammar::base_type(write_broadcast_distribution_table_rule) {

		write_broadcast_distribution_table_rule = broadcast_distribution_table_rule;
		broadcast_distribution_table_rule = broadcast_distribution_table_grammar_;

		write_broadcast_distribution_table_rule.name("write_broadcast_distribution_table_rule");
		broadcast_distribution_table_rule.name("broadcast_distribution_table_rule");
	}
};

}}}}


namespace bacnet { namespace bvll { namespace frame { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll::frame;
using namespace bacnet::bvll::bvlc::parser;

template<typename Iterator>
struct write_broadcast_distribution_table_grammar : grammar<Iterator, write_broadcast_distribution_table()> {

	rule<Iterator, write_broadcast_distribution_table()> write_broadcast_distribution_table_rule;
	rule<Iterator, broadcast_distribution_table()> broadcast_distribution_table_rule;

	broadcast_distribution_table_grammar<Iterator> broadcast_distribution_table_grammar_;

	write_broadcast_distribution_table_grammar() : write_broadcast_distribution_table_grammar::base_type(write_broadcast_distribution_table_rule) {

		write_broadcast_distribution_table_rule = broadcast_distribution_table_rule >> attr(0);
		broadcast_distribution_table_rule = broadcast_distribution_table_grammar_;

		write_broadcast_distribution_table_rule.name("write_broadcast_distribution_table_rule");
		broadcast_distribution_table_rule.name("broadcast_distribution_table_rule");
	}
};



}}}}

#endif /* SRC_BACNET_BVLL_FRAME_WRITE_BROADCAST_DISTRIBUTION_TABLE_HPP_ */
