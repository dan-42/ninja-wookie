
#ifndef NINJA_WOOKIE_BACNET_BVLL_DETAIL_BACNET_IP_ADDRESS_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_BVLL_DETAIL_BACNET_IP_ADDRESS_GRAMMAR_HPP


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/bvll/bacnet_ip_address.hpp>

namespace bacnet { namespace bvll { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll;

template<typename Iterator>
struct bacnet_ip_address_grammar : grammar<Iterator, bacnet_ip_address()> {

  rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
  rule<Iterator, uint32_t()> ip_address_v4_rule;
  rule<Iterator, uint16_t()> port_rule;

  bacnet_ip_address_grammar() : bacnet_ip_address_grammar::base_type(bacnet_ip_address_rule) {

    bacnet_ip_address_rule = ip_address_v4_rule << port_rule;

    ip_address_v4_rule = big_dword;
    port_rule = big_word;

    bacnet_ip_address_rule.name("bacnet_ip_address_rule");
    ip_address_v4_rule.name("ip_address_v4_rule");
    port_rule.name("port_rule");
  }
};

}}}}


namespace bacnet { namespace bvll { namespace detail { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll;

template<typename Iterator>
struct bacnet_ip_address_grammar : grammar<Iterator, bacnet_ip_address()> {

  rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
  rule<Iterator, uint32_t()> ip_address_v4_rule;
  rule<Iterator, uint16_t()> port_rule;

  bacnet_ip_address_grammar() : bacnet_ip_address_grammar::base_type(bacnet_ip_address_rule) {

    bacnet_ip_address_rule = ip_address_v4_rule > port_rule;

    ip_address_v4_rule = big_dword;
    port_rule = big_word;

    bacnet_ip_address_rule.name("bacnet_ip_address_rule");
    ip_address_v4_rule.name("ip_address_v4_rule");
    port_rule.name("port_rule");
  }
};


}}}}


#endif //NINJA_WOOKIE_BACNET_BVLL_DETAIL_BACNET_IP_ADDRESS_GRAMMAR_HPP
