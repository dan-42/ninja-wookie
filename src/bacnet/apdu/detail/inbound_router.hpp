/*
 * inbound_router.hpp
 *
 *  Created on: Jul 29, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_
#define SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_


#include <bacnet/apdu/frame/frames.hpp>


namespace bacnet { namespace  apdu { namespace  detail {


using namespace bacnet::apdu;

template<typename CallbackManager, typename RequestManager>
class inbound_router {

public:

  inbound_router(CallbackManager& cbm, RequestManager& rm) : callback_manager_(cbm), request_manager_(rm){
  }

  inline void meta_information(bacnet::common::protocol::meta_information meta) {
    meta_information_ = meta;
  }

  /**
   * handle segmentation, each complex message could be segmented,
   * and would need concatenation before sending up
   */
  void operator()(frame::segment_ack response) {
    //xxx build up whole frame and then invoke handler
    std::cout << "apdu::detail::inbound_router segment_ack" << std::endl;
    meta_information_.invoke_id = response.original_invoke_id;
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// new requests

  void operator()(frame::confirmed_request request) {
    if( request.pdu_type_and_control_information.is_segmented()) {

    }
    else {
      bacnet::error ec;
      meta_information_.invoke_id = request.invoke_id;
      callback_manager_.invoke_callback(request, ec, meta_information_);
    }
  }

  void operator()(frame::unconfirmed_request request) {
    bacnet::error ec;
    callback_manager_.invoke_callback(request, ec, meta_information_);
  }

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //// responses to requests

  void operator()(frame::simple_ack response) {
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
    if(handler) {
      bacnet::error success;
      meta_information_.invoke_id = response.original_invoke_id;
      handler(success, frame::complex_ack{}, meta_information_);
    }
  }

  void operator()(frame::complex_ack response) {

    if( response.pdu_type_and_control_information.is_segmented()) {

    }
    else {

      auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
      if(handler) {
        bacnet::error ec;
        meta_information_.invoke_id = response.original_invoke_id;
        handler(ec, response, meta_information_);
      }
    }
  }

  void operator()(frame::error response) {
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
    if(handler) {
      meta_information_.invoke_id = response.original_invoke_id;
      bacnet::error ec(response.error_.error_code.value, response.error_.error_class.value);
      handler(ec, frame::complex_ack{}, meta_information_);
    }
  }

  void operator()(frame::reject response) {
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
    if(handler) {
      meta_information_.invoke_id = response.original_invoke_id;
      bacnet::error ec = bacnet::make_reject_reason(response.reject_reason);
      handler(ec, frame::complex_ack{}, meta_information_);
    }
  }

  void operator()(frame::abort response) {
    auto handler = request_manager_.get_handler_and_purge(meta_information_.address, response.original_invoke_id);
    if(handler) {
      meta_information_.invoke_id = response.original_invoke_id;
      bacnet::error ec = bacnet::make_abort_reason(response.abort_reason);
      handler(ec, frame::complex_ack{}, meta_information_);
    }
  }



private:
  CallbackManager& callback_manager_;
  RequestManager& request_manager_;
  bacnet::common::protocol::meta_information meta_information_;

};

}}}

#endif /* SRC_BACNET_APDU_DETAIL_INBOUND_ROUTER_HPP_ */
