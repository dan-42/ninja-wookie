/*
 * foreign_device_table_entry.hpp
 *
 *  Created on: May 14, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_BVLL_FOREIGN_DEVICE_TABLE_ENTRY_HPP_
#define SRC_BACNET_BVLL_FOREIGN_DEVICE_TABLE_ENTRY_HPP_


#include <boost/fusion/include/define_struct.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/bacnet_ip_address.hpp>

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(bvlc),foreign_device_table_entry,
	(bacnet::bvll::bvlc::bacnet_ip_address, address)
	(uint16_t, time_to_live_in_sec)
	(uint16_t, time_to_purge_in_sec)
)


namespace bacnet { namespace bvll { namespace bvlc { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll::bvlc;

template<typename Iterator>
struct foreign_device_table_entry_grammar : grammar<Iterator, foreign_device_table_entry()> {

	bacnet_ip_address_grammar<Iterator> bacnet_ip_address_grammar_;

	rule<Iterator, foreign_device_table_entry()> foreign_device_table_entry_rule;
	rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
	rule<Iterator, uint16_t()> time_to_live_in_sec_rule;
	rule<Iterator, uint16_t()> time_to_purge_in_sec_rule;

	foreign_device_table_entry_grammar() : foreign_device_table_entry_grammar::base_type(foreign_device_table_entry_rule) {

		foreign_device_table_entry_rule = bacnet_ip_address_rule << time_to_live_in_sec_rule << time_to_purge_in_sec_rule;

		bacnet_ip_address_rule = bacnet_ip_address_grammar_;
		time_to_live_in_sec_rule = big_word;
		time_to_purge_in_sec_rule = big_word;


		foreign_device_table_entry_rule.name("foreign_device_table_entry_rule");
		bacnet_ip_address_rule.name("bacnet_ip_address_rule");
		time_to_live_in_sec_rule.name("time_to_live_in_sec_rule");
		time_to_purge_in_sec_rule.name("time_to_purge_in_sec_rule");
	}
};


template<typename Container>
bool generate(Container &c, foreign_device_table_entry &v) {
	std::back_insert_iterator<Container> sink(c);
	bacnet::bvll::bvlc::generator::foreign_device_table_entry_grammar<decltype(sink)> g;
	return boost::spirit::karma::generate(sink, g, v);
}

}}}}


namespace bacnet { namespace bvll { namespace bvlc { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll::bvlc;

template<typename Iterator>
struct foreign_device_table_entry_grammar : grammar<Iterator, foreign_device_table_entry()> {

	bacnet_ip_address_grammar<Iterator> bacnet_ip_address_grammar_;

	rule<Iterator, foreign_device_table_entry()> foreign_device_table_entry_rule;
	rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
	rule<Iterator, uint16_t()> time_to_live_in_sec_rule;
	rule<Iterator, uint16_t()> time_to_purge_in_sec_rule;

	foreign_device_table_entry_grammar() : foreign_device_table_entry_grammar::base_type(foreign_device_table_entry_rule) {

		foreign_device_table_entry_rule = bacnet_ip_address_rule > time_to_live_in_sec_rule > time_to_purge_in_sec_rule;

		bacnet_ip_address_rule = bacnet_ip_address_grammar_;
		time_to_live_in_sec_rule = big_word;
		time_to_purge_in_sec_rule = big_word;


		foreign_device_table_entry_rule.name("foreign_device_table_entry_rule");
		bacnet_ip_address_rule.name("bacnet_ip_address_rule");
		time_to_live_in_sec_rule.name("time_to_live_in_sec_rule");
		time_to_purge_in_sec_rule.name("time_to_purge_in_sec_rule");
	}
};


template<typename Container>
bool parse(Container &i, foreign_device_table_entry &v){
	auto start = i.begin(); auto end = i.end();
	foreign_device_table_entry_grammar<decltype(start)> grammar;
	return boost::spirit::qi::parse(start, end, grammar, v);
}

}}}}



#endif /* SRC_BACNET_BVLL_FOREIGN_DEVICE_TABLE_ENTRY_HPP_ */
