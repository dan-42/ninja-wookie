//
// Created by dan on 10.10.15.
//

#ifndef NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP

#include <stdexcept>

#include <util/callback_manager.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/api.hpp>


namespace bacnet { namespace service { namespace detail {

typedef boost::fusion::map<
    boost::fusion::pair<service::who_is,                      callback_service_who_is_t>,
    boost::fusion::pair<service::i_am,                        callback_service_i_am_t  >,
    boost::fusion::pair<service::reinitialize_device,         callback_service_reinitialize_device_t >,
    boost::fusion::pair<service::read_property_request,       callback_service_read_property_t >,
    boost::fusion::pair<service::read_property_ack,           callback_service_ack_property_t >
> callback_map_type;

      using namespace bacnet::service;
      using namespace bacnet::service::service;
      struct callback_manager {

        template<typename... Callbacks>
        void set_service_callbacks(Callbacks... callbacks) {
          callback_manager_.set_callbacks(callbacks...);
        }

        template<typename Service>
        void invoke(const Service &service, const bacnet::error &ec, const bacnet::common::protocol::meta_information &mi) {
          callback_manager_.invoke_callback(service, ec, mi);
        }


        void add_who_is_service_callback(callback_service_who_is_t callback) {
          callbacks_service_who_is.push_back(std::move(callback));
        }

        std::size_t set_i_am_service_callback(callback_service_i_am_t callback) {
          callbacks_service_i_am_idx_last++;
          callbacks_service_i_am[callbacks_service_i_am_idx_last] = callback;
          return callbacks_service_i_am_idx_last;
        }

        void clear_i_am_service_callback(std::size_t idx) {
          if(idx <= callbacks_service_i_am_idx_last) {
            callbacks_service_i_am.erase(idx);
            callbacks_service_i_am_idx_last--;
          }
         }

      private:
          util::callback::callback_manager<callback_map_type>  callback_manager_;
          std::map<std::size_t, callback_service_i_am_t> callbacks_service_i_am;
          std::list<callback_service_who_is_t> callbacks_service_who_is;
          std::size_t  callbacks_service_i_am_idx_last;
      };




      template<>
      void callback_manager::invoke<service::i_am>(const service::i_am &service, const bacnet::error &ec, const bacnet::common::protocol::meta_information &mi) {
        for(auto &callback :  callbacks_service_i_am) {
          if(callback.second) {
            callback.second(service, ec, mi );
          }
        }
        callback_manager_.invoke_callback(service, ec, mi);
      }

      template<>
      void callback_manager::invoke<service::who_is>(const service::who_is &service, const bacnet::error &ec, const bacnet::common::protocol::meta_information &mi) {
        for(auto &callback :  callbacks_service_who_is) {
          if(callback) {
            callback(service, ec, mi );
          }
        }
        callback_manager_.invoke_callback(service, ec, mi);
      }
    }}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP
