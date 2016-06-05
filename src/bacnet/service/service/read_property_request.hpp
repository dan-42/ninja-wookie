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
#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_READ_PROPERTY_REQUEST_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_READ_PROPERTY_REQUEST_HPP


#include <cstdint>
#include <boost/optional.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <bacnet/type/object_identifier.hpp>
#include <bacnet/service/service/detail/service_choice.hpp>
#include <bacnet/service/service/traits.hpp>


namespace bacnet { namespace service { namespace service {
  struct read_property_request {

    read_property_request() = default;

    read_property_request(bacnet::type::object_identifier oi, uint32_t pi) :  object_identifier(oi),
                                                                        property_identifier(pi) {
    }

    read_property_request(bacnet::type::object_identifier oi, uint32_t pi, uint32_t array_index) :
                                                                        object_identifier(oi),
                                                                        property_identifier(pi),
                                                                        property_array_index(array_index) {
    }

    bacnet::type::object_identifier   object_identifier{};
    uint32_t                          property_identifier {0};
    boost::optional<uint32_t>         property_array_index;
  };

}}}

BOOST_FUSION_ADAPT_STRUCT(
  bacnet::service::service::read_property_request,
  object_identifier,
  property_identifier,
  property_array_index
);



namespace bacnet { namespace service { namespace service { namespace detail {

  using namespace bacnet::service::service;

  template<>
  struct service_choice<read_property_request> : std::integral_constant<uint8_t, comfirmed_service::read_property> {
    typedef read_property_request type;
  };


}}}}


namespace bacnet { namespace service { namespace service {    
    
    template<> struct is_confirmed<read_property_request> :  boost::mpl::true_ {};
    
    template<> struct is_request<read_property_request> :    boost::mpl::true_ {};    
    
    template<> struct has_complex_response<read_property_request> :    boost::mpl::true_ {};

}}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_READ_PROPERTY_REQUEST_HPP
