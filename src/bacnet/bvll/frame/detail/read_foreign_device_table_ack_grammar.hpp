/*
 * read_foreign_device_table_ack.hpp
 *
 *  Created on: May 21, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_GRAMMAR_HPP_
#define SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_GRAMMAR_HPP_


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <util/boost/spirit/unused_type.hpp>
#include <bacnet/bvll/frame/read_foreign_device_table_ack.hpp>
#include <bacnet/bvll/detail/foreign_device_table_grammar.hpp>

namespace bacnet { namespace bvll { namespace frame { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll;
using namespace bacnet::bvll::detail::generator;

template<typename Iterator>
struct read_foreign_device_table_ack_grammar : grammar<Iterator, read_foreign_device_table_ack()> {

  rule<Iterator, read_foreign_device_table_ack()> read_foreign_device_table_ack_rule;
  rule<Iterator, bacnet::bvll::foreign_device_table()> foreign_device_table_rule;

  foreign_device_table_grammar<Iterator> foreign_device_table_grammar_;
  unused_grammar<Iterator> unused_grammar_;

  read_foreign_device_table_ack_grammar() : read_foreign_device_table_ack_grammar::base_type(
      read_foreign_device_table_ack_rule) {

    read_foreign_device_table_ack_rule = foreign_device_table_rule << unused_grammar_;
    foreign_device_table_rule = foreign_device_table_grammar_;

    read_foreign_device_table_ack_rule.name("read_foreign_device_table_ack_rule");
    foreign_device_table_rule.name("foreign_device_table_rule");
  }
};

}}}}}


namespace bacnet { namespace bvll { namespace frame { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll;
using namespace bacnet::bvll::detail::parser;

template<typename Iterator>
struct read_foreign_device_table_ack_grammar : grammar<Iterator, read_foreign_device_table_ack()> {

  rule<Iterator, read_foreign_device_table_ack()> read_foreign_device_table_ack_rule;
  rule<Iterator, bacnet::bvll::foreign_device_table()> foreign_device_table_rule;

  foreign_device_table_grammar<Iterator> foreign_device_table_grammar_;
  unused_grammar<Iterator> unused_grammar_;

  read_foreign_device_table_ack_grammar() : read_foreign_device_table_ack_grammar::base_type(
      read_foreign_device_table_ack_rule) {

    read_foreign_device_table_ack_rule = foreign_device_table_rule >> unused_grammar_;
    foreign_device_table_rule = foreign_device_table_grammar_;

    read_foreign_device_table_ack_rule.name("read_foreign_device_table_ack_rule");
    foreign_device_table_rule.name("foreign_device_table_rule");
  }
};


}}}}}


#endif /* SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_GRAMMAR_HPP_ */
