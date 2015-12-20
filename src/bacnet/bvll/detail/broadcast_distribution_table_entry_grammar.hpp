#ifndef NINJA_WOOKIE_BACNET_BVLL_DETAIL_BROADCAST_DISTRIBUTION_TABLE_ENTRY_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_BVLL_DETAIL_BROADCAST_DISTRIBUTION_TABLE_ENTRY_GRAMMAR_HPP

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



#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/bacnet_ip_address.hpp>
#include <bacnet/bvll/detail/bacnet_ip_address_grammar.hpp>

extern template struct bacnet::bvll::detail::generator::bacnet_ip_address_grammar<bacnet::generate_iterator>;
extern template struct bacnet::bvll::detail::parser::bacnet_ip_address_grammar<bacnet::parse_iterator>;

namespace bacnet { namespace bvll { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll;


template<typename Iterator>
struct broadcast_distribution_table_entry_grammar : grammar<Iterator, broadcast_distribution_table_entry()> {


  rule<Iterator, broadcast_distribution_table_entry()> broadcast_distribution_table_entry_rule;
  rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
  rule<Iterator, uint32_t()> broadcast_distribution_mask_rule;

  bacnet_ip_address_grammar<Iterator> bacnet_ip_address_grammar_;

  broadcast_distribution_table_entry_grammar() : broadcast_distribution_table_entry_grammar::base_type(broadcast_distribution_table_entry_rule) {

    broadcast_distribution_table_entry_rule = bacnet_ip_address_rule << broadcast_distribution_mask_rule;

    bacnet_ip_address_rule = bacnet_ip_address_grammar_;
    broadcast_distribution_mask_rule = big_word;

    broadcast_distribution_table_entry_rule.name("broadcast_distribution_table_entry_rule");
    bacnet_ip_address_rule.name("bacnet_ip_address_rule");
    broadcast_distribution_mask_rule.name("broadcast_distribution_mask_rule");
  }
};


}}}}


namespace bacnet { namespace bvll { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll;


template<typename Iterator>
struct broadcast_distribution_table_entry_grammar : grammar<Iterator, broadcast_distribution_table_entry()> {


  rule<Iterator, broadcast_distribution_table_entry()> broadcast_distribution_table_entry_rule;
  rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
  rule<Iterator, uint32_t()> broadcast_distribution_mask_rule;

  bacnet_ip_address_grammar<Iterator> bacnet_ip_address_grammar_;

  broadcast_distribution_table_entry_grammar() : broadcast_distribution_table_entry_grammar::base_type(broadcast_distribution_table_entry_rule) {


    broadcast_distribution_table_entry_rule = bacnet_ip_address_rule > broadcast_distribution_mask_rule;

    bacnet_ip_address_rule = bacnet_ip_address_grammar_;
    broadcast_distribution_mask_rule = big_word;

    broadcast_distribution_table_entry_rule.name("broadcast_distribution_table_entry_rule");
    bacnet_ip_address_rule.name("bacnet_ip_address_rule");
    broadcast_distribution_mask_rule.name("broadcast_distribution_mask_rule");
  }
};


}}}}

#endif //NINJA_WOOKIE_BACNET_BVLL_DETAIL_BROADCAST_DISTRIBUTION_TABLE_ENTRY_GRAMMAR_HPP
