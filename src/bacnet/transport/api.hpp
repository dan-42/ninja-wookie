//
// Created by dan on 07.12.15.
//

#ifndef NINJA_WOOKIE_BACNET_TRANSPORT_API_HPP
#define NINJA_WOOKIE_BACNET_TRANSPORT_API_HPP


#include <boost/system/error_code.hpp>
#include <functional>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/common/protocol/mac/address.hpp>

namespace bacnet { namespace transport {

    typedef std::function<void(boost::system::error_code, bacnet::common::protocol::mac::address, bacnet::binary_data)> async_receive_callback;



    namespace config {
      static const constexpr char*  DEFAULT_LISTENING_ADDRESS{"0.0.0.0"};
      static const constexpr uint16_t DEFAULT_LISTENING_PORT{0xBAC0};
    }

    struct configuration {

      configuration() : listening_address(config::DEFAULT_LISTENING_ADDRESS),
                        listening_port(config::DEFAULT_LISTENING_PORT)  {
      }

      configuration(const std::string& l_addr, const uint16_t& l_port) : listening_address(l_addr),
                                                                                                    listening_port(l_port) {
      }

      std::string listening_address;
      uint16_t listening_port;
    };



}}

#endif //NINJA_WOOKIE_BACNET_TRANSPORT_API_HPP
