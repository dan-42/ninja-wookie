//
// Created by schoko on 9/13/15.
//

#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_OBJECT_IDENTIFIER_GENERATOR_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_OBJECT_IDENTIFIER_GENERATOR_HPP

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>

#include <bacnet/apdu/type/object_identifier.hpp>
#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/detail/object_identifier_grammar.hpp>



namespace  bacnet { namespace apdu { namespace type {

static bacnet::binary_data generate(const object_identifier &oi) {
  using namespace bacnet::apdu;
  bacnet::binary_data binary;

  std::back_insert_iterator <bacnet::binary_data> sink(binary);
  type::detail::generator::object_identifier_grammar<decltype(sink)> generator;
  bool result = false;
  try {
    result = boost::spirit::karma::generate(sink, generator, oi);
  }
  catch (std::exception &e) {
    std::cerr << "exception: apdu generate  unsigned_integer" << e.what() << std::endl;
  }
  if (!result) {
    return bacnet::binary_data();
  }

  return binary;
}


static bool parse(bacnet::binary_data& data, object_identifier &oi) {
  using namespace bacnet::apdu;

  auto start = data.begin();
  auto end = data.end();

  type::detail::parser::object_identifier_grammar<decltype(start)> parser;
  bool has_succeeded = false;
  try {
    has_succeeded = boost::spirit::qi::parse(start, end, parser, oi);
  }
  catch (std::exception &e) {
    std::cerr << "exception: apdu parse unsigned_integer" << e.what() << std::endl;
  }
  if (has_succeeded) {
    data.erase(data.begin(), start);
    return true;
  }

  return false;
}


}}}


#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_OBJECT_IDENTIFIER_GENERATOR_HPP
