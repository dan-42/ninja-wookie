/*
 * read_foreign_device_table_ack.hpp
 *
 *  Created on: May 21, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_HPP_
#define SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_HPP_


#include <boost/fusion/include/define_struct.hpp>


#include <bacnet/detail/common/types.hpp>
#include <bacnet/bvll/foreign_device_table.hpp>

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),read_foreign_device_table_ack,
	(bacnet::bvll::bvlc::foreign_device_table, foreign_device_table_)
	(bacnet::unused_type, unused)
)




namespace bacnet { namespace bvll { namespace frame { namespace generator {

using namespace ::boost::spirit;
using namespace ::boost::spirit::karma;
using namespace bacnet::bvll::bvlc;

template<typename Iterator>
struct read_foreign_device_table_ack_grammar : grammar<Iterator, read_foreign_device_table_ack()> {

	rule<Iterator, read_foreign_device_table_ack()> read_foreign_device_table_ack_rule;
	rule<Iterator, bacnet::bvll::bvlc::foreign_device_table()> foreign_device_table_rule;

	foreign_device_table_grammar<Iterator> foreign_device_table_grammar_;

	read_foreign_device_table_ack_grammar() : read_foreign_device_table_ack_grammar::base_type(read_foreign_device_table_ack_rule) {

		read_foreign_device_table_ack_rule = foreign_device_table_rule;
		foreign_device_table_rule = foreign_device_table_grammar_;

		read_foreign_device_table_ack_rule.name("read_foreign_device_table_ack_rule");
		foreign_device_table_rule.name("foreign_device_table_rule");
	}
};

}}}}


namespace bacnet { namespace bvll { namespace frame { namespace parser {

using namespace ::boost::spirit;
using namespace ::boost::spirit::qi;
using namespace bacnet::bvll::bvlc;

template<typename Iterator>
struct read_foreign_device_table_ack_grammar : grammar<Iterator, read_foreign_device_table_ack()> {

	rule<Iterator, read_foreign_device_table_ack()> read_foreign_device_table_ack_rule;
	rule<Iterator, bacnet::bvll::bvlc::foreign_device_table()> foreign_device_table_rule;

	foreign_device_table_grammar<Iterator> foreign_device_table_grammar_;

	read_foreign_device_table_ack_grammar() : read_foreign_device_table_ack_grammar::base_type(read_foreign_device_table_ack_rule) {

		read_foreign_device_table_ack_rule = foreign_device_table_rule  >> attr(0);
		foreign_device_table_rule = foreign_device_table_grammar_;

		read_foreign_device_table_ack_rule.name("read_foreign_device_table_ack_rule");
		foreign_device_table_rule.name("foreign_device_table_rule");
	}
};


}}}}



#endif /* SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_HPP_ */
