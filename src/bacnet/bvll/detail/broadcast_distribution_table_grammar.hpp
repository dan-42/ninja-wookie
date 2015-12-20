//
// Created by dan on 20.12.15.
//

#ifndef NINJA_WOOKIE_BACNET_BVLL_DETAIL_BROADCAST_DISTRIBUTION_TABLE_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_BVLL_DETAIL_BROADCAST_DISTRIBUTION_TABLE_GRAMMAR_HPP



#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/detail/common/types.hpp>

#include <bacnet/bvll/detail/broadcast_distribution_table_entry_grammar.hpp>



namespace bacnet { namespace bvll { namespace detail  { namespace  generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll;

template<typename Iterator>
struct broadcast_distribution_table_grammar : grammar<Iterator, broadcast_distribution_table()> {

  rule<Iterator, broadcast_distribution_table()> broadcast_distribution_table_rule;
  rule<Iterator, broadcast_distribution_table_entry()> broadcast_distribution_table_entry_rule;

  broadcast_distribution_table_entry_grammar<Iterator> broadcast_distribution_table_entry_grammar_;

  broadcast_distribution_table_grammar() : broadcast_distribution_table_grammar::base_type(broadcast_distribution_table_rule) {

    broadcast_distribution_table_rule = *broadcast_distribution_table_entry_rule;
    broadcast_distribution_table_entry_rule = broadcast_distribution_table_entry_grammar_;

    broadcast_distribution_table_rule.name("broadcast_distribution_table_rule");
    broadcast_distribution_table_entry_rule.name("broadcast_distribution_table_entry_rule");
  }
};

}}}}


namespace bacnet { namespace bvll { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll;

template<typename Iterator>
struct broadcast_distribution_table_grammar : grammar<Iterator, broadcast_distribution_table()> {

  rule<Iterator, broadcast_distribution_table()> broadcast_distribution_table_rule;
  rule<Iterator, broadcast_distribution_table_entry()> broadcast_distribution_table_entry_rule;

  broadcast_distribution_table_entry_grammar<Iterator> broadcast_distribution_table_entry_grammar_;

  broadcast_distribution_table_grammar() : broadcast_distribution_table_grammar::base_type(broadcast_distribution_table_rule) {

    broadcast_distribution_table_rule = *broadcast_distribution_table_entry_rule;
    broadcast_distribution_table_entry_rule = broadcast_distribution_table_entry_grammar_;


    broadcast_distribution_table_rule.name("broadcast_distribution_table_rule");
    broadcast_distribution_table_entry_rule.name("broadcast_distribution_table_entry_rule");
  }
};


}}}}

#endif //NINJA_WOOKIE_BACNET_BVLL_DETAIL_BROADCAST_DISTRIBUTION_TABLE_GRAMMAR_HPP
