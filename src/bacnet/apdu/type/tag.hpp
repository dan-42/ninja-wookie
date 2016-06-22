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
#include <bacnet/apdu/type/detail/util/helper.hpp>


namespace bacnet { namespace apdu {  namespace type {


enum class  application_tag : uint8_t {
    null                     =  0,
    boolean                  =  1,
    unsigned_integer         =  2,
    signed_integer           =  3, // (2's complement notation)
    real                     =  4, //Real (ANSI/IEEE-754 floating point)
    double_presision         =  5, //Double (ANSI/IEEE-754 double precision floating point)
    octet_string             =  6,
    character_string         =  7,
    bit_string               =  8,
    enumerated               =  9,
    date                     = 10,
    time                     = 11,
    bacnet_object_identifier = 12,
    reserved_13              = 13,
    reserved_14              = 14,
    reserved_15              = 15
};


struct tag {

    enum class type : uint8_t {
       application,
       context,
       opening,
       closing
    };

    uint32_t  length_value_type_{0};
    uint8_t   number_{0};
    type      type_{type::application};


    //easy creation
    tag()                                             : length_value_type_(0),
                                                        number_(0),
                                                        type_{type::application}{
    }

    //normal application tags
    tag(const application_tag &n)                     : length_value_type_(0),
                                                        number_(static_cast<decltype(number_)>(n)),
                                                        type_{type::application} {
    }

  //normal application tags with fixed known length
  tag(const application_tag &n, const uint32_t &length )
                                                      : length_value_type_(length),
                                                      number_(static_cast<decltype(number_)>(n)),
                                                      type_{type::application} {
  }

    // normal constructed/context id
    tag(const uint8_t &n              )              : length_value_type_(0),
                                                       number_(n),
                                                       type_(type::context)  {
    }

    // normal constructed/context id
    tag(const uint8_t &n, const uint32_t &length)    : length_value_type_(length),
                                                     number_(n),
                                                     type_(type::context)  {
    }

    //for open and closing tags
    tag(const uint8_t &n, const type &t)              : length_value_type_(0),
                                                        number_(n),
                                                        type_(t)  {
    }

     //general purpose
    tag(const uint8_t &n, const uint32_t &v, const type &t)
                                                      : length_value_type_(v),
                                                        number_(n),
                                                        type_(t){
    }



    inline uint8_t number() const { return number_; }

    inline uint32_t length_value_type() const { return length_value_type_; }

    inline type tag_type() const { return type_; }


    inline void number(uint8_t v) { number_ = v; }

    inline void length_value_type(uint32_t v) { length_value_type_ = v; }

    inline void tag_type(type t) { type_ = t; }


    inline bool is_context_tag() const { return type_ == type::context; }

    inline bool is_application_tag() const { return type_ == type::application; }

    inline bool is_opening_tag() const { return type_ == type::opening; }

    inline bool is_closing_tag() const { return type_ == type::closing; }




    template<typename Out>
    friend inline Out& operator<<(Out& os, const bacnet::apdu::type::tag &tag_) {

      os  << " number: "            << std::dec << (uint32_t) tag_.number()
          << " length_value_type: " << std::dec << (uint32_t) tag_.length_value_type()
          << " type: " << tag_.type_;
      return os;
    }
};


template<typename Out>
static inline Out& operator<<(Out& os, const bacnet::apdu::type::tag::type &t) {

  if     (t == tag::type::application) os << "application ";
  else if(t == tag::type::context)     os << "context ";
  else if(t == tag::type::closing)     os << "closing ";
  else if(t == tag::type::opening)     os << "closing ";
  else                                 os << "unknown ";

  return os;
}

}}}



BOOST_FUSION_ADAPT_STRUCT(
    bacnet::apdu::type::tag,
    number_,
    length_value_type_,
    type_
);

#endif //NINJA_WOOKIE_TAG_HPP
