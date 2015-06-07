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


#ifndef SRC_BACNET_BVLL_BROADCAST_DISTRIBUTION_TABLE_HPP_
#define SRC_BACNET_BVLL_BROADCAST_DISTRIBUTION_TABLE_HPP_

#include <boost/fusion/include/define_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/broadcast_distribution_table_entry.hpp>

namespace bacnet { namespace bvll {
	typedef std::vector<bacnet::bvll::broadcast_distribution_table_entry> broadcast_distribution_table;
}}


namespace bacnet { namespace bvll { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll;

template<typename Iterator>
struct broadcast_distribution_table_grammar : grammar<Iterator, broadcast_distribution_table()> {

	rule<Iterator, broadcast_distribution_table()> broadcast_distribution_table_rule;
	rule<Iterator, broadcast_distribution_table_entry()> broadcast_distribution_table_entry_rule;

	broadcast_distribution_table_entry_grammar<Iterator> broadcast_distribution_table_entry_grammar_;

	broadcast_distribution_table_grammar() : broadcast_distribution_table_grammar::base_type(broadcast_distribution_table_rule) {

		broadcast_distribution_table_rule = *broadcast_distribution_table_entry_rule;
		broadcast_distribution_table_entry_rule = broadcast_distribution_table_entry_grammar_;

		broadcast_distribution_table_rule.name("broadcast_distribution_table_rule");
		broadcast_distribution_table_entry_rule.name("broadcast_distribution_table_entry_rule");
	}
};



template<typename Container>
bool generate(Container &c, broadcast_distribution_table &v) {
	std::back_insert_iterator<Container> sink(c);
	bacnet::bvll::generator::broadcast_distribution_table_grammar<decltype(sink)> g;
	return boost::spirit::karma::generate(sink, g, v);
}

}}}


namespace bacnet { namespace bvll { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll;

template<typename Iterator>
struct broadcast_distribution_table_grammar : grammar<Iterator, broadcast_distribution_table()> {

	rule<Iterator, broadcast_distribution_table()> broadcast_distribution_table_rule;
	rule<Iterator, broadcast_distribution_table_entry()> broadcast_distribution_table_entry_rule;

	broadcast_distribution_table_entry_grammar<Iterator> broadcast_distribution_table_entry_grammar_;

	broadcast_distribution_table_grammar() : broadcast_distribution_table_grammar::base_type(broadcast_distribution_table_rule) {

		broadcast_distribution_table_rule = *broadcast_distribution_table_entry_rule;
		broadcast_distribution_table_entry_rule = broadcast_distribution_table_entry_grammar_;


		broadcast_distribution_table_rule.name("broadcast_distribution_table_rule");
		broadcast_distribution_table_entry_rule.name("broadcast_distribution_table_entry_rule");
	}
};

template<typename Container>
bool parse(Container &i, broadcast_distribution_table &v){
	auto start = i.begin(); auto end = i.end();
	broadcast_distribution_table_grammar<decltype(start)> grammar;
	return boost::spirit::qi::parse(start, end, grammar, v);
}

}}}

#endif /* SRC_BACNET_BVLL_BROADCAST_DISTRIBUTION_TABLE_HPP_ */
