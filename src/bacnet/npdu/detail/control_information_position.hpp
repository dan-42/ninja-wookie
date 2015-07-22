/*
 * control_information_position.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_NPDU_DETAIL_CONTROL_INFORMATION_POSITION_HPP_
#define SRC_BACNET_NPDU_DETAIL_CONTROL_INFORMATION_POSITION_HPP_


namespace bacnet { namespace  npdu { namespace detail {

enum control_information_position {
  position_has_network_layer_message = 7,
  position_bit6_unused = 6,
  position_has_destination_specifier = 5,
  position_bit4_unused = 4,
  position_has_source_specifier = 3,
  position_has_confirmedReq_or_ComplxAck_or_expectingReply = 2,
  position_priority_hiBit = 1,
  position_priority_loBit = 0
};



}}}




#endif /* SRC_BACNET_NPDU_DETAIL_CONTROL_INFORMATION_POSITION_HPP_ */
