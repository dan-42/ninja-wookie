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

#ifndef NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_SERVICE_REINITIALIZE_DEVICE_HPP
#define NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_SERVICE_REINITIALIZE_DEVICE_HPP

#include <iostream>
#include <boost/test/included/unit_test.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/service/reinitialize_device.hpp>
#include <bacnet/service/service/detail/reinitialize_device_grammar.hpp>


/*
bool is_equal(const bacnet::apdu::type::character_string& a, const bacnet::apdu::type::character_string& b) {
  if(a.encoding_ != b.encoding_) {
    return false;
  }
  if(a.value_.compare(b.value_) != 0) {
    return false;
  }
  if(a.tag_.number() != b.tag_.number()) {
    return false;
  }
  if(a.tag_.is_context_tag() != b.tag_.is_context_tag()) {
    return false;
  }
  if(a.tag_.length_value_type() != b.tag_.length_value_type()) {
    return false;
  }
  return true;
}
*/

BOOST_AUTO_TEST_SUITE( service_reninialize_device)

  BOOST_AUTO_TEST_CASE( test_case1 ) {

    bacnet::service::service::reinitialize_device rd(1, "aa");



    auto generated = bacnet::service::service::detail::generate(rd);
    bacnet::print(generated);

    //BOOST_TEST(is_equal(generation_expected, generated), "fail tag generation failed");
    //BOOST_TEST(bacnet::apdu::type::parse(generated, character_string_parsed), "fail parse simple tag");
    //BOOST_TEST(is_equal(character_string_to_generate, character_string_parsed), "failed parsed is not expected");

  }

BOOST_AUTO_TEST_SUITE_END()



#endif //NINJA_WOOKIE_TEST_UNIT_TEST_BACNET_SERVICE_REINITIALIZE_DEVICE_HPP
