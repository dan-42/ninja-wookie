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


#define BOOST_TEST_MODULE test ninja wookie bacnet apdu types date
#include <boost/test/included/unit_test.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/date.hpp>
#include <bacnet/apdu/type/detail/date_grammar.hpp>


bool is_equal(const bacnet::apdu::type::date& a, const bacnet::apdu::type::date& b) {
  if(a.year_minus_1900 != b.year_minus_1900) {
    return false;
  }
  if(a.month != b.month) {
     return false;
  }
  if(a.day_of_month != b.day_of_month) {
     return false;
  }
  if(a.day_of_week != b.day_of_week) {
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

BOOST_AUTO_TEST_SUITE( apdu_type_date )

BOOST_AUTO_TEST_CASE( test_case1 ) {

using namespace bacnet::apdu::type;

  bacnet::apdu::type::detail::generator::date_grammar< std::back_insert_iterator <bacnet::binary_data> >  grammar_gen;
  bacnet::apdu::type::detail::parser::date_grammar<bacnet::parse_iterator>                                grammar_parse;
  {
    bacnet::apdu::type::date date_to_generate;
    bacnet::apdu::type::date date_parsed;
    bacnet::binary_data generated;
    bacnet::binary_data generation_expected;
    generation_expected.push_back(0xA4); //tag
    generation_expected.push_back(0x5B);
    generation_expected.push_back(0x01);
    generation_expected.push_back(0x18);
    generation_expected.push_back(0x04);


    date_to_generate.year_minus_1900 = 91;
    date_to_generate.month           = 1;
    date_to_generate.day_of_month    = 24;
    date_to_generate.day_of_week     = 4;

    std::cout << "date_to_generate " << date_to_generate << std::endl;

    std::back_insert_iterator <bacnet::binary_data> sink(generated);
    bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, date_to_generate );
    BOOST_TEST(success_generating, " failed to generate data");

    bacnet::print(generated);

    auto start = generated.begin();
    auto end = generated.end();
    auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, date_parsed);
    BOOST_TEST(success_parsing, " failed parsing data");



    BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");
    BOOST_TEST(is_equal(date_to_generate, date_parsed), "failed parsed is not expected");

    std::cout << "parsed date " << date_parsed << std::endl;
  }

  std::cout << std::endl << "--------------------------------------------------------------" << std::endl;


}

BOOST_AUTO_TEST_SUITE_END()

