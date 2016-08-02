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

#include <pre/json/to_json.hpp>

#include <bacnet/service/api.hpp>
#include <bacnet/service/detail/callback_manager.hpp>
#include <bacnet/service/detail/device_manager.hpp>
#include <bacnet/service/detail/inbound_router.hpp>

#include <bacnet/service/service.hpp>

#include <bacnet/service/service/detail/service_grammar.hpp>
#include <bacnet/common/configuration.hpp>

#include <bacnet/apdu/api.hpp>
#include <bacnet/type/types.hpp>
#include <bacnet/error/error.hpp>


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



namespace bacnet { namespace service { namespace detail {

using namespace bacnet::service;

template<class Service, class Enable = void>
struct invoke_handler_ {

  static constexpr bool expect_complex_response = false;

  template<typename Handler, typename T>
  static inline void invoke(Handler &&handler, bacnet::error ec, T response ) {
      handler(std::move(ec));
  }
  template<typename Handler>
  static inline void invoke(Handler &&handler, bacnet::error ec) {
    handler(std::move(ec));
  }
};


template<class Service>
struct invoke_handler_<Service, typename std::enable_if<  service::has_complex_response<typename std::decay<Service>::type >::value  >::type> {

  static constexpr bool expect_complex_response = true;

  template<typename Handler>
  static inline void invoke(Handler &&handler, bacnet::error ec ) {
    typedef pre::lambda::function_traits<typename std::decay<Handler>::type > callback_traits;
    typedef typename callback_traits::template arg<1> arg_1_t;
    typedef typename std::decay<arg_1_t>::type service_response_type;
    service_response_type empty_resp{};
    handler(ec, empty_resp);
  }

  template<typename Handler, typename T>
  static inline void invoke(Handler &&handler, bacnet::error ec, T response ) {
    typedef pre::lambda::function_traits<typename std::decay<Handler>::type > callback_traits;
    typedef typename callback_traits::template arg<1> arg_1_t;
    typedef typename std::decay<arg_1_t>::type service_response_type;
    auto ff = boost::get<service_response_type>(response);
    handler(ec, ff);
  }

};

}}}


namespace bacnet { namespace service {

    static const std::chrono::milliseconds time_wait_for_i_am_answer{2000};

template<typename UnderlyingLayer, typename ApduSize>
class controller {
public:



  controller(boost::asio::io_service& io_service, UnderlyingLayer& lower_layer, bacnet::config config):
                io_service_(io_service),
                lower_layer_(lower_layer),
                inbound_router_(callback_manager_, device_manager_),
                device_object_identifier_(bacnet::type::object_type::device, config.device_object_id),
                config_(config) {
  }

  inline bacnet::config config() const { return config_; }

  void start() {
    lower_layer_.register_callbacks(
        [this](bacnet::apdu::frame::unconfirmed_request request,  bacnet::error ec, bacnet::common::protocol::meta_information mi){
            inbound_router_.meta_information(std::move(mi));
            auto f = bacnet::service::service::detail::parse_unconfirmed(request.service_data);
            f.apply_visitor(inbound_router_);
          },
        [this](bacnet::apdu::frame::confirmed_request request,  bacnet::error ec, bacnet::common::protocol::meta_information mi){
            inbound_router_.meta_information(std::move(mi));
            auto f = bacnet::service::service::detail::parse_confirmed_request(request.service_data);
            f.apply_visitor(inbound_router_);
          }
    );

    lower_layer_.start();
    /*
     * Dependent on the config, a callback for who_is request is registered, and requests are automatically answered
     */
    if(config_.send_i_am_frames) {
      i_am_message_ = service::i_am{device_object_identifier_,
                                    ApduSize::size_in_bytes,
                                    bacnet::common::segmentation(bacnet::common::segmentation::segment::both),\
                                    ApduSize::size_in_bytes
                                    };
      callback_manager_.add_who_is_service_callback([this](bacnet::service::who_is service, bacnet::error ec, bacnet::common::protocol::meta_information mi){
        if(!ec)
          if(  (     !service.device_instance_range_low_limit
                  && !service.device_instance_range_high_limit
               )
                ||
               (     this->config_.device_object_id >= service.device_instance_range_low_limit.value()
                  && this->config_.device_object_id <= service.device_instance_range_high_limit.value()
               )) {
            this->async_send(this->i_am_message_, [](const bacnet::error& ec){});
        }
      });
      async_send(i_am_message_, [](const bacnet::error& ec){});
    }
  }


  /*
   * make async_send dependent on a bacnet::endpoint, as a generic way to send unidirectional services
   */
  template<typename Service, typename Handler>
  void async_send(Service &&service, Handler handler) {
    auto data =  bacnet::service::service::detail::generate_unconfirmed(service);

    if( bacnet::service::service::detail::is_broadcast_service<typename std::decay<Service>::type>::value) {
      lower_layer_.async_send_unconfirmed_request_as_broadcast(std::move(data), handler);
    }
    else {
      std::cerr << "async_send() is not a broadcast service" << std::endl;
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
    using invoker = typename bacnet::service::detail::invoke_handler_<Service>;

    auto data =  bacnet::service::service::detail::generate_confirmed_request(std::move(service));
    lower_layer_.async_send_confirmed_request(address, std::move(data), [this, handler]
                                                                       ( const bacnet::error& ec,
                                                                               bacnet::apdu::frame::complex_ack frame,
                                                                               bacnet::common::protocol::meta_information mi) {
                                      if(invoker::expect_complex_response) {
                                        if(ec) {
                                          invoker::invoke(handler, ec);
                                        }
                                        else {
                                          auto f = bacnet::service::service::detail::parse_confirmed_response(frame.service_ack_data);
                                          invoker::invoke(handler, ec, f);
                                        }
                                      }
                                      else {
                                        invoker::invoke(handler, ec);
                                      }
                                    });
  }

  template<typename Service, typename Handler>
  void async_send(bacnet::type::object_identifier device_object_identifier, Service service, Handler handler) {
    /* lookup doi */
    auto endpoints = device_manager_.get_endpoint(device_object_identifier);
    if(endpoints.size() == 1) {
      async_send(endpoints.front(), service, handler);
    }
    else {
      find_device_and_execute(device_object_identifier, service, handler);
    }
  }

  template<typename ...Callbacks>
  void async_receive(Callbacks... callbacks) {
    callback_manager_.set_service_callbacks(callbacks...);
  }
  template<typename Service, typename Handler>
  void async_send_response(Service service, bacnet::common::protocol::meta_information mi, Handler handler) {
    auto data =  bacnet::service::service::detail::generate_confirmed_response(std::move(service));
    lower_layer_.async_send_confirmed_response(std::move(data), mi, handler);
  }

  template<typename Handler>
  void async_send_response(bacnet::error error, bacnet::common::protocol::meta_information mi, Handler handler) {
    lower_layer_.async_send_confirmed_response(error, mi, handler);
  }

private:


  struct pending_request {
    typedef std::function<void(boost::asio::steady_timer &timer, bool& is_active)> callback_t;

    boost::asio::steady_timer timer;
    callback_t callback;
    bool is_active{true};

    pending_request(boost::asio::io_service& ios, callback_t cbf) :
      timer(ios), callback(cbf) {
      callback(timer, is_active);
    }
    virtual ~pending_request() { }
  };

  inline void maintain_list_of_device_search_requests() {
    auto new_end = std::remove_if(list_of_device_search_requests.begin(), list_of_device_search_requests.end(),
                                  [](std::shared_ptr<pending_request> r) {
                                      return ( (r == nullptr)   ||   (!r->is_active) );
                                  });
    list_of_device_search_requests.erase(new_end, list_of_device_search_requests.end());
  }

  template<typename Service, typename Handler>
  void find_device_and_execute(bacnet::type::object_identifier device_object_identifier, Service service, Handler handler) {
    using invoker = typename bacnet::service::detail::invoke_handler_<Service>;

    maintain_list_of_device_search_requests();

    list_of_device_search_requests.emplace_back(std::make_shared<pending_request>(io_service_,
              [&](boost::asio::steady_timer &timer,  bool& is_active) {
                   auto callback_idx =  callback_manager_.set_i_am_service_callback(
                                               [handler, service, device_object_identifier, this, &timer]
                                                    (bacnet::service::i_am i_am, bacnet::error ec, bacnet::common::protocol::meta_information mi) {
                                                      if(i_am.i_am_device_identifier == device_object_identifier) {
                                                        timer.cancel();
                                                        async_send(mi.address, service, handler);
                                                      }
                                                     });
                   timer.expires_from_now(time_wait_for_i_am_answer);
                   timer.async_wait(
                                       [handler, callback_idx,  this, &is_active]
                                           (boost::system::error_code ec) {
                                                  this->callback_manager_.clear_i_am_service_callback(callback_idx);
                                                  if(ec == boost::asio::error::operation_aborted) { /*no op*/  }
                                                  else if(!ec) {
                                                    auto e = bacnet::make_error(bacnet::err::error_class::communication, bacnet::err::error_code::bad_destination_device_id);
                                                    invoker::invoke(handler, e);
                                                  }
                                                  else {
                                                    invoker::invoke(handler, ec);
                                                  }
                                                  is_active = false;
                                            });
                   bacnet::service::service::who_is wi(device_object_identifier.instance_number);
                   async_send(wi, [](bacnet::error ec) {  });
                }));
  }

  std::list< std::shared_ptr<pending_request> > list_of_device_search_requests;
  boost::asio::io_service& io_service_;
  UnderlyingLayer &lower_layer_;
  bacnet::service::detail::device_manager device_manager_;
  bacnet::service::detail::callback_manager callback_manager_;
  bacnet::service::detail::inbound_router inbound_router_;
  bacnet::type::object_identifier device_object_identifier_;
  bacnet::config config_;
  service::i_am i_am_message_;
};



}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_CONTROLLER_HPP
