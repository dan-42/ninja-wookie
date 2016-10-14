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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_WHO_IS_GRAMMA_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_WHO_IS_GRAMMA_HPP

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/service/who_is.hpp>

#include <bacnet/apdu/type/detail/primitive/unsigned_integer_grammar.hpp>

namespace bacnet { namespace service { namespace service { namespace detail {


namespace service = bacnet::service::service;
namespace apdu    = bacnet::apdu::type;

namespace parser {


using namespace boost::spirit;
using namespace boost::spirit::qi;
using boost::spirit::qi::rule;
using bacnet::apdu::type::detail::parser::unsigned_integer_grammar;




template<typename Iterator>
struct who_is_grammar : grammar<Iterator, service::who_is()> {


  rule<Iterator, service::who_is()>  start_rule;

  rule<Iterator, boost::optional<uint32_t>()>  low_limit_rule;
  rule<Iterator, boost::optional<uint32_t>()>  height_limit_rule;

  unsigned_integer_grammar<Iterator> tag_0_rule_{0};
  unsigned_integer_grammar<Iterator> tag_1_rule_{1};


  who_is_grammar() : who_is_grammar::base_type(start_rule) {

    start_rule        =  byte_(uint8_t(service::detail::service_choice<service::who_is>::value))
                      >> low_limit_rule
                      >> height_limit_rule;

    low_limit_rule    = -tag_0_rule_;
    height_limit_rule = -tag_1_rule_;
    start_rule.name("start_rule");
    low_limit_rule.name("low_limit_rule");
    height_limit_rule.name("height_limit_rule");
    /*debug(start_rule);
    debug(low_limit_rule);
    debug(height_limit_rule);*/
  }


};


}



namespace generator {


using namespace boost::spirit;
using namespace boost::spirit::karma;
using boost::spirit::karma::rule;


using bacnet::apdu::type::detail::generator::unsigned_integer_grammar;

template<typename Iterator>
struct who_is_grammar : grammar<Iterator, service::who_is()> {


  rule<Iterator, service::who_is()>  start_rule;

  rule<Iterator, uint32_t()>  low_limit_rule;
  rule<Iterator, uint32_t()>  height_limit_rule;


  unsigned_integer_grammar<Iterator> tag_0_rule_{0};
  unsigned_integer_grammar<Iterator> tag_1_rule_{1};


  who_is_grammar() : who_is_grammar::base_type(start_rule) {

    start_rule        = // byte_(uint8_t(uncomfirmed_service::who_is))
                      //<<
                      -low_limit_rule
                      << -height_limit_rule
                      ;

    low_limit_rule    = tag_0_rule_;
    height_limit_rule = tag_1_rule_;


    start_rule.name("who_is_grammar::start_rule");
    low_limit_rule.name("who_is_grammar::low_limit_rule");
    height_limit_rule.name("who_is_grammar::height_limit_rule");

    debug(start_rule);
    debug(low_limit_rule);
    debug(height_limit_rule);

  }

};


}


}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_WHO_IS_GRAMMA_HPP
