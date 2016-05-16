/**
 * ninja-wooki, is a BACnet stack C++ library
 *
 * Copyright (C) 2015 Daniel Friedrich
 *
 * This file is part of ninja-wooki.
 *
 * ninja-wooki is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * ninja-wooki is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with Mupen64PlusAE. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Daniel Friedrich
 */


#ifndef SRC_BACNET_SERVICE_DETAIL_SEGMENTATION_MANAGER_HPP_
#define SRC_BACNET_SERVICE_DETAIL_SEGMENTATION_MANAGER_HPP_

#include <chrono>
#include <boost/format.hpp>
#include <bacnet/apdu/frame/confirmed_request.hpp>
#include <bacnet/common/protocol/meta_information.hpp>
#include <bacnet/common/segment.hpp>

namespace bacnet { namespace service { namespace detail {

using bacnet::common::protocol::meta_information;
using bacnet::apdu::frame::confirmed_request;

class segmentation_manager {
public:

  /**
   * insert segmented request, builds up to whole segment,
   * if last segment is added, return true as indication
   */
  inline bool insert(confirmed_request request,meta_information mi) {


    return false;
  }

  std::vector<bacnet::common::protocol::mac::endpoint> get_endpoint( const bacnet::type::object_identifier& object_identifier) {
    //print_device_list();
    std::vector<bacnet::common::protocol::mac::endpoint> endpoints;
    for(auto& device: devices) {
      std::cout << "get_endpoint " << device.first << std::endl;
      if(device.first == object_identifier) {
        endpoints.push_back(device.second.endpoint);
      }
    }
    return endpoints;
  }
  void print_device_list() {

    auto &os = std::cout;

    os << std::endl;
  }


private:
  struct device {
    bacnet::common::protocol::mac::endpoint endpoint;
    bacnet::type::object_identifier device_object_identifier;
    uint32_t max_apdu_size;
    bacnet::common::segmentation max_segemnations;
    uint16_t vendor_id;
    std::chrono::steady_clock::time_point last_update;
  };


  bool has_device( const bacnet::common::protocol::mac::endpoint& endpoint) {
    for( auto &device : devices) {
      if(device.second.endpoint == endpoint) {
        return true;
      }
    }
    return false;
  }

  bool has_device(const bacnet::type::object_identifier& object_identifier) {
    if(devices.count(object_identifier) > 0) {
      return true;
    }
    return false;
  }

  bool update(const bacnet::common::protocol::mac::endpoint& endpoint,
              const bacnet::type::object_identifier& object_identifier,
              const uint32_t& max_apdu_size,
              const bacnet::common::segmentation& max_segemnations,
              const uint16_t& vendor_id) {
    for(auto &device : devices) {
      if(device.second.endpoint == endpoint && device.second.device_object_identifier == object_identifier) {
        device.second.max_apdu_size = max_apdu_size;
        device.second.max_segemnations = max_segemnations;
        device.second.vendor_id = vendor_id;
        device.second.last_update =  std::chrono::steady_clock::now();
      }
    }
    return false;
  }

 // std::list<device> devices;
    std::multimap<bacnet::type::object_identifier, device> devices;

};


}}}


#endif //SRC_BACNET_SERVICE_DETAIL_SEGMENTATION_MANAGER_HPP_
