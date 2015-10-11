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

#ifndef NINJA_WOOKIE_SERVICE_GENERATOR_HPP
#define NINJA_WOOKIE_SERVICE_GENERATOR_HPP


#include <bacnet/detail/common/types.hpp>

namespace bacnet { namespace service { namespace service { namespace detail {

  template<typename Service>
  bacnet::binary_data generate(const Service &service) {
    return bacnet::binary_data{};
  }

}}}}



namespace bacnet { namespace service { namespace service { namespace detail {

  template<typename Service>
  bool parse(bacnet::binary_data& binary_data, Service &service) {
    std::cout << "parse<GENERIC>" << std::endl;
    return false;
  }

}}}}

#endif //NINJA_WOOKIE_SERVICE_GENERATOR_HPP
