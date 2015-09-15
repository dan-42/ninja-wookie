//
// Created by schoko on 9/13/15.
//

#ifndef NINJA_WOOKIE_UNSIGNED_INTEGER_GENERATOR_HPP_HPP
#define NINJA_WOOKIE_UNSIGNED_INTEGER_GENERATOR_HPP_HPP

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/detail/unsigned_integer_grammar.hpp>

namespace  bacnet { namespace apdu { namespace type {

static bacnet::binary_data generate(const unsigned_integer &v) {
  using namespace bacnet::apdu;
  bacnet::binary_data binary;

  std::back_insert_iterator <bacnet::binary_data> sink(binary);
  type::detail::generator::unsigned_integer_grammar<decltype(sink)> generator;
  bool result = false;
  try {
    result = boost::spirit::karma::generate(sink, generator, v);
  }
  catch (std::exception &e) {
    std::cerr << "exception: apdu generate  unsigned_integer" << e.what() << std::endl;
  }
  if (!result) {
    return bacnet::binary_data();
  }

  return binary;
}


}}}







#endif //NINJA_WOOKIE_UNSIGNED_INTEGER_GENERATOR_HPP_HPP
