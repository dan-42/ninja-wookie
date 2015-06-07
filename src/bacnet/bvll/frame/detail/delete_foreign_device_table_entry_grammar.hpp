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

#ifndef SRC_BACNET_BVLL_DELET_FOREIGN_DEVICE_TABLE_ENTRY_GRAMMAR_HPP_
#define SRC_BACNET_BVLL_DELET_FOREIGN_DEVICE_TABLE_ENTRY_GRAMMAR_HPP_

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/frame/delete_foreign_device_table_entry.hpp>
#include <bacnet/bvll/bacnet_ip_address.hpp>
#include <bacnet/detail/common/types.hpp>
#include <util/boost/spirit/unused_type.hpp>

namespace bacnet { namespace bvll { namespace frame { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll;
using namespace bacnet::bvll::generator;

template<typename Iterator>
struct delete_foreign_device_table_entry_grammar : grammar<Iterator, delete_foreign_device_table_entry()> {


  rule<Iterator, delete_foreign_device_table_entry()> delete_foreign_device_table_entry_rule;
  rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;

  bacnet_ip_address_grammar<Iterator> bacnet_ip_address_grammar_;
  unused_grammar<Iterator> unused_grammar_;

  delete_foreign_device_table_entry_grammar() : delete_foreign_device_table_entry_grammar::base_type(
      delete_foreign_device_table_entry_rule) {

    delete_foreign_device_table_entry_rule = bacnet_ip_address_rule << unused_grammar_;
    bacnet_ip_address_rule = bacnet_ip_address_grammar_;

    delete_foreign_device_table_entry_rule.name("delete_foreign_device_table_entry_rule");
    bacnet_ip_address_rule.name("bacnet_ip_address_rule");
  }
};


}}}}}


namespace bacnet { namespace bvll { namespace frame { namespace detail { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll;
using namespace bacnet::bvll::parser;


template<typename Iterator>
struct delete_foreign_device_table_entry_grammar : grammar<Iterator, delete_foreign_device_table_entry()> {


  rule<Iterator, delete_foreign_device_table_entry()> delete_foreign_device_table_entry_rule;
  rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;

  bacnet_ip_address_grammar<Iterator> bacnet_ip_address_grammar_;
  unused_grammar<Iterator> unused_grammar_;

  delete_foreign_device_table_entry_grammar() : delete_foreign_device_table_entry_grammar::base_type(
      delete_foreign_device_table_entry_rule) {

    delete_foreign_device_table_entry_rule = bacnet_ip_address_rule >> unused_grammar_;
    bacnet_ip_address_rule = bacnet_ip_address_grammar_;

    delete_foreign_device_table_entry_rule.name("delete_foreign_device_table_entry_rule");
    bacnet_ip_address_rule.name("bacnet_ip_address_rule");
  }
};


}}}}}

#endif /* SRC_BACNET_BVLL_DELET_FOREIGN_DEVICE_TABLE_ENTRY_GRAMMAR_HPP_ */
