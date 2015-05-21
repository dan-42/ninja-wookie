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


#ifndef SRC_BACNET_BVLL_DELET_FOREIGN_DEVICE_TABLE_ENTRY_HPP_
#define SRC_BACNET_BVLL_DELET_FOREIGN_DEVICE_TABLE_ENTRY_HPP_


#include <boost/fusion/include/define_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>


#include <bacnet/bvll/bacnet_ip_address.hpp>
#include <bacnet/detail/common/types.hpp>


BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),delete_foreign_device_table_entry,
	(bacnet::bvll::bvlc::bacnet_ip_address, address_to_delete)
	(bacnet::unused_type, unused)
)

namespace bacnet { namespace bvll { namespace frame { namespace generator {

using namespace ::boost::spirit;
using namespace ::boost::spirit::karma;
using namespace bacnet::bvll::bvlc;
using namespace bacnet::bvll::bvlc::generator;

template<typename Iterator>
struct delete_foreign_device_table_enry_grammar : grammar<Iterator, delete_foreign_device_table_enry()> {


	rule<Iterator, delete_foreign_device_table_enry()> delete_foreign_device_table_enry_rule;
	rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;

        bacnet_ip_address_grammar<Iterator> bacnet_ip_address_grammar_;

	delete_foreign_device_table_enry_grammar() : delete_foreign_device_table_enry_grammar::base_type(delete_foreign_device_table_enry_rule) {

		delete_foreign_device_table_enry_rule = bacnet_ip_address_rule;
  		bacnet_ip_address_rule = bacnet_ip_address_grammar_;

		delete_foreign_device_table_enry_rule.name("delete_foreign_device_table_enry_rule");
		bacnet_ip_address_rule.name("bacnet_ip_address_rule");
	}
};

}}}}


namespace bacnet { namespace bvll { namespace frame { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll::bvlc;
using namespace bacnet::bvll::bvlc;
using namespace bacnet::bvll::bvlc::parser;

template<typename Iterator>
struct delete_foreign_device_table_enry_grammar : grammar<Iterator, delete_foreign_device_table_enry()> {


	rule<Iterator, delete_foreign_device_table_enry()> delete_foreign_device_table_enry_rule;
	rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;

        bacnet_ip_address_grammar<Iterator> bacnet_ip_address_grammar_;

	delete_foreign_device_table_enry_grammar() : delete_foreign_device_table_enry_grammar::base_type(delete_foreign_device_table_enry_rule) {

		delete_foreign_device_table_enry_rule = bacnet_ip_address_rule >> attr(0);
  		bacnet_ip_address_rule = bacnet_ip_address_grammar_;

		delete_foreign_device_table_enry_rule.name("delete_foreign_device_table_enry_rule");
		bacnet_ip_address_rule.name("bacnet_ip_address_rule");
	}
};


}}}}

#endif /* SRC_BACNET_BVLL_DELET_FOREIGN_DEVICE_TABLE_ENTRY_HPP_ */
