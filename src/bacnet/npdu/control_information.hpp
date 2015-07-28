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
