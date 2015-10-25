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

#ifndef NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_APDU_TYPE_CHARACTER_STRING_HPP
#define NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_APDU_TYPE_CHARACTER_STRING_HPP

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/character_string.hpp>
#include <bacnet/apdu/type/character_string_generator.hpp>
#include <bacnet/apdu/type/detail/character_string_grammar.hpp>


bool is_equal(const bacnet::apdu::type::character_string& a, const bacnet::apdu::type::character_string& b) {
  if(a.encoding_ != b.encoding_) {
    return false;
  }
  if(a.value_.compare(b.value_) != 0) {
    return false;
  }
  if(a.tag_.number() != b.tag_.number()) {
    return false;
  }
  if(a.tag_.is_context_tag() != b.tag_.is_context_tag()) {
    return false;
  }
  if(a.tag_.length_value_type() != b.tag_.length_value_type()) {
    return false;
  }
  return true;
}


BOOST_AUTO_TEST_SUITE( apdu_type_character_string )

BOOST_AUTO_TEST_CASE( test_case1 ) {


    bacnet::apdu::type::tag tag;
    bacnet::apdu::type::character_string character_string_to_generate;
    bacnet::apdu::type::character_string character_string_parsed;

    bacnet::binary_data generated;
    bacnet::binary_data generation_expected;


    std::string string_to_generate("Français");

    generation_expected.push_back(0x75); //tag
    generation_expected.push_back(0x0a); //extended length
    generation_expected.push_back(0x00); //encoding
    generation_expected.push_back(0x46); //string
    generation_expected.push_back(0x72);
    generation_expected.push_back(0x61);
    generation_expected.push_back(0x6E);
    generation_expected.push_back(0xC3);
    generation_expected.push_back(0xA7);
    generation_expected.push_back(0x61);
    generation_expected.push_back(0x69);
    generation_expected.push_back(0x73);
    tag.is_context_tag(false);
    tag.number(7);
    tag.length_value_type(string_to_generate.size()+1);

    character_string_to_generate.tag_ = tag;
    character_string_to_generate.encoding_ = bacnet::apdu::type::string_encoding_type::iso_10646_utf_8;
    character_string_to_generate.value_ = string_to_generate;


    generated = bacnet::apdu::type::generate(character_string_to_generate);

    BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated, character_string_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(character_string_to_generate, character_string_parsed), "failed parsed is not expected");

  }

BOOST_AUTO_TEST_SUITE_END()

#endif /*NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_APDU_TYPE_CHARACTER_STRING_HPP*/