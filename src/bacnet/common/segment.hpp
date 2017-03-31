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
#include <bacnet/type/enumerated.hpp>

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


      segmentation() = default;
      segmentation(segment s) : segmented_(std::move(s)) {

      }

      static inline bool can_segmented_transmit(segment s)  {
         if(     s == segment::transmit
             ||  s == segment::both )   {
           return true;
         }
         return false;
       }

      static inline bool can_segmented_receive(segment s)  {
         if(     s == segment::receive
             ||  s == segment::both )   {
           return true;
         }
         return false;
       }

      inline bool can_segmented_transmit() {
        return can_segmented_transmit(segmented_);
      }

      inline bool can_segmented_receive() {
        return can_segmented_receive(segmented_);
      }

      inline segment segmented() const {
        return segmented_;
      }

      inline void segmented(segment s) {
        segmented_ = s;
      }



      friend inline bool operator==(const segmentation& a1, const segmentation& a2) {
        if(a1.segmented_ == a2.segmented_) {
          return true;
        }
        return false;
      }

      friend bool operator!=(const segmentation& a1, const segmentation& a2) {
        return !(a1 == a2);
      }

      friend inline bool operator<(const segmentation& a1, const segmentation& a2) {
        if(a1.segmented_ < a2.segmented_) {
          return true;
        }
        return false;
      }

      static inline segmentation from_enumerated(const bacnet::type::enumerated& e) {
        return from_native(e.value);
      }

      static inline segmentation from_native(const underlying_type& seg_value) {
        segmentation seg{segment::none};

        switch(static_cast<segment>(seg_value)) {
          case segment::both :
            seg.segmented(segment::both);
            break;
          case segment::transmit :
            seg.segmented(segment::transmit);
            break;
          case segment::receive :
            seg.segmented(segment::receive);
            break;
          case segment::none :
            seg.segmented(segment::none);
            break;
        }
        return seg;

      }

      static inline underlying_type to_native(const segmentation& seg_value)  {
        return static_cast<underlying_type>(seg_value.segmented());
      }


    private:

      segment segmented_ = segment::both ;

    };

    static inline std::ostream& operator<<(std::ostream& os, const segmentation &s) {
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
