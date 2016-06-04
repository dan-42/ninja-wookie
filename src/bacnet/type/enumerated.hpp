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
#include <sstream>

#include <boost/fusion/include/adapt_struct.hpp>


namespace bacnet { namespace type {


struct enumerated {

  enum class e {
    undefined,
    error_code,
    error_class,
    abort_reason,
    device_status,
    door_alarm_state,
    engineering_units,
    event_state,
    event_type,
    life_safety_mode,
    life_safety_state,
    life_safety_operation,
    logging_type,
    maintenance,
    object_type,
    program_error,
    property_identifier,
    property_states,
    reliability,
    reject_reason,
    restart_reason,
    silenced_state,
    vt_class,
    access_authentication_factor_disable,
    access_credential_disable,
    access_credential_disable_reason,
    access_event,
    access_user_type,
    access_zone_occupancy_state,
    authorization_exemption,
    authorization_mode,
    lighting_operation,
    lighting_transition
  };
  e type{e::undefined};
  uint32_t value{0};


  enumerated() = default;

  enumerated(enumerated::e en, uint32_t v) : type(en), value(v) {}

  enumerated(uint32_t v) : type(e::undefined), value(v) {}

  friend std::ostream& operator<<(std::ostream& os, const enumerated::e& v) {
      switch(v) {
        case enumerated::e::undefined :                           os << "undefined"; break;
        case enumerated::e::error_code :                          os << "error_code"; break;
        case enumerated::e::error_class :                         os << "error_class"; break;
        case enumerated::e::abort_reason :                        os << "abort_reason"; break;
        case enumerated::e::device_status :                       os << "device_status"; break;
        case enumerated::e::door_alarm_state :                    os << "door_alarm_state"; break;
        case enumerated::e::engineering_units :                   os << "engineering_units"; break;
        case enumerated::e::event_state :                         os << "event_state"; break;
        case enumerated::e::event_type :                          os << "event_type"; break;
        case enumerated::e::life_safety_mode :                    os << "life_safety_mode"; break;
        case enumerated::e::life_safety_state :                   os << "life_safety_state"; break;
        case enumerated::e::life_safety_operation :               os << "life_safety_operation"; break;
        case enumerated::e::logging_type :                        os << "logging_type"; break;
        case enumerated::e::maintenance :                         os << "maintenance"; break;
        case enumerated::e::object_type :                         os << "object_type"; break;
        case enumerated::e::program_error :                       os << "program_error"; break;
        case enumerated::e::property_identifier :                 os << "property_identifier"; break;
        case enumerated::e::property_states :                     os << "property_states"; break;
        case enumerated::e::reliability :                         os << "reliability"; break;
        case enumerated::e::reject_reason :                       os << "reject_reason"; break;
        case enumerated::e::restart_reason :                      os << "restart_reason"; break;
        case enumerated::e::silenced_state :                      os << "silenced_state"; break;
        case enumerated::e::vt_class :                            os << "vt_class"; break;
        case enumerated::e::access_authentication_factor_disable :os << "access_authentication_factor_disable"; break;
        case enumerated::e::access_credential_disable :           os << "access_credential_disable"; break;
        case enumerated::e::access_credential_disable_reason :    os << "access_credential_disable_reason"; break;
        case enumerated::e::access_event :                        os << "access_event"; break;
        case enumerated::e::access_user_type :                    os << "access_user_type"; break;
        case enumerated::e::access_zone_occupancy_state :         os << "access_zone_occupancy_state"; break;
        case enumerated::e::authorization_exemption :             os << "authorization_exemption"; break;
        case enumerated::e::authorization_mode :                  os << "authorization_mode"; break;
        case enumerated::e::lighting_operation :                  os << "lighting_operation"; break;
        case enumerated::e::lighting_transition :                 os << "lighting_transition"; break;
      };
      return os;
    }


  template<typename T>
  inline std::string to_string() {
    std::stringstream os;
    os << "type: " << type << "  value: " << value;
    return os.str();
  }
};



}}


BOOST_FUSION_ADAPT_STRUCT(
    bacnet::type::enumerated,
    type,
    value
);








////////////////////////////////////////////////////////////////////////////

namespace bacnet { namespace type {


struct device_status{
  static constexpr uint32_t operational             =  0;
  static constexpr uint32_t operational_read_only   =  1;
  static constexpr uint32_t download_required       =  2;
  static constexpr uint32_t download_in_progress    =  3;
  static constexpr uint32_t non_operational         =  4;
  static constexpr uint32_t non_backup_in_progress  =  5;
};


template<>
inline std::string enumerated::to_string<device_status> () {
  std::stringstream os;
  os << type << ":";
  switch(value) {
    case device_status::operational             : os << "operational";              break;
    case device_status::operational_read_only   : os << "operational_read_only";    break;
    case device_status::download_required       : os << "download_required";        break;
    case device_status::download_in_progress    : os << "download_in_progress";     break;
    case device_status::non_operational         : os << "non_operational";          break;
    case device_status::non_backup_in_progress  : os << "non_backup_in_progress";   break;
    default                                     : os << "unknown";                  break;

    os << "(" << value << ")";
  }
  return os.str();
}



}}

#endif //NINJA_WOOKIE_BACNET_TYPE_ENUMERATED_HPP
