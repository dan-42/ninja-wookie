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





#ifndef SRC_BACNET_BVLL_FRAMES_HPP_
#define SRC_BACNET_BVLL_FRAMES_HPP_

#include <iostream>
#include <iomanip>

#include <vector>
#include <string>

#include <boost/fusion/include/define_struct.hpp>
#include <boost/fusion/include/io.hpp>
#include <boost/fusion/include/map.hpp>
#include <boost/fusion/include/boost_tuple.hpp>

#include <boost/variant.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_io.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/bind/bind_member_variable.hpp>


#include <bacnet/bvll/bacnet_ip_address.hpp>


namespace bacnet { namespace bvll { namespace bvlc {


enum class type: uint8_t {
	bvll_bacnet_ip_v4 = 0x81
};

uint8_t base_type(const type& t){
	return static_cast<uint8_t>(t);
}

std::ostream& operator<<(std::ostream& os, const type& t) {
	switch(t){
	  case type::bvll_bacnet_ip_v4 :
		os << "bvll_bacnet_ip_v4(0x81)";
		break;
	  default:
		  os << "unknown bvlc type (0x" << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(t) << ")";
	}
	return os;
}




enum class function : uint8_t {
  bvlc_result 							= 0x00,
  write_broadcast_distribution_table 	= 0x01,
  read_broadcast_distribution_table 	= 0x02,
  read_broadcast_distribution_table_ack = 0x03,
  forwarded_npdu 						= 0x04,
  register_foreign_device				= 0x05,
  read_foreign_device_table				= 0x06,
  read_foreign_device_table_ack			= 0x07,
  delete_foreign_device_table_entry		= 0x08,
  distribute_broadcast_to_network		= 0x09,
  original_unicast_npdu					= 0x0A,
  original_broadcast_npdu				= 0x0B,
  original_secure_bvll					= 0x0C
};

uint8_t base_type(const function& f){
	return static_cast<uint8_t>(f);
}

std::ostream& operator<<(std::ostream& os, const function& f) {
	switch(f){
	  case function::bvlc_result :
		os << "bvlc_result(0x00)";
		break;
	  case function::write_broadcast_distribution_table :
	  		os << "write_broadcast_distribution_table(0x01)";
	  		break;
	  case function::read_broadcast_distribution_table :
	  		os << "read_broadcast_distribution_table(0x02)";
	  		break;
	  case function::read_broadcast_distribution_table_ack :
	  		os << "read_broadcast_distribution_table_ack(0x03)";
	  		break;
	  case function::forwarded_npdu :
	  		os << "forwarded_npdu(0x04)";
	  		break;
	  case function::register_foreign_device :
	  		os << "register_foreign_device(0x05)";
	  		break;
	  case function::read_foreign_device_table :
	  		os << "read_foreign_device_table(0x06)";
	  		break;
	  case function::read_foreign_device_table_ack :
	  		os << "read_foreign_device_table_ack(0x07)";
	  		break;
	  case function::delete_foreign_device_table_entry :
	  		os << "delete_foreign_device_table_entry(0x08)";
	  		break;
	  case function::distribute_broadcast_to_network :
	  		os << "distribute_broadcast_to_network(0x09)";
	  		break;
	  case function::original_unicast_npdu :
	  		os << "original_unicast_npdu(0x0A)";
	  		break;
	  case function::original_broadcast_npdu :
	  	  	os << "original_broadcast_npdu(0x0B)";
	  	  	break;
	  case function::original_secure_bvll :
	  	  	os << "original_secure_bvll(0x0C)";
	  	  	break;
	  default:
		  os << "unknown bvlc function (0x" << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(f) << ")";
	}
	return os;
}








enum class result_code : uint16_t {
	successful_completion					= 0x0000,
	write_broadcast_distribution_table_nak	= 0x0010,
	read_broadcast_distribution_table_nak	= 0x0020,
	register_foreign_device_nak				= 0x0030,
	read_foreign_device_table_nak			= 0x0040,
	delete_foreign_device_table_entry_nak	= 0x0050,
	distribute_broadcast_to_network_nak		= 0x0060
};

uint16_t base_type(const result_code& rc){
	return static_cast<uint16_t>(rc);
}


std::ostream& operator<<(std::ostream& os, const result_code& rc) {
	switch(rc){
	  case result_code::successful_completion :
		os << "successful_completion(0x0000)";
		break;
	  case result_code::write_broadcast_distribution_table_nak :
		os << "write_broadcast_distribution_table_nak(0x0010)";
		break;
	  case result_code::read_broadcast_distribution_table_nak :
		os << "read_broadcast_distribution_table_nak(0x0020)";
		break;
	  case result_code::register_foreign_device_nak :
		os << "register_foreign_device_nak(0x0030)";
		break;
	  case result_code::read_foreign_device_table_nak :
		os << "read_foreign_device_table_nak(0x0040)";
		break;
	  case result_code::delete_foreign_device_table_entry_nak :
		os << "delete_foreign_device_table_entry_nak(0x0050)";
		break;
	  case result_code::distribute_broadcast_to_network_nak :
		os << "distribute_broadcast_to_network_nak(0x0060)";
		break;
	  default:
		os << "unknown result_code  (0x" << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(rc) << ")";
	}
	return os;
}




}}}





BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(bvlc),broadcast_distribution_table_entry,
	(bacnet::bvll::bvlc::bacnet_ip_address, address)
	(uint32_t, broadcast_distribution_mask)
)
namespace bacnet { namespace bvll { namespace bvlc {
 typedef std::vector<bacnet::bvll::bvlc::broadcast_distribution_table_entry> broadcast_distribution_table;
}}}

namespace bacnet { namespace bvll { namespace bvlc { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll::bvlc;

template<typename Iterator>
struct broadcast_distribution_table_entry_grammar : grammar<Iterator, broadcast_distribution_table_entry> {

	rule<Iterator, broadcast_distribution_table_entry()> broadcast_distribution_table_entry_rule;
	rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
	rule<Iterator, uint32_t()> broadcast_distribution_mask_rule;

	broadcast_distribution_table_entry_grammar() : broadcast_distribution_table_entry_grammar::base_type(bacnet_ip_address_rule) {

		bacnet_ip_address_grammar<Iterator> bacnet_ip_address_grammar_;

		broadcast_distribution_table_entry_rule = bacnet_ip_address_rule < broadcast_distribution_mask_rule;

		bacnet_ip_address_rule = bacnet_ip_address_grammar_;
		broadcast_distribution_mask_rule = big_word;

		broadcast_distribution_table_entry_rule.name("broadcast_distribution_table_entry_rule");
		bacnet_ip_address_rule.name("bacnet_ip_address_rule");
		broadcast_distribution_mask_rule.name("broadcast_distribution_mask_rule");
	}
};

}}}}





BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(bvlc),foreign_device_table_entry,
	(bacnet::bvll::bvlc::bacnet_ip_address, address)
	(uint16_t, time_to_live_in_sec)
	(uint16_t, time_to_purge_in_sec)
)
namespace bacnet { namespace bvll { namespace bvlc {
 typedef std::vector<bacnet::bvll::bvlc::foreign_device_table_entry> foreign_device_table;
}}}





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
bool generate(Container c, foreign_device_table_entry &v) {
	std::back_insert_iterator<decltype(c)> sink(c);
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
bool parse(Container i, foreign_device_table_entry &v){

	auto start = i.begin();
	auto end = i.end();
	foreign_device_table_entry_grammar<decltype(start)> grammar;

	return boost::spirit::qi::parse(start, end, grammar, v);
}

}}}}

















/*
BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),bvlc_result,
	(bacnet::bvll::bvlc::result_code, result_code)
)

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),write_broadcast_distribution_table,
	(bacnet::bvll::bvlc::broadcast_distribution_table, broadcast_distribution_table_)
)

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),read_broadcast_distribution_table,

)

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),read_broadcast_distribution_table_ack,
	(bacnet::bvll::bvlc::broadcast_distribution_table, broadcast_distribution_table_)
)


BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),forwarded_npdu,
	(bacnet::bvll::bvlc::bacnet_ip_address, address_of_origin_device)
	(std::string, npdu_data_from_origin_device)
)


BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),register_foreign_device,
	(uint16_t, time_to_live_in_sec)
)


BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),read_foreign_device_table,
)


BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),read_foreign_device_table_ack,
	(bacnet::bvll::bvlc::foreign_device_table, foreign_device_table_)
)

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),delete_foreign_device_table_entry,
	(bacnet::bvll::bvlc::bacnet_ip_address, address_to_delete)
)

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),distribute_broadcast_to_network,
	(std::string, npdu_data)
)

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),original_unicast_npdu,
	(std::string, npdu_data)
)

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),original_broadcast_npdu,
	(std::string, npdu_data)
)


BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),original_secure_bvll,
	(std::string, security_wrapped_data)
)

namespace bacnet { namespace bvll { namespace frame {
 typedef boost::variant<
			bvlc_result,
			write_broadcast_distribution_table,
			read_broadcast_distribution_table,
			read_broadcast_distribution_table_ack,
			forwarded_npdu,
			register_foreign_device,
			read_foreign_device_table,
			read_foreign_device_table_ack,
			delete_foreign_device_table_entry,
			distribute_broadcast_to_network,
			original_unicast_npdu,
			original_broadcast_npdu,
			original_secure_bvll
		 > possible_bvll_frame;
}}}




BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),bvll_frame,
	(bacnet::bvll::bvlc::type, type)
	(bacnet::bvll::bvlc::function, function)
	(uint16_t, length)
	(bacnet::bvll::frame::possible_bvll_frame, payload)
)


*/

#endif /* SRC_BACNET_BVLL_FRAMES_HPP_ */
