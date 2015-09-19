//
// Created by dan on 9/19/15.
//

#ifndef NINJA_WOOKIE_BACNET_APDU_CALLBACK_MANAGER_HPP
#define NINJA_WOOKIE_BACNET_APDU_CALLBACK_MANAGER_HPP



#include <bacnet/apdu/api.hpp>

namespace bacnet { namespace  apdu { namespace detail {

      using namespace bacnet::apdu;

      struct callback_manager {

        async_received_service_callback_t async_received_service_callback_;
      };

    }}}


#endif //NINJA_WOOKIE_BACNET_APDU_CALLBACK_MANAGER_HPP
