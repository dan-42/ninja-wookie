//
// Created by schoko on 6/16/15.
//

#ifndef NINJA_WOOKIE_BVLL_API_HPP
#define NINJA_WOOKIE_BVLL_API_HPP

#include <boost/function.hpp>
#include <boost/asio/ip/udp.hpp>

namespace bacnet { namespace bvll {

typedef  boost::function<void (const bacnet::binary_data&, const boost::asio::ip::udp::endpoint& )> async_receive_broadcast_callback_t;
typedef  boost::function<void (const bacnet::binary_data&, const boost::asio::ip::udp::endpoint& )> async_receive_unicast_callback_t;

}}

#endif //NINJA_WOOKIE_BVLL_API_HPP
