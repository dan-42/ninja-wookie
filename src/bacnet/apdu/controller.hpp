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

#ifndef NINJA_WOOKIE_APDU_CONTROLLER_HPP
#define NINJA_WOOKIE_APDU_CONTROLLER_HPP

#include <boost/asio.hpp>
#include <boost/variant.hpp>
#include <bacnet/apdu/service/services.hpp>



namespace bacnet { namespace  apdu { namespace detail { namespace pdu_type {

/*
 * the pdu_type is a 4bit value
 * and is encoded in the hi_nibble
 * of the first byte in the apdu-header
 */

constexpr uint8_t  confirmed_request          = 0x00;
constexpr uint8_t  unconfirmed_request        = 0x01;
constexpr uint8_t  simple_ack                 = 0x02;
constexpr uint8_t  complex_ack                = 0x03;
constexpr uint8_t  segment_ack                = 0x04;
constexpr uint8_t  error                      = 0x05;
constexpr uint8_t  reject                     = 0x06;
constexpr uint8_t  abort                      = 0x07;

static std::ostream &operator<<(std::ostream &os, const uint8_t &pdu_type){

  switch (pdu_type) {
    case pdu_type::confirmed_request :
      os << "confirmed_request(0x00)";
      break;
    case pdu_type::unconfirmed_request :
      os << "unconfirmed_request(0x01)";
      break;
    case pdu_type::simple_ack :
      os << "simple_ack(0x02)";
      break;
    case pdu_type::complex_ack :
      os << "complex_ack(0x03)";
      break;
    case pdu_type::segment_ack :
      os << "segment_ack(0x04)";
      break;
    case pdu_type::error :
      os << "error(0x05)";
      break;
    case pdu_type::reject :
      os << "reject(0x06)";
      break;
    case pdu_type::abort :
      os << "abort(0x07)";
      break;
    default:
      os  << "unknown pdu_type  (0x" << std::hex
          << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(pdu_type)
          << ")";
  }
  return os;
}

}}}}




namespace bacnet { namespace  apdu { namespace detail { namespace  header {

struct alignas(1) confirmed_request {
  uint8_t pdu_type_                        : 4;
  uint8_t is_segmented_                    : 1;
  uint8_t has_more_segments_following_     : 1;
  uint8_t is_segmented_response_accepted_  : 1;
  uint8_t unused_                          : 1;

  confirmed_request() : pdu_type_(0),
                        is_segmented_(0),
                        has_more_segments_following_(0),
                        is_segmented_response_accepted_(0),
                        unused_(0) {
  }

  uint8_t pdu_type(){
    return pdu_type_;
  }
  bool is_segmented(){
    return is_segmented_==true;
  }
  bool has_more_segments_following(){
    return has_more_segments_following_==true;
  }
  bool is_segmented_response_accepted(){
    return is_segmented_response_accepted_==true;
  }
};

struct alignas(1) unconfirmed_request {
  uint8_t pdu_type_                        : 4;
  uint8_t unused_                          : 4;

  unconfirmed_request() : pdu_type_(0),
                          unused_(0) {
  }

  uint8_t pdu_type(){
    return pdu_type_;
  }
};

struct alignas(1) simple_ack {
  uint8_t pdu_type_                        : 4;
  uint8_t unused_                          : 4;

  simple_ack() : pdu_type_(0),
                 unused_(0) {
  }

  uint8_t pdu_type(){
    return pdu_type_;
  }
};


struct alignas(1) complex_ack {
  uint8_t pdu_type_                        : 4;
  uint8_t is_segmented_                    : 1;
  uint8_t has_more_segments_following_     : 1;
  uint8_t unused_                          : 2;

  complex_ack() : pdu_type_(0),
                        is_segmented_(0),
                        has_more_segments_following_(0),
                        unused_(0) {
  }

  uint8_t pdu_type(){
    return pdu_type_;
  }
  bool is_segmented(){
    return is_segmented_==true;
  }
  bool has_more_segments_following(){
    return has_more_segments_following_==true;
  }
};

struct alignas(1) segment_ack {
  uint8_t pdu_type_                        : 4;
  uint8_t unused_                          : 2;
  uint8_t is_normal_ack_                   : 1;
  uint8_t is_send_by_server_               : 1;

  segment_ack() : pdu_type_(0),
                  unused_(0),
                  is_normal_ack_(0),
                  is_send_by_server_(0) {
  }

  uint8_t pdu_type(){
    return pdu_type_;
  }
  bool is_normal_ack(){
    return is_normal_ack_==true;
  }
  bool is_send_by_server(){
    return is_send_by_server_==true;
  }
};


struct alignas(1) error {
  uint8_t pdu_type_                        : 4;
  uint8_t unused_                          : 4;

  error() : pdu_type_(0),
            unused_(0)  {
  }

  uint8_t pdu_type(){
    return pdu_type_;
  }
};

struct alignas(1) reject {
  uint8_t pdu_type_                        : 4;
  uint8_t unused_                          : 4;

  reject() : pdu_type_(0),
             unused_(0)  {
  }

  uint8_t pdu_type(){
    return pdu_type_;
  }
};

struct alignas(1) abort {
  uint8_t pdu_type_                        : 4;
  uint8_t unused_                          : 3;
  uint8_t is_send_by_server_               : 1;

  abort() : pdu_type_(0),
            unused_(0),
            is_send_by_server_(0){
  }

  uint8_t pdu_type(){
    return pdu_type_;
  }

  bool is_send_by_server(){
    return is_send_by_server_==true;
  }

};

}}}}






















void handler(const boost::system::error_code& error_code, const std::size_t &bytes_transfered){
  std::cout << "handler " <<  error_code.message() << std::endl;
}



namespace bacnet { namespace apdu {

template<class UnderlyingLayerController>
struct controller {

  controller(boost::asio::io_service &io_service, UnderlyingLayerController &underlying_controller) :
      io_service_(io_service), underlying_controller_(underlying_controller) {

  }

  void service(const service::possible_service& service_) {

    service::generate_frame gf;
    auto data = service_.apply_visitor(gf);
    underlying_controller_.async_send_broadcast(data, &handler);
  }

private:
  boost::asio::io_service &io_service_;
  UnderlyingLayerController underlying_controller_;
};

}}

#endif //NINJA_WOOKIE_APDU_CONTROLLER_HPP
