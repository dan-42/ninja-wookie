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


#ifndef NINJA_WOOKIE_FUNCTION_HPP
#define NINJA_WOOKIE_FUNCTION_HPP

#include <iostream>

namespace bacnet { namespace bvll {


enum class function : uint8_t {
  bvlc_result = 0x00,
  write_broadcast_distribution_table = 0x01,
  read_broadcast_distribution_table = 0x02,
  read_broadcast_distribution_table_ack = 0x03,
  forwarded_npdu = 0x04,
  register_foreign_device = 0x05,
  read_foreign_device_table = 0x06,
  read_foreign_device_table_ack = 0x07,
  delete_foreign_device_table_entry = 0x08,
  distribute_broadcast_to_network = 0x09,
  original_unicast_npdu = 0x0A,
  original_broadcast_npdu = 0x0B,
  original_secure_bvll = 0x0C
};

static uint8_t base_type(const function &f);

static std::ostream &operator<<(std::ostream &os, const function &f);

}}

#include <bacnet/bvll/impl/function.ipp>

#endif //NINJA_WOOKIE_FUNCTION_HPP
