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

#include <type_traits>
#include <chrono>
#include <iostream>
#include <boost/system/error_code.hpp>
#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/asio/steady_timer.hpp>

#include <bacnet/service/api.hpp>
#include <bacnet/service/detail/callback_manager.hpp>
#include <bacnet/service/detail/device_manager.hpp>

#include <bacnet/service/service.hpp>
#include <bacnet/service/service/detail/who_is_grammar.hpp>
#include <bacnet/service/service/detail/i_am_garmmar.hpp>
#include <bacnet/service/service/detail/reinitialize_device_grammar.hpp>
#include <bacnet/common/configuration.hpp>

namespace bacnet { namespace service { namespace service { namespace detail {
  using namespace bacnet::service;
  static inline unconfirmed::possible_service parse(binary_data& data) {
    unconfirmed::possible_service parsed_service{};

    //todo make it nice and clean with boost spirit
    if(!data.empty()) {
      if(data.front() == uncomfirmed_service::who_is) {
        //std::cout << "unconfirmed::possible_service parse who_is " << std::endl;
        who_is service_;
        if(bacnet::service::service::detail::parse(data , service_)) {
          parsed_service = service_;
        }
        else {
          std::cout << "unconfirmed::possible_service parse who_is failed" << std::endl;
        }
      }
      else if(data.front() == uncomfirmed_service::i_am) {
        //std::cout << "unconfirmed::possible_service parse i_am " << std::endl;
        i_am service_;
        if(bacnet::service::service::detail::parse(data , service_)){
          parsed_service = service_;
        }
        else {
          std::cout << "unconfirmed::possible_service parse i_am failed" << std::endl;
        }
      }
      else {
        std::cout << "unconfirmed::possible_service parse undefined " << std::endl;
        bacnet::print(data);
      }
    }
    else {
      std::cout << "unconfirmed::possible_service parse data empty " << std::endl;
    }

    return parsed_service;
  }

}}}}


namespace bacnet { namespace service { namespace detail {

  using namespace bacnet::service;
  struct inbound_router : boost::static_visitor<> {

    inbound_router(callback_manager& cm, bacnet::service::detail::device_manager& dm) : callback_manager_(cm), device_manager_(dm) {
    }

    inline void meta_information(bacnet::common::protocol::meta_information meta_information) {
      meta_information_ = meta_information;
    }

    void operator()(service::who_is service) {
      boost::system::error_code ec{error::errc::success, error::get_error_category()};
      callback_manager_.invoke(ec, std::move(meta_information_), std::move(service));
    }

    void operator()(service::i_am service) {
      device_manager_.insert_device(bacnet::common::protocol::mac::endpoint{meta_information_.npdu_source.network_number, meta_information_.address},
                                    service.i_am_device_identifier,
                                    service.max_apdu_length_accepted,
                                    service.segmentation_supported,
                                    service.vendor_id);
      device_manager_.print_device_list();
      if(!callback_manager_.callback_service_i_am_.empty()) {
        boost::system::error_code ec{error::errc::success, error::get_error_category()};
        callback_manager_.callback_service_i_am_(ec, std::move(meta_information_), std::move(service));

      }
    }

  private:

    callback_manager& callback_manager_;
    bacnet::service::detail::device_manager& device_manager_;
    bacnet::common::protocol::meta_information meta_information_;
  };

}}}


namespace bacnet { namespace service {

    static const std::chrono::milliseconds time_wait_for_i_am_answer{500};

template<typename UnderlyingLayer, typename ApduSize>
class controller {
public:



  controller(boost::asio::io_service& io_service, UnderlyingLayer& lower_layer, bacnet::config config):
                io_service_(io_service),
                lower_layer_(lower_layer),
                timeout_timer_(io_service_),
                inbound_router_(callback_manager_, device_manager_),
                device_object_identifier_(bacnet::object_type::device, config.device_object_id),
                config_(config){

    lower_layer_.register_async_received_service_callback(boost::bind(&controller::async_received_service_handler, this, _1, _2));

  }

 void async_received_service_handler(bacnet::common::protocol::meta_information mi, bacnet::binary_data data) {
   auto possible_service_frame = bacnet::service::service::detail::parse(data);
   inbound_router_.meta_information(mi);
   possible_service_frame.apply_visitor(inbound_router_);
 }


    /*
     * make async_send dependant on a bacnet::endpoint, as a generic way to send unidirectional services
     */

  template<typename Service, typename Handler>
  void async_send(Service &&service, Handler handler) {
    auto data =  bacnet::service::service::detail::generate(service);

    if( bacnet::service::service::detail::is_broadcast_service<typename std::decay<Service>::type>::value) {
      //std::cout << "send broadcast " << std::endl;
      //bacnet::print(data);
      lower_layer_.async_send_unconfirmed_request_as_broadcast(std::move(data), [this, &handler]( const boost::system::error_code& ec){
        handler(ec);
      });
    }
    else {
      std::cout << "not a broadcast service  " << std::endl;
      auto ec = boost::system::errc::make_error_code(boost::system::errc::bad_message);
      //bacnet::service::possible_service_response res;
      handler(ec);
    }
  }

  template<typename Service, typename Handler>
  void async_send(bacnet::common::protocol::mac::endpoint mac_endpoint, Service&& service, Handler handler) {
    auto data =  bacnet::service::service::detail::generate(std::move(service));

    lower_layer_.async_send_confirmed_request(mac_endpoint.address(), std::move(data), [this, handler]( const boost::system::error_code& ec){
      bacnet::service::possible_service_response res;
      handler(ec, res);
    });
  }


  template<typename Service, typename Handler>
  void async_send(bacnet::common::object_identifier device_object_identifier, Service service, Handler handler) {

    /* lookup doi */
    auto endpoints = device_manager_.get_endpoint(device_object_identifier);
    if(endpoints.size() == 1) {
      async_send(endpoints.front(), service, handler);
      return;
    }
    else {
      /**
       * send who is, and if more then one answers, send error up to calling layer
       */
      bool service_has_been_send = false;
      bacnet::service::callback_service_i_am_t i_am_callback = [handler, service, endpoints, &service_has_been_send, &device_object_identifier, this](boost::system::error_code ec, bacnet::common::protocol::meta_information mi, bacnet::service::i_am i_am){
        if(i_am.i_am_device_identifier == device_object_identifier) {
          async_send(endpoints.front(), service, handler);
          service_has_been_send = true;
        }
      };

      callback_manager_.set_service_callback(i_am_callback);
      bacnet::service::service::who_is wi(device_object_identifier.instance_number(), device_object_identifier.instance_number());
      async_send(wi, [handler](boost::system::error_code ec) {
        if(ec) {
          //todo set special error_code on error
          bacnet::service::possible_service_response res;
          handler(ec, res);
        }
      });


      timeout_timer_.expires_from_now(time_wait_for_i_am_answer);
      timeout_timer_.async_wait([handler, service, endpoints, &service_has_been_send, &device_object_identifier, this](boost::system::error_code ec) {

        if(!ec) {
          if(service_has_been_send) {
            //todo set special error_code on error
            bacnet::service::possible_service_response res;
            handler(ec, res);
          }
          else {
            std::cout << "no device with doi found  " << std::endl;
            //todo set special error_code on error
            bacnet::service::possible_service_response res;
            handler(ec, res);
          }
        }
        else {
          std::cout << "async_send timer error  "<< ec << std::endl;
          //todo set special error_code on error
          bacnet::service::possible_service_response res;
          handler(ec, res);
        }
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
    boost::asio::steady_timer timeout_timer_;
    bacnet::service::detail::device_manager device_manager_;
    bacnet::service::detail::callback_manager callback_manager_;
    bacnet::service::detail::inbound_router inbound_router_;
    bacnet::common::object_identifier device_object_identifier_;
    bacnet::config config_;




};

}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_CONTROLLER_HPP
