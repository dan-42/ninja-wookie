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
#include <bacnet/apdu/detail/callback_manager.hpp>
#include <bacnet/apdu/detail/request_manager.hpp>


namespace bacnet { namespace  apdu { namespace  detail {


using namespace bacnet::apdu;

class inbound_router : public boost::static_visitor<> {

public:

  inbound_router(callback_manager& cbm, request_manager& rm) : callback_manager_(cbm), request_manager_(rm){
  }

  inline void meta_information(bacnet::common::protocol::meta_information meta) {
    meta_information_ = meta;
  }


  void operator()(frame::confirmed_request request) {
    std::cout << "apdu::detail::inbound_router confirmed_request" << std::endl;
    boost::system::error_code ec;
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, request.invoke_id);
    if(handler) {
      handler(ec, request, meta_information_);
    }
  }

  void operator()(frame::unconfirmed_request request) {

      if(callback_manager_.async_received_service_callback_) {
       // meta_info.service_choice = request.service_choice;
        auto data = request.service_data;
        callback_manager_.async_received_service_callback_(std::move(meta_information_), std::move(data));
      }

  }

  void operator()(frame::simple_ack request) {
    std::cout << "apdu::detail::inbound_router simple_ack" << std::endl;
    boost::system::error_code ec;
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, request.original_invoke_id);
    if(handler) {
      handler(ec, request, meta_information_);
    }
  }

  void operator()(frame::complex_ack request) {
    std::cout << "apdu::detail::inbound_router complex_ack" << std::endl;
    boost::system::error_code ec;
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, request.original_invoke_id);
    if(handler) {
      handler(ec, request, meta_information_);
    }
  }

  void operator()(frame::segment_ack request) {
    //xxx build up whole frame and then invoke handler
      std::cout << "apdu::detail::inbound_router segment_ack" << std::endl;
  }

  void operator()(frame::error request) {
      std::cout << "apdu::detail::inbound_router error" << std::endl;
    if(callback_manager_.async_received_service_callback_) {
      auto data = request.error_data;
      callback_manager_.async_received_error_callback_(std::move(meta_information_), std::move(data));
    }
    boost::system::error_code ec;
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, request.original_invoke_id);
    if(handler) {
      handler(ec, request, meta_information_);
    }
  }

  void operator()(frame::reject request) {
      std::cout << "apdu::detail::inbound_router reject" << std::endl;
      boost::system::error_code ec;
      auto handler = request_manager_.get_handler_and_purge(meta_information_.address, request.original_invoke_id);
      if(handler) {
        handler(ec, request, meta_information_);
      }
  }

  void operator()(frame::abort request) {
      std::cout << "apdu::detail::inbound_router abort" << std::endl;
      boost::system::error_code ec;
      auto handler = request_manager_.get_handler_and_purge(meta_information_.address, request.original_invoke_id);
      if(handler) {
        handler(ec, request, meta_information_);
      }
  }

private:
  callback_manager& callback_manager_;
  request_manager& request_manager_;
  bacnet::common::protocol::meta_information meta_information_;

};

}}}

#endif /* SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_ */
