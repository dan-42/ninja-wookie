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

#ifndef NINJA_WOOKIE_GRAMMAR_HPP
#define NINJA_WOOKIE_GRAMMAR_HPP

#include <mapbox/boost_spirit_qi.hpp>
#include <mapbox/boost_spirit_karma.hpp>


#include <iostream>
#include <iomanip>
#include <vector>
#include <string>


//#include <boost/variant.hpp>


#include <bacnet/bvll/common/bacnet_ip_address.hpp>
#include <bacnet/bvll/common/foreign_device_table_entry.hpp>
#include <bacnet/bvll/common/foreign_device_table.hpp>
#include <bacnet/bvll/common/broadcast_distribution_table_entry.hpp>
#include <bacnet/bvll/common/broadcast_distribution_table.hpp>

#include <bacnet/bvll/frame/bvlc_result.hpp>
#include <bacnet/bvll/frame/read_broadcast_distribution_table_ack.hpp>
#include <bacnet/bvll/frame/read_broadcast_distribution_table.hpp>
#include <bacnet/bvll/frame/write_broadcast_distribution_table.hpp>
#include <bacnet/bvll/frame/forwarded_npdu.hpp>
#include <bacnet/bvll/frame/register_foreign_device.hpp>
#include <bacnet/bvll/frame/original_broadcast_npdu.hpp>
#include <bacnet/bvll/frame/original_unicast_npdu.hpp>
#include <bacnet/bvll/frame/distribute_broadcast_to_network.hpp>
#include <bacnet/bvll/frame/read_foreign_device_table_ack.hpp>
#include <bacnet/bvll/frame/read_foreign_device_table.hpp>
#include <bacnet/bvll/frame/delete_foreign_device_table_entry.hpp>
#include <bacnet/bvll/frame/original_secure_bvll.hpp>
#include <bacnet/bvll/frame/raw.hpp>

#include <bacnet/bvll/frame/detail/combined.hpp>

#include <bacnet/bvll/result_code.hpp>
#include <bacnet/bvll/type.hpp>
#include <bacnet/bvll/function.hpp>




namespace bacnet { namespace bvll { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using boost::phoenix::construct;
using boost::spirit::qi::_1;
using boost::spirit::qi::_2;

using namespace bacnet::bvll;
using namespace bacnet::bvll::frame;
using namespace bacnet::bvll::frame::detail::parser;




template<typename Iterator>
struct bvll_grammar : grammar<Iterator, possible_bvll_frame()> {

  rule<Iterator, possible_bvll_frame()> possible_bvll_frame_rule;


  rule<Iterator, possible_bvll_frame()> bvlc_result_rule;
  rule<Iterator, possible_bvll_frame()> write_broadcast_distribution_table_rule;
  rule<Iterator, possible_bvll_frame()> read_broadcast_distribution_table_rule;
  rule<Iterator, possible_bvll_frame()> read_broadcast_distribution_table_ack_rule;
  rule<Iterator, possible_bvll_frame()> forwarded_npdu_rule;
  rule<Iterator, possible_bvll_frame()> register_foreign_device_rule;
  rule<Iterator, possible_bvll_frame()> read_foreign_device_table_rule;
  rule<Iterator, possible_bvll_frame()> read_foreign_device_table_ack_rule;
  rule<Iterator, possible_bvll_frame()> delete_foreign_device_table_entry_rule;
  rule<Iterator, possible_bvll_frame()> distribute_broadcast_to_network_rule;
  rule<Iterator, possible_bvll_frame()> original_unicast_npdu_rule;
  rule<Iterator, possible_bvll_frame()> original_broadcast_npdu_rule;
  rule<Iterator, possible_bvll_frame()> original_secure_bvll_rule;
  rule<Iterator, possible_bvll_frame()> raw_rule;


  bvlc_result_grammar<Iterator> bvlc_result_grammar_;
  write_broadcast_distribution_table_grammar<Iterator> write_broadcast_distribution_table_grammar_;
  read_broadcast_distribution_table_grammar<Iterator> read_broadcast_distribution_table_grammar_;
  read_broadcast_distribution_table_ack_grammar<Iterator> read_broadcast_distribution_table_ack_grammar_;
  forwarded_npdu_grammar<Iterator> forwarded_npdu_grammar_;
  register_foreign_device_grammar<Iterator> register_foreign_device_grammar_;
  read_foreign_device_table_grammar<Iterator> read_foreign_device_table_grammar_;
  read_foreign_device_table_ack_grammar<Iterator> read_foreign_device_table_ack_grammar_;
  delete_foreign_device_table_entry_grammar<Iterator> delete_foreign_device_table_entry_grammar_;
  distribute_broadcast_to_network_grammar<Iterator> distribute_broadcast_to_network_grammar_;
  original_unicast_npdu_grammar<Iterator> original_unicast_npdu_grammar_;
  original_broadcast_npdu_grammar<Iterator> original_broadcast_npdu_grammar_;
  original_secure_bvll_grammar<Iterator> original_secure_bvll_grammar_;
  raw_grammar<Iterator> raw_grammar_;



  bvll_grammar() : bvll_grammar::base_type(possible_bvll_frame_rule) {




    //bvll_frame_rule = type_rule > function_rule > length_rule >  payload_rule;
    possible_bvll_frame_rule = ( byte_(base_type(type::bvll_bacnet_ip_v4)) >
                                 (
                                       	write_broadcast_distribution_table_rule
                                     |	read_broadcast_distribution_table_rule
                                     |	read_broadcast_distribution_table_ack_rule
                                     |	forwarded_npdu_rule
                                     |	register_foreign_device_rule
                                     |	read_foreign_device_table_rule
                                     |	read_foreign_device_table_ack_rule
                                     |	delete_foreign_device_table_entry_rule
                                     |	distribute_broadcast_to_network_rule
                                     |	original_unicast_npdu_rule
                                     |	original_broadcast_npdu_rule
                                     |	original_secure_bvll_rule
                                     |  bvlc_result_rule
                                 ))  | ( (!byte_(base_type(type::bvll_bacnet_ip_v4))) > raw_rule ); //xxx first byte is missing, when do ing this!


    bvlc_result_rule = (
        byte_(base_type(function::bvlc_result))
        > omit[big_word]
        > bvlc_result_grammar_
    );

    write_broadcast_distribution_table_rule = (
        byte_(base_type(function::write_broadcast_distribution_table))
        > omit[big_word]
        > write_broadcast_distribution_table_grammar_
    );


    read_broadcast_distribution_table_rule = (
        byte_(base_type(function::read_broadcast_distribution_table))
        > omit[big_word]
        > read_broadcast_distribution_table_grammar_
    );

    read_broadcast_distribution_table_ack_rule = (
        byte_(base_type(function::read_broadcast_distribution_table_ack))
        > omit[big_word]
        > read_broadcast_distribution_table_ack_grammar_
    );

    forwarded_npdu_rule = (
        byte_(base_type(function::forwarded_npdu))
        > omit[big_word]
        > forwarded_npdu_grammar_
    );

    register_foreign_device_rule = (
        byte_(base_type(function::register_foreign_device))
        > omit[big_word]
        > register_foreign_device_grammar_
    );

    read_foreign_device_table_rule = (
        byte_(base_type(function::read_foreign_device_table))
        > omit[big_word]
        > read_foreign_device_table_grammar_
    );


    read_foreign_device_table_ack_rule = (
        byte_(base_type(function::read_foreign_device_table_ack))
        > omit[big_word]
        > read_foreign_device_table_ack_grammar_
    );


    delete_foreign_device_table_entry_rule = (
        byte_(base_type(function::delete_foreign_device_table_entry))
        > omit[big_word]
        > delete_foreign_device_table_entry_grammar_
    );

    distribute_broadcast_to_network_rule = (
        byte_(base_type(function::distribute_broadcast_to_network))
        > omit[big_word]
        > distribute_broadcast_to_network_grammar_
    );

    original_unicast_npdu_rule = (
        byte_(base_type(function::original_unicast_npdu))
        > omit[big_word]
        > original_unicast_npdu_grammar_
    );

    original_broadcast_npdu_rule = (
        byte_(base_type(function::original_broadcast_npdu))
        > omit[big_word]
        > original_broadcast_npdu_grammar_
    );

    original_secure_bvll_rule = (
        byte_(base_type(function::original_secure_bvll))
        > omit[big_word]
        > original_secure_bvll_grammar_
    );

    raw_rule = (
        raw_grammar_
    );


    bvlc_result_rule.name("bvlc_result_rule");
    write_broadcast_distribution_table_rule.name("write_broadcast_distribution_table_rule");
    read_broadcast_distribution_table_ack_rule.name("read_broadcast_distribution_table_ack_rule");
    forwarded_npdu_rule.name("forwarded_npdu_rule");
    register_foreign_device_rule.name("register_foreign_device_rule");
    distribute_broadcast_to_network_rule.name("distribute_broadcast_to_network_rule");
    original_unicast_npdu_rule.name("original_unicast_npdu_rule");
    original_broadcast_npdu_rule.name("original_broadcast_npdu_rule");
    raw_rule.name("raw_rule");

//
/*
		debug(bvlc_result_rule);
		debug(write_broadcast_distribution_table_rule);
		debug(read_broadcast_distribution_table_ack_rule);
		debug(forwarded_npdu_rule);
		debug(register_foreign_device_rule);
		debug(distribute_broadcast_to_network_rule);
		debug(original_unicast_npdu_rule);
		debug(original_broadcast_npdu_rule);
// */
  };
};

}}}




/////////////////////////////GENERATOR////////////////////////////

namespace boost { namespace spirit { namespace traits {
template <>
struct transform_attribute<bacnet::bvll::frame::possible_bvll_frame const, bacnet::bvll::frame::original_broadcast_npdu, boost::spirit::karma::domain>
{
  typedef bacnet::bvll::frame::original_broadcast_npdu type;
  //static bacnet::bvll::frame::original_broadcast_npdu pre(bacnet::bvll::frame::possible_bvll_frame const& d) { return boost::get<type>(d); }
  static bacnet::bvll::frame::original_broadcast_npdu pre(bacnet::bvll::frame::possible_bvll_frame const& d) { return mapbox::util::get<type>(d); }
};
}}}



namespace bacnet { namespace bvll { namespace generator {

using namespace ::boost::spirit;
using namespace ::boost::spirit::karma;
using boost::phoenix::construct;


using namespace bacnet::bvll;
using namespace bacnet::bvll::frame;
using namespace bacnet::bvll::frame::detail::generator;


template<typename Iterator>
struct bvll_grammar : grammar<Iterator, possible_bvll_frame()> {

  static constexpr uint32_t frame_size_offset = 4;

  rule<Iterator, possible_bvll_frame()> possible_bvll_frame_rule;

  rule<Iterator, original_broadcast_npdu()> original_broadcast_npdu_rule;
  rule<Iterator, original_unicast_npdu()> original_unicast_npdu_rule;

  original_broadcast_npdu_grammar<Iterator> original_broadcast_npdu_grammar_;
  original_unicast_npdu_grammar<Iterator> original_unicast_npdu_grammar_;


  bvll_grammar(const uint32_t &size) : bvll_grammar::base_type(possible_bvll_frame_rule), size_(size) {
    size_ += frame_size_offset;
    possible_bvll_frame_rule =  original_broadcast_npdu_rule | original_unicast_npdu_rule;

    original_broadcast_npdu_rule    = byte_(base_type(type::bvll_bacnet_ip_v4))
                                   <<	byte_(base_type(function::original_broadcast_npdu))
                                   << big_word[_1 = boost::phoenix::ref(size_)]
                                   << original_broadcast_npdu_grammar_;

    original_unicast_npdu_rule    = byte_(base_type(type::bvll_bacnet_ip_v4))
                                    <<	byte_(base_type(function::original_unicast_npdu))
                                    << big_word[_1 = boost::phoenix::ref(size_)]
                                    << original_unicast_npdu_grammar_;

    possible_bvll_frame_rule.name("possible_bvll_frame_rule");
    original_broadcast_npdu_rule.name("original_broadcast_npdu_rule");
    original_unicast_npdu_rule.name("original_unicast_npdu_rule");



//
 /*
		debug(possible_bvll_frame_rule);
		debug(original_broadcast_npdu_rule);
		debug(original_unicast_npdu_rule);

// */


  }

  uint32_t size_;
};

}}}


#endif //NINJA_WOOKIE_GRAMMAR_HPP
