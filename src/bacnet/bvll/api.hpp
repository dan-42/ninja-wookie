//
// Created by schoko on 6/16/15.
//

#ifndef NINJA_WOOKIE_BVLL_API_HPP
#define NINJA_WOOKIE_BVLL_API_HPP

#include <boost/function.hpp>
#include <boost/asio/ip/udp.hpp>

#include <bacnet/common/protocol/meta_information.hpp>
namespace bacnet { namespace bvll {

typedef  boost::function<void (bacnet::binary_data&&,  bacnet::common::protocol::meta_information&& )> async_receive_broadcast_callback_t;
typedef  boost::function<void ( bacnet::binary_data&&, bacnet::common::protocol::meta_information&& )> async_receive_unicast_callback_t;

}}

#endif //NINJA_WOOKIE_BVLL_API_HPP
