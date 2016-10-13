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

#ifndef SRC_BACNET_BVLL_FRAMES_HPP_
#define SRC_BACNET_BVLL_FRAMES_HPP_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>


//#include <boost/variant.hpp>

#include <mapbox/variant.hpp>



#include <bacnet/bvll/common/bacnet_ip_address.hpp>
#include <bacnet/bvll/common/foreign_device_table_entry.hpp>
#include <bacnet/bvll/common/foreign_device_table.hpp>
#include <bacnet/bvll/common/broadcast_distribution_table_entry.hpp>
#include <bacnet/bvll/common/broadcast_distribution_table.hpp>

#include <bacnet/bvll/frame/bvlc_result.hpp>
#include <bacnet/bvll/frame/read_broadcast_distribution_table_ack.hpp>
#include <bacnet/bvll/frame/read_broadcast_distribution_table.hpp>
#include <bacnet/bvll/frame/write_broadcast_distribution_table.hpp>
#include <bacnet/bvll/frame/forwarded_npdu.hpp>
#include <bacnet/bvll/frame/register_foreign_device.hpp>
#include <bacnet/bvll/frame/original_broadcast_npdu.hpp>
#include <bacnet/bvll/frame/original_unicast_npdu.hpp>
#include <bacnet/bvll/frame/distribute_broadcast_to_network.hpp>
#include <bacnet/bvll/frame/read_foreign_device_table_ack.hpp>
#include <bacnet/bvll/frame/read_foreign_device_table.hpp>
#include <bacnet/bvll/frame/delete_foreign_device_table_entry.hpp>
#include <bacnet/bvll/frame/original_secure_bvll.hpp>
#include <bacnet/bvll/frame/raw.hpp>



#include <bacnet/bvll/result_code.hpp>
#include <bacnet/bvll/type.hpp>
#include <bacnet/bvll/function.hpp>




namespace bacnet { namespace bvll { namespace frame {
  typedef mapbox::util::variant <
  //typedef boost::variant<
			bvlc_result,
			write_broadcast_distribution_table,
			read_broadcast_distribution_table,
			read_broadcast_distribution_table_ack,
			forwarded_npdu,
			register_foreign_device,
			read_foreign_device_table,
			read_foreign_device_table_ack,
			delete_foreign_device_table_entry,
			distribute_broadcast_to_network,
			original_unicast_npdu,
			original_broadcast_npdu,
			original_secure_bvll,
			raw
		 > possible_bvll_frame;
}}}









namespace bacnet { namespace bvll { namespace frame {

struct frame_size /* : public boost::static_visitor<uint32_t> */ {


  uint32_t operator()(const bvlc_result &operand) {
    return 255;
  }

  uint32_t operator()(const write_broadcast_distribution_table &operand) {
    return 255;
  }

  uint32_t operator()(const read_broadcast_distribution_table &operand) {
    return 255;
  }

  uint32_t operator()(const read_broadcast_distribution_table_ack &operand) {
    return 255;
  }

  uint32_t operator()(const forwarded_npdu &operand) {
    return operand.npdu_data_from_origin_device.size();
  }

  uint32_t operator()(const register_foreign_device &operand) {
    return 255;
  }

  uint32_t operator()(const read_foreign_device_table &operand) {
    return 255;
  }

  uint32_t operator()(const read_foreign_device_table_ack &operand) {
    return 255;
  }

  uint32_t operator()(const delete_foreign_device_table_entry &operand) {
    return 255;
  }

  uint32_t operator()(const distribute_broadcast_to_network &operand) {
    return 255;
  }

  uint32_t operator()(const original_unicast_npdu &operand) {
    return operand.npdu_data.size();
  }

  uint32_t operator()(const original_broadcast_npdu &operand) {
    return operand.npdu_data.size();
  }

  uint32_t operator()(const original_secure_bvll &operand) {
    return 255;
  }

  uint32_t operator()(const raw &operand) {
    return 255;
  }

};


}}}




namespace bacnet { namespace bvll { namespace parser {

using namespace bacnet::bvll::frame;

possible_bvll_frame parse(bacnet::binary_data data);

}}}


namespace bacnet { namespace bvll { namespace generator {

using namespace bacnet::bvll::frame;

bacnet::binary_data generate(const possible_bvll_frame& frame);

}}}

#endif /* SRC_BACNET_BVLL_FRAMES_HPP_ */
