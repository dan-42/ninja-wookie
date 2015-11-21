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

#ifndef NINJA_WOOKIE_BACNET_COMMON_CONFIGURATION_HPP
#define NINJA_WOOKIE_BACNET_COMMON_CONFIGURATION_HPP

#include <cstdint>

#include <boost/mpl/map.hpp>
#include <boost/mpl/char.hpp>







namespace bacnet { namespace configuration {

namespace detail {


//   20.1.2.4   max-segments-accepted
enum class number_of_max_segments_accepted : uint8_t {
    unspecified = 0b000,
    segments_2 = 0b001,
    segments_4 = 0b010,
    segments_8 = 0b011,
    segments_16 = 0b100,
    segments_32 = 0b101,
    segments_64 = 0b110,
    segments_more_then_64 = 0b111
};


//20.1.2.5  max-APDU-length-accepted
enum class max_apdu_length_accepted : uint8_t {
    up_to_50_bytes = 0b0000, //minimum
    up_to_128_bytes = 0b0001,
    up_to_206_bytes = 0b0010, //(fits in a LonTalk frame)
    up_to_480_bytes = 0b0011, //(fits in an ARCNET frame)
    up_to_1024_bytes = 0b0100,
    up_to_1476_bytes = 0b0101, //(fits in an ISO 8802-3 frame/ ETHERNET/UDP/IP)
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

}


  namespace apdu_size {

    template<uint32_t Size, detail::max_apdu_length_accepted Enum>
    struct apdu_size_t {
        decltype(Size) size_in_bytes;
        decltype(Enum) size_as_enum;
    };

    typedef apdu_size_t<50,   detail::max_apdu_length_accepted::up_to_50_bytes>     _50_bytes_minimal;
    typedef apdu_size_t<128,  detail::max_apdu_length_accepted::up_to_128_bytes>    _128_bytes;
    typedef apdu_size_t<206,  detail::max_apdu_length_accepted::up_to_206_bytes>    _206_bytes_lon_talk;
    typedef apdu_size_t<480,  detail::max_apdu_length_accepted::up_to_480_bytes>    _480_bytes_arcnet;
    typedef apdu_size_t<1024, detail::max_apdu_length_accepted::up_to_1024_bytes>   _1024_bytes;
    typedef apdu_size_t<1476, detail::max_apdu_length_accepted::up_to_1476_bytes>   _1476_bytes_ipv4;

  }

}}




#endif //NINJA_WOOKIE_BACNET_COMMON_CONFIGURATION_HPP
