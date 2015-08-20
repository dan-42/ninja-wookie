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

#ifndef SRC_BACNET_NPDU_DETAIL_ADDRESS_GRAMMAR_HPP_
#define SRC_BACNET_NPDU_DETAIL_ADDRESS_GRAMMAR_HPP_


#include <cstdint>

#include <boost/spirit/home/qi.hpp>
#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>

#include <bacnet/npdu/address.hpp>


namespace bacnet { namespace  npdu {  namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using namespace bacnet::npdu::detail;

using boost::spirit::qi::rule;
using boost::spirit::qi::_1;

template<typename Iterator>
struct address_grammar : grammar<Iterator, address() > {

  rule<Iterator, address()>             address_rule;
  rule<Iterator, uint16_t()>            network_number_rule;
  rule <Iterator>                       length_rule;
  rule<Iterator, bacnet::binary_data()> binary_address_rule;

  address_grammar() : address_grammar::base_type(address_rule) {

    address_rule = (network_number_rule >> length_rule >> binary_address_rule);

    network_number_rule = big_word;
    length_rule = byte_[ref(length) = _1];
    binary_address_rule = repeat(ref(length))[byte_];

    address_rule.name("address_rule");
    network_number_rule.name("network_number_rule");
    binary_address_rule.name("binary_address_rule");

    //debug(address_rule);
    //debug(network_number_rule);
    //debug(binary_address_rule);
  }

  uint8_t length = 0;
};

}}}}



namespace bacnet { namespace  npdu { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;

using namespace bacnet::npdu::detail;
using namespace bacnet::npdu;

using boost::spirit::karma::rule;
using boost::spirit::karma::_1;

template<typename Iterator>
struct address_grammar : grammar<Iterator, address() > {

  rule<Iterator, address()>             address_rule;
  rule<Iterator, uint16_t()>            network_number_rule;
  rule<Iterator, bacnet::binary_data()> length_rule;
  rule<Iterator, bacnet::binary_data()> binary_address_rule;

  address_grammar() : address_grammar::base_type(address_rule) {

    address_rule = (network_number_rule <<  binary_address_rule);

    network_number_rule = big_word;
    length_rule = attr_cast(byte_);
    binary_address_rule =  length_rule[_1 = _val] << (repeat[byte_])[_1 = _val];

    address_rule.name("address_rule");
    network_number_rule.name("network_number_rule");
    binary_address_rule.name("binary_address_rule");

    //debug(address_rule);
    //debug(network_number_rule);
    //debug(binary_address_rule);
  }
};


}}}}

#endif /* SRC_BACNET_NPDU_DETAIL_ADDRESS_GRAMMAR_HPP_ */
