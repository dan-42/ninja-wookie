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


#include <bacnet/apdu/>



typedef boost::mpl::map<
    boost::mpl::pair<boost::mpl::integral_c<uint8_t, 0>, boost::mpl::integral_c<uint16_t, 50>>,
    boost::mpl::pair<boost::mpl::integral_c<uint8_t, 1>, boost::mpl::integral_c<uint16_t, 128>>,
    boost::mpl::pair<boost::mpl::integral_c<uint8_t, 2>, boost::mpl::integral_c<uint16_t, 206>>,
    boost::mpl::pair<boost::mpl::integral_c<uint8_t, 3>, boost::mpl::integral_c<uint16_t, 480>>,
    boost::mpl::pair<boost::mpl::integral_c<uint8_t, 4>, boost::mpl::integral_c<uint16_t, 1024>>,
    boost::mpl::pair<boost::mpl::integral_c<uint8_t, 5>, boost::mpl::integral_c<uint16_t, 1476>>,
    boost::mpl::pair<boost::mpl::integral_c<uint8_t, 6>, boost::mpl::integral_c<uint16_t, 1>>
> segmentation;




namespace bacnet { namespace configuration {



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
            up_to_1476_bytes = 0b0101, //(fits in an ISO 8802-3 frame)
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




        namespace settings {

          namespace apdu_size {
            static const constexpr auto minimal = static_cast<typename std::underlying_type<decltype(detail::max_apdu_length_accepted::up_to_50_bytes)>::type>(
                detail::max_apdu_length_accepted::up_to_50_bytes);
            static const constexpr auto ip = static_cast<typename std::underlying_type<decltype(detail::max_apdu_length_accepted::up_to_1476_bytes)>::type>(
                detail::max_apdu_length_accepted::up_to_1476_bytes);
          }

        }

      }}










    struct configuration {
      bacnet::apdu::settings::apdu_size::ip
    };


  }}


#endif //NINJA_WOOKIE_BACNET_COMMON_CONFIGURATION_HPP
