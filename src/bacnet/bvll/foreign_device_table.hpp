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


#ifndef SRC_BACNET_BVLL_FOREIGN_DEVICE_TABLE_HPP_
#define SRC_BACNET_BVLL_FOREIGN_DEVICE_TABLE_HPP_

#include <boost/fusion/include/define_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/foreign_device_table_entry.hpp>

// xxx put it into a Fusion struct as well?
namespace bacnet { namespace bvll {
typedef std::vector<bacnet::bvll::foreign_device_table_entry> foreign_device_table;
}}

namespace bacnet { namespace bvll { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll;

template<typename Iterator>
struct foreign_device_table_grammar : grammar<Iterator, foreign_device_table()> {

	rule<Iterator, foreign_device_table()> foreign_device_table_rule;
	rule<Iterator, foreign_device_table_entry()> foreign_device_table_entry_rule;
	foreign_device_table_entry_grammar<Iterator> foreign_device_table_entry_grammar_;

	foreign_device_table_grammar() : foreign_device_table_grammar::base_type(foreign_device_table_rule) {

		foreign_device_table_rule = *foreign_device_table_entry_rule;
		foreign_device_table_entry_rule = foreign_device_table_entry_grammar_;

		foreign_device_table_rule.name("foreign_device_table");
		foreign_device_table_entry_rule.name("foreign_device_table_entry_rule");
	}
};




template<typename Container>
bool generate(Container &c, foreign_device_table &v) {
	std::back_insert_iterator<Container> sink(c);
	bacnet::bvll::generator::foreign_device_table_grammar<decltype(sink)> g;
	return boost::spirit::karma::generate(sink, g, v);
}

}}}

namespace bacnet { namespace bvll { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll;

template<typename Iterator>
struct foreign_device_table_grammar : grammar<Iterator, foreign_device_table()> {

	rule<Iterator, foreign_device_table()> foreign_device_table_rule;
	rule<Iterator, foreign_device_table_entry()> foreign_device_table_entry_rule;
	foreign_device_table_entry_grammar<Iterator> foreign_device_table_entry_grammar_;

	foreign_device_table_grammar() : foreign_device_table_grammar::base_type(foreign_device_table_rule) {

		foreign_device_table_rule = *foreign_device_table_entry_rule;
		foreign_device_table_entry_rule = foreign_device_table_entry_grammar_;


		foreign_device_table_rule.name("foreign_device_table");
		foreign_device_table_entry_rule.name("foreign_device_table_entry_rule");
	}
};

template<typename Container>
bool parse(Container &i, foreign_device_table &v){
	auto start = i.begin(); auto end = i.end();
	foreign_device_table_grammar<decltype(start)> grammar;
	return boost::spirit::qi::parse(start, end, grammar, v);
}

}}}


#endif /* SRC_BACNET_BVLL_FOREIGN_DEVICE_TABLE_HPP_ */
