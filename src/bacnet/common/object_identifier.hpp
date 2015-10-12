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

#ifndef NINJA_WOOKIE_BACNET_COMMON_OBJECT_IDENTIFIER_HPP
#define NINJA_WOOKIE_BACNET_COMMON_OBJECT_IDENTIFIER_HPP


#include <cstdint>
#include <boost/fusion/adapted/adt/adapt_adt.hpp>
#include <boost/fusion/include/adapt_adt.hpp>


namespace bacnet {
  namespace object_type {
    static constexpr uint32_t analog_input      = 0;
    static constexpr uint32_t analog_output     = 1;
    static constexpr uint32_t analog_value = 2;
    static constexpr uint32_t binary_input = 3;
    static constexpr uint32_t binary_output = 4;
    static constexpr uint32_t binary_value = 5;
    static constexpr uint32_t calendar = 6;
    static constexpr uint32_t command = 7;
    static constexpr uint32_t device = 8;
    static constexpr uint32_t event_enrollment = 9;
    static constexpr uint32_t file = 10;
    static constexpr uint32_t group = 11;
    static constexpr uint32_t loop = 12;
    static constexpr uint32_t multi_state_input = 13;
    static constexpr uint32_t multi_state_output = 14;
    static constexpr uint32_t notification_class = 15;
    static constexpr uint32_t program = 16;
    static constexpr uint32_t schedule = 17;
    static constexpr uint32_t averaging = 18;
    static constexpr uint32_t multi_state_value = 19;
    static constexpr uint32_t trend_log = 20;
    static constexpr uint32_t life_safety_point = 21;
    static constexpr uint32_t life_safety_zone = 22;
    static constexpr uint32_t accumulator = 23;
    static constexpr uint32_t pulse_converter = 24;
    static constexpr uint32_t event_log = 25;
    static constexpr uint32_t global_group = 26;
    static constexpr uint32_t trend_log_multiple = 27;
    static constexpr uint32_t load_control = 28;
    static constexpr uint32_t structured_view = 29;
    static constexpr uint32_t access_door = 30;
    static constexpr uint32_t unassigned_31 = 31;
    static constexpr uint32_t access_credential = 32;
    static constexpr uint32_t access_point = 33;
    static constexpr uint32_t access_rights = 34;
    static constexpr uint32_t access_user = 35;
    static constexpr uint32_t access_zone = 36;
    static constexpr uint32_t credential_data_input = 37;
    static constexpr uint32_t network_security = 38;
    static constexpr uint32_t bitstring_value = 39;
    static constexpr uint32_t characterstring_value = 40;
    static constexpr uint32_t date_pattern_value = 41;
    static constexpr uint32_t date_value = 42;
    static constexpr uint32_t datetime_pattern_value = 43;
    static constexpr uint32_t datetime_value = 44;
    static constexpr uint32_t integer_value = 45;
    static constexpr uint32_t large_analog_value = 46;
    static constexpr uint32_t octetstring_value = 47;
    static constexpr uint32_t positive_integer_value = 48;
    static constexpr uint32_t time_pattern_value = 49;
    static constexpr uint32_t time_value = 50;
    static constexpr uint32_t notification_forwarder = 51;
    static constexpr uint32_t alert_enrollment = 52;
    static constexpr uint32_t channel = 53;
    static constexpr uint32_t lighting_output = 54;
  }
}


namespace bacnet { namespace common {

  struct object_identifier  {

  public:

    static constexpr uint32_t  min_instance_number  = 0x00000000;
    static constexpr uint32_t  max_instance_number  = 0x003FFFFF;
    static constexpr uint32_t  min_object_type      = 0x00400000;
    static constexpr uint32_t  max_object_type      = 0xFFC00000;

    inline void object_typ(uint32_t const& ot)  {
      object_type_ = ot;
    }

    inline uint32_t object_typ() const  {
      return object_type_;
    }

    inline void instance_number(uint32_t const& in)  {
      instance_number_ = in;
    }

    inline uint32_t instance_number() const  {
      return instance_number_;
    }


    inline void from_native(uint32_t const& object_type_and_instance_number){
      instance_number_  = object_type_and_instance_number & max_instance_number;
      object_type_      = (object_type_and_instance_number & max_object_type) >> object_type_shift_offset;
    }

    inline uint32_t to_native() const {
      return (object_type_ << object_type_shift_offset) | instance_number_;
    }

  private:

    static constexpr uint32_t object_type_shift_offset = 22;

    uint32_t instance_number_;
    uint32_t object_type_;

  };

static inline std::ostream& operator<<(std::ostream& os, const object_identifier &oi) {
  os << " type: "     << std::dec << oi.object_typ()
     << " instance: " << std::dec << oi.instance_number();
  return os;
}

}}


BOOST_FUSION_ADAPT_ADT(
    bacnet::common::object_identifier,
    (obj.to_native(), obj.from_native(val))
)




#endif //NINJA_WOOKIE_BACNET_COMMON_OBJECT_IDENTIFIER_HPP
