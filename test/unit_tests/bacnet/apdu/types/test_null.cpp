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


#define BOOST_TEST_MODULE test ninja wookie bacnet apdu types null
#include <boost/test/included/unit_test.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/null.hpp>
#include <bacnet/apdu/type/detail/null_grammar.hpp>


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

BOOST_AUTO_TEST_SUITE( apdu_type_null )

BOOST_AUTO_TEST_CASE( test_case_application_tag ) {

  bacnet::apdu::type::null to_generate;
  bacnet::apdu::type::null parsed;

  bacnet::binary_data generated;
  bacnet::binary_data generation_expected;


  generation_expected.push_back(0x00); //application tag, inclusive value

  std::back_insert_iterator <bacnet::binary_data> sink(generated);

  bacnet::apdu::type::detail::generator::null_grammar<decltype(sink)> grammar_gen;
  bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, to_generate );
  BOOST_TEST(success_generating, " failed to generate data");

  bacnet::print(generated);

  auto start = generated.begin();
  auto end = generated.end();
  bacnet::apdu::type::detail::parser::null_grammar<decltype(start)> grammar_parse;
  auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, parsed);
  BOOST_TEST(success_parsing, " failed parsing data");



  BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");

  std::cout << "parsed null " << std::endl;

}



BOOST_AUTO_TEST_CASE( test_case_context_tag ) {

  bacnet::apdu::type::null to_generate;
  bacnet::apdu::type::null parsed;

  bacnet::binary_data generated;
  bacnet::binary_data generation_expected;


  generation_expected.push_back(0x38); //context tag 3, inclusive value

  std::back_insert_iterator <bacnet::binary_data> sink(generated);

  bacnet::apdu::type::detail::generator::null_grammar<decltype(sink)> grammar_gen(3);
  bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, to_generate );
  BOOST_TEST(success_generating, " failed to generate data");

  bacnet::print(generated);

  auto start = generated.begin();
  auto end = generated.end();
  bacnet::apdu::type::detail::parser::null_grammar<decltype(start)> grammar_parse;
  auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, parsed);
  BOOST_TEST(success_parsing, " failed parsing data");



  BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");


  std::cout << "parsed null " << std::endl;

}


BOOST_AUTO_TEST_SUITE_END()

