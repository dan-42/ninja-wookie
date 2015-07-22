/*
 * control_information.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_NPDU_CONTROL_INFORMATION_HPP_
#define SRC_BACNET_NPDU_CONTROL_INFORMATION_HPP_

#include <cstdint>
#include <iostream>

namespace  bacnet { namespace npdu {


struct  control_information {
  uint8_t priority_                  : 2;
  uint8_t has_confirmedReq_or_ComplxAck_or_expectingReply_ : 1;
  uint8_t has_source_specifier_      : 1;
  uint8_t bit4_unused_               : 1;
  uint8_t has_destination_specifier_ : 1;
  uint8_t bit6_unused_               : 1;
  uint8_t has_network_layer_message_ : 1;

  control_information();

  bool has_confirmedReq_or_ComplxAck_or_expectingReply();
  bool has_source_specifier();
  bool has_destination_specifier();
  bool has_network_layer_message_type();
};

std::ostream &operator<<(std::ostream &os, const bacnet::npdu::control_information &ci);


}}


#endif /* SRC_BACNET_NPDU_CONTROL_INFORMATION_HPP_ */
