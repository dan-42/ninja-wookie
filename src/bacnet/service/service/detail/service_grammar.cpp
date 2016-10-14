/**
 * ninja-wooki, is a BACnet stack C++ library
 *
 * Copyright (C) 2015 Daniel Friedrich
 *
 * This file is part of ninja-wooki.
 *
 * ninja-wooki is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) service later version.
 *
 * ninja-wooki is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with Mupen64PlusAE. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Daniel Friedrich
 */

#include <bacnet/service/service/detail/service_grammar.hpp>
#include <bacnet/service/service/detail/service_grammar_impl.hpp>

#include <pre/json/to_json.hpp>

bacnet::service::service::unconfirmed::service bacnet::service::service::detail::parse_unconfirmed(bacnet::binary_data& binary_data) {
  bacnet::service::service::unconfirmed::service parsed{};
  auto start = binary_data.begin();
  auto end = binary_data.end();
  bacnet::service::service::detail::parser::unconfirmed_service_grammar<bacnet::parse_iterator> grammar;
  auto success = boost::spirit::qi::parse(start, end, grammar, parsed);
  if(!success) {
    std::cout << "service::parse_unconfirmed() error parsing " << std::endl;
  }
  return parsed;
}
bacnet::service::service::confirmed::request bacnet::service::service::detail::parse_confirmed_request(bacnet::binary_data& binary_data) {
  bacnet::service::service::confirmed::request parsed{};
  auto start = binary_data.begin();
  auto end = binary_data.end();
  bacnet::service::service::detail::parser::confirmed_request_grammar<bacnet::parse_iterator> grammar;
  auto success = boost::spirit::qi::parse(start, end, grammar, parsed);
  return parsed;
}

bacnet::service::service::confirmed::response bacnet::service::service::detail::parse_confirmed_response(bacnet::binary_data& binary_data) {
  bacnet::service::service::confirmed::response parsed{};
  auto start = binary_data.begin();
  auto end = binary_data.end();
  bacnet::service::service::detail::parser::confirmed_response_grammar<bacnet::parse_iterator> grammar;
  auto success = boost::spirit::qi::parse(start, end, grammar, parsed);
  return parsed;
}

///////////////////////////////////////////////////////////////////////////////


bacnet::binary_data bacnet::service::service::detail::generate_unconfirmed(const bacnet::service::service::unconfirmed::service &service) {
  bacnet::binary_data data{};
  bacnet::generate_iterator sink(data);
  bacnet::service::service::detail::generator::unconfirmed_service_grammar<bacnet::generate_iterator> grammar;
  auto success = boost::spirit::karma::generate(sink, grammar, service);
  std::cout << "generate_unconfirmed() ";
  print(data);
  if(success) {
    return data;
  }
  else {
    return bacnet::binary_data{};
  }
}
bacnet::binary_data bacnet::service::service::detail::generate_confirmed_request(const bacnet::service::service::confirmed::request &service) {
  bacnet::binary_data data;
  bacnet::generate_iterator sink(data);
  bacnet::service::service::detail::generator::confirmed_request_grammar<bacnet::generate_iterator> grammar;
  auto success = boost::spirit::karma::generate(sink, grammar, service);
  if(success) {
    return data;
  }
  else {
    return bacnet::binary_data{};
  }
}
bacnet::binary_data bacnet::service::service::detail::generate_confirmed_response(const bacnet::service::service::confirmed::response &service) {
  bacnet::binary_data data;
  bacnet::generate_iterator sink(data);
  bacnet::service::service::detail::generator::confirmed_response_grammar<bacnet::generate_iterator> grammar;
  auto success = boost::spirit::karma::generate(sink, grammar, service);
  if(success) {
    return data;
  }
  else {
    return bacnet::binary_data{};
  }
}



