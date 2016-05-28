//
// Created by dan on 12/9/15.
//

#ifndef NINJA_WOOKIE_BACNET_TRANSPORT__IP_V4_MOCKUP_HPP
#define NINJA_WOOKIE_BACNET_TRANSPORT__IP_V4_MOCKUP_HPP


#include <iostream>

#include <boost/asio.hpp>
#include <functional>
#include <boost/bind.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/transport/api.hpp>


namespace bacnet { namespace transport {


typedef std::function<bacnet::error_code (boost::asio::ip::udp::endpoint,  ::bacnet::binary_data) > from_application_callback;

/**
 * simple mockup for testing the stack without the need of a real IP-connection
 * calling async_send  -> calls async_send_from_stack_callback
 * calling async_send_to_stack  -> calls async_receive_callback
 */
struct ip_v4_mockup {

public:


    ip_v4_mockup(boost::asio::io_service &io_service) :  io_service_(io_service) {

    }

    /**
     * needed api for upper layer
     */
    void register_receive_callback(const ::bacnet::transport::receive_callback &callback) {
      receive_callback_ = callback;
    }

    /**
     * needed by api
     */
    void start() {
      if(!receive_callback_ || !from_application_callback_) {
        throw std::runtime_error("transport::ip_v4_mockup : no callback set, cant work without it");
      }
    }

    /**
     * needed by api
     */
    template<typename Handler>
    void async_send(const ::bacnet::binary_data &data, const ::bacnet::common::protocol::mac::address &receiver, const Handler &handler) {
      io_service_.post([this, data, receiver, handler](){
        if(!receiver.is_ip()) {
          throw std::runtime_error("transport::ip_v4_mockup : its not a ip endpoint");
        }
        auto ip_receiver = receiver.ip().to_system_endpoint();
        bacnet::error_code ec = from_application_callback_(ip_receiver, data);
        handler(ec);
      });
    }


    /**
     * mockup callback, is called when something is send from application_layer to the network
     */
    void set_from_application_callback(const from_application_callback &callback) {
      from_application_callback_ = callback;
    }

    /**
     * mockup used to send somthing to the application_layer
     */
    void send_to_application(const bacnet::error_code &ec, const boost::asio::ip::udp::endpoint &ep ,const ::bacnet::binary_data& data) {
      auto ip_ep = ::bacnet::common::protocol::mac::address_ip::from_native(ep);
      ::bacnet::common::protocol::mac::address bacnet_ep(ip_ep);

      io_service_.post([=]() {
        auto send_ec = ec;
        auto send_ep = bacnet_ep;
        auto send_data = data;
        receive_callback_(std::move(send_ec), std::move(send_ep), std::move(send_data));
      });
    }
    /**
     * mockup used to send somthing to the application_layer
     */
    void send_to_application(const bacnet::error_code &ec, const ::bacnet::common::protocol::mac::address &ep, const ::bacnet::binary_data& data) {
      io_service_.post([=]() {
        auto send_ec = ec;
        auto send_ep = ep;
        auto send_data = data;
        receive_callback_(std::move(send_ec), std::move(send_ep), std::move(send_data));
      });
    }

private:

    boost::asio::io_service &io_service_;
    ::bacnet::transport::receive_callback receive_callback_;
    from_application_callback from_application_callback_;

};


}}



#endif //NINJA_WOOKIE_BACNET_TRANSPORT__IP_V4_MOCKUP_HPP
