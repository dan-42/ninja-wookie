/**
 * ninja-wooki, is a BACnet stack C++ library
 *
 * Copyright (C) 2015 Daniel Friedrich
 *
 * This file is part of ninja-wooki.
 *
 * ninja-wooki is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * ninja-wooki is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with Mupen64PlusAE. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Daniel Friedrich
 */

#ifndef SRC_BACNET_NPDU_ADDRESS_HPP_
#define SRC_BACNET_NPDU_ADDRESS_HPP_


#include <iostream>
#include <string>
#include <cstdint>
#include <limits>

#include <boost/lexical_cast.hpp>
#include <boost/fusion/include/define_struct.hpp>

#include <bacnet/detail/common/types.hpp>
#include <boost/asio/ip/address.hpp>



/*
 * good idea but the address is decoded a a 6 byte  value, adn asio::address has only 4 or 16, and no port and so on
 * us it as idea but implement is your own way?
 *
 */

/*
namespace bacnet {

typedef boost::asio::ip::address_v4 address_ip_v4;
typedef boost::asio::ip::address_v6 address_ip_v6;
typedef uint8_t address_mstp;





struct address {

private:
  uint16_t network_number_;
  enum { ipv4, ipv6, mstp } type_;
  boost::asio::ip::address address_ip_;
  uint8_t address_mstp_;


public:

    inline address();
    inline address(const address_ip_v4& ipv4_address);
    inline address(const address_ip_v6& ipv6_address);
    inline address(const address_mstp& ipv6_address);

    inline address& operator=(const address_ip_v4& ipv4_address);
    inline address& operator=(const address_ip_v6& ipv6_address);
    inline address& operator=(const address_mstp& ipv6_address);


    bool is_ip_v4() const  {
      return type_ == ipv4;
    }

    bool is_ip_v6() const {
      return type_ == ipv6;
    }

    bool is_ip_mstp() const {
      return type_ == mstp;
    }


    inline address(const address& other);
    inline address(address&& other);
    inline address& operator=(const address& other);
    inline address& operator=(address&& other);

    inline std::string to_string() const;

    inline static address from_string(const char* str);
    inline static address from_string(const char* str, bacnet::error_code& ec);
    inline static address from_string(const std::string& str);

    inline bool is_multicast() const;

    inline friend bool operator==(const address& a1, const address& a2);
    inline friend bool operator<(const address& a1, const address& a2);



    friend bool operator!=(const address& a1, const address& a2) {
      return !(a1 == a2);
    }

    friend bool operator>(const address& a1, const address& a2)   {
      return a2 < a1;
    }


    friend bool operator<=(const address& a1, const address& a2)  {
      return !(a2 < a1);
    }


    friend bool operator>=(const address& a1, const address& a2)    {
      return !(a1 < a2);
    }


};

}



namespace bacnet {

address::address()
  :   network_number_(1),
      type_(ipv4),
      address_ip_(),
      address_mstp_(0)
{
}

address::address(const boost::asio::ip::address_v4& ipv4_address)
  : network_number_(1),
    type_(ipv4),
    address_ip_(ipv4_address),
    address_mstp_(0)
{
}

address::address(const boost::asio::ip::address_v6& ipv6_address)
  : network_number_(1),
    type_(ipv6),
    address_ip_(ipv6_address),
    address_mstp_(0)
{
}

address::address(const address& other)
  : network_number_(other.network_number_),
    type_(other.type_),
    address_ip_(other.address_ip_),
    address_mstp_(other.address_mstp_)
{
}


address::address(address&& other)
  : network_number_(other.network_number_),
    type_(other.type_),
    address_ip_(other.address_ip_),
    address_mstp_(other.address_mstp_)
{
}


address& address::operator=(const address& other) {
  network_number_(other.network_number_);
  type_ = other.type_;
  address_ip_ = other.address_ip_;
  address_mstp_ = other.address_mstp_;
  return *this;
}


address& address::operator=(address&& other) {
  network_number_(other.network_number_);
  type_ = other.type_;
  address_ip_ = other.address_ip_;
  address_mstp_ = other.address_mstp_;
  return *this;
}


address& address::operator=(const boost::asio::ip::address_v4& ipv4_address) {
  type_ = ipv4;
  address_ip_ = ipv4_address;
  return *this;
}

address& address::operator=(const boost::asio::ip::address_v6& ipv6_address) {
  type_ = ipv6;
  address_ip_ = ipv6_address;
  return *this;
}



std::string address::to_string() const {
  if (type_ == ipv6 || type_ == ipv4)
    return address_ip_.to_string();

  return std::to_string((int)address_mstp_);
}

address address::from_string(const char* str) {
  bacnet::error_code ec;
  address addr = from_string(str, ec);
  boost::asio::detail::throw_error(ec);
  return addr;
}

address address::from_string(const char* str, bacnet::error_code& ec) {
  boost::asio::ip::address ip_address =  boost::asio::ip::address::from_string(str, ec);
  if (!ec)
  {
    address tmp;
    tmp.type_ = ip_address.is_v4() ? ipv4 : ipv6;
    tmp.address_ip_ = ip_address;
    return tmp;
  }

  try {
    int value = boost::lexical_cast<int>(str);
    if(value >= std::numeric_limits<uint8_t>::min() || value <= std::numeric_limits<uint8_t>::max())    {
      address tmp;
      tmp.type_ = mstp;
      tmp.address_mstp_ = (uint8_t)value;
      return tmp;
    }
  }
  catch (boost::bad_lexical_cast& e) {
    return address();
  }
  return address();
}

address address::from_string(const std::string& str) {
  return from_string(str.c_str());
}


bool address::is_multicast() const {
  return (type_ == ipv4 || type_ == ipv6)
    ? address_ip_.is_multicast()
    : address_mstp_ == 255;
}

bool operator==(const address& a1, const address& a2) {
  if (a1.type_ != a2.type_)
    return false;
  if (a1.type_ == address::ipv6 || a1.type_ == address::ipv4)
    return a1.address_ip_ == a2.address_ip_;

  return a1.address_mstp_ == a2.address_mstp_;
}

bool operator<(const address& a1, const address& a2) {
  if (a1.type_ < a2.type_)
    return true;
  if (a1.type_ > a2.type_)
    return false;

  if (a1.type_ == address::ipv6 || a1.type_ == address::ipv4  )
    return a1.address_ip_ < a2.address_ip_;

  return a1.address_mstp_ < a2.address_mstp_;
}

} // namespace bacnet







*/







BOOST_FUSION_DEFINE_STRUCT(
    (bacnet)(npdu), address,
    (uint16_t, network_number)
    (bacnet::binary_data, binary_address)
)

std::ostream &operator<<(std::ostream &os, const bacnet::npdu::address &a);

#endif /* SRC_BACNET_NPDU_ADDRESS_HPP_ */
