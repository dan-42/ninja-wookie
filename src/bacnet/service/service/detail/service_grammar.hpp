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

#ifndef NINJA_WOOKIE_SERVICE_GENERATOR_HPP
#define NINJA_WOOKIE_SERVICE_GENERATOR_HPP


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/service/service.hpp>
#include <bacnet/service/service/detail/i_am_garmmar.hpp>
#include <bacnet/service/service/detail/read_property_request_grammar.hpp>
#include <bacnet/service/service/detail/who_is_grammar.hpp>
#include <bacnet/service/service/detail/reinitialize_device_grammar.hpp>

namespace bacnet { namespace service { namespace service { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::service;

  template<typename Iterator>
  struct unconfirmed_service_grammar : grammar<Iterator, unconfirmed::possible_service()> {
    rule<Iterator, unconfirmed::possible_service()>   start_rule;
    who_is_grammar<Iterator>                          who_is_grammar_;
    i_am_grammar<Iterator>                            i_am_grammar_;
    reinitialize_device_grammar<Iterator>             reinitialize_device_grammar_;
    unconfirmed_service_grammar() : unconfirmed_service_grammar::base_type(start_rule) {
      start_rule  =
                     who_is_grammar_
                  |  i_am_grammar_
                  ;
    }
  };

  template<typename Iterator>
  struct confirmed_service_grammar : grammar<Iterator, confirmed::possible_service()> {
    rule<Iterator, confirmed::possible_service()>   start_rule;

    read_property_request_grammar<Iterator>                 read_property_grammar_;
    reinitialize_device_grammar<Iterator>           reinitialize_device_grammar_;
    confirmed_service_grammar() : confirmed_service_grammar::base_type(start_rule) {
      start_rule  =
                     reinitialize_device_grammar_
                  |  read_property_grammar_
                  ;
    }
  };


}}}}}


namespace bacnet { namespace service { namespace service { namespace detail {  namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::service;

  template<typename Iterator>
  struct unconfirmed_service_grammar : grammar<Iterator, unconfirmed::possible_service()> {
    rule<Iterator,  unconfirmed::possible_service()>  start_rule;
    who_is_grammar<Iterator>                          who_is_grammar_;
    i_am_grammar<Iterator>                            i_am_grammar_;
    reinitialize_device_grammar<Iterator>             reinitialize_device_grammar_;
    unconfirmed_service_grammar() : unconfirmed_service_grammar::base_type(start_rule) {

      start_rule  =
                     who_is_grammar_
                  |  i_am_grammar_
                  ;
    }
  };
  template<typename Iterator>
  struct confirmed_service_grammar : grammar<Iterator, confirmed::possible_service()> {
    rule<Iterator,  confirmed::possible_service()>    start_rule;
    read_property_request_grammar<Iterator>                 read_property_grammar_;
    reinitialize_device_grammar<Iterator>           reinitialize_device_grammar_;
    confirmed_service_grammar() : confirmed_service_grammar::base_type(start_rule) {
      start_rule =
                    reinitialize_device_grammar_
                 |  read_property_grammar_
                 ;
    }
  };


}}}}}








namespace bacnet { namespace service { namespace service { namespace detail {

  unconfirmed::possible_service parse_unconfirmed(bacnet::binary_data& binary_data) {
    unconfirmed::possible_service parsed{};
    auto start = binary_data.begin();
    auto end = binary_data.end();
    bacnet::service::service::detail::parser::unconfirmed_service_grammar<bacnet::parse_iterator> grammar;
    auto success = boost::spirit::qi::parse(start, end, grammar, parsed);
    if(!success) {
      std::cout << "service::parse_unconfirmed() error parsing " << std::endl;
    }
    return parsed;
  }
  confirmed::possible_service parse_confirmed(bacnet::binary_data& binary_data) {
    confirmed::possible_service parsed{};
    auto start = binary_data.begin();
    auto end = binary_data.end();
    bacnet::service::service::detail::parser::confirmed_service_grammar<bacnet::parse_iterator> grammar;
    auto success = boost::spirit::qi::parse(start, end, grammar, parsed);
    return parsed;
  }


  bacnet::binary_data generate_unconfirmed(const unconfirmed::possible_service &service) {
    bacnet::binary_data data;
    bacnet::generate_iterator sink(data);
    bacnet::service::service::detail::generator::unconfirmed_service_grammar<bacnet::generate_iterator> grammar;
    auto success = boost::spirit::karma::generate(sink, grammar, service);
    if(success) {
     return data;
    }
    else {
     return bacnet::binary_data{};
    }
  }
  bacnet::binary_data generate_confirmed(const confirmed::possible_service &service) {
    bacnet::binary_data data;
    bacnet::generate_iterator sink(data);
    bacnet::service::service::detail::generator::confirmed_service_grammar<bacnet::generate_iterator> grammar;
    auto success = boost::spirit::karma::generate(sink, grammar, service);
    if(success) {
    return data;
    }
    else {
      return bacnet::binary_data{};
    }
  }


}}}}

#endif //NINJA_WOOKIE_SERVICE_GENERATOR_HPP
