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

#include <bacnet/type/object_type.hpp>


namespace bacnet { namespace type {

  struct object_identifier  {

  public:

    static constexpr uint32_t  min_instance_number  = 0x00000000;
    static constexpr uint32_t  max_instance_number  = 0x003FFFFF;
    static constexpr uint32_t  min_object_type      = 0x00400000;
    static constexpr uint32_t  max_object_type      = 0xFFC00000;

    object_identifier() : object_type(0), instance_number(0) {

    }
    object_identifier(const uint32_t &in) : object_type(bacnet::type::object_type::device), instance_number(in) {

    }

    object_identifier(uint32_t type, uint32_t in) noexcept: object_type(std::move(type)), instance_number(std::move(in)) {

    }

    object_identifier(const object_identifier& other) : object_type(other.object_type),
                                                        instance_number(other.instance_number)   {

    }
    object_identifier(object_identifier&& other)  : object_type(other.object_type),
                                                    instance_number(other.instance_number)   {
    }

    object_identifier& operator=(object_identifier&& other) {
      object_type = other.object_type;
      instance_number = other.instance_number;
      return *this;
    }
    object_identifier& operator=(const object_identifier& other) {
      object_type = other.object_type;
      instance_number = other.instance_number;
      return *this;
    }




    inline void from_native(uint32_t const& object_type_and_instance_number){
      instance_number  = object_type_and_instance_number & max_instance_number;
      object_type      = (object_type_and_instance_number & max_object_type) >> object_type_shift_offset;
    }

    inline uint32_t to_native() const {
      return (object_type << object_type_shift_offset) | instance_number;
    }

    static inline object_identifier make_object_identifier(uint32_t const& object_type_and_instance_number) {
      object_identifier tmp{};
      tmp.from_native(object_type_and_instance_number);
      return tmp;
    }

    friend constexpr bool operator==(const object_identifier& a1, const object_identifier& a2) {
      return (a1.object_type == a2.object_type && a1.instance_number == a2.instance_number) ? true : false;
    }

    friend constexpr bool operator!=(const object_identifier& a1, const object_identifier& a2) {
      return !(a1 == a2);
    }
    friend constexpr bool operator<(const object_identifier& a1, const object_identifier& a2) {
      return (a1.object_type < a2.object_type) ? true : (
          (a1.instance_number < a2.instance_number) ? true : false );
    }
    friend constexpr bool operator>=(const object_identifier& a1, const object_identifier& a2){
      return !(a1 < a2);
    }


    uint32_t object_type;
    uint32_t instance_number;

  private:

    static constexpr uint32_t object_type_shift_offset = 22;




  };

static inline std::ostream& operator<<(std::ostream& os, const object_identifier &oi) {
  os << " type: "     << std::dec << oi.object_type
     << " instance: " << std::dec << oi.instance_number;
  return os;
}

}}


BOOST_FUSION_ADAPT_STRUCT(
    bacnet::type::object_identifier,
    object_type,
    instance_number
);


#endif //NINJA_WOOKIE_BACNET_COMMON_OBJECT_IDENTIFIER_HPP
