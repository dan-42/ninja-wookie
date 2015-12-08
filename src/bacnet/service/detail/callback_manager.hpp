//
// Created by dan on 10.10.15.
//

#ifndef NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP

#include <stdexcept>
#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/api.hpp>

namespace bacnet { namespace service { namespace detail {



      using namespace bacnet::service;
      using namespace bacnet::service::service;
      struct callback_manager {

        void set_service_callback(callback_service_who_is_t service_callback) {
          callbacks_service_who_is_.push_back(std::move(service_callback));
        }

        void set_service_callback(callback_service_i_am_t service_callback) {
          callback_service_i_am_ = std::move(service_callback);
        }


        void invoke(const boost::system::error_code &ec, const bacnet::common::protocol::meta_information &mi, const bacnet::service::who_is &service) {
          for(auto &callback_service_who_is_ : callbacks_service_who_is_) {
            if(!callback_service_who_is_.empty()) {
              callback_service_who_is_(ec, mi, service);
            }
          }
        }

        callback_service_i_am_t callback_service_i_am_;

      private:
        std::list<callback_service_who_is_t> callbacks_service_who_is_;
      };
    }}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP
