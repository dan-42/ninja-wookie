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

#ifndef NINJA_WOOKIE_BACNET_TYPE_ENUMERATED_HPP
#define NINJA_WOOKIE_BACNET_TYPE_ENUMERATED_HPP

#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>


namespace bacnet { namespace type {


struct enumerated {

  enum class e {
    undefined,
    error_code,
    error_class,
    DeviceStatus ,
    DoorAlarmState ,
    DoorSecuredStatus ,
    DoorStatus ,
    DoorValue,
    EngineeringUnits ,
    EventState,
    EventType,
    FaultType,
    FileAccessMethod,LifeSafetyMode,
    LifeSafetyOperation ,
    LifeSafetyState,
    LightingInProgress ,
    LightingOperation ,
    LightingTransition,
    LockStatus ,
    LoggingType,
  };
  e type{e::undefined};
  uint32_t value{0};


  enumerated() = default;

  enumerated(enumerated e, uint32_t v) : type(e), value(v) {}

  enumerated(uint32_t v) : type(e::undefined), value(v) {}

  friend std::ostream& operator<<(std::ostream& os, const enumerated& v) {

    return os;
  }
};


}}


BOOST_FUSION_ADAPT_STRUCT(
    bacnet::type::enumerated,
    type,
    value
);


#endif //NINJA_WOOKIE_BACNET_TYPE_ENUMERATED_HPP
