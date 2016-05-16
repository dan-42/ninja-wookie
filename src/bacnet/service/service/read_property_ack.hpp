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
#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/service/detail/service_choice.hpp>


namespace bacnet { namespace service { namespace service {
  struct read_property_ack {

    read_property_ack() = default;

    read_property_ack(bacnet::type::object_identifier oi, uint16_t pi, bacnet::binary_data d) :
                                                                        object_identifier(oi),
                                                                        property_identifier(pi),
                                                                        raw_data(std::move(d)) {
    }

    read_property_ack(bacnet::type::object_identifier oi, uint16_t pi, uint32_t array_index, bacnet::binary_data d) :
                                                                        object_identifier(oi),
                                                                        property_identifier(pi),
                                                                        property_array_index(array_index),
                                                                        raw_data(std::move(d)){
    }

    bacnet::type::object_identifier object_identifier{};
    uint16_t                          property_identifier {0};
    boost::optional<uint32_t>         property_array_index;
    bacnet::binary_data               raw_data;
  };

}}}

BOOST_FUSION_ADAPT_STRUCT(
  bacnet::service::service::read_property_ack,
  object_identifier,
  property_identifier,
  property_array_index,
  raw_data
);



namespace bacnet { namespace service { namespace service { namespace detail {

  using namespace bacnet::service::service;

  template<>
  struct service_choice<read_property_ack> {
    static constexpr  uint8_t value = 12;
    typedef read_property_ack type;
  };


}}}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_READ_PROPETRY_ACK_HPP
