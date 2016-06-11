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


#define BOOST_TEST_MODULE test ninja wookie bacnet apdu types character string
#include <boost/test/included/unit_test.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/type/character_string.hpp>
#include <bacnet/apdu/type/detail/primitive/character_string_grammar.hpp>


bool is_equal(const bacnet::type::character_string& a, const bacnet::type::character_string& b) {
  if(a.encoding != b.encoding) {
    return false;
  }
  if(a.value.compare(b.value) != 0) {
    return false;
  }
  return true;
}
bool is_equal(const bacnet::binary_data& a, const bacnet::binary_data& b) {
  if(a.size() != b.size()) {
    return false;
  }
  for(std::size_t idx = 0; idx < a.size(); ++idx) {
    if(a.at(idx) != b.at(idx)) {
      return false;
    }
  }
  return true;
}

BOOST_AUTO_TEST_SUITE( apdu_type_character_string )

BOOST_AUTO_TEST_CASE( test_case1 ) {

    bacnet::type::character_string character_string_to_generate;
    bacnet::type::character_string character_string_parsed;

    bacnet::binary_data generated;
    bacnet::binary_data generation_expected;


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

    character_string_to_generate.encoding = bacnet::type::string_encoding_type::iso_10646_utf_8;
    character_string_to_generate.value    = std::string {"Français"};



    std::back_insert_iterator <bacnet::binary_data> sink(generated);

    bacnet::apdu::type::detail::generator::character_string_grammar<decltype(sink)> grammar_gen;
    bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, character_string_to_generate );
    BOOST_TEST(success_generating, " failed to generate data");

    bacnet::print(generated);

    auto start = generated.begin();
    auto end = generated.end();
    bacnet::apdu::type::detail::parser::character_string_grammar<decltype(start)> grammar_parse;
    auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, character_string_parsed);
    BOOST_TEST(success_parsing, " failed parsing data");



    BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");
    BOOST_TEST(is_equal(character_string_to_generate, character_string_parsed), "failed parsed is not expected");

    std::cout << "parsed string " << character_string_parsed.value << std::endl;

  }

BOOST_AUTO_TEST_SUITE_END()

