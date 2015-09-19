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

#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>

#include <bacnet/service/i_am.hpp>
#include <bacnet/service/who_is.hpp>

#include <bacnet/service/detail/service_choice.hpp>
#include <bacnet/service/detail/who_is_generator.hpp>

#include <bacnet/apdu/api.hpp>

namespace bacnet { namespace service {

template<typename UnderlyingLayer>
class controller {
public:
  controller(boost::asio::io_service& io_service, UnderlyingLayer& lower_layer): io_service_(io_service), lower_layer_(lower_layer) {

    lower_layer_.register_async_received_service_callback([this](const bacnet::apdu::meta_information_t& mi,const bacnet::binary_data& data){
      std::cout << "mi.service_choice " << (int)mi.service_choice << std::endl;
      if(dispatch_item_ != nullptr && mi.service_choice == detail::service_choice<who_is>::value){
       if(detail::parse(data, dispatch_item_->who_is_)){
        dispatch_item_->handler_();
       }

      }

    });

  }

  template<typename Service>
  void send(Service& service) {
    auto data = detail::generate(service);
    auto service_choice = detail::service_choice<Service>::value;

    if(detail::is_broadcast_service<Service>::value) {
      lower_layer_.send_unconfirmed_request_as_broadcast(service_choice, data);
    }
    else {
      std::cerr << "no support yet for unicast messages";
      lower_layer_.send_unconfirmed_request_as_broadcast(service_choice, data);
    }
  }

  void async_receive(service::who_is& who_is, boost::function<void()> handler){

    dispatch_item_ = boost::make_shared<dispatch_item_t>(who_is, handler);
  }



private:
    boost::asio::io_service& io_service_;
    UnderlyingLayer &lower_layer_;


  //template<typename T>
  struct dispatch_item_t {

    dispatch_item_t(service::who_is& who_is, const boost::function<void()>& handler) : who_is_(who_is), handler_(handler){

    }

    service::who_is& who_is_;
    boost::function<void()> handler_;

  };

  boost::shared_ptr<dispatch_item_t> dispatch_item_;

};

}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_CONTROLLER_HPP
