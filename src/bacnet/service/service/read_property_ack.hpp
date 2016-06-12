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
#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_READ_PROPETRY_ACK_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_READ_PROPETRY_ACK_HPP


#include <cstdint>
#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <bacnet/type/object_identifier.hpp>
#include <bacnet/type/types.hpp>
#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/service/detail/service_choice.hpp>
#include <bacnet/service/service/traits.hpp>


namespace bacnet { namespace service { namespace service {
  struct read_property_ack {

    read_property_ack() = default;

    read_property_ack(bacnet::type::object_identifier oi, uint16_t pi, bacnet::type::possible_type d) :
                                                                        object_identifier(oi),
                                                                        property_identifier(pi),
                                                                        property_value(std::move(d)) {
    }

    read_property_ack(bacnet::type::object_identifier oi, uint16_t pi, uint32_t array_index, bacnet::type::possible_type d) :
                                                                        object_identifier(oi),
                                                                        property_identifier(pi),
                                                                        property_array_index(array_index),
                                                                        property_value(std::move(d)){
    }

    read_property_ack(read_property_request request, bacnet::type::possible_type d) :
                                                                        object_identifier(request.object_identifier),
                                                                        property_identifier(request.property_identifier),
                                                                        property_array_index(request.property_array_index),
                                                                        property_value(std::move(d)){
    }

    bacnet::type::object_identifier object_identifier{};
    uint16_t                          property_identifier {0};
    boost::optional<uint32_t>         property_array_index;
    bacnet::type::possible_type       property_value;
  };

}}}

BOOST_FUSION_ADAPT_STRUCT(
  bacnet::service::service::read_property_ack,
  object_identifier,
  property_identifier,
  property_array_index,
  property_value
);



namespace bacnet { namespace service { namespace service { namespace detail {

  using namespace bacnet::service::service;

  template<>
  struct service_choice<read_property_ack> : std::integral_constant<uint8_t,  comfirmed_service::read_property> {
    typedef read_property_ack type;
  };


}}}}


namespace bacnet { namespace service { namespace service {    
    
    template<> struct is_confirmed<read_property_ack> :  boost::mpl::true_ {};    
    
    template<> struct is_response<read_property_ack> :   boost::mpl::true_ {};    
    
}}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_READ_PROPETRY_ACK_HPP
