/*
 * address_grammar.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
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
