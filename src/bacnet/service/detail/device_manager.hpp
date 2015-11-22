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


#ifndef NINJA_WOOKIE_BACNET_SERVICE_DETAIL_DEVICE_MANAGER_HPP
#define NINJA_WOOKIE_DEVICE_MANAGER_HPP

#include <chrono>
#include <bacnet/common/protocol/mac/address.hpp>
#include <bacnet/common/object_identifier.hpp>
#include <bacnet/common/segment.hpp>

namespace bacnet { namespace service { namespace detail {


/**
 * todo
 * improve with a random access underlying container. e.g. std::map
 * find solution for multiple doi on network
 *
 */
class device_manager {
public:

  inline void insert_device(const bacnet::common::protocol::mac::endpoint& endpoint,
                            const bacnet::common::object_identifier& object_identifier,
                            const uint32_t& max_apdu_size,
                            const bacnet::common::segmentation& max_segmentaions,
                            const uint16_t& vendor_id) {

    if(has_device(endpoint, object_identifier)) {
      update(endpoint, object_identifier, max_apdu_size, max_segmentaions, vendor_id);
    }
    else {
      devices.push_back({endpoint, object_identifier, max_apdu_size, max_segmentaions, vendor_id, std::chrono::steady_clock::now()});
    }
  }

  bacnet::common::protocol::mac::endpoint get_endpoint( const bacnet::common::object_identifier& object_identifier) {
    bacnet::common::protocol::mac::endpoint endpoint;
    uint32_t  matches{0};
    for(auto& device: devices) {
      if(device.device_object_identifier == object_identifier) {
        endpoint = device.endpoint;
        matches++;
      }
    }
    if(matches > 1) {
      std::cerr << "device_manager: " << "more then one endpoint with that doi";
    }
    return endpoint;
  }
  void print_device_list() {
    auto formatter_device = boost::format("| %1$+9d | %2$+21d | %3$+6d | %4$_6d | %5$_6d | %6$_8s | %7%\n");

    auto &os = std::cout;

    os << "device_manager: device_list" << std::endl;
    for(auto& device: devices) {

      os << formatter_device % device.device_object_identifier.instance_number()
                   % device.endpoint.address().to_string()
                   % device.endpoint.network()
                   % device.vendor_id
                   % device.max_apdu_size
                   % device.max_segemnations
                   % " ";
    }
    os << std::endl;
  }


private:
  struct device {
    bacnet::common::protocol::mac::endpoint endpoint;
    bacnet::common::object_identifier device_object_identifier;
    uint32_t max_apdu_size;
    bacnet::common::segmentation max_segemnations;
    uint16_t vendor_id;
    std::chrono::steady_clock::time_point last_update;
  };

  bool has_device(const bacnet::common::protocol::mac::endpoint& endpoint,
                  const bacnet::common::object_identifier& object_identifier) {
    for(auto &device : devices) {
      if(device.endpoint == endpoint && device.device_object_identifier == object_identifier) {
        return true;
      }
    }
    return false;
  }

  bool update(const bacnet::common::protocol::mac::endpoint& endpoint,
              const bacnet::common::object_identifier& object_identifier,
              const uint32_t& max_apdu_size,
              const bacnet::common::segmentation& max_segemnations,
              const uint16_t& vendor_id) {
    for(auto &device : devices) {
      if(device.endpoint == endpoint && device.device_object_identifier == object_identifier) {
        device.max_apdu_size = max_apdu_size;
        device.max_segemnations = max_segemnations;
        device.vendor_id = vendor_id;
        device.last_update =  std::chrono::steady_clock::now();
      }
    }
    return false;
  }

  std::list<device> devices;

};


}}}


#endif //NINJA_WOOKIE_DEVICE_MANAGER_HPP
