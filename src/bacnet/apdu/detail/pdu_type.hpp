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
