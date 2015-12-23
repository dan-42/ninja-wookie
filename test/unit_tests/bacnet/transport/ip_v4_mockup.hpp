//
// Created by dan on 12/9/15.
//

#ifndef NINJA_WOOKIE_BACNET_TRANSPORT__IP_V4_MOCKUP_HPP
#define NINJA_WOOKIE_BACNET_TRANSPORT__IP_V4_MOCKUP_HPP


#include <iostream>

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/transport/api.hpp>


namespace bacnet { namespace transport {


typedef boost::function<boost::system::error_code (boost::asio::ip::udp::endpoint,  ::bacnet::binary_data) > async_send_from_stack_callback;

/**
 * simple mockup for testing the stack without the need of a real IP-connection
 * calling async_send  -> calls async_send_from_stack_callback
 * calling async_send_to_stack  -> calls async_receive_callback
 */
struct ip_v4_mockup {

public:


    ip_v4_mockup(boost::asio::io_service &io_service) :  io_service_(io_service) {

    }

    void set_async_receive_callback(const ::bacnet::transport::async_receive_callback &callback) {
      async_receive_callback_ = callback;
    }

    void set_async_send_from_stack_callback(const async_send_from_stack_callback &callback) {
      async_send_from_stack_callback_ = callback;
    }



    template<typename Handler>
    void async_send(const ::bacnet::binary_data &data, const ::bacnet::common::protocol::mac::address &receiver, const Handler &handler) {
      bacnet::print(data);
      io_service_.post([this, data, receiver, handler](){
        if(!receiver.is_ip()) {
          throw new std::runtime_error("transport::ip_v4 : its not a ip endpoint");
        }
        auto ip_receiver = receiver.ip().to_system_endpoint();
        boost::system::error_code ec = async_send_from_stack_callback_(ip_receiver, data);
        handler(ec);
      });
    }

    void start() {

      if(async_receive_callback_.empty() || async_send_from_stack_callback_.empty()) {
        throw new std::runtime_error("transport::ip_v4 : no callback set, cant work without it");
      }

    }

    void async_send_to_stack(boost::system::error_code ec, ::bacnet::common::protocol::mac::address ep ,::bacnet::binary_data data) {
      io_service_.post([=]() {
        async_receive_callback_(ec, ep, data);
      });
    }

private:

    boost::asio::io_service &io_service_;
    ::bacnet::transport::async_receive_callback async_receive_callback_;
    async_send_from_stack_callback async_send_from_stack_callback_;

};


}}



#endif //NINJA_WOOKIE_BACNET_TRANSPORT__IP_V4_MOCKUP_HPP
