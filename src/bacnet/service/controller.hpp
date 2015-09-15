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


#ifndef NINJA_WOOKIE_BACNET_SERVICE_CONTROLLER_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_CONTROLLER_HPP

#include <bacnet/service/i_am.hpp>
#include <bacnet/service/who_is.hpp>

#include <bacnet/service/detail/service_choice.hpp>
#include <bacnet/service/detail/who_is_generator.hpp>


namespace bacnet { namespace service {

template<typename UnderlyingLayer>
class controller {
public:
  controller(boost::asio::io_service& io_service, UnderlyingLayer& lower_layer): io_service_(io_service), lower_layer_(lower_layer) {

  }

  template<typename Service>
  void send(Service& service) {
    auto data = detail::generate(service);
    auto service_choice = detail::service_choice(service);

    lower_layer_.send_unconfirmed_request_as_broadcast(service_choice, data);
  }

private:
    boost::asio::io_service& io_service_;
    UnderlyingLayer &lower_layer_;


};

}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_CONTROLLER_HPP