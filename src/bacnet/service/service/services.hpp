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


#ifndef NINJA_WOOKIE_SERVICES_HPP
#define NINJA_WOOKIE_SERVICES_HPP


#include <cstdint>

#include <boost/variant.hpp>
#include <boost/fusion/include/define_struct.hpp>


#include <bacnet/service/service/who_is.hpp>
#include <bacnet/service/service/i_am.hpp>
#include <bacnet/service/service/read_property_request.hpp>
#include <bacnet/service/service/read_property_ack.hpp>
#include <bacnet/service/service/reinitialize_device.hpp>

namespace bacnet { namespace service { namespace service {

  struct unused_service{};

}}}

namespace bacnet { namespace service { namespace service { namespace unconfirmed {
  typedef boost::variant<
                          who_is,
                          i_am
                        >
          possible_service;

}}}}



namespace bacnet { namespace service { namespace service { namespace confirmed_request {

  typedef boost::variant<
                            reinitialize_device,
                            read_property_request
                        >
          possible_service;

}}}}

namespace bacnet { namespace service { namespace service { namespace confirmed_response {

  typedef boost::variant<
                        unused_service,
                        read_property_ack
                        >
          possible_service;

}}}}


namespace bacnet { namespace service {

//xxx todo implement possible responses
        typedef boost::variant<
            service::who_is,
            service::i_am,
            service::reinitialize_device
        > possible_service_response;
}}

#endif //NINJA_WOOKIE_SERVICES_HPP
