/*
 * request_manager.hpp
 *
 *  Created on: Apr 8, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_APDU_DETAIL_REQUEST_MANAGER_HPP_
#define SRC_BACNET_APDU_DETAIL_REQUEST_MANAGER_HPP_

#include <chrono>
#include <list>
#include <cstdint>

#include <bacnet/apdu/api.hpp>

namespace bacnet { namespace apdu { namespace detail {

/**
 *
    key is   endpoint + invoke id
    idea: for each endpoint one transmissionmanager?

 *
 */

  struct transmission_identifier {

    transmission_identifier() = default;
    transmission_identifier(uint8_t id, std::chrono::steady_clock::time_point time_point) :
                                              invoke_id(std::move(id)),
                                              time_point_invoked(std::move(time_point)) {

    }

    uint8_t invoke_id{0};
    std::chrono::steady_clock::time_point time_point_invoked;
    confirmed_request_handler_type handler;
  };

  typedef std::list<transmission_identifier> transmission_list_type;

  /**
   * for each client the stack requests to, this object is created and stored  e.g. a map.
   * so for each new request to a client, we can generate a new invoke_id, including timepoint
   */
  struct device_request_manager {

    uint8_t get_next_invoke_id() {
      invoke_id_counter++;
      transmissions.emplace_back(invoke_id_counter, std::chrono::steady_clock::now());
      return invoke_id_counter;
    }

    void store_handler(uint8_t id, confirmed_request_handler_type handler) {
      /*
       * we start from the end, as we expect that after the invoke id was created,
       * the frame was send and we can store the handler.
       * so best case the last element is already the one we are looking for
       */
      auto itr = transmissions.rbegin();
       while(itr != transmissions.rend()) {
         if(itr->invoke_id == id) {
           itr->handler = handler;
           break;
         }
         --itr;
       }
    }

    confirmed_request_handler_type get_handler_and_purge(uint8_t id) {
      bool removed_id{false};
      auto itr = transmissions.begin();
      while(itr != transmissions.end()) {
        if(itr->invoke_id == id) {
          break;
        }
        ++itr;
      }

      confirmed_request_handler_type handler_tmp{};

      if(itr != transmissions.end()) {
        handler_tmp = itr->handler;
        transmissions.erase(itr);
      }
      return handler_tmp;
    }


    /*
     * return true if invoke ide existsted and was removed
     * false otherwise
     */
    bool purge_invoke_id(uint8_t id) {
      bool removed_id{false};
      auto itr = transmissions.begin();
      while(itr != transmissions.end()) {
        if(itr->invoke_id == id) {
          break;
        }
        ++itr;
      }

      if(itr != transmissions.end()) {
        removed_id = true;
        transmissions.erase(itr);
      }
      return removed_id;
    }


  private:

    /**
     * when getting first invoke id, the counter is incremented and resulting invoke_id_counter as 0 as it overflows
     * invoke_ids will be reused when they overflow at 255 and restart with 0;
     */
    uint8_t invoke_id_counter{std::numeric_limits<uint8_t>::max()};

    /**
     * new invoke ids are added to the back, so when deleting we start at the front
     * as expecting to have the requests answerd in order, but does not to be so.
     */
    transmission_list_type transmissions;
  };

  typedef std::map<bacnet::common::protocol::mac::address, device_request_manager> device_request_map_type;




  struct request_manager {
    uint8_t get_next_invoke_id(const bacnet::common::protocol::mac::address &adr) {
      return device_request_map_[adr].get_next_invoke_id();
    }

    void store_handler(const bacnet::common::protocol::mac::address &adr, uint8_t id, confirmed_request_handler_type handler) {
      device_request_map_[adr].store_handler(id, handler);
    }

    confirmed_request_handler_type get_handler_and_purge(const bacnet::common::protocol::mac::address &adr, uint8_t id) {
      return device_request_map_[adr].get_handler_and_purge(id);
    }

    bool purge_invoke_id(const bacnet::common::protocol::mac::address &adr, uint8_t id) {
      return device_request_map_[adr].purge_invoke_id(id);
    }

  private:
    device_request_map_type device_request_map_;
  };



}}}


#endif /* SRC_BACNET_APDU_DETAIL_REQUEST_MANAGER_HPP_ */
