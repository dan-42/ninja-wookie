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

#ifndef SRC_BACNET_NPDU_DETAIL_CONTROL_INFORMATION_POSITION_HPP_
#define SRC_BACNET_NPDU_DETAIL_CONTROL_INFORMATION_POSITION_HPP_


namespace bacnet { namespace  npdu { namespace detail {

enum control_information_position {
  position_has_network_layer_message  = 7,
  position_bit6_unused                = 6,
  position_has_destination_specifier  = 5,
  position_bit4_unused                = 4,
  position_has_source_specifier       = 3,
  position_has_confirmedReq_or_ComplxAck_or_expectingReply = 2,
  position_priority_hiBit             = 1,
  position_priority_loBit             = 0
};



}}}




#endif /* SRC_BACNET_NPDU_DETAIL_CONTROL_INFORMATION_POSITION_HPP_ */
