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

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <bacnet/service/service.hpp>

//#include <bacnet/service/service/detail/service_choice.hpp>
//#include <bacnet/service/service/detail/who_is_generator.hpp>

#include <bacnet/service/api.hpp>
#include <bacnet/service/detail/callback_manager.hpp>


namespace bacnet { namespace service { namespace service { namespace detail {
  using namespace bacnet::service;
  static inline unconfirmed::possible_service parse(const binary_data& data) {
    unconfirmed::possible_service parsed_service{};

    std::cout << "unconfirmed::possible_service parse(const binary_data& data) { " << std::endl;
    return parsed_service;
  }


  static inline binary_data generate(const unconfirmed::possible_service& service) {

    std::cout << "unconfirmed::possible_service generate(const binary_data& data) { " << std::endl;
    return binary_data{};
  }

}}}}



namespace bacnet { namespace service {



template<typename UnderlyingLayer>
class controller {
public:
  controller(boost::asio::io_service& io_service, UnderlyingLayer& lower_layer): io_service_(io_service), lower_layer_(lower_layer) {

    lower_layer_.register_async_received_service_callback(boost::bind(&controller::async_received_service_handler, this, _1, _2));

  }

 void async_received_service_handler(bacnet::apdu::meta_information_t mi, bacnet::binary_data data) {

    std::cout << "async_received_service_handler " << std::endl;
   auto possible_service_frame = bacnet::service::service::detail::parse(data);

  }


    /*
     * make async_send dependant on a bacnet::endpoint, as a generic way to send unidirectional services
     */

  template<typename Service, typename Handler>
  void async_send(Service&& service, Handler handler) {
    auto data =  bacnet::service::service::detail::generate(service);
    auto service_choice =  bacnet::service::service::detail::service_choice<Service>::value;

    if( bacnet::service::service::detail::is_broadcast_service<Service>::value) {

      lower_layer_.async_send_unconfirmed_request_as_broadcast(service_choice, data, [this, &handler]( const boost::system::error_code& ec,  std::size_t bytes_transferred){
        handler(ec);
      });
    }
    else {
      std::cerr << "no support yet for unicast messages";
      lower_layer_.async_send_unconfirmed_request_as_broadcast(service_choice, data, [this, &handler]( const boost::system::error_code& ec,  std::size_t bytes_transferred){
        handler(ec);
      });
    }
  }


  template<typename ServiceType, typename FunctionHandler>
  void async_receive(FunctionHandler function_handler) {
    callback_manager_.set_service_callback(function_handler);
  }


private:
    boost::asio::io_service& io_service_;
    UnderlyingLayer &lower_layer_;
    bacnet::service::detail::callback_manager callback_manager_;


};

}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_CONTROLLER_HPP
