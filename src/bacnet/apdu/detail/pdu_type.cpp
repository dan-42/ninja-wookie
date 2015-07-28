/*
 * pdu_type.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
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

