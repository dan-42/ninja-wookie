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

#include <boost/variant.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/remove.hpp>
#include <boost/mpl/remove_if.hpp>
#include <boost/mpl/lambda.hpp>
#include <boost/mpl/not.hpp>
#include <boost/mpl/logical.hpp>
#include <boost/fusion/include/define_struct.hpp>

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
                                who_is,  
                                i_am,
  
                        
                                read_property_request,
                                read_property_ack,

                                reinitialize_device
                        
  > possible_services;
  








  typedef boost::mpl::remove_if<
    bacnet::service::service::possible_services,
    boost::mpl::lambda< 
           boost::mpl::not_<   bacnet::service::service::is_supported< boost::mpl::_1 >  >
    >::type
  >::type supported_services;  
    
  typedef boost::make_variant_over< bacnet::service::service::supported_services >::type supported_service;
  

}}}

namespace bacnet { namespace service { namespace service { namespace unconfirmed {

  typedef boost::mpl::remove_if<
    bacnet::service::service::supported_services,
    boost::mpl::lambda< 
        boost::mpl::not_<    bacnet::service::service::is_unconfirmed< boost::mpl::_1 > >
    >::type
  >::type services;  
                                
  typedef boost::make_variant_over< services >::type service;

}}}}



namespace bacnet { namespace service { namespace service { namespace confirmed {

 typedef boost::mpl::remove_if<
    bacnet::service::service::supported_services,
    boost::mpl::lambda< 
        boost::mpl::not_<    bacnet::service::service::is_confirmed< boost::mpl::_1 > >
    >::type
  >::type services;  
                                

  typedef boost::make_variant_over< services >::type service;                                
  
  
  
  typedef boost::mpl::remove_if<
    bacnet::service::service::confirmed::services,
    boost::mpl::lambda< 
        boost::mpl::not_<    bacnet::service::service::is_request< boost::mpl::_1 > >
    >::type
  >::type requests;  

  typedef boost::make_variant_over< requests >::type request;
  
  
  
  
  
  typedef boost::mpl::remove_if<
    bacnet::service::service::confirmed::services,
    boost::mpl::lambda< 
        boost::mpl::not_<    bacnet::service::service::is_response< boost::mpl::_1 > >
    >::type
  >::type responses;

  typedef boost::make_variant_over< responses >::type response;



}}}}


















// */
//////////////////////////////////////////////////////////////////////////////////

/*

namespace bacnet { namespace service { namespace service {

  
                        
  
  typedef boost::variant< 
                                who_is,  
                                i_am,
  
                        
                                read_property_request,
                                read_property_ack,

                                reinitialize_device
  > supported_service;
  

}}}

namespace bacnet { namespace service { namespace service { namespace unconfirmed {

  typedef boost::variant< 
                                who_is,  
                                i_am
  
  > service;

}}}}



namespace bacnet { namespace service { namespace service { namespace confirmed {

   typedef boost::variant<                                
                        
                                read_property_request,
                                read_property_ack,

                                reinitialize_device
  >  service;                                
  
  
  
   typedef boost::variant<  
                                read_property_request,                                

                                reinitialize_device
  >   request;
  
  
  
  

   typedef boost::variant<      
                                read_property_ack
                                
  >   response;


    typedef read_property_ack response;

}}}}

*/

#endif //NINJA_WOOKIE_SERVICES_HPP
