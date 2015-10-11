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


#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERVICE_CHOICE_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERVICE_CHOICE_HPP

#include <cstdint>

namespace bacnet { namespace service { namespace service { namespace detail {

      namespace uncomfirmed_service {
        constexpr uint8_t i_am                          =  0;
        constexpr uint8_t i_have                        =  1;
        constexpr uint8_t change_of_value_notification  =  2;
        constexpr uint8_t event_notification            =  3;
        constexpr uint8_t private_transfer              =  4;
        constexpr uint8_t text_message                  =  5;
        constexpr uint8_t time_synchronization          =  6;
        constexpr uint8_t who_has                       =  7;
        constexpr uint8_t who_is                        =  8;
        constexpr uint8_t utc_time_synchronization      =  9;
        constexpr uint8_t write_group                   = 10;
      }

      namespace comfirmed_service {
        //-- Alarm and Event Services
        constexpr uint8_t acknowledge_alarm             =  0;
        constexpr uint8_t change_of_value_notification  =  1;
        constexpr uint8_t event_notification            =  2;
        constexpr uint8_t get_alarm_summary             =  3;
        constexpr uint8_t get_enrollment_summary        =  4;
        constexpr uint8_t get_event_information         = 29;
        constexpr uint8_t subscribe_change_of_value     =  5;
        constexpr uint8_t subscribe_change_of_value_property = 28;
        constexpr uint8_t life_safety_operation         = 27;
        //-- File Access Services
        constexpr uint8_t atomic_read_file              =  6;
        constexpr uint8_t atomic_Write_file             =  7;
        //-- Object Access Services
        constexpr uint8_t add_list_element              =  8;
        constexpr uint8_t remove_list_element           =  9;
        constexpr uint8_t create_object                 = 10;
        constexpr uint8_t delete_object                 = 11;
        constexpr uint8_t read_property                 = 12;
        constexpr uint8_t read_property_multiple        = 14;
        constexpr uint8_t read_range                    = 26;
        constexpr uint8_t write_property                = 15;
        constexpr uint8_t write_property_multiple       = 16;
        //-- Remote Device Management Services
        constexpr uint8_t device_communication_control  = 17;
        constexpr uint8_t confirmed_private_transfer    = 18;
        constexpr uint8_t confirmed_text_message        = 19;
        constexpr uint8_t reinitialize_device           = 20;
        //-- Virtual Terminal Services
        constexpr uint8_t vt_open                       = 21;
        constexpr uint8_t vt_close                      = 22;
        constexpr uint8_t vt_data                       = 23;
        //-- removed Services
        constexpr uint8_t removed_rev_12_read_property_conditional = 13;
        constexpr uint8_t removed_rev_11_authenticate   = 24;
        constexpr uint8_t removed_rev_11_request_key    = 25;
      }
}}}}

namespace bacnet { namespace service { namespace service { namespace detail {

  struct unused{};

  template<typename Service>
  struct service_choice {
    static constexpr uint8_t value = 0xFF;
    typedef unused type;
  };

  template<typename Service>
  struct is_broadcast_service : std::false_type {
  };

}}}}



#endif //NINJA_WOOKIE_BACNET_SERVICE_SERVICE_CHOICE_HPP