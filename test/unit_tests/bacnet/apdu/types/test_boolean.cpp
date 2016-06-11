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


#define BOOST_TEST_MODULE test ninja wookie bacnet apdu types boolean
#include <boost/test/included/unit_test.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/detail/primitive/boolean_grammar.hpp>


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

BOOST_AUTO_TEST_SUITE( apdu_type_boolean )

BOOST_AUTO_TEST_CASE( test_application_tag ) {
  {
    bool to_generate{false};
    bool parsed{false};

    bacnet::binary_data generated;
    bacnet::binary_data generation_expected;


    generation_expected.push_back(0x11); //application tag= 1, including value true
    to_generate = true;

    std::back_insert_iterator <bacnet::binary_data> sink(generated);

    bacnet::apdu::type::detail::generator::boolean_grammar<decltype(sink)> grammar_gen;
    bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, to_generate );
    BOOST_TEST(success_generating, " failed to generate data");

    std::cout << "generated: " ;
    bacnet::print(generated);

    auto start = generated.begin();
    auto end = generated.end();
    bacnet::apdu::type::detail::parser::boolean_grammar<decltype(start)> grammar_parse;
    auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, parsed);
    BOOST_TEST(success_parsing, " failed parsing data");



    BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");
    BOOST_TEST(to_generate == parsed, "failed parsed is not expected");

    std::cout << "parsed boolean " <<  (parsed ? "true" : "false") << std::endl;
  }
  std::cout << "-----------------------------------------------" << std::endl;

  {
      bool to_generate{false};
      bool parsed{true};
      bacnet::binary_data generated;
      bacnet::binary_data generation_expected;


      generation_expected.push_back(0x10); //application tag= 1, including value true
      to_generate = false;

      std::back_insert_iterator <bacnet::binary_data> sink(generated);
      bacnet::apdu::type::detail::generator::boolean_grammar<decltype(sink)> grammar_gen;
      bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, to_generate );
      BOOST_TEST(success_generating, " failed to generate data");

      std::cout << "generated: " ;
      bacnet::print(generated);

      auto start = generated.begin();
      auto end = generated.end();
      bacnet::apdu::type::detail::parser::boolean_grammar<decltype(start)> grammar_parse;
      auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, parsed);
      BOOST_TEST(success_parsing, " failed parsing data");



      BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");
      BOOST_TEST(to_generate == parsed, "failed parsed is not expected");

      std::cout << "parsed boolean " <<  (parsed ? "true" : "false") << std::endl;
    }
  std::cout << "-----------------------------------------------" << std::endl;
}


//////////////////////////////////////////////////////////////////////////////////////////////////


BOOST_AUTO_TEST_CASE( test_context_tag ) {
  {
    bool to_generate{false};
    bool parsed{false};

    bacnet::binary_data generated;
    bacnet::binary_data generation_expected;


    generation_expected.push_back(0x69); //context tag = 6
    generation_expected.push_back(0x00); //value false
    to_generate = false;

    std::back_insert_iterator <bacnet::binary_data> sink(generated);

    bacnet::apdu::type::detail::generator::boolean_grammar<decltype(sink)> grammar_gen(6);
    bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, to_generate );
    BOOST_TEST(success_generating, " failed to generate data");

    std::cout << "generated: " ;
    bacnet::print(generated);

    auto start = generated.begin();
    auto end = generated.end();
    bacnet::apdu::type::detail::parser::boolean_grammar<decltype(start)> grammar_parse(6);
    auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, parsed);
    BOOST_TEST(success_parsing, " failed parsing data");



    BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");
    BOOST_TEST(to_generate == parsed, "failed parsed is not expected");

    std::cout << "parsed boolean " <<  (parsed ? "true" : "false") << std::endl;
  }
  std::cout << "-----------------------------------------------" << std::endl;

  {
      bool to_generate{false};
      bool parsed{true};
      bacnet::binary_data generated;
      bacnet::binary_data generation_expected;

      generation_expected.push_back(0xF9); //context tag = 27
      generation_expected.push_back(0x1B); //context tag extended
      generation_expected.push_back(0x01); //value true
      to_generate = true;

      std::back_insert_iterator <bacnet::binary_data> sink(generated);
      bacnet::apdu::type::detail::generator::boolean_grammar<decltype(sink)> grammar_gen(27);
      bool success_generating = boost::spirit::karma::generate(sink, grammar_gen, to_generate );
      BOOST_TEST(success_generating, " failed to generate data");
      std::cout << "generated: " ;
      bacnet::print(generated);

      auto start = generated.begin();
      auto end = generated.end();
      bacnet::apdu::type::detail::parser::boolean_grammar<decltype(start)> grammar_parse(27);
      auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, parsed);
      BOOST_TEST(success_parsing, " failed parsing data");



      BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");
      BOOST_TEST(to_generate == parsed, "failed parsed is not expected");

      std::cout << "parsed boolean " <<  (parsed ? "true" : "false") << std::endl;
    }
  std::cout << "-----------------------------------------------" << std::endl;

}


BOOST_AUTO_TEST_SUITE_END()

