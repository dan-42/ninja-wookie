/*
 * frame.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_NPDU_FRAME_HPP_
#define SRC_BACNET_NPDU_FRAME_HPP_

#include <iostream>

#include <boost/fusion/include/define_struct.hpp>

#include <bacnet/detail/common/types.hpp>

#include <bacnet/npdu/address.hpp>
#include <bacnet/npdu/control_information.hpp>



BOOST_FUSION_DEFINE_STRUCT(
  (bacnet)(npdu), frame,
  (uint8_t, protocol_version)
  (bacnet::npdu::control_information, control_field)
  (bacnet::npdu::address, destination)
  (bacnet::npdu::address, source)
  (uint8_t, hop_count)
  (uint8_t, message_type)
  (uint16_t, vendor_id)
  (bacnet::binary_data, apdu_data)
)


std::ostream &operator<<(std::ostream &os, const bacnet::npdu::frame &f) ;


#endif /* SRC_BACNET_NPDU_FRAME_HPP_ */
