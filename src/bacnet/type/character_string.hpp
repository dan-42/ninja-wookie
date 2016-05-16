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

#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_CHARACTER_STRING_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_CHARACTER_STRING_HPP

#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>


namespace bacnet { namespace type {
  enum class string_encoding_type : uint8_t {
      iso_10646_utf_8     = 0,
      ibm_microsoft_dbcs  = 1,
      jis_x_0208          = 2,
      iso_10646_ucs_4     = 3,
      iso_10646_ucs_2     = 4,
      iso_8859_1          = 5
  };

      static std::ostream& operator<<(std::ostream& os, const string_encoding_type& v) {

        return os;
      }


      struct character_string {

        character_string() = default;
        character_string(std::string s) : value(std::move(s)) {
        }

        character_string(string_encoding_type e, std::string s) : encoding(std::move(e)), value(std::move(s)) {

        }


        string_encoding_type encoding{string_encoding_type::iso_10646_utf_8};
        std::string value;
      };

}}



BOOST_FUSION_ADAPT_STRUCT(
    bacnet::type::character_string,
    encoding,
    value
);

namespace bacnet { namespace type {


      static std::ostream& operator<<(std::ostream& os, const character_string& v) {

        return os;
      }

    }}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_CHARACTER_STRING_HPP
