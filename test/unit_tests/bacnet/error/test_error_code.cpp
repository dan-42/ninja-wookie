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


#define BOOST_TEST_MODULE test ninja wookie bacnet error error_code
#include <boost/test/included/unit_test.hpp>

#include <iostream>
#include <bacnet/error/error.hpp>



BOOST_AUTO_TEST_SUITE( test_error_code_simple )

  BOOST_AUTO_TEST_CASE( test_send_reinitialize_device_doi ) {

      auto boost_ec_succsess            = boost::system::errc::make_error_code(boost::system::errc::success);
      auto boost_ec_operation_canceled  = boost::system::errc::make_error_code(boost::system::errc::operation_canceled);

      BOOST_TEST(!boost_ec_succsess);
      BOOST_TEST(boost_ec_operation_canceled);

      std::cout << "boost_ec_succsess: "            <<  boost_ec_succsess << std::endl;
      std::cout << "boost_ec_operation_canceled: "  << boost_ec_operation_canceled << std::endl;

      bacnet::error_code bacnet_ec_success{boost_ec_succsess};
      bacnet::error_code bacnet_ec_from_boost_error{boost_ec_operation_canceled};


      BOOST_TEST(!bacnet_ec_success);
      BOOST_TEST(bacnet_ec_from_boost_error);
      std::cout << "bacnet_ec_success: "          << bacnet_ec_success << std::endl;
      std::cout << "bacnet_ec_from_boost_error: " << bacnet_ec_from_boost_error << std::endl;


      bacnet::error_code bacnet_ec_known_error(bacnet::error::error_code::abort_apdu_too_long, bacnet::error::error_class::communication);
      BOOST_TEST(bacnet_ec_known_error);
      std::cout << "bacnet_ec_known_error: " << bacnet_ec_known_error << std::endl;


      bacnet::error_code bacnet_ec_unknown_error(1337, 42);
      BOOST_TEST(bacnet_ec_unknown_error);
      std::cout << "bacnet_ec_unknown_error: " << bacnet_ec_unknown_error << std::endl;


      BOOST_TEST(boost_ec_succsess == bacnet_ec_success);

      BOOST_TEST(boost_ec_operation_canceled == bacnet_ec_from_boost_error);

      BOOST_TEST(boost_ec_operation_canceled != bacnet_ec_success);

  }


////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////



BOOST_AUTO_TEST_SUITE_END()
