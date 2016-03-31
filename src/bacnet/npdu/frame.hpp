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

#ifndef SRC_BACNET_NPDU_FRAME_HPP_
#define SRC_BACNET_NPDU_FRAME_HPP_

#include <iostream>

#include <boost/fusion/include/define_struct.hpp>
#include <boost/variant.hpp>

#include <bacnet/detail/common/types.hpp>

#include <bacnet/npdu/address.hpp>
#include <bacnet/npdu/control_information_t.hpp>

#include <bacnet/npdu/frame/apdu.hpp>
#include <bacnet/npdu/frame/raw.hpp>

namespace bacnet { namespace npdu {
    typedef boost::variant<
        bacnet::npdu::frame_body::apdu,
        bacnet::npdu::frame_body::raw
    > frame_body_t;
}}


BOOST_FUSION_DEFINE_STRUCT(
  (bacnet)(npdu), frame,
  (uint8_t, protocol_version)
  (bacnet::npdu::control_information_t, control_field)
  (bacnet::npdu::address, destination)
  (bacnet::npdu::address, source)
  (uint8_t, hop_count)
  (uint8_t, message_type)
  (uint16_t, vendor_id)
  (bacnet::npdu::frame_body_t, body)
)

//todo use fusion operator
std::ostream &operator<<(std::ostream &os, const bacnet::npdu::frame &f) ;


#endif /* SRC_BACNET_NPDU_FRAME_HPP_ */
