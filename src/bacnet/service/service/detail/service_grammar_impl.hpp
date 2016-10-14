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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_GRAMMAR_IMPL_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_GRAMMAR_IMPL_HPP


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/service/service.hpp>
#include <bacnet/service/service/detail/i_am_garmmar.hpp>
#include <bacnet/service/service/detail/read_property_request_grammar.hpp>
#include <bacnet/service/service/detail/read_property_ack_grammar.hpp>
#include <bacnet/service/service/detail/who_is_grammar.hpp>
#include <bacnet/service/service/detail/reinitialize_device_grammar.hpp>

namespace bacnet { namespace service { namespace service { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::service;
using namespace bacnet::service::service;

  template<typename Iterator>
  struct unconfirmed_service_grammar : grammar<Iterator, service::unconfirmed::service()> {
    rule<Iterator, unconfirmed::service()>   start_rule;
    who_is_grammar<Iterator>                 who_is_grammar_;
    i_am_grammar<Iterator>                   i_am_grammar_;
    reinitialize_device_grammar<Iterator>    reinitialize_device_grammar_;
    unconfirmed_service_grammar() : unconfirmed_service_grammar::base_type(start_rule) {
      start_rule  =  who_is_grammar_
                  |  i_am_grammar_
                  ;
    }
  };

  template<typename Iterator>
  struct confirmed_request_grammar : grammar<Iterator, confirmed::request()> {
    rule<Iterator, confirmed::request()>        start_rule;
    read_property_request_grammar<Iterator>     read_property_request_grammar_;
    reinitialize_device_grammar<Iterator>       reinitialize_device_grammar_;
    confirmed_request_grammar() : confirmed_request_grammar::base_type(start_rule) {
      start_rule  =  reinitialize_device_grammar_
                  |  read_property_request_grammar_
                  ;
    }
  };

  template<typename Iterator>
  struct confirmed_response_grammar : grammar<Iterator, confirmed::response()> {
    rule<Iterator, confirmed::response()>   start_rule;
    read_property_ack_grammar<Iterator>     read_property_ack_grammar_;
    confirmed_response_grammar() : confirmed_response_grammar::base_type(start_rule) {
      start_rule  =  read_property_ack_grammar_
                  |  eps
                  ;
    }
  };


}}}}}


namespace bacnet { namespace service { namespace service { namespace detail {  namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::service;

  template<typename Iterator>
  struct unconfirmed_service_grammar : grammar<Iterator, unconfirmed::service()> {
    rule<Iterator,  unconfirmed::service()>     start_rule;
    who_is_grammar<Iterator>                    who_is_grammar_;
    i_am_grammar<Iterator>                      i_am_grammar_;
    unconfirmed_service_grammar() : unconfirmed_service_grammar::base_type(start_rule) {
      start_rule  =  who_is_grammar_
                  |  i_am_grammar_
                  ;
    }
  };

  template<typename Iterator>
  struct confirmed_request_grammar : grammar<Iterator, confirmed::request()> {
    rule<Iterator,  confirmed::request()>       start_rule;
    read_property_request_grammar<Iterator>     read_property_request_grammar_;
    reinitialize_device_grammar<Iterator>       reinitialize_device_grammar_;
    confirmed_request_grammar() : confirmed_request_grammar::base_type(start_rule) {
      start_rule =  reinitialize_device_grammar_
                 |  read_property_request_grammar_
                 ;
    }
  };

  template<typename Iterator>
  struct confirmed_response_grammar : grammar<Iterator, confirmed::response()> {
    rule<Iterator,  confirmed::response()>          start_rule;
    read_property_ack_grammar<Iterator>             read_property_ack_grammar_;

    confirmed_response_grammar() : confirmed_response_grammar::base_type(start_rule) {
      start_rule =  read_property_ack_grammar_
                 ;
    }
  };

}}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_GRAMMAR_IMPL_HPP
