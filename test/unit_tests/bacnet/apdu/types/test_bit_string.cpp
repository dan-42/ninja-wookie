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


#define BOOST_TEST_MODULE test ninja wookie bacnet apdu types bit string
#include <boost/test/included/unit_test.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/type/bit_string.hpp>
#include <bacnet/apdu/type/detail/bit_string_grammar.hpp>


bool is_equal(const bacnet::type::bit_string& a, const bacnet::type::bit_string& b) {
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

BOOST_AUTO_TEST_SUITE( apdu_type_bit_string )

BOOST_AUTO_TEST_CASE( test_case1 ) {

using namespace bacnet::apdu::type;

  bacnet::apdu::type::detail::generator::bit_string_grammar< std::back_insert_iterator <bacnet::binary_data> >  grammar_gen;
  bacnet::apdu::type::detail::parser::bit_string_grammar<bacnet::parse_iterator>                                grammar_parse;
  {
    bacnet::type::bit_string bit_string_to_generate;
    bacnet::type::bit_string bit_string_parsed;
    bacnet::binary_data generated;
    bacnet::binary_data generation_expected;
    generation_expected.push_back(0x82); //tag
    generation_expected.push_back(0x03); //unused bit
    generation_expected.push_back(0xA8); //string

    bit_string_to_generate.push_back(true);
    bit_string_to_generate.push_back(false);
    bit_string_to_generate.push_back(true);
    bit_string_to_generate.push_back(false);
    bit_string_to_generate.push_back(true);

    std::cout << "bit_string_to_generate " << bit_string_to_generate << std::endl;

    std::back_insert_iterator <bacnet::binary_data> sink(generated);
    bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, bit_string_to_generate );
    BOOST_TEST(success_generating, " failed to generate data");

    bacnet::print(generated);

    auto start = generated.begin();
    auto end = generated.end();
    auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, bit_string_parsed);
    BOOST_TEST(success_parsing, " failed parsing data");



    BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");
    BOOST_TEST(is_equal(bit_string_to_generate, bit_string_parsed), "failed parsed is not expected");

    std::cout << "parsed bit string " << bit_string_parsed << std::endl;
  }

  std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
  {
    bacnet::type::bit_string bit_string_to_generate;
    bacnet::type::bit_string bit_string_parsed;
    bacnet::binary_data generated;
    bit_string_to_generate.push_back(true);
    bit_string_to_generate.push_back(true);
    bit_string_to_generate.push_back(true);
    bit_string_to_generate.push_back(true);
    bit_string_to_generate.push_back(false);
    bit_string_to_generate.push_back(false);
    bit_string_to_generate.push_back(false);
    bit_string_to_generate.push_back(false);
    bit_string_to_generate.push_back(true);
    bit_string_to_generate.push_back(false);
    bit_string_to_generate.push_back(true);

    std::cout << "bit_string_to_generate " << bit_string_to_generate << std::endl;

    std::back_insert_iterator <bacnet::binary_data> sink(generated);
    bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, bit_string_to_generate );
    BOOST_TEST(success_generating, " failed to generate data");
    std::cout << "bit_string_generated : " ;
    bacnet::print(generated);

    auto start = generated.begin();
    auto end   = generated.end();
    auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, bit_string_parsed);
    BOOST_TEST(success_parsing, " failed parsing data");

    BOOST_TEST(is_equal(bit_string_to_generate, bit_string_parsed), "failed parsed is not expected");

    std::cout << "parsed bit string " << bit_string_parsed << std::endl;
  }

  std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
  {
    bacnet::type::bit_string bit_string_to_generate;
    bacnet::type::bit_string bit_string_parsed;
    bacnet::binary_data generated;
    std::cout << "bit_string_to_generate " << bit_string_to_generate << std::endl;


    std::back_insert_iterator <bacnet::binary_data> sink(generated);
    bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, bit_string_to_generate );
    BOOST_TEST(success_generating, " failed to generate data");
    std::cout << "bit_string_generated : " ;
    bacnet::print(generated);

    auto start = generated.begin();
    auto end   = generated.end();
    auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, bit_string_parsed);
    BOOST_TEST(success_parsing, " failed parsing data");

    BOOST_TEST(is_equal(bit_string_to_generate, bit_string_parsed), "failed parsed is not expected");

    std::cout << "parsed bit string " << bit_string_parsed << std::endl;
  }

  std::cout << std::endl << "--------------------------------------------------------------" << std::endl;
   {
     bacnet::type::bit_string bit_string_to_generate;
     bacnet::type::bit_string bit_string_parsed;
     bacnet::binary_data generated;
     std::srand(42);
     for(int i = 0; i < 1337; ++i) {
       int random_variable = std::rand() % 2;
       bit_string_to_generate.push_back( (random_variable == 1) );
     }

     std::cout << "bit_string_to_generate " << bit_string_to_generate << std::endl;

     std::back_insert_iterator <bacnet::binary_data> sink(generated);
     bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, bit_string_to_generate );
     BOOST_TEST(success_generating, " failed to generate data");
     std::cout << "bit_string_generated : " ;
     bacnet::print(generated);

     auto start = generated.begin();
     auto end   = generated.end();
     auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, bit_string_parsed);
     BOOST_TEST(success_parsing, " failed parsing data");

     BOOST_TEST(is_equal(bit_string_to_generate, bit_string_parsed), "failed parsed is not expected");

     std::cout << "parsed bit string " << bit_string_parsed << std::endl;
   }


}

BOOST_AUTO_TEST_SUITE_END()

