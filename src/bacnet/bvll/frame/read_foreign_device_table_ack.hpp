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
	(bacnet::bvll::foreign_device_table, foreign_device_table_)
	(bacnet::unused_type, unused)
)


#endif /* SRC_BACNET_BVLL_FRAME_READ_FOREIGN_DEVICE_TABLE_ACK_HPP_ */
