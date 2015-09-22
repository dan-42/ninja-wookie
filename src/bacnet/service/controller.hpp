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

    lower_layer_.register_async_received_service_callback([this](const bacnet::apdu::meta_information_t& mi, const bacnet::binary_data& data){
      //xxx copy to workaround const constraints of data;
      bacnet::binary_data data_ = data;

      auto item = dispatch_item_map_.find(mi.service_choice);
      if(item == dispatch_item_map_.end()){
        return;
      }

      boost::any dispatch_item_any = item->second;

      //xxx find solution for generic cast?
      if(mi.service_choice == detail::service_choice<who_is>::value) {
        auto dispatch_item_ptr = boost::any_cast<boost::shared_ptr<dispatch_item_t<who_is>>>(dispatch_item_any);
        if(dispatch_item_ptr == nullptr){
          return;
        }

        if(detail::parse(data_, dispatch_item_ptr->service_)){
          dispatch_item_ptr->handler_();
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

  template<typename Service>
  void async_receive(Service &service, boost::function<void()> handler){

    auto dispatch_item_ = boost::make_shared<dispatch_item_t<Service>>(service, handler);

    uint8_t key = detail::service_choice<Service>::value;
    dispatch_item_map_[key] = dispatch_item_;
  }



private:
    boost::asio::io_service& io_service_;
    UnderlyingLayer &lower_layer_;


  template<typename Service>
  struct dispatch_item_t {

    dispatch_item_t(Service& service, const boost::function<void()>& handler) : service_(service), handler_(handler) {
    }

    Service& service_;
    boost::function<void()> handler_;
  };

  std::map<uint8_t, boost::any> dispatch_item_map_;
};

}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_CONTROLLER_HPP
