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

#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_DATE_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_DATE_HPP

#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>
#include <bacnet/apdu/type/tag.hpp>



namespace bacnet { namespace apdu { namespace type {
  enum class day_of_weeks : uint8_t {
      monday    = 1,
      tuesday   = 2,
      wednesday = 3,
      thursday  = 4,
      friday    = 5,
      saturday  = 6,
      sunday    = 7,
      any       = 255
  };
  enum class month : uint8_t {
        january   =  1,
        februrary =  2,
        march     =  3,
        april     =  4,
        may       =  5,
        june      =  6,
        juli      =  7,
        august    =  8,
        september =  9,
        october   = 10,
        november  = 11,
        december  = 12,
        odd       = 13,
        even      = 14,
        any       = 255
  };




  struct date {

    date() = default;



    static const constexpr uint8_t unspecified{0xff};
    static const constexpr uint8_t wildcard{0xff};
    static const constexpr uint8_t any{0xff};
    static const constexpr uint8_t odd_month{13};
    static const constexpr uint8_t even_month{14};
    static const constexpr uint8_t last_day_of_month{0x32};
    static const constexpr uint8_t odd_days_of_month{0x33};
    static const constexpr uint8_t even_days_of_month{0x34};


    bool is_any() {
      if(   year_minus_1900 == wildcard
         && month           == wildcard
         && day_of_month    == wildcard
         && day_of_week     == wildcard) {
        return true;
      }
      return false;

    }

    uint8_t year_minus_1900{0};
    uint8_t month{1};
    uint8_t day_of_month{1};
    uint8_t day_of_week{1};

  };

}}}



BOOST_FUSION_ADAPT_STRUCT(
    bacnet::apdu::type::date,
    year_minus_1900,
    month,
    day_of_month,
    day_of_week
);

namespace bacnet { namespace apdu { namespace type {


  static std::ostream& operator<<(std::ostream& os, const date& v) {

    return os;
  }

}}}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_DATE_HPP
