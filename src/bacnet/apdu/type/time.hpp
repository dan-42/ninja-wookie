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

#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_time_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_time_HPP

#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>
#include <bacnet/apdu/type/tag.hpp>



namespace bacnet { namespace apdu { namespace type {

  struct time {
    time() = default;
    static const constexpr uint8_t unspecified{0xff};
    static const constexpr uint8_t wildcard   {0xff};
    static const constexpr uint8_t any        {0xff};
    bool is_any() {
      if(   hours     == wildcard
         && minutes   == wildcard
         && seconds   == wildcard
         && hundreds  == wildcard) {
        return true;
      }
      return false;

    }
    uint8_t hours{0};
    uint8_t minutes{0};
    uint8_t seconds{0};
    uint8_t hundreds{0};

  };

}}}



BOOST_FUSION_ADAPT_STRUCT(
    bacnet::apdu::type::time,
    hours,
    minutes,
    seconds,
    hundreds
);

namespace bacnet { namespace apdu { namespace type {


  static std::ostream& operator<<(std::ostream& os, const time& v) {

    return os;
  }

}}}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_time_HPP
