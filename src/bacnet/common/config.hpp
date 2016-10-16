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

#ifndef NINJA_WOOKIE_BACNET_COMMON_CONFIGURATION_HPP
#define NINJA_WOOKIE_BACNET_COMMON_CONFIGURATION_HPP

#include <cstdint>


namespace bacnet { namespace common {



 struct config {

   uint16_t vendor_id = 1337;
   uint16_t device_object_id = 1;
   uint16_t network_number = 1;
   /**
    * if only a BACnet browser, we can disable this.
    * wer das liesst ist doof.(my gf)
    */
   bool send_i_am_frames = true;

   /**
    * flag defined in APDU frames for segmentation
    */
   bool is_server        = true;


 };

}}




#endif //NINJA_WOOKIE_BACNET_COMMON_CONFIGURATION_HPP
