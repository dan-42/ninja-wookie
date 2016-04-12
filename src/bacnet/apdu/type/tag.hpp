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


#ifndef NINJA_WOOKIE_TAG_HPP
#define NINJA_WOOKIE_TAG_HPP

#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>



namespace bacnet { namespace apdu {  namespace type {


struct tag {

    uint32_t length_value_type_;
    bool is_context_tag_;
    uint8_t number_;

    tag() :   length_value_type_(0), is_context_tag_(0), number_(0) {
    }

    tag(const uint8_t &n) : length_value_type_(0), is_context_tag_(0), number_(n) {
    }

    tag(const uint8_t &n, const bool &is_context) : length_value_type_(0), is_context_tag_(is_context), number_(n) {
    }

    tag(const uint8_t &n, const bool &is_context, const uint32_t &v) : length_value_type_(v), is_context_tag_(is_context), number_(n) {
    }

    inline uint8_t number() const { return number_; }

    inline bool is_context_tag() const { return is_context_tag_; }

    inline uint32_t length_value_type() const { return length_value_type_; }

    inline void number(uint8_t v) { number_ = v; }

    inline void is_context_tag(bool v) { is_context_tag_ = v; }

    inline void length_value_type(uint32_t v) { length_value_type_ = v; }

};






namespace application_tag_number {
  uint8_t null                     =  0;
  uint8_t boolean                  =  1;
  uint8_t unsigned_interger        =  2;
  uint8_t signed_integer           =  3; // (2's complement notation)
  uint8_t real                     =  4; //Real (ANSI/IEEE-754 floating point)
  uint8_t double_presision         =  5; //Double (ANSI/IEEE-754 double precision floating point)
  uint8_t octet_string             =  6;
  uint8_t character_string         =  7;
  uint8_t bit_string               =  8;
  uint8_t enumerated               =  9;
  uint8_t date                     = 10;
  uint8_t time                     = 11;
  uint8_t bacnet_object_identifier = 12;
  uint8_t reserved_13              = 13;
  uint8_t reserved_14              = 14;
  uint8_t reserved_15              = 15;
};

struct null_t;


}}}

static inline std::ostream& operator<<(std::ostream& os, const bacnet::apdu::type::tag &tag_) {

  os << " number: "            << std::dec << (uint32_t) tag_.number()
  << " is_context_tag: "    << std::dec << (uint32_t) tag_.is_context_tag()
  << " length_value_type: " << std::dec << (uint32_t) tag_.length_value_type() ;

  return os;
}

BOOST_FUSION_ADAPT_STRUCT(
    bacnet::apdu::type::tag,
    number_,
    is_context_tag_,
    length_value_type_
)

#endif //NINJA_WOOKIE_TAG_HPP
