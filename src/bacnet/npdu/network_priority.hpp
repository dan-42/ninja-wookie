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

#ifndef SRC_BACNET_NPDU_NETWORK_PRIORITY_HPP_
#define SRC_BACNET_NPDU_NETWORK_PRIORITY_HPP_

#include <cstdint>

namespace bacnet { namespace  npdu {



enum class network_priority_t : uint8_t {
  normal_message             = 0x00,
  urgent_message             = 0x01,
  critical_equipment_message = 0x02,
  life_safety_message        = 0x03
};

}}


#endif /* SRC_BACNET_NPDU_NETWORK_PRIORITY_HPP_ */
