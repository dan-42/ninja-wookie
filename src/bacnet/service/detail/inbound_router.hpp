/*
 * inbound_router.hpp
 *
 *  Created on: Jul 29, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_SERVICE_DETAIL_INBOUND_ROUTER_HPP
#define SRC_BACNET_SERVICE_DETAIL_INBOUND_ROUTER_HPP



#include <iostream>
#include <iomanip>

#include <boost/variant/static_visitor.hpp>
#include <bacnet/service/service/services.hpp>
#include <bacnet/service/detail/callback_manager.hpp>
#include <bacnet/service/detail/device_manager.hpp>




namespace bacnet { namespace service { namespace detail {

  using namespace bacnet::apdu;
  using namespace bacnet::service;

  struct inbound_router : boost::static_visitor<> {

    inbound_router(callback_manager& cm, bacnet::service::detail::device_manager& dm) : callback_manager_(cm), device_manager_(dm) {
    }

    inline void meta_information(bacnet::common::protocol::meta_information meta_information) {
      meta_information_ = meta_information;
    }

    template<typename Service>
    inline void operator()(Service service) {
      bacnet::error ec;
      meta_information_.service_choice = bacnet::service::service::detail::service_choice<Service>::value;
      callback_manager_.invoke(std::move(service), ec, std::move(meta_information_));
    }

  private:

    callback_manager& callback_manager_;
    bacnet::service::detail::device_manager& device_manager_;
    bacnet::common::protocol::meta_information meta_information_;
  };


  /**
   * specialisation used to update internal DOI-Mapping list
   */
template<>
inline void inbound_router::operator()<service::i_am>(service::i_am service) {
  device_manager_.insert_device(bacnet::common::protocol::mac::endpoint{meta_information_.npdu_source.network_number, meta_information_.address},
                                service.i_am_device_identifier,
                                service.max_apdu_length_accepted,
                                service.segmentation_supported,
                                service.vendor_id);
  //device_manager_.print_device_list();
  bacnet::error ec;
  callback_manager_.invoke(std::move(service), ec, std::move(meta_information_));
}


}}}



#endif /* SRC_BACNET_SERVICE_DETAIL_INBOUND_ROUTER_HPP */
