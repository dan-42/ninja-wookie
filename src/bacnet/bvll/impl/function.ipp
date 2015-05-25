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


#ifndef NINJA_WOOKIE_FUNCTION_IMPL
#define NINJA_WOOKIE_FUNCTION_IMPL

using namespace bacnet::bvll;

uint8_t bacnet::bvll::base_type(const function &f) {
  return static_cast<uint8_t>(f);
}

std::ostream &bacnet::bvll::operator<<(std::ostream &os, const function &f) {
  switch (f) {
    case function::bvlc_result :
      os << "bvlc_result(0x00)";
      break;
    case function::write_broadcast_distribution_table :
      os << "write_broadcast_distribution_table(0x01)";
      break;
    case function::read_broadcast_distribution_table :
      os << "read_broadcast_distribution_table(0x02)";
      break;
    case function::read_broadcast_distribution_table_ack :
      os << "read_broadcast_distribution_table_ack(0x03)";
      break;
    case function::forwarded_npdu :
      os << "forwarded_npdu(0x04)";
      break;
    case function::register_foreign_device :
      os << "register_foreign_device(0x05)";
      break;
    case function::read_foreign_device_table :
      os << "read_foreign_device_table(0x06)";
      break;
    case function::read_foreign_device_table_ack :
      os << "read_foreign_device_table_ack(0x07)";
      break;
    case function::delete_foreign_device_table_entry :
      os << "delete_foreign_device_table_entry(0x08)";
      break;
    case function::distribute_broadcast_to_network :
      os << "distribute_broadcast_to_network(0x09)";
      break;
    case function::original_unicast_npdu :
      os << "original_unicast_npdu(0x0A)";
      break;
    case function::original_broadcast_npdu :
      os << "original_broadcast_npdu(0x0B)";
      break;
    case function::original_secure_bvll :
      os << "original_secure_bvll(0x0C)";
      break;
    default:
      os << "unknown bvlc function (0x" << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(f) <<
      ")";
  }
  return os;
}


#endif //NINJA_WOOKIE_FUNCTION_IMPL
