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
/*
  - [x] BACnetObjectType  //enumeration
  - [x] BACnetDeviceStatus //enumerated
  - [x] BACnetPropertyIdentifier //enumerated
  - [x] BACnetRestartReason //enumerated
  - [x] BACnetSegmentation //enumeration
  - [x] BACnetList of BACnetVTClass //enumeration
  - [x] BACnetBackupState //enumerated

  - [-] BACnetServicesSupported  // bit-string
  - [ ] BACnetObjectTypesSupported // bit-string

  - [ ] BACnetList of BACnetVTSession       // sequence
  - [ ] BACnetList of BACnetRecipient       //choice of two sequence
  - [ ] BACnetList of BACnetAddressBinding  // sequence of two complex
  - [ ] BACnetTimeStamp                     //choice time, unsigned, dateTime
  - [ ] BACnetList of BACnetCOVSubscription //sequence

 */
namespace bacnet { namespace type {
    struct undefined{};
    struct error_code;
    struct error_class;
    struct abort_reason;
    struct backup_state;
    struct device_status;
    struct door_alarm_state;
    struct engineering_units;
    struct event_state;
    struct event_type;
    struct life_safety_mode;
    struct life_safety_state;
    struct life_safety_operation;
    struct logging_type;
    struct maintenance;
    struct object_type;
    struct program_error;
    struct property_identifier;
    struct property_states;
    struct reliability;
    struct reject_reason;
    struct restart_reason;
    struct segmentation;
    struct silenced_state;
    struct vt_class;
    struct access_authentication_factor_disable;
    struct access_credential_disable;
    struct access_credential_disable_reason;
    struct access_event;
    struct access_user_type;
    struct access_zone_occupancy_state;
    struct authorization_exemption;
    struct authorization_mode;
    struct lighting_operation;
    struct lighting_transition;
}}


namespace bacnet { namespace type {



struct enumerated {


  enum class e {
    undefined,
    error_code,
    error_class,
    abort_reason,
    backup_state,
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
    segmentation,
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


  template<typename OStream>
  friend OStream& operator<<(OStream& os, const enumerated::e& e) {
    os << "enumerated::type: " << static_cast<std::underlying_type<enumerated::e>::type>(e);
    return os;
  }

  template<typename OStream>
  friend OStream& operator<<(OStream& os, const enumerated& e) {
    switch(e.type) {
      case enumerated::e::undefined :                           os << "undefined_enum::"                      << e.to_string<undefined>(); break;
      case enumerated::e::error_code :                          os << "error_code::"                          << e.to_string<error_code>(); break;
      case enumerated::e::error_class :                         os << "error_class::"                         << e.to_string<error_class>(); break;
      case enumerated::e::abort_reason :                        os << "abort_reason::"                        << e.to_string<abort_reason>(); break;
      case enumerated::e::backup_state :                        os << "backup_state::"                        << e.to_string<backup_state>(); break;
      case enumerated::e::device_status :                       os << "device_status::"                       << e.to_string<device_status>(); break;
      case enumerated::e::door_alarm_state :                    os << "door_alarm_state::"                    << e.to_string<door_alarm_state>(); break;
      case enumerated::e::engineering_units :                   os << "engineering_units::"                   << e.to_string<engineering_units>(); break;
      case enumerated::e::event_state :                         os << "event_state::"                         << e.to_string<event_state>(); break;
      case enumerated::e::event_type :                          os << "event_type::"                          << e.to_string<event_type>(); break;
      case enumerated::e::life_safety_mode :                    os << "life_safety_mode::"                    << e.to_string<life_safety_mode>(); break;
      case enumerated::e::life_safety_state :                   os << "life_safety_state::"                   << e.to_string<life_safety_state>(); break;
      case enumerated::e::life_safety_operation :               os << "life_safety_operation::"               << e.to_string<life_safety_operation>(); break;
      case enumerated::e::logging_type :                        os << "logging_type::"                        << e.to_string<logging_type>(); break;
      case enumerated::e::maintenance :                         os << "maintenance::"                         << e.to_string<maintenance>(); break;
      case enumerated::e::object_type :                         os << "object_type::"                         << e.to_string<object_type>(); break;
      case enumerated::e::program_error :                       os << "program_error::"                       << e.to_string<program_error>(); break;
      case enumerated::e::property_identifier :                 os << "property_identifier::"                 << e.to_string<property_identifier>(); break;
      case enumerated::e::property_states :                     os << "property_states::"                     << e.to_string<property_states>(); break;
      case enumerated::e::reliability :                         os << "reliability::"                         << e.to_string<reliability>(); break;
      case enumerated::e::reject_reason :                       os << "reject_reason::"                       << e.to_string<reject_reason>(); break;
      case enumerated::e::restart_reason :                      os << "restart_reason::"                      << e.to_string<restart_reason>(); break;
      case enumerated::e::silenced_state :                      os << "silenced_state::"                      << e.to_string<silenced_state>(); break;
      case enumerated::e::vt_class :                            os << "vt_class::"                            << e.to_string<vt_class>(); break;
      case enumerated::e::access_authentication_factor_disable :os << "access_authentication_factor_disable::"<< e.to_string<access_authentication_factor_disable>(); break;
      case enumerated::e::access_credential_disable :           os << "access_credential_disable::"           << e.to_string<access_credential_disable>(); break;
      case enumerated::e::access_credential_disable_reason :    os << "access_credential_disable_reason::"    << e.to_string<access_credential_disable_reason>(); break;
      case enumerated::e::access_event :                        os << "access_event::"                        << e.to_string<access_event>(); break;
      case enumerated::e::access_user_type :                    os << "access_user_type::"                    << e.to_string<access_user_type>(); break;
      case enumerated::e::access_zone_occupancy_state :         os << "access_zone_occupancy_state::"         << e.to_string<access_zone_occupancy_state>(); break;
      case enumerated::e::authorization_exemption :             os << "authorization_exemption::"             << e.to_string<authorization_exemption>(); break;
      case enumerated::e::authorization_mode :                  os << "authorization_mode::"                  << e.to_string<authorization_mode>(); break;
      case enumerated::e::lighting_operation :                  os << "lighting_operation::"                  << e.to_string<lighting_operation>(); break;
      case enumerated::e::lighting_transition :                 os << "lighting_transition::"                 << e.to_string<lighting_transition>(); break;
    };
    return os;
  }


  template<typename T>
  std::string to_string() const {
    std::stringstream os;
    os  << "value: " << value;
    return os.str();
  }


};

}}



BOOST_FUSION_ADAPT_STRUCT(
    bacnet::type::enumerated,
    type,
    value
);



#endif //NINJA_WOOKIE_BACNET_TYPE_ENUMERATED_HPP
