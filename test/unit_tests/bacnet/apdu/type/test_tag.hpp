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

#ifndef NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_APDU_TYPE_TAG_HPP
#define NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_APDU_TYPE_TAG_HPP

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/apdu/type/detail/tag_grammar.hpp>




bool is_equal(const bacnet::apdu::type::tag& a, const bacnet::apdu::type::tag& b) {
  if(a.is_context_tag() != b.is_context_tag()) {
    return false;
  }
  if(a.length_value_type() != b.length_value_type()) {
    return false;
  }
  if(a.number() != b.number()) {
    return false;
  }
  return true;
}


namespace  bacnet { namespace apdu { namespace type {
static bacnet::binary_data generate(const bacnet::apdu::type::tag &tag_) {
  using namespace bacnet::apdu;
  bacnet::binary_data binary;

  std::back_insert_iterator<bacnet::binary_data> sink(binary);
  type::detail::generator::tag_grammar<decltype(sink)> generator;
  bool result = false;
  try {
    result = boost::spirit::karma::generate(sink, generator, tag_);
  }
  catch (std::exception &e) {
    BOOST_FAIL( "exception: cant generate tag" );
  }
  if (!result) {
    return bacnet::binary_data();
  }

  return binary;
}


static bool parse(bacnet::binary_data& data, bacnet::apdu::type::tag &tag_) {
  using namespace bacnet::apdu;

  using namespace bacnet::apdu;

  auto start = data.begin();
  auto end = data.end();

  type::detail::parser::tag_grammar<decltype(start)> parser;
  bool has_succeeded = false;
  try {
    has_succeeded = boost::spirit::qi::parse(start, end, parser, tag_);
  }
  catch (std::exception &e) {
    BOOST_FAIL( "exception: cant parse tag" );
  }
  if (has_succeeded) {
    data.erase(data.begin(), start);
    return true;
  }
  BOOST_FAIL(" error parse tag");
  return false;
}


}}}

BOOST_AUTO_TEST_SUITE( apdu_type_tag )

BOOST_AUTO_TEST_CASE( test_case1 ) {



    bacnet::apdu::type::tag tag_to_generate;
    bacnet::binary_data generated_tag;
    bacnet::binary_data tag_generation_expected;

    bacnet::apdu::type::tag tag_parsed;
    bacnet::apdu::type::tag tag_parse_expected;



    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(4);
    tag_generation_expected.push_back(0xc4);

    BOOST_TEST(tag_to_generate.is_context_tag() == false, " context is wrong");
    BOOST_TEST(tag_to_generate.number() == (uint8_t)12, "number is wrong");
    BOOST_TEST(tag_to_generate.length_value_type() == (uint32_t)4, "length value is wrong");


    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");



    std::cout << "-----tag_extended_number---15--------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(15);
    tag_to_generate.length_value_type(4);

    tag_generation_expected.push_back(0xf4);
    tag_generation_expected.push_back(0xf);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");








    std::cout << "-----tag_extended_number----16-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(16);
    tag_to_generate.length_value_type(4);

    tag_generation_expected.push_back(0xf4);
    tag_generation_expected.push_back(0x10);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);

    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");





    std::cout << "-----tag_extended_number----17-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(17);
    tag_to_generate.length_value_type(4);

    tag_generation_expected.push_back(0xf4);
    tag_generation_expected.push_back(0x11);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);

    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");




    std::cout << "-----tag_extended_number----254-------------" << std::endl;

    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(254);
    tag_to_generate.length_value_type(4);

    tag_generation_expected.push_back(0xf4);
    tag_generation_expected.push_back(0xfe);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);

    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");





    std::cout << "-----tag_extended_length----4-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(4);

    tag_generation_expected.push_back(0xc4);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");


    std::cout << "-----tag_extended_length----5-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(5);
    generated_tag = bacnet::apdu::type::generate(tag_to_generate);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0x05);

    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");



    std::cout << "-----tag_extended_length----6-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(6);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0x06);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);

    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");




    std::cout << "-----tag_extended_length----253-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(253);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0xfd);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);

    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");



    std::cout << "-----tag_extended_length----254-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(254);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0xfe);
    tag_generation_expected.push_back(0x00);
    tag_generation_expected.push_back(0xfe);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");



    std::cout << "-----tag_extended_length----255-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(255);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0xfe);
    tag_generation_expected.push_back(0x00);
    tag_generation_expected.push_back(0xff);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");



    
    std::cout << "-----tag_extended_length----65534-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(65534);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0xfe);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xfe);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");



    
    std::cout << "-----tag_extended_length----65535-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(65535);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0xfe);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");





    std::cout << "-----tag_extended_length----65536-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(65536);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0x00);
    tag_generation_expected.push_back(0x01);
    tag_generation_expected.push_back(0x00);
    tag_generation_expected.push_back(0x00);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");


    std::cout << "-----tag_extended_length----65537-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(65537);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0x00);
    tag_generation_expected.push_back(0x01);
    tag_generation_expected.push_back(0x00);
    tag_generation_expected.push_back(0x01);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");




    std::cout << "-----tag_extended_length----4294967294-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(4294967294);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xfe);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");




    std::cout << "-----tag_extended_length----4294967295-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(12);
    tag_to_generate.length_value_type(4294967295);

    tag_generation_expected.push_back(0xc5);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");


    

    
    std::cout << "--tag_extended_number 254---tag_extended_length----4294967295-------------" << std::endl;
    tag_generation_expected.clear();
    tag_to_generate = decltype(tag_to_generate){};

    tag_to_generate.is_context_tag(false);
    tag_to_generate.number(254);
    tag_to_generate.length_value_type(4294967295);

    tag_generation_expected.push_back(0xf5);
    tag_generation_expected.push_back(0xfe);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);
    tag_generation_expected.push_back(0xff);

    generated_tag = bacnet::apdu::type::generate(tag_to_generate);
    BOOST_TEST(is_equal(tag_generation_expected, generated_tag), "fail tag generation failed");
    BOOST_TEST(bacnet::apdu::type::parse(generated_tag, tag_parsed), "fail parse simple tag");
    BOOST_TEST(is_equal(tag_to_generate, tag_parsed), "failed parsed is not expected");


  }

BOOST_AUTO_TEST_SUITE_END()

#endif /*NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_APDU_TYPE_TAG_HPP*/