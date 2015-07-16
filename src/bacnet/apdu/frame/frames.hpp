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


#include <bitset>
#include <boost/fusion/include/define_struct.hpp>
#include <bacnet/detail/common/types.hpp>
#include <util/boost/spirit/unused_type.hpp>

#include <bacnet/apdu/detail/headers.hpp>

#include <boost/dynamic_bitset.hpp>
#ifndef NINJA_WOOKIE_APDU_FRAMES_HPP
#define NINJA_WOOKIE_APDU_FRAMES_HPP




namespace bacnet { namespace  apdu { namespace frame {

struct alignas(1) segmentation {
  uint8_t unused_                          : 1;
  uint8_t max_segments_                    : 3;
  uint8_t _     : 1;
  uint8_t is_segmented_response_accepted_  : 1;
  uint8_t unused_                          : 1;

  confirmed_request() : pdu_type_(0),
                        is_segmented_(0),
                        has_more_segments_following_(0),
                        is_segmented_response_accepted_(0),
                        unused_(0) {
  }

  uint8_t pdu_type(){
    return pdu_type_;
  }
  bool is_segmented(){
    return is_segmented_==true;
  }
  bool has_more_segments_following(){
    return has_more_segments_following_==true;
  }
  bool is_segmented_response_accepted(){
    return is_segmented_response_accepted_==true;
  }
};


}}}




BOOST_FUSION_DEFINE_STRUCT(
        (bacnet)(apdu)(frame),confirmed_request,
        (bacnet::binary_data, npdu_data)
        (unused_t, unused)
)









#endif
