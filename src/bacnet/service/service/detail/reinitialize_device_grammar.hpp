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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_REINITIALIZE_DEVICE_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_REINITIALIZE_DEVICE_GRAMMAR_HPP



/*
 *
 F.4.4 Encoding for Example E.4.4 - ReinitializeDevice Service
X'00'
X'01'
X'02'
X'14'
PDU Type=0 (BACnet-Confirmed-Request-PDU, SEG=0, MOR=0, SA=0)
Maximum APDU Size Accepted=128 octets
Invoke ID=2
Service Choice=20 (ReinitializeDevice-Request)
X'09'
X'01'
X'1D'
X'09'
X'00'
X'4162436445664768'
SD Context Tag 0 (Reinitialized State Of Device, L=1)
1 (WARMSTART)
SD Context Tag 1 (Password, L>4)
Extended Length=9
ISO 10646 (UTF-8) Encoding
"AbCdEfGh"
Assuming this service procedure executes correctly, a simple acknowledgment is returned:
X'20'
X'02'
X'14'
PDU Type=2 (BACnet-SimpleACK-PDU)
Invoke ID=2
Service ACK Choice=20 (ReinitializeDevice)



 */

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/service/reinitialize_device.hpp>

#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/type/character_string.hpp>
#include <bacnet/apdu/type/detail/primitive/enumeration_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/character_string_grammar.hpp>


namespace bacnet { namespace service { namespace service { namespace detail { namespace parser {


using namespace boost::spirit;
using namespace boost::spirit::qi;

using namespace bacnet::apdu::type;
using namespace bacnet::type;
using namespace bacnet::apdu::type::detail::parser;

template<typename Iterator>
struct reinitialize_device_grammar : grammar<Iterator, service::reinitialize_device()> {


  rule<Iterator, service::reinitialize_device()>       start_rule;

  rule<Iterator, enumerated()>                           reinitialize_state_of_device_rule;
  rule<Iterator, boost::optional<character_string>()>  password_rule;

  enumeration_grammar<Iterator>      tag_0_rule_{0};
  character_string_grammar<Iterator> tag_1_rule_{1};

  reinitialize_device_grammar() : reinitialize_device_grammar::base_type(start_rule) {

    start_rule                          =  byte_(service_choice<service::reinitialize_device>::value)
                                        >> reinitialize_state_of_device_rule
                                        >> password_rule;

    reinitialize_state_of_device_rule   = tag_0_rule_;
    password_rule                       = -tag_1_rule_;
  }
};


}}}}}

namespace bacnet { namespace service { namespace service { namespace detail {  namespace generator {


using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::apdu::type;
using namespace bacnet::type;
using namespace bacnet::apdu::type::detail::generator;

template<typename Iterator>
struct reinitialize_device_grammar : grammar<Iterator, service::reinitialize_device()> {


  rule<Iterator, service::reinitialize_device()>  start_rule;

  rule<Iterator, enumerated()>                           reinitialize_state_of_device_rule;
  rule<Iterator, boost::optional<character_string>()>  password_rule;

  enumeration_grammar<Iterator>      tag_0_rule_{0};
  character_string_grammar<Iterator> tag_1_rule_{1};


  reinitialize_device_grammar() : reinitialize_device_grammar::base_type(start_rule) {

    start_rule        =  byte_(service_choice<service::reinitialize_device>::value)
                      << reinitialize_state_of_device_rule
                      << password_rule;

    reinitialize_state_of_device_rule   = tag_0_rule_;
    password_rule                       = -tag_1_rule_;
  }

};


}}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_REINITIALIZE_DEVICE_GRAMMAR_HPP
