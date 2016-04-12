/*
 * inbound_router.hpp
 *
 *  Created on: Jul 29, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_
#define SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_



#include <iostream>
#include <iomanip>

#include <boost/variant/static_visitor.hpp>
#include <bacnet/apdu/frame/frames.hpp>

#include <bacnet/apdu/detail/request_manager.hpp>


namespace bacnet { namespace  apdu { namespace  detail {


using namespace bacnet::apdu;

template<typename CallbackManager>
class inbound_router : public boost::static_visitor<> {

public:

  inbound_router(CallbackManager& cbm, request_manager& rm) : callback_manager_(cbm), request_manager_(rm){
  }

  inline void meta_information(bacnet::common::protocol::meta_information meta) {
    meta_information_ = meta;
  }

  /**
   * handle segmentation, each complex message could be segmented,
   * and would need concatinatinon before sending up
   */
  void operator()(frame::segment_ack response) {
    //xxx build up whole frame and then invoke handler
    std::cout << "apdu::detail::inbound_router segment_ack" << std::endl;
  }

  //// new requests
  void operator()(frame::confirmed_request request) {
    std::cout << "apdu::detail::inbound_router confirmed_request" << std::endl;
    boost::system::error_code ec;
    callback_manager_.invoke_callback(request, ec, meta_information_);
  }

  void operator()(frame::unconfirmed_request request) {
    boost::system::error_code ec;
    callback_manager_.invoke_callback(request, ec, meta_information_);
  }


  //// responses to requests
  void operator()(frame::simple_ack response) {
    std::cout << "apdu::detail::inbound_router simple_ack" << std::endl;
    boost::system::error_code ec;
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
    if(handler) {
      handler(ec, response, meta_information_);
    }
  }

  void operator()(frame::complex_ack response) {
    std::cout << "apdu::detail::inbound_router complex_ack" << std::endl;
    boost::system::error_code ec;
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
    if(handler) {
      handler(ec, response, meta_information_);
    }
  }

  void operator()(frame::error response) {
    std::cout << "apdu::detail::inbound_router error" << std::endl;
    boost::system::error_code ec;
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
    if(handler) {
      handler(ec, response, meta_information_);
    }
  }

  void operator()(frame::reject response) {
    std::cout << "apdu::detail::inbound_router reject" << std::endl;
    boost::system::error_code ec;
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
    if(handler) {
      handler(ec, response, meta_information_);
    }
  }

  void operator()(frame::abort response) {
    std::cout << "apdu::detail::inbound_router abort" << std::endl;
    boost::system::error_code ec;
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
    if(handler) {
      handler(ec, response, meta_information_);
    }
  }



private:
  CallbackManager& callback_manager_;
  request_manager& request_manager_;
  bacnet::common::protocol::meta_information meta_information_;

};

}}}

#endif /* SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_ */
