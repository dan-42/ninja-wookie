//
// Created by dan on 07.12.15.
//

#ifndef NINJA_WOOKIE_BACNET_TRANSPORT_IP_V4_HPP
#define NINJA_WOOKIE_BACNET_TRANSPORT_IP_V4_HPP

#include <iostream>

#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <bacnet/transport/api.hpp>


namespace bacnet { namespace transport {


struct ip_v4 {

public:


  ip_v4(boost::asio::io_service &io_service) :
                                                io_service_(io_service),
                                                socket_(io_service),
                                                port_(bacnet::transport::config::DEFAULT_LISTENING_PORT),
                                                listen_address_(boost::asio::ip::address::from_string(bacnet::transport::config::DEFAULT_LISTENING_ADDRESS)),
                                                listen_endpoint_(listen_address_, port_) {

  }

  ip_v4(boost::asio::io_service &io_service, const bacnet::transport::configuration& config) :
                                                io_service_(io_service),
                                                socket_(io_service),
                                                port_(config.listening_port),
                                                listen_address_(boost::asio::ip::address::from_string(config.listening_address)),
                                                listen_endpoint_(listen_address_, port_) {

  }

  void set_async_receive_callback(const async_receive_callback &callback) {
    async_receive_callback_ = callback;
  }

  template<typename Handler>
  void async_send(const bacnet::binary_data &data, bacnet::common::protocol::mac::address &receiver, const Handler &handler) {
    if(!receiver.is_ip()) {
      throw new std::runtime_error("transport::ip_v4 : its not a ip endpoint");
    }
    auto ip_receiver = receiver.ip().to_system_endpoint();
    socket_.async_send_to(boost::asio::buffer(data, data.size()), ip_receiver, [this, handler]( const boost::system::error_code& ec,  std::size_t bytes_transferred){
      handler(ec);
    });
  }

  void start() {

    if(async_receive_callback_.empty()) {
      throw new std::runtime_error("transport::ip_v4 : no callback set, cant work without it");
    }

    socket_.open(listen_endpoint_.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.set_option(boost::asio::socket_base::broadcast(true));
    socket_.bind(listen_endpoint_);

    auto callback = boost::bind(&ip_v4::handle_receive_from, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred);
    socket_.async_receive_from(boost::asio::buffer(data_, std::numeric_limits<uint16_t>::max()), sender_endpoint_, callback);
  }

private:


  void handle_receive_from(const boost::system::error_code& ec,  std::size_t bytes_transferred) {

    bacnet::common::protocol::mac::address sender(bacnet::common::protocol::mac::address_ip::from_native(sender_endpoint_));

    if(!ec) {
      bacnet::binary_data input(data_.begin(), data_.begin() + bytes_transferred);
      async_receive_callback_(ec, sender, std::move(input));
    }
    else {
      async_receive_callback_(ec, sender, bacnet::binary_data{});
    }

    auto callback = boost::bind(&ip_v4::handle_receive_from, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred);
    socket_.async_receive_from(boost::asio::buffer(data_, std::numeric_limits<uint16_t>::max()), sender_endpoint_, callback);
  }


  boost::asio::io_service &io_service_;
  async_receive_callback async_receive_callback_;
  boost::asio::ip::udp::socket socket_;
  uint16_t port_;
  boost::asio::ip::address listen_address_;
  boost::asio::ip::udp::endpoint listen_endpoint_;
  boost::asio::ip::udp::endpoint sender_endpoint_;
  std::array<uint8_t, std::numeric_limits<uint16_t>::max()> data_;

};


  }}


#endif //NINJA_WOOKIE_BACNET_TRANSPORT_IP_V4_HPP
