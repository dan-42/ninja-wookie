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

#include <iomanip>

#include <bacnet/apdu/detail/pdu_type.hpp>

namespace bacnet { namespace  apdu { namespace detail { namespace pdu_type {

static std::ostream &operator<<(std::ostream &os, const uint8_t &pdu_type){

  switch (pdu_type) {
    case pdu_type::confirmed_request :
      os << "confirmed_request(0x00)";
      break;
    case pdu_type::unconfirmed_request :
      os << "unconfirmed_request(0x01)";
      break;
    case pdu_type::simple_ack :
      os << "simple_ack(0x02)";
      break;
    case pdu_type::complex_ack :
      os << "complex_ack(0x03)";
      break;
    case pdu_type::segment_ack :
      os << "segment_ack(0x04)";
      break;
    case pdu_type::error :
      os << "error(0x05)";
      break;
    case pdu_type::reject :
      os << "reject(0x06)";
      break;
    case pdu_type::abort :
      os << "abort(0x07)";
      break;
    default:
      os  << "unknown pdu_type  (0x" << std::hex
          << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(pdu_type)
          << ")";
  }
  return os;
}

}}}}

