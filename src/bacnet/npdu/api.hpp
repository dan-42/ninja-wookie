//
// Created by schoko on 6/16/15.
//

#ifndef NINJA_WOOKIE_NPDU_API_HPP
#define NINJA_WOOKIE_NPDU_API_HPP

#include <boost/function.hpp>


namespace bacnet { namespace npdu {

typedef  boost::function<void (const bacnet::binary_data&)> async_receive_broadcast_callback_t;
typedef  boost::function<void (const bacnet::binary_data&)> async_receive_unicast_callback_t;

typedef  boost::function<void (const bacnet::binary_data&)> async_received_apdu_callback_t;

}}

#endif //NINJA_WOOKIE_NPDU_API_HPP
