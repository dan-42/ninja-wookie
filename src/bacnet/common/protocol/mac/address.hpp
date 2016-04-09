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

      static address_ip from_native(const boost::asio::ip::udp::endpoint &ep)  {
        return address_ip{ep.address().to_v4(), ep.port() };
      }

      static address_ip broadcast(uint16_t port = default_port)  {
        return address_ip(boost::asio::ip::address_v4::broadcast(), port );
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

      friend inline bool operator==(const address_ip& a1, const address_ip& a2) {
        if(a1.address_ == a2.address_ && a1.port_ == a2.port_) {
          return true;
        }
        return false;
      }

      friend bool operator!=(const address_ip& a1, const address_ip& a2) {
        return !(a1 == a2);
      }

      friend inline bool operator<(const address_ip& a1, const address_ip& a2) {
        if(a1.address_ < a2.address_ && a1.port_ < a2.port_) {
          return true;
        }
        return false;
      }

      inline std::string to_string() {
        return (address_.to_string() + ":" + std::to_string(port_));
      }


      inline boost::asio::ip::udp::endpoint to_system_endpoint() const {

        return boost::asio::ip::udp::endpoint{address_, port_};
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
      address_ip ip() const {
        return address_ip_;
      }
      address_ipv6 ipv6() const {
        return address_ipv6_;
      }
      address_mstp mstp() const {
        return address_mstp_;
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

      friend bool operator==(const address& a1, const address& a2) {
        if ( a1.type_ != a2.type_) {
          return false;
        }
        switch (a1.type_) {
          case ip_:
            return a1.address_ip_ == a2.address_ip_;
          case ipv6_:
            return a1.address_ipv6_ == a2.address_ipv6_;
          case mstp_:
            /*to do*/
            return false;
        }
        return false;
      }

      friend bool operator!=(const address& a1, const address& a2) {
        return !(a1 == a2);
      }


      friend bool operator<(const address& a1, const address& a2) {
         if ( a1.type_ >= a2.type_) {
           return false;
         }
         switch (a1.type_) {
           case ip_:
             return a1.address_ip_ < a2.address_ip_;
           case ipv6_:
             return a1.address_ipv6_ < a2.address_ipv6_;
           case mstp_:
             /*to do*/
             return false;
         }
         return false;
       }

      inline std::string to_string() {
       switch(type_) {
         case ip_:
           return address_ip_.to_string();
         default:
           return "dick butt";
       }
      }

      inline bool is_ip() const {
        return type_ == ip_;
      }

      inline bool is_ipv6() const {
        return type_ == ipv6_;
      }

      inline bool is_mstp() const {
        return type_ == mstp_;
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
      endpoint(const bacnet::common::protocol::mac::address& address)    : network_(1), address_(address)  {
      }
      endpoint(const bacnet::common::protocol::mac::address_ip& address) : network_(1), address_(address)  {
      }
      endpoint(const bacnet::common::protocol::mac::address_ipv6& address)  : network_(1), address_(address)  {
      }
      endpoint(const bacnet::common::protocol::mac::address_mstp& address)  : network_(1), address_(address)  {
      }

      endpoint(uint16_t network, const bacnet::common::protocol::mac::address& address) : network_(network), address_(address)  {
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

      friend bool operator==(const endpoint& a1, const endpoint& a2) {
        if(a1.network_ == a2.network_ && a1.address_ == a2.address_) {
          return true;
        }
        return false;
      }

      friend bool operator!=(const endpoint& a1, const endpoint& a2) {
        return !(a1 == a2);
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
