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

#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_NULL_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_NULL_HPP

#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>

namespace bacnet { namespace type {


      struct null {

        null() = default;

     };

}}



BOOST_FUSION_ADAPT_STRUCT(
    bacnet::type::null
);

namespace bacnet { namespace type {

static std::ostream& operator<<(std::ostream& os, const null& v) {
  os << "null";
  return os;
}

}}

#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_NULL_HPP
