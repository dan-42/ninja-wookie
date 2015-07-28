/*
 * pdu_type.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_DETAIL_PDU_TYPE_HPP_
#define SRC_BACNET_APDU_DETAIL_PDU_TYPE_HPP_



#include <cstdint>
#include <iostream>

namespace bacnet { namespace  apdu { namespace detail { namespace pdu_type {

/*
 * the pdu_type is a 4bit value
 * and is encoded in the hi_nibble
 * of the first byte in the apdu-header
 */

constexpr uint8_t  confirmed_request          = 0x00;
constexpr uint8_t  unconfirmed_request        = 0x01;
constexpr uint8_t  simple_ack                 = 0x02;
constexpr uint8_t  complex_ack                = 0x03;
constexpr uint8_t  segment_ack                = 0x04;
constexpr uint8_t  error                      = 0x05;
constexpr uint8_t  reject                     = 0x06;
constexpr uint8_t  abort                      = 0x07;

static std::ostream &operator<<(std::ostream &os, const uint8_t &pdu_type);

}}}}



#endif /* SRC_BACNET_APDU_DETAIL_PDU_TYPE_HPP_ */
