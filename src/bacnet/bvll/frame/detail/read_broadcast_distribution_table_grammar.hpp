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

#ifndef SRC_BACNET_BVLL_BVLC_READ_BROADCAST_DISTRIBUTION_TABLE_GRAMMAR_HPP_
#define SRC_BACNET_BVLL_BVLC_READ_BROADCAST_DISTRIBUTION_TABLE_GRAMMAR_HPP_


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/frame/read_broadcast_distribution_table.hpp>


namespace bacnet { namespace bvll { namespace frame { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll;

template<typename Iterator>
struct read_broadcast_distribution_table_grammar : grammar<Iterator, read_broadcast_distribution_table()> {

  rule<Iterator, read_broadcast_distribution_table()> read_broadcast_distribution_table_rule;

  read_broadcast_distribution_table_grammar()
      : read_broadcast_distribution_table_grammar::base_type(read_broadcast_distribution_table_rule) {

    read_broadcast_distribution_table_rule = eps;

    read_broadcast_distribution_table_rule.name("read_broadcast_distribution_table_rule");
  }
};


}}}}} /* namespaces */


namespace bacnet { namespace bvll { namespace frame { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll;

template<typename Iterator>
struct read_broadcast_distribution_table_grammar : grammar<Iterator, read_broadcast_distribution_table()> {

  rule<Iterator, read_broadcast_distribution_table()> read_broadcast_distribution_table_rule;

  read_broadcast_distribution_table_grammar()
      : read_broadcast_distribution_table_grammar::base_type(read_broadcast_distribution_table_rule) {

    read_broadcast_distribution_table_rule = eps;

    read_broadcast_distribution_table_rule.name("read_broadcast_distribution_table_rule");
  }
};

}}}}} /* namespaces */

#endif /* SRC_BACNET_BVLL_BVLC_READ_BROADCAST_DISTRIBUTION_TABLE_GRAMMAR_HPP_ */