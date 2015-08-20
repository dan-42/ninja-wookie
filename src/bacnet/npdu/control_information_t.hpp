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

#ifndef SRC_BACNET_NPDU_CONTROL_INFORMATION_T_HPP_
#define SRC_BACNET_NPDU_CONTROL_INFORMATION_T_HPP_

#include <cstdint>
#include <iostream>

#include <bacnet/npdu/network_priority.hpp>

namespace  bacnet { namespace npdu {


struct  control_information_t {
  uint8_t priority_                  : 2;
  uint8_t has_confirmedReq_or_ComplxAck_or_expectingReply_ : 1;
  uint8_t has_source_specifier_      : 1;
  uint8_t bit4_unused_               : 1;
  uint8_t has_destination_specifier_ : 1;
  uint8_t bit6_unused_               : 1;
  uint8_t has_network_layer_message_ : 1;

  control_information_t();

  bacnet::npdu::network_priority_t network_priority() const;
  bool has_confirmed_req_OR_Complx_ack_OR_expecting_reply() const;
  bool has_source_specifier() const;
  bool has_destination_specifier() const;
  bool has_network_layer_message_type() const;
};

std::ostream &operator<<(std::ostream &os, const bacnet::npdu::control_information_t &ci);


}}


#endif /* SRC_BACNET_NPDU_CONTROL_INFORMATION_T_HPP_ */
