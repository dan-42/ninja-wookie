//
// Created by schoko on 6/16/15.
//

#ifndef NINJA_WOOKIE_BVLL_CALLBACK_MANAGER_HPP
#define NINJA_WOOKIE_BVLL_CALLBACK_MANAGER_HPP

#include <bacnet/bvll/api.hpp>

namespace bacnet { namespace  bvll { namespace detail {


struct callback_manager {

  bacnet::bvll::async_receive_broadcast_callback_t async_receive_broadcast_callback_;
  bacnet::bvll::async_receive_unicast_callback_t async_receive_unicast_callback_;
};

}}}


#endif //NINJA_WOOKIE_BVLL_CALLBACK_MANAGER_HPP
