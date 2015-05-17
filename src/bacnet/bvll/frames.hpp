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
#include <boost/spirit/repository/include/qi_advance.hpp>

#include <boost/spirit/include/karma.hpp>

#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_stl.hpp>
#include <boost/phoenix/bind/bind_member_variable.hpp>









#include <bacnet/bvll/bacnet_ip_address.hpp>
#include <bacnet/bvll/foreign_device_table_entry.hpp>
#include <bacnet/bvll/foreign_device_table.hpp>
#include <bacnet/bvll/broadcast_distribution_table_entry.hpp>
#include <bacnet/bvll/broadcast_distribution_table.hpp>

#include <bacnet/bvll/frame/bvlc_result.hpp>
#include <bacnet/bvll/frame/read_broadcast_distribution_table_ack.hpp>
#include <bacnet/bvll/frame/write_broadcast_distribution_table.hpp>
#include <bacnet/bvll/frame/forwarded_npdu.hpp>
#include <bacnet/bvll/frame/register_foreign_device.hpp>
#include <bacnet/bvll/frame/original_broadcast_npdu.hpp>
#include <bacnet/bvll/frame/original_unicast_npdu.hpp>
#include <bacnet/bvll/frame/distribute_broadcast_to_network.hpp>


#include <bacnet/bvll/bvlc/result_code.hpp>

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

}}}








/* not working
BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),read_broadcast_distribution_table,
)*/

/* not workin :0
BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),read_foreign_device_table,
)
*/



/*
BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),read_foreign_device_table_ack,
	(bacnet::bvll::bvlc::foreign_device_table, foreign_device_table_)
)

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),delete_foreign_device_table_entry,
	(bacnet::bvll::bvlc::bacnet_ip_address, address_to_delete)
)

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),original_secure_bvll,
	(std::string, security_wrapped_data)
)
*/

namespace bacnet { namespace bvll { namespace frame {
 typedef boost::variant<
			bvlc_result,
			write_broadcast_distribution_table,
			//read_broadcast_distribution_table,
			read_broadcast_distribution_table_ack,
			forwarded_npdu,
			register_foreign_device,
			//read_foreign_device_table,
			//read_foreign_device_table_ack,
			//delete_foreign_device_table_entry,
			distribute_broadcast_to_network,
			original_unicast_npdu,
			original_broadcast_npdu
			//original_secure_bvll
		 > possible_bvll_frame;
}}}



//xx do I need this?
/*
BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),bvll_frame,
	(bacnet::bvll::bvlc::type, type)
	(bacnet::bvll::bvlc::function, function)
	(uint16_t, length)
	(bacnet::bvll::frame::possible_bvll_frame, payload)
)
*/

namespace bacnet { namespace bvll { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using boost::phoenix::construct;
using namespace bacnet::bvll::bvlc;
using namespace bacnet::bvll::frame;
using namespace bacnet::bvll::frame::parser;



template<typename Iterator>
struct bvll_grammar : grammar<Iterator, possible_bvll_frame()> {

	rule<Iterator, possible_bvll_frame()> possible_bvll_frame_rule;
	//rule<Iterator, type()> type_rule;
	//rule<Iterator, function()> function_rule;
	//rule<Iterator, uint16_t()> length_rule;


	rule<Iterator, bvlc_result()> bvlc_result_rule;
	rule<Iterator, write_broadcast_distribution_table()> write_broadcast_distribution_table_rule;
//	rule<Iterator, read_broadcast_distribution_table()> read_broadcast_distribution_table_rule;
	rule<Iterator, read_broadcast_distribution_table_ack()> read_broadcast_distribution_table_ack_rule;
	rule<Iterator, forwarded_npdu()> forwarded_npdu_rule;
	rule<Iterator, register_foreign_device()> register_foreign_device_rule;
//	rule<Iterator, read_foreign_device_table()> read_foreign_device_table_rule;
//	rule<Iterator, read_foreign_device_table_ack()> read_foreign_device_table_ack_rule;
//	rule<Iterator, delete_foreign_device_table_entry()> delete_foreign_device_table_entry_rule;
	rule<Iterator, distribute_broadcast_to_network()> distribute_broadcast_to_network_rule;
	rule<Iterator, original_unicast_npdu()> original_unicast_npdu_rule;
	rule<Iterator, original_broadcast_npdu()> original_broadcast_npdu_rule;
//	rule<Iterator, original_secure_bvll()> original_secure_bvll_rule;



	bvll_grammar() : bvll_grammar::base_type(possible_bvll_frame_rule) {


		bvlc_result_grammar<Iterator> bvlc_result_grammar;
		write_broadcast_distribution_table_grammar<Iterator> write_broadcast_distribution_table_grammar;
		//read_broadcast_distribution_table_grammar<Iterator> read_broadcast_distribution_table_grammar;
		read_broadcast_distribution_table_ack_grammar<Iterator> read_broadcast_distribution_table_ack_grammar;
		forwarded_npdu_grammar<Iterator> forwarded_npdu_grammar;
		register_foreign_device_grammar<Iterator> register_foreign_device_grammar;
		//read_foreign_device_table_grammar<Iterator> read_foreign_device_table_grammar;
		//read_foreign_device_table_ack_grammar<Iterator> read_foreign_device_table_ack_grammar;
//		delete_foreign_device_table_entry_grammar<Iterator> delete_foreign_device_table_entry_grammar;
		distribute_broadcast_to_network_grammar<Iterator> distribute_broadcast_to_network_grammar;
		original_unicast_npdu_grammar<Iterator> original_unicast_npdu_grammar;
		original_broadcast_npdu_grammar<Iterator> original_broadcast_npdu_grammar;
//		original_secure_bvl_grammar<Iterator> original_secure_bvl_grammar;



		//bvll_frame_rule = type_rule > function_rule > length_rule >  payload_rule;
		possible_bvll_frame_rule = byte_(base_type(type::bvll_bacnet_ip_v4)) >
						(
								bvlc_result_rule
							|	write_broadcast_distribution_table_rule
						//	|	read_broadcast_distribution_table_rule
							|	read_broadcast_distribution_table_ack_rule
							|	forwarded_npdu_rule
							|	register_foreign_device_rule
						//	|	read_foreign_device_table_rule
						//	|	read_foreign_device_table_ack_rule
						//	|	delete_foreign_device_table_entry_rule
							|	distribute_broadcast_to_network_rule
							|	original_unicast_npdu_rule
							|	original_broadcast_npdu_rule
						//	|	original_secure_bvll_rule
						);


		bvlc_result_rule = (
							   byte_(base_type(function::bvlc_result))
							  > big_word
							  > bvlc_result_grammar
						   )[_val = boost::spirit::_2];

		write_broadcast_distribution_table_rule = (
							   byte_(base_type(function::write_broadcast_distribution_table))
							  > big_word
							  > write_broadcast_distribution_table_grammar
						   )[_val = boost::spirit::_2];

		/*
		read_broadcast_distribution_table_rule = (
							   byte_(base_type(function::read_broadcast_distribution_table))
							  > big_word
							  > read_broadcast_distribution_table_grammar
						   )[_val = boost::spirit::_2];
		*/

		read_broadcast_distribution_table_ack_rule = (
							   byte_(base_type(function::read_broadcast_distribution_table_ack))
							  > big_word
							  > read_broadcast_distribution_table_ack_grammar
						   )[_val = boost::spirit::_2];

		forwarded_npdu_rule = (
							   byte_(base_type(function::forwarded_npdu))
							  > big_word
							  > forwarded_npdu_grammar
						   )[_val = boost::spirit::_2];

		register_foreign_device_rule = (
							   byte_(base_type(function::register_foreign_device))
							  > big_word
							  > register_foreign_device_grammar
						   )[_val = boost::spirit::_2];
		/*
		read_foreign_device_table_rule = (
							   byte_(base_type(function::read_foreign_device_table))
							  > big_word
							  > read_foreign_device_table_grammar
						   )[_val = boost::spirit::_2];
		*/
		/*
		read_foreign_device_table_ack_rule = (
							   byte_(base_type(function::read_foreign_device_table_ack))
							  > big_word
							  > read_foreign_device_table_acke_grammar
						   )[_val = boost::spirit::_2];
		*/
		/*
		delete_foreign_device_table_entry_rule = (
							   byte_(base_type(function::delete_foreign_device_table_entry))
							  > big_word
							  > delete_foreign_device_table_entry_grammar
						   )[_val = boost::spirit::_2];
		*/
		distribute_broadcast_to_network_rule = (
							   byte_(base_type(function::distribute_broadcast_to_network))
							  > big_word
							  > distribute_broadcast_to_network_grammar
						   )[_val = boost::spirit::_2];

		original_unicast_npdu_rule = (
							   byte_(base_type(function::original_unicast_npdu))
							  > big_word
							  > original_unicast_npdu_grammar
						   )[_val = boost::spirit::_2];

		original_broadcast_npdu_rule = (
							   byte_(base_type(function::original_broadcast_npdu))
							  > big_word
							  > original_broadcast_npdu_grammar
						   )[_val = boost::spirit::_2];
		/*
		original_secure_bvll_rule = (
							   byte_(base_type(function::original_secure_bvll))
							  > big_word
							  > original_secure_bvll_grammar
						   )[_val = boost::spirit::_2];
		*/

		bvlc_result_rule.name("bvlc_result_rule");
		write_broadcast_distribution_table_rule.name("write_broadcast_distribution_table_rule");
		read_broadcast_distribution_table_ack_rule.name("read_broadcast_distribution_table_ack_rule");
		forwarded_npdu_rule.name("forwarded_npdu_rule");
		register_foreign_device_rule.name("register_foreign_device_rule");
		distribute_broadcast_to_network_rule.name("distribute_broadcast_to_network_rule");
		original_unicast_npdu_rule.name("original_unicast_npdu_rule");
		original_broadcast_npdu_rule.name("original_broadcast_npdu_rule");

/*
		debug(bvlc_result_rule);
		debug(write_broadcast_distribution_table_rule);
		debug(read_broadcast_distribution_table_ack_rule);
		debug(forwarded_npdu_rule);
		debug(register_foreign_device_rule);
		debug(distribute_broadcast_to_network_rule);
		debug(original_unicast_npdu_rule);
		debug(original_broadcast_npdu_rule);
*/



		//type_rule = byte_;
		//function_rule = byte_;
		//length_rule = big_word;
	}
};



possible_bvll_frame parse(const std::string &i){
	auto start = i.begin();
	auto end = i.end();
	possible_bvll_frame frame;
	bvll_grammar<decltype(start)> grammar;
	bool result = false;
	try {
		result = boost::spirit::qi::parse(start, end, grammar, frame);
	}
	catch(std::exception &e) {
		std::cerr << "exception: frames.hpp parse(Container &i, possible_bvll_frame &v) " << e.what() << std::endl;
	}
	return frame;

}


}}}


#endif /* SRC_BACNET_BVLL_FRAMES_HPP_ */
