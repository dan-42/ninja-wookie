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

#ifndef NINJA_WOOKIE_BACNET_APDU_API_HPP
#define NINJA_WOOKIE_BACNET_APDU_API_HPP

#include <cstdint>

#include <functional>
#include <bacnet/detail/common/types.hpp>
#include <bacnet/common/protocol/meta_information.hpp>
#include <bacnet/apdu/frame/frames.hpp>
#include <bacnet/error/error.hpp>


namespace bacnet { namespace apdu {
   /* called when new requests are incomming    */
  typedef  std::function<void (frame::unconfirmed_request, bacnet::error, bacnet::common::protocol::meta_information)> received_unconfirmed_callback_t;
  typedef  std::function<void (frame::confirmed_request  , bacnet::error, bacnet::common::protocol::meta_information)> received_confirmed_callback_t;


  /* called after sending a request to somewhere */
  typedef std::function< void (const  bacnet::error&,
                                      frame::possible_confirmed_respons,
                                      bacnet::common::protocol::meta_information )> confirmed_request_handler_type;
  typedef std::function< void (const bacnet::error&)>                   unconfirmed_request_handler_type;


}}

#endif //NINJA_WOOKIE_BACNET_APDU_API_HPP
