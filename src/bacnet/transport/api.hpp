//
// Created by dan on 07.12.15.
//

#ifndef NINJA_WOOKIE_BACNET_TRANSPORT_API_HPP
#define NINJA_WOOKIE_BACNET_TRANSPORT_API_HPP



#include <functional>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/common/protocol/mac/address.hpp>
#include <bacnet/error/error.hpp>


/**
 * a transport layer must implement the following stups
  struct transport {
    void register_receive_callback(const async_receive_callback &callback);
    template<typename CompletionHandler>
    void async_send(bacnet::binary_data data, bacnet::common::protocol::mac::address receiver, const CompletionHandler &handler);
    void start() ;
  }
 *
 */
namespace bacnet { namespace transport {

    typedef std::function<void(bacnet::error&&, bacnet::common::protocol::mac::address&&, bacnet::binary_data&&)> receive_callback;

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
