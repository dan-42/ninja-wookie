//
// Created by schoko on 6/16/15.
//

#ifndef NINJA_WOOKIE_NPDU_CALLBACK_MANAGER_HPP
#define NINJA_WOOKIE_NPDU_CALLBACK_MANAGER_HPP

#include <bacnet/npdu/api.hpp>

namespace bacnet { namespace  npdu { namespace detail {

using namespace bacnet::npdu;

struct callback_manager {

  async_receive_broadcast_callback_t async_receive_broadcast_callback_;
  async_receive_unicast_callback_t async_receive_unicast_callback_;

  async_received_apdu_callback_t async_received_apdu_callback_;
};

}}}


#endif //NINJA_WOOKIE_NPDU_CALLBACK_MANAGER_HPP
