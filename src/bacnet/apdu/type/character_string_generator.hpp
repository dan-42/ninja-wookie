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


#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_CHARACTER_STRING_GENERATOR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_CHARACTER_STRING_GENERATOR_HPP

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>

#include <bacnet/apdu/type/character_string.hpp>
#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/detail/character_string_grammar.hpp>


namespace  bacnet { namespace apdu { namespace type {

static bacnet::binary_data generate(const character_string &oi) {
  using namespace bacnet::apdu;
  bacnet::binary_data binary;

  std::back_insert_iterator <bacnet::binary_data> sink(binary);
  type::detail::generator::character_string_grammar<decltype(sink)> generator;
  bool result = false;
  try {
    result = boost::spirit::karma::generate(sink, generator, oi);
  }
  catch (std::exception &e) {
    std::cerr << "exception: apdu generate  character_string" << e.what() << std::endl;
  }
  if (!result) {
    std::cerr << "failed: apdu generate  character_string" << std::endl;
    return bacnet::binary_data();
  }

  return binary;
}


static bool parse(bacnet::binary_data& data, character_string &oi) {
  using namespace bacnet::apdu;

  auto start = data.begin();
  auto end = data.end();

  type::detail::parser::character_string_grammar<decltype(start)> parser;
  bool has_succeeded = false;
  try {
    has_succeeded = boost::spirit::qi::parse(start, end, parser, oi);
  }
  catch (std::exception &e) {
    std::cerr << "exception: apdu parse character_string" << e.what() << std::endl;
  }
  if (has_succeeded) {
    data.erase(data.begin(), start);
    return true;
  }
  std::cerr << "fail: apdu parse character_string"  << std::endl;
  return false;
}


}}}


#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_CHARACTER_STRING_GENERATOR_HPP
