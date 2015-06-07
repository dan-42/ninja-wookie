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

#ifndef TEST_SPIRIT_UNUSED_TYPE_HPP
#define TEST_SPIRIT_UNUSED_TYPE_HPP

#include <cstdint>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>


typedef uint8_t unused_t;
//typedef boost::spirit::unused_type unused_t;

namespace boost { namespace spirit { namespace qi {


template<typename Iterator>
struct unused_grammar : grammar<Iterator, unused_t()> {

  rule<Iterator, unused_t()> start;

  unused_grammar() : unused_grammar::base_type(start) {
    start = attr(uint8_t{0});
  }
};
}}}


namespace boost { namespace spirit { namespace karma {

  template<typename Iterator>
  struct unused_grammar : grammar<Iterator, unused_t()> {

    rule<Iterator, unused_t()> start;

    unused_grammar() : unused_grammar::base_type(start) {
      start = omit[byte_(0x00)];
    }
};
}}}


#endif //TEST_SPIRIT_UNUSED_TYPE_HPP
