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
#include <bacnet/service/detail/inbound_router.hpp>

#include <bacnet/service/service.hpp>
#include <bacnet/service/service/detail/who_is_grammar.hpp>
#include <bacnet/service/service/detail/i_am_garmmar.hpp>
#include <bacnet/service/service/detail/reinitialize_device_grammar.hpp>
#include <bacnet/common/configuration.hpp>

#include <bacnet/apdu/api.hpp>


/**
 * SCOPE OF THIS LAYER
 * * decodes variable part of apdu
 *   * dependant on unconfirmed or confirmed service
 * * offer height level api to send services
 * * holds list of known clients (DOI<--> Address mapping)
 * * sends who_is if DOI is not known
 * *
 *
 */





namespace bacnet { namespace service { namespace service { namespace detail {
  using namespace bacnet::service;
  static inline unconfirmed::possible_service parse(bacnet::apdu::frame::unconfirmed_request& frame) {
    unconfirmed::possible_service parsed_service{};
    auto &data = frame.service_data;
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


  using namespace bacnet::service;
    static inline confirmed::possible_service parse(bacnet::apdu::frame::confirmed_request& frame) {
      confirmed::possible_service parsed_service{};
      auto &data = frame.service_data;
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


  }

  void start() {
    lower_layer_.register_callbacks(
        [this](bacnet::apdu::frame::unconfirmed_request request,  boost::system::error_code ec, bacnet::common::protocol::meta_information mi){
          std::cout << "bacnet::service::controller received unconfirmed_request " << std::endl;

          //parse and visitor for unconfirmed
          inbound_router_.meta_information(std::move(mi));
          auto f = bacnet::service::service::detail::parse(request);
           f.apply_visitor(inbound_router_);

          },
        [this](bacnet::apdu::frame::confirmed_request request,  boost::system::error_code ec, bacnet::common::protocol::meta_information mi){
            std::cout << "bacnet::service::controller received confirmed_request " << std::endl;
            inbound_router_.meta_information(std::move(mi));
            auto f = bacnet::service::service::detail::parse(request);
             f.apply_visitor(inbound_router_);
            //parse and visitor for confirmed
          }
    );

    lower_layer_.start();
    /*
     * dependant on the config, a callback for who_is request is registered, and requests are automaticly answered
     */
    if(config_.send_i_am_frames) {
      i_am_message_ = service::i_am{device_object_identifier_,
                                    ApduSize::size_in_bytes,
                                    bacnet::common::segmentation(bacnet::common::segmentation::segment::both),\
                                    ApduSize::size_in_bytes
                                    };
      callback_manager_.add_who_is_service_callback([this](bacnet::service::who_is service, boost::system::error_code ec, bacnet::common::protocol::meta_information mi){
        if(!ec)
          if(  (     service.device_instance_range_low_limit  == 0
                  && service.device_instance_range_high_limit == 0
               )
                ||
               (     this->config_.device_object_id >= service.device_instance_range_low_limit
                  && this->config_.device_object_id <= service.device_instance_range_high_limit
               )) {
            this->async_send(this->i_am_message_, [](const boost::system::error_code& ec){});
        }
      });
      async_send(i_am_message_, [](const boost::system::error_code& ec){});
    }
  }


  /*
   * make async_send dependent on a bacnet::endpoint, as a generic way to send unidirectional services
   */
  template<typename Service, typename Handler>
  void async_send(Service &&service, Handler handler) {
    auto data =  bacnet::service::service::detail::generate(service);

    if( bacnet::service::service::detail::is_broadcast_service<typename std::decay<Service>::type>::value) {
      lower_layer_.async_send_unconfirmed_request_as_broadcast(std::move(data), [this, &handler]( const boost::system::error_code& ec) {
        handler(ec);
      });
    }
    else {
      auto ec = boost::system::errc::make_error_code(boost::system::errc::bad_message);
      handler(ec);
    }
  }

  template<typename Service, typename Handler>
  void async_send(bacnet::common::protocol::mac::endpoint mac_endpoint, Service&& service, Handler handler) {
    async_send(mac_endpoint.address(), std::move(service), handler);
  }



  /*
   * handler accepts only possible service responses
   */
  template<typename Service, typename Handler>
  void async_send(bacnet::common::protocol::mac::address address, Service&& service, Handler handler) {
    auto data =  bacnet::service::service::detail::generate(std::move(service));

    lower_layer_.async_send_confirmed_request(address, std::move(data), [this, handler]
                                                                       ( const boost::system::error_code& ec,
                                                                               bacnet::apdu::frame::possible_confirmed_respons frame,
                                                                               bacnet::common::protocol::meta_information mi) {

      /*
       *
       */
      if(ec) {
        handler(ec, bacnet::service::possible_service_response());
      }
      else {
        inbound_router_.meta_information(std::move(mi));
        //xxx frame must be service
        //frame.apply_visitor(inbound_router_);
      }

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
     auto callback_idx =  callback_manager_.set_i_am_service_callback(
         [handler, service, endpoints, device_object_identifier, this]
           (bacnet::service::i_am i_am, boost::system::error_code ec, bacnet::common::protocol::meta_information mi) {
               if(i_am.i_am_device_identifier == device_object_identifier) {
                 async_send(mi.address, service, handler);
               }
            });

     bacnet::service::service::who_is wi(device_object_identifier.instance_number(), device_object_identifier.instance_number());
     async_send(wi, [handler](boost::system::error_code ec) {  });


      timeout_timer_.expires_from_now(time_wait_for_i_am_answer);
      timeout_timer_.async_wait([handler,callback_idx,  this](boost::system::error_code ec) {
        callback_manager_.clear_i_am_service_callback(callback_idx);

        if(ec == boost::asio::error::operation_aborted) {
            //todo store handler and wait for answer!
            bacnet::service::possible_service_response res;
            handler(ec, res);
          }
        else {
          std::cout << "no device with doi found  " << std::endl;
          //todo set special error_code on error
          bacnet::service::possible_service_response res;
          handler(ec, res);
        }
      });
    }
  }

  template<typename ...Callbacks>
  void async_receive(Callbacks... callbacks) {
    callback_manager_.set_service_callbacks(callbacks...);
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
    service::i_am i_am_message_;




};

}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_CONTROLLER_HPP
