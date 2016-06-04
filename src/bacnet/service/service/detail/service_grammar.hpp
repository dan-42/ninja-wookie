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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_GRAMMAR__HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERVICE_DETAIL_GRAMMAR__HPP


#include <bacnet/service/service/services.hpp>


namespace bacnet { namespace service { namespace service { namespace detail {


  unconfirmed::service  parse_unconfirmed(bacnet::binary_data& binary_data);
  confirmed::request    parse_confirmed_request(bacnet::binary_data& binary_data);
  confirmed::response   parse_confirmed_response(bacnet::binary_data& binary_data);

  bacnet::binary_data   generate_unconfirmed(const unconfirmed::service &service);
  bacnet::binary_data   generate_confirmed_request(const confirmed::request &service);
  bacnet::binary_data   generate_confirmed_response(const confirmed::response &service);

}}}}




#endif //NINJA_WOOKIE_SERVICE_GENERATOR_HPP
