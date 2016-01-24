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

#include <exception>
#include <iostream>

#include <boost/asio.hpp>

#include <bacnet_application.hpp>

int main(int argc, char *argv[]) {


  //try {

    boost::asio::io_service io_service;
    my_bacnet_application my_app(io_service);
    io_service.post(boost::bind(&my_bacnet_application::run, &my_app));


    //blocking call
    io_service.run();
  //}
 // catch (const std::exception &e) {
 //   std::cerr << "Exception: " << e.what() << "\n";
 //   throw;
  //}

  return 0;
}
