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


#ifndef SRC_BACNET_BVLL_BACNET_IP_ADDRESS_HPP_
#define SRC_BACNET_BVLL_BACNET_IP_ADDRESS_HPP_

#include <boost/fusion/include/define_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>



BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(bvlc),bacnet_ip_address,
	(uint32_t, ip_address)
	(uint16_t, port)
)

namespace bacnet { namespace bvll { namespace bvlc { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll::bvlc;

template<typename Iterator>
struct bacnet_ip_address_grammar : grammar<Iterator, bacnet_ip_address()> {

	rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
	rule<Iterator, uint32_t()> ip_address_v4_rule;
	rule<Iterator, uint16_t()> port_rule;

	bacnet_ip_address_grammar() : bacnet_ip_address_grammar::base_type(bacnet_ip_address_rule) {

		bacnet_ip_address_rule = ip_address_v4_rule << port_rule;

		ip_address_v4_rule = big_dword;
		port_rule = big_word;

		bacnet_ip_address_rule.name("bacnet_ip_address_rule");
		ip_address_v4_rule.name("ip_address_v4_rule");
		port_rule.name("port_rule");
	}
};

template<typename Container>
bool generate(Container c, bacnet_ip_address &v) {
	std::back_insert_iterator<Container> sink(c);
	bacnet::bvll::bvlc::generator::bacnet_ip_address_grammar<decltype(sink)> g;
	return boost::spirit::karma::generate(sink, g, v);
}

}}}}


namespace bacnet { namespace bvll { namespace bvlc { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll::bvlc;

template<typename Iterator>
struct bacnet_ip_address_grammar : grammar<Iterator, bacnet_ip_address()> {

	rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
	rule<Iterator, uint32_t()> ip_address_v4_rule;
	rule<Iterator, uint16_t()> port_rule;

	bacnet_ip_address_grammar() : bacnet_ip_address_grammar::base_type(bacnet_ip_address_rule) {

		bacnet_ip_address_rule = ip_address_v4_rule > port_rule;

		ip_address_v4_rule = big_dword;
		port_rule = big_word;

		bacnet_ip_address_rule.name("bacnet_ip_address_rule");
		ip_address_v4_rule.name("ip_address_v4_rule");
		port_rule.name("port_rule");
	}
};


template<typename Container>
bool parse(Container &i, bacnet_ip_address &v){
	auto start = i.begin(); auto end = i.end();
	bacnet_ip_address_grammar<decltype(start)> grammar;
	return boost::spirit::qi::parse(start, end, grammar, v);
}


}}}}




#endif /* SRC_BACNET_BVLL_BACNET_IP_ADDRESS_HPP_ */
