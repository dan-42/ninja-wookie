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

#ifndef NINJA_WOOKIE_HELPER_HPP
#define NINJA_WOOKIE_HELPER_HPP

#include <cstdint>

namespace bacnet { namespace apdu {  namespace type { namespace detail {


static uint8_t length_helper(uint32_t v) {
  static constexpr uint32_t max_for_one_byte = 0x000000FF;
  static constexpr uint32_t max_for_two_byte = 0x0000FFFF;
  static constexpr uint32_t max_for_three_byte = 0x00FFFFFF;

  if (v > max_for_three_byte) return 4;
  else if (v > max_for_two_byte) return 3;
  else if (v > max_for_one_byte) return 2;
  else return 1;
}

}}}}

#endif //NINJA_WOOKIE_HELPER_HPP
