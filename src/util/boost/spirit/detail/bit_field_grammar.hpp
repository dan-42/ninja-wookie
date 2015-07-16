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

#ifndef NINJA_WOOKIE_BIT_FIELD_GRAMMAR_HPP
#define NINJA_WOOKIE_BIT_FIELD_GRAMMAR_HPP



#include <cstdint>

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>


namespace boost { namespace spirit { namespace qi {


template<typename Iterator, typename ReturnType>
struct bit_field : grammar<Iterator, ReturnType()> {
  static_assert((sizeof(ReturnType) == 1), "size of ReturnType must be 1 byte in size!");
  static_assert((std::is_class<ReturnType>::value), "ReturnType must be struct or class!");

  bit_field() : bit_field::base_type(start) {

    start = byte_[_val = *boost::phoenix::reinterpret_cast_<ReturnType*>(&_1) ];

  }

  rule<Iterator,ReturnType()> start;

};

}}}



namespace boost { namespace spirit { namespace karma {


template<typename Iterator, typename ReturnType>
struct bit_field : grammar<Iterator, ReturnType()> {
  static_assert((sizeof(ReturnType) == 1), "size of ReturnType must be 1 byte in size!");
  static_assert((std::is_class<ReturnType>::value), "ReturnType must be struct or class!");

  bit_field() : bit_field::base_type(start) {

	  start = byte_[_1 = *boost::phoenix::reinterpret_cast_<const uint8_t*>(&_val) ];

  }

  rule<Iterator, ReturnType()> start;

};

}}}


#endif
