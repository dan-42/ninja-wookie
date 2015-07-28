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

#ifndef NINJA_WOOKIE_APDU_FRAMES_HPP
#define NINJA_WOOKIE_APDU_FRAMES_HPP



#include <boost/variant.hpp>

#include <bacnet/apdu/frame/confirmed_request.hpp>
#include <bacnet/apdu/frame/unconfirmed_request.hpp>
#include <bacnet/apdu/frame/simple_ack.hpp>
#include <bacnet/apdu/frame/complex_ack.hpp>
#include <bacnet/apdu/frame/segmented_ack.hpp>
#include <bacnet/apdu/frame/error.hpp>
#include <bacnet/apdu/frame/abort.hpp>
#include <bacnet/apdu/frame/reject.hpp>


namespace bacnet { namespace apdu  { namespace frame {


typedef boost::variant<
    confirmed_request,
    unconfirmed_request,
    simple_ack,
    complex_ack,
    segmented_ack,
    error,
    abort,
    reject
    > possible_frame;

}}}


#endif
