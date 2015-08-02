/*
 * inbound_router.hpp
 *
 *  Created on: Jul 29, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_
#define SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_



#include <iostream>
#include <boost/variant/static_visitor.hpp>

#include <bacnet/apdu/frame/frames.hpp>


namespace bacnet { namespace  apdu { namespace  detail {


using namespace bacnet::apdu;

class inbound_router : public boost::static_visitor<> {

public:

  void operator()(frame::confirmed_request request) {
    std::cout << "apdu::detail::inbound_router confirmed_request" << std::endl;
  }

  void operator()(frame::unconfirmed_request request) {
      std::cout << "apdu::detail::inbound_router unconfirmed_request" << std::endl;
  }

  void operator()(frame::simple_ack request) {
      std::cout << "apdu::detail::inbound_router simple_ack" << std::endl;
  }

  void operator()(frame::complex_ack request) {
      std::cout << "apdu::detail::inbound_router complex_ack" << std::endl;
  }

  void operator()(frame::segment_ack request) {
      std::cout << "apdu::detail::inbound_router segment_ack" << std::endl;
  }

  void operator()(frame::error request) {
      std::cout << "apdu::detail::inbound_router error" << std::endl;
  }

  void operator()(frame::reject request) {
      std::cout << "apdu::detail::inbound_router reject" << std::endl;
  }

  void operator()(frame::abort request) {
      std::cout << "apdu::detail::inbound_router abort" << std::endl;
  }

};

}}}

#endif /* SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_ */
