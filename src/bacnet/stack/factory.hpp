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
#include <bacnet/service/controller.hpp>
#include <bacnet/common/configuration.hpp>


namespace bacnet { namespace stack {

 enum stack_t{
   ip_v4,
   ip_v6,
   mstp
 };


namespace detail {
  namespace ip_v4 {

    typedef bacnet::configuration::apdu_size::_1476_bytes_ipv4 apdu_size;

    typedef bacnet::transport::ip_v4                                  transporter_t;
    typedef bacnet::bvll::controller<transporter_t>                   bvll_controller_t;
    typedef bacnet::npdu::controller<bvll_controller_t>               npdu_controller_t;
    typedef bacnet::apdu::controller<npdu_controller_t, apdu_size>    apdu_controller_t;
    typedef bacnet::service::controller<apdu_controller_t, apdu_size> service_controller_t;
  }
 }

template<stack_t T>
struct factory { };


template<>
struct factory<ip_v4> {
  factory(boost::asio::io_service &ios, const std::string& ip, uint16_t port) :
             transporter(ios, {ip, port} ),
             bvll_controller(ios, transporter),
             npdu_controller(bvll_controller),
             apdu_controller(ios, npdu_controller),
             service_controller(ios, apdu_controller, bacnet::config{}) {
  }

  factory(boost::asio::io_service &ios, const std::string& ip, uint16_t port, bacnet::config c) :
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



}}

#endif /* SRC_BACNET_STACK_FACTORY_HPP_ */
