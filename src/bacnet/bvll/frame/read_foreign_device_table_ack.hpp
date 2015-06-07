/*
 * read_foreign_device_table_ack.hpp
 *
 *  Created on: May 21, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_HPP_
#define SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_HPP_


#include <utility>
#include <boost/fusion/include/adapt_struct.hpp>
#include <bacnet/detail/common/types.hpp>
#include <util/boost/spirit/unused_type.hpp>
#include <bacnet/bvll/foreign_device_table.hpp>

namespace bacnet { namespace bvll { namespace frame {
struct read_foreign_device_table_ack {
	explicit read_foreign_device_table_ack(bacnet::bvll::foreign_device_table d) : foreign_device_table_(std::move(d))  { }
  read_foreign_device_table_ack() = default;

  bacnet::bvll::foreign_device_table foreign_device_table_;
	unused_t unused;
};
}}}

BOOST_FUSION_ADAPT_STRUCT(
		bacnet::bvll::frame::read_foreign_device_table_ack,
		(bacnet::bvll::foreign_device_table, foreign_device_table_)
		(unused_t, unused)
)



#endif /* SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_HPP_ */
