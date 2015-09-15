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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_WHO_IS_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_WHO_IS_HPP

#include <cstdint>

#include <boost/fusion/include/define_struct.hpp>

BOOST_FUSION_DEFINE_STRUCT(
  (bacnet)(service), who_is,
  (uint32_t, device_instance_range_low_limit)
  (uint32_t, device_instance_range_high_limit)
)



#endif //NINJA_WOOKIE_BACNET_SERVICE_WHO_IS_HPP
