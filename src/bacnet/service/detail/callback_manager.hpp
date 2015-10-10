//
// Created by dan on 10.10.15.
//

#ifndef NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/api.hpp>

namespace bacnet { namespace service { namespace detail {

      using namespace bacnet::service;
      struct callback_manager {

        void set_service_callback(const callback_service_who_is_t &service_callback) {
          callback_service_who_is_ = service_callback;
        }

        void set_service_callback(const callback_service_i_am_t &service_callback) {
          callback_service_i_am_ = service_callback;
        }

        callback_service_who_is_t callback_service_who_is_;
        callback_service_i_am_t callback_service_i_am_;
      };
    }}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP
