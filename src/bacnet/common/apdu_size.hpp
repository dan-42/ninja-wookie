/*
 * apdu_size.hpp
 *
 *  Created on: Oct 22, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_COMMON_APDU_SIZE_HPP_
#define SRC_BACNET_COMMON_APDU_SIZE_HPP_

namespace bacnet { namespace common { namespace apdu_size {

using apdu_size_type = uint32_t;

static constexpr apdu_size_type _50_bytes     =    50;
static constexpr apdu_size_type _128_bytes    =   128;
static constexpr apdu_size_type _206_bytes    =   206;
static constexpr apdu_size_type _480_bytes    =   480;
static constexpr apdu_size_type _1024_bytes   =  1024;
static constexpr apdu_size_type _1476_bytes   =  1476;


//20.1.2.5  max-APDU-length-accepted, 4bit value
enum  length_accepted : uint8_t {
  up_to_50_bytes    = 0b0000, //minimum
  up_to_128_bytes   = 0b0001,
  up_to_206_bytes   = 0b0010, //(fits in a LonTalk frame)
  up_to_480_bytes   = 0b0011, //(fits in an ARCNET frame)
  up_to_1024_bytes  = 0b0100,
  up_to_1476_bytes  = 0b0101, //(fits in an ISO 8802-3 frame/ ETHERNET/UDP/IP)
  reserved_value_07 = 0b0110,
  reserved_value_08 = 0b0111,
  reserved_value_09 = 0b1001,
  reserved_value_10 = 0b1010,
  reserved_value_11 = 0b1011,
  reserved_value_12 = 0b1100,
  reserved_value_13 = 0b1101,
  reserved_value_14 = 0b1110,
  reserved_value_15 = 0b1111
};




}}}



#endif /* SRC_BACNET_COMMON_APDU_SIZE_HPP_ */
