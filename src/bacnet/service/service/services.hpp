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

#include <mapbox/variant.hpp>
#include <mapbox/variant_io.hpp>

#include <bacnet/service/service/traits.hpp>

#include <bacnet/service/service/who_is.hpp>
#include <bacnet/service/service/i_am.hpp>
#include <bacnet/service/service/read_property_request.hpp>
#include <bacnet/service/service/read_property_ack.hpp>
#include <bacnet/service/service/reinitialize_device.hpp>


/*
 -- ASHRAE. Proprietary extensions are made by using the UnconfirmedPrivateTransfer service. See Clause 23.
BACnet-Unconfirmed-Service  is request and response
    - [x] i-Am
    - [ ] i-Have
    - [ ] unconfirmedCOVNotification
    - [ ] unconfirmedEventNotification
    - [ ] unconfirmedPrivateTransfer
    - [ ] unconfirmedTextMessage
    - [ ] timeSynchronization
    - [ ] who-Has
    - [x] who-Is
    - [ ] utcTimeSynchronization
    - [ ] writeGroup


## confirmed requests

    - [ ] AcknowledgeAlarm-Request,
    - [ ] ConfirmedCOVNotification-Request,
    - [ ] ConfirmedEventNotification-Request,

    - [ ] GetEnrollmentSummary-Request,
    - [ ] GetEventInformation-Request,
    - [ ] SubscribeCOV-Request,
    - [ ] SubscribeCOVProperty-Request,
    - [ ] LifeSafetyOperation-Request,

    - [ ] AtomicReadFile-Request,
    - [ ] AtomicWriteFile-Request,

    - [ ] AddListElement-Request,
    - [ ] RemoveListElement-Request,
    - [ ] CreateObject-Request,
    - [ ] DeleteObject-Request,
    - [ ] ReadProperty-Request,
    - [ ] ReadPropertyMultiple-Request,
    - [ ] ReadRange-Request,
    - [ ] WriteProperty-Request,
    - [ ] WritePropertyMultiple-Request,


    - [ ] DeviceCommunicationControl-Request,
    - [ ] ConfirmedPrivateTransfer-Request,
    - [ ] ConfirmedTextMessage-Request,
    - [x] ReinitializeDevice-Request,

    - [ ] VT-Open-Request,
    - [ ] VT-Close-Request,
    - [ ] VT-Data-Request

    -- added after 1995 see separate part
    - [ ] readRange
    - [ ] lifeSafetyOperation
    - [ ] subscribeCOVProperty

    - [ ] getEventInformation


## confirmed responses
    - [ ] GetAlarmSummary-ACK,
    - [ ] GetEnrollmentSummary-ACK,
    - [ ] GetEventInformation-ACK,

    - [ ] AtomicReadFile-ACK,
    - [ ] AtomicWriteFile-ACK,

    - [ ] CreateObject-ACK,
    - [ ] ReadProperty-ACK,
    - [ ] ReadPropertyMultiple-ACK,
    - [ ] ReadRange-ACK,

    - [ ] ConfirmedPrivateTransfer-ACK,

    - [ ] VT-Open-ACK,
    - [ ] VT-Data-ACK

 */

 // /*

namespace bacnet { namespace service { namespace service {

typedef boost::mpl::vector<


 > possible_services;



 using supported_service  = mapbox::util::variant<
                                    who_is,
                                    i_am,

                                    read_property_request,
                                    read_property_ack,

                                    reinitialize_device
                                    >;
  

}}}

namespace bacnet { namespace service { namespace service { namespace unconfirmed {

  using service  = mapbox::util::variant<
                                    who_is,
                                    i_am
                                    >;


}}}}



namespace bacnet { namespace service { namespace service { namespace confirmed {

using service  = mapbox::util::variant<
                                    read_property_request,
                                    read_property_ack,

                                    reinitialize_device
                                    >;
  
  
  
using request  = mapbox::util::variant<
                                    read_property_request,

                                    reinitialize_device
                                    >;
  
  
  
  
  
using response  = mapbox::util::variant<
                                    read_property_ack
                                    >;


}}}}


#endif //NINJA_WOOKIE_SERVICES_HPP
