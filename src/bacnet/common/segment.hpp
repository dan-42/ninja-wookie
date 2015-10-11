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

#ifndef NINJA_WOOKIE_SEGMENTED_HPP
#define NINJA_WOOKIE_SEGMENTED_HPP

#include <cstdint>
#include <iostream>

namespace bacnet { namespace common {


    struct segmentation  {

    public:

      typedef uint8_t underlying_type;

      enum class segment : underlying_type {
        both     = 0,
        transmit = 1,
        receive  = 2,
        none     = 3
      };


      inline segment segmented() const {
        return segmented_;
      }

      inline void segmented(segment s) {
        segmented_ = s;
      }

      inline void from_native(const underlying_type& seg_value) {
        segmented_ = segment::none;
        switch(static_cast<segment>(seg_value)) {
          case segment::both :
            segmented_ = segment::both;
            break;
          case segment::transmit :
            segmented_ = segment::transmit;
            break;
          case segment::receive :
            segmented_ = segment::receive;
            break;
          case segment::none :
            segmented_ = segment::none;
            break;
        }

      }

      inline underlying_type to_native() const {
        return static_cast<underlying_type>(segmented_);
      }


    private:

      segment segmented_;

    };

    static inline std::ostream& operator<<(std::ostream& os, const segmentation &s) {

      os << " segmentation: ";
      switch(s.segmented()) {
        case segmentation::segment::both :
          os << "both";
          break;
        case segmentation::segment::transmit :
          os << "transmit";
          break;
        case segmentation::segment::receive :
          os << "receive";
          break;
        case segmentation::segment::none :
          os << "none";
          break;
        }

      return os;
    }

  }}


#endif //NINJA_WOOKIE_SEGMENTED_HPP
