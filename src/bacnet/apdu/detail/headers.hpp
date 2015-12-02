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

#ifndef NINJA_WOOKIE_APDU_HEADERS_HPP
#define NINJA_WOOKIE_APDU_HEADERS_HPP


#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace bacnet { namespace  apdu { namespace detail { namespace  header {

/**
 * the first byte in the APDU has a 4bit pdu_type
 * and then depending on the pdu_type the following 4 bit
 * have different meanings. default the must be 0 if not used
 */
struct pdu_type_and_control_information_t {
	uint8_t is_segmented_       			                        : 1;
	uint8_t has_more_segments_following_                      : 1;
	uint8_t is_segmented_response_accepted_OR_is_normal_ack_  : 1;
	uint8_t is_send_by_server_  			                        : 1;
	uint8_t pdu_type_                                         : 4;

	pdu_type_and_control_information_t() :
										is_segmented_(0),
										has_more_segments_following_(0),
										is_segmented_response_accepted_OR_is_normal_ack_(0),
										is_send_by_server_(0),
										pdu_type_(0) {
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


	//used by all
	bool is_segmented_response_accepted(){
		return is_segmented_response_accepted_OR_is_normal_ack_==true;
	}
	//for segment_ack only
	bool is_normal_ack(){
		return is_segmented_response_accepted_OR_is_normal_ack_==true;
	}

	//for segment_ack &&  abort
	bool is_send_by_server(){
		return is_send_by_server_==true;
	}


	friend std::ostream& operator<<(std::ostream& os, pdu_type_and_control_information_t const& t) {
	    std::stringstream ss;
	    ss << std::hex << std::setw(2) << std::setfill('0')
	       << (int)t.pdu_type_ << (int)t.is_segmented_
	       << (int)t.has_more_segments_following_
	       << (int)t.is_segmented_response_accepted_OR_is_normal_ack_
	       << (int)t.is_send_by_server_;

	    os << ss.str();
	    return os;
	  }

};





struct  segmentation_t {
  uint8_t unused_                : 1;
  uint8_t max_segments_          : 3;
  uint8_t max_accepted_apdu_     : 4;


  segmentation_t() : unused_(0),
                   max_segments_(0),
                   max_accepted_apdu_(0)  {
  }

  uint8_t max_segments() {
    return max_segments_;
  }

  uint8_t max_accepted_apdu() {
    return max_accepted_apdu_;
  }



  friend std::ostream& operator<<(std::ostream& os, segmentation_t const& t) {
    std::stringstream ss;
    ss << std::hex << std::setw(2) << std::setfill('0')
       << " " << (int)t.unused_
			 << " " << (int)t.max_segments_
			 << " " << (int)t.max_accepted_apdu_;

    os << ss.str();
    return os;
  }

};



}}}}




#endif //NINJA_WOOKIE_APDU_HEADERS_HPP
