/*
 * ip_v4.hpp
 *
 *  Created on: Feb 13, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_STACK_FACTORY_HPP_
#define SRC_BACNET_STACK_FACTORY_HPP_

#include <iostream>
#include <exception>

#include <limits>

#include <boost/asio.hpp>
#include <boost/format.hpp>

#include <bacnet/transport/api.hpp>
#include <bacnet/transport/ip_v4.hpp>

#include <bacnet/bvll/controller.hpp>
#include <bacnet/npdu/controller.hpp>
#include <bacnet/apdu/controller.hpp>
#include <bacnet/apdu/config.hpp>
#include <bacnet/common/config.hpp>
#include <bacnet/service/controller.hpp>
#include <bacnet/type/types.hpp>

namespace bacnet { namespace stack {

 enum stack_t{
   ip_v4_server,
   ip_v4_client,
   ip_v6,
   mstp
 };


namespace detail {
  namespace ip_v4 {

    typedef bacnet::apdu::config::default_                                   static_config_t;

    typedef bacnet::transport::ip_v4                                         transporter_t;
    typedef bacnet::bvll::controller<transporter_t>                          bvll_controller_t;
    typedef bacnet::npdu::controller<bvll_controller_t>                      npdu_controller_t;
    typedef bacnet::apdu::controller<npdu_controller_t, static_config_t>     apdu_controller_t;
    typedef bacnet::service::controller<apdu_controller_t, static_config_t>  service_controller_t;
  }
 }

template<stack_t T>
struct factory { };


template<>
struct factory<ip_v4_server> {
  factory(boost::asio::io_service &ios, const std::string& ip, uint16_t port) :
             transporter(ios, {ip, port} ),
             bvll_controller(ios, transporter),
             npdu_controller(bvll_controller),
             apdu_controller(ios, npdu_controller),
             service_controller(ios, apdu_controller, bacnet::common::config{}) {
  }

  factory(boost::asio::io_service &ios, const std::string& ip, uint16_t port, bacnet::common::config c) :
               transporter(ios, {ip, port} ),
               bvll_controller(ios, transporter),
               npdu_controller(bvll_controller),
               apdu_controller(ios, npdu_controller),
               service_controller(ios, apdu_controller, c) {
    }

  detail::ip_v4::service_controller_t & controller() {
    return service_controller;
  }

private:
    detail::ip_v4::transporter_t         transporter;
    detail::ip_v4::bvll_controller_t     bvll_controller;
    detail::ip_v4::npdu_controller_t     npdu_controller;
    detail::ip_v4::apdu_controller_t     apdu_controller;
    detail::ip_v4::service_controller_t  service_controller;

};


template<>
struct factory<ip_v4_client> {
  factory(boost::asio::io_service &ios, const std::string& ip, uint16_t port) :
             config(bacnet::common::config{1337,    // vendor_id
                                           1,       // device_object_id
                                           1,       // network_number
                                           false,   // send_i_am_frames
                                           false}), //is_server
             transporter(ios, {ip, port} ),
             bvll_controller(ios, transporter),
             npdu_controller(bvll_controller),
             apdu_controller(ios, npdu_controller),
             service_controller(ios, apdu_controller, config) {
  }

  factory(boost::asio::io_service &ios, const std::string& ip, uint16_t port, bacnet::common::config c) :
               config(c),
               transporter(ios, {ip, port} ),
               bvll_controller(ios, transporter),
               npdu_controller(bvll_controller),
               apdu_controller(ios, npdu_controller),
               service_controller(ios, apdu_controller, config) {
    }

  detail::ip_v4::service_controller_t & controller() {
    return service_controller;
  }

private:
    bacnet::common::config               config{};
    detail::ip_v4::transporter_t         transporter;
    detail::ip_v4::bvll_controller_t     bvll_controller;
    detail::ip_v4::npdu_controller_t     npdu_controller;
    detail::ip_v4::apdu_controller_t     apdu_controller;
    detail::ip_v4::service_controller_t  service_controller;

};

}}

#endif /* SRC_BACNET_STACK_FACTORY_HPP_ */
