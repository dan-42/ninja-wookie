//
// Created by dan on 10.10.15.
//

#ifndef NINJA_WOOKIE_SERVICE_API_HPP
#define NINJA_WOOKIE_SERVICE_API_HPP


#include <functional>
#include <bacnet/service/service.hpp>
#include <bacnet/common/protocol/meta_information.hpp>
#include <bacnet/error/error.hpp>

namespace bacnet { namespace service {
  typedef std::function<void(bacnet::service::who_is,                   bacnet::error, bacnet::common::protocol::meta_information)>   callback_service_who_is_t;
  typedef std::function<void(bacnet::service::i_am,                     bacnet::error, bacnet::common::protocol::meta_information)>   callback_service_i_am_t;
  typedef std::function<void(bacnet::service::reinitialize_device,      bacnet::error, bacnet::common::protocol::meta_information)>   callback_service_reinitialize_device_t;
  typedef std::function<void(bacnet::service::read_property_request,    bacnet::error, bacnet::common::protocol::meta_information)>   callback_service_read_property_t;
  typedef std::function<void(bacnet::service::read_property_ack,        bacnet::error, bacnet::common::protocol::meta_information)>   callback_service_ack_property_t;


}}

#endif //NINJA_WOOKIE_SERVICE_API_HPP
