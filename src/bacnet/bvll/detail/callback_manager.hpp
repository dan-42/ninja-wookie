//
// Created by schoko on 6/16/15.
//

#ifndef NINJA_WOOKIE_BVLL_CALLBACK_MANAGER_HPP
#define NINJA_WOOKIE_BVLL_CALLBACK_MANAGER_HPP

#include <bacnet/bvll/api.hpp>

namespace bacnet { namespace  bvll { namespace detail {

using namespace bacnet::bvll;

struct callback_manager {

  async_receive_broadcast_callback_t async_receive_broadcast_callback_;
  async_receive_unicast_callback_t async_receive_unicast_callback_;
};

}}}


#endif //NINJA_WOOKIE_BVLL_CALLBACK_MANAGER_HPP
