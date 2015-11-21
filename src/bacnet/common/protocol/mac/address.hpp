//
// Created by dan on 14.10.15.
//

#ifndef NINJA_WOOKIE_BACNET_MAC_ENDPOINT_HPP
#define NINJA_WOOKIE_BACNET_MAC_ENDPOINT_HPP

#include <boost/asio.hpp>

#include <bacnet/detail/common/types.hpp>

namespace bacnet {  namespace common { namespace protocol { namespace mac {
    //todo with ipv6
    typedef boost::asio::ip::address_v6 address_ipv6;

    class address_ip {
    public:

      static constexpr uint16_t default_port = 0xBAC0;

      static address_ip from_string(const std::string s, uint16_t port = default_port) {
        return address_ip(boost::asio::ip::address_v4::from_string(s), port);
      }

      static address_ip from_bytes(const bacnet::binary_data bytes) {
        //static constexpr uint8_t size_expected = 6;
        //if(bytes.size() != size_expected) {
        //  return address_ip{};
        //}
        //boost::asio::ip::address::f
        return address_ip{};
      }


      address_ip() : port_(default_port) {
      }
      address_ip(const address_ip& other)
          : address_(other.address_), port_(other.port_) {
      }
      address_ip(address_ip&& other)
          : address_(other.address_), port_(other.port_) {
      }
      address_ip(const boost::asio::ip::address_v4& address, uint16_t port)
          : address_(address), port_(port) {
      }
      address_ip(const std::string& address_str, uint16_t port)
          : address_(boost::asio::ip::address_v4::from_string(address_str)), port_(port) {
      }

      address_ip& operator=(address_ip&& other) {
        address_ = other.address_;
        port_ = other.port_;
        return *this;
      }
      address_ip& operator=(const address_ip& other) {
        address_ = other.address_;
        port_ = other.port_;
        return *this;
      }

      inline std::string to_string() {
        return (address_.to_string() + ":" + std::to_string(port_));
      }


      inline boost::asio::ip::udp::endpoint to_system_endpoint() const {
        //todo
        return boost::asio::ip::udp::endpoint{};
      }

    private:
      boost::asio::ip::address_v4 address_;
      uint16_t port_;

    };


    class address_mstp {
        /*  to do  */
    };


    class address {
    public:
      static address_ip ip() {
        return address_ip();
      }
      static address_ipv6 ipv6() {
        return address_ipv6();
      }
      static address_mstp mstp() {
        return address_mstp();
      }


      address() : type_(ip_), address_ip_(address_ip{}){

      }
      address(const address_ip& address) : type_(ip_), address_ip_(address)  {

      }
      address(const address_ipv6& address)  : type_(ipv6_), address_ipv6_(address)  {

      }
      address(const address_mstp& address)  : type_(mstp_), address_mstp_(address)  {

      }
      address(const address& other) : type_(other.type_),
                                      address_ip_(other.address_ip_),
                                      address_ipv6_(other.address_ipv6_),
                                      address_mstp_(other.address_mstp_)  {

      }
      address(address&& other)  : type_(other.type_),
                                  address_ip_(other.address_ip_),
                                  address_ipv6_(other.address_ipv6_),
                                  address_mstp_(other.address_mstp_)  {
      }

      address& operator=(address&& other) {
        type_ = other.type_;
        address_ip_ = other.address_ip_;
        address_ipv6_ = other.address_ipv6_;
        address_mstp_ = other.address_mstp_;
        return *this;
      }
      address& operator=(const address& other) {
        type_ = other.type_;
        address_ip_ = other.address_ip_;
        address_ipv6_ = other.address_ipv6_;
        address_mstp_ = other.address_mstp_;
        return *this;
      }


        inline std::string to_string() {
         switch(type_) {
           case ip_:
             return address_ip_.to_string();
           default:
             return "dick butt";
         }
        }


    private:
      enum { ip_, ipv6_,  mstp_ } type_;

      address_ip address_ip_;
      address_ipv6 address_ipv6_;
      address_mstp address_mstp_;

    };

    class endpoint {
    public:
      endpoint() : network_(1), address_(address_ip{})  {

      }
      endpoint(const bacnet::common::protocol::mac::address_ip& address) : network_(1), address_(address)  {
      }
      endpoint(const bacnet::common::protocol::mac::address_ipv6& address)  : network_(1), address_(address)  {
      }
      endpoint(const bacnet::common::protocol::mac::address_mstp& address)  : network_(1), address_(address)  {
      }

      endpoint(uint16_t network, const bacnet::common::protocol::mac::address_ip& address) : network_(network), address_(address)  {
      }
      endpoint(uint16_t network, const bacnet::common::protocol::mac::address_ipv6& address)  : network_(network), address_(address)  {
      }
      endpoint(uint16_t network, const bacnet::common::protocol::mac::address_mstp& address)  : network_(network), address_(address)  {
      }

      endpoint(const endpoint& other) : network_(other.network_),
                                        address_(other.address_)   {

      }
      endpoint(endpoint&& other)  : network_(other.network_),
                                    address_(other.address_)   {
      }

      endpoint& operator=(endpoint&& other) {
        network_ = other.network_;
        address_ = other.address_;
        return *this;
      }
      endpoint& operator=(const endpoint& other) {
        network_ = other.network_;
        address_ = other.address_;
        return *this;
      }

      inline void network(uint16_t net) { network_ = net;}
      inline void address(const bacnet::common::protocol::mac::address &adr) { address_ = adr;}

      inline uint16_t network() const { return network_;}
      inline bacnet::common::protocol::mac::address address() const { return address_;}

    private:
      uint16_t network_;
      bacnet::common::protocol::mac::address address_;
    };


}}}}


#endif //NINJA_WOOKIE_BACNET_MAC_ENDPOINT_HPP
