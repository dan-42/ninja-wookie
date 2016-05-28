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


#define BOOST_TEST_MODULE test ninja wookie bacnet apdu types enumerated
#include <boost/test/included/unit_test.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/detail/enumeration_grammar.hpp>
#include <bacnet/type/enumerated.hpp>

bool is_equal(const  bacnet::type::enumerated &a, const bacnet::type::enumerated& b) {
  if(a.value != b.value) {
    return false;
  }
  if(a.type != b.type) {
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

BOOST_AUTO_TEST_SUITE( apdu_type_enumerated )

BOOST_AUTO_TEST_CASE( test_case1 ) {

    bacnet::type::enumerated enumerated_parsed;
    bacnet::binary_data      generated;
    bacnet::type::enumerated to_generate;



    {
      to_generate.value = 1337;
      enumerated_parsed = bacnet::type::enumerated{};
      std::back_insert_iterator <bacnet::binary_data> sink(generated);

      bacnet::apdu::type::detail::generator::enumeration_grammar<decltype(sink)> grammar_gen;
      auto success_generating = boost::spirit::karma::generate(sink, grammar_gen, to_generate );
      BOOST_TEST(success_generating, " failed to generate data");

      bacnet::print(generated);

      auto start = generated.begin();
      auto end = generated.end();
      bacnet::apdu::type::detail::parser::enumeration_grammar<decltype(start)> grammar_parse;
      auto success_parsing = boost::spirit::qi::parse(start, end, grammar_parse, enumerated_parsed);
      BOOST_TEST(success_parsing, " failed parsing data");

      BOOST_TEST(is_equal(to_generate, enumerated_parsed), " failed generated and parsed ar not the same");
    }



  }



BOOST_AUTO_TEST_SUITE_END()

