//
// Created by dan on 08.10.15.
//

#ifndef NINJA_WOOKIE_SERVICES_HPP
#define NINJA_WOOKIE_SERVICES_HPP


#include <cstdint>

#include <boost/variant.hpp>
#include <boost/fusion/include/define_struct.hpp>
#include <bacnet/service/service/detail/service_generator.hpp>
#include <bacnet/service/service/detail/service_choice.hpp>


BOOST_FUSION_DEFINE_STRUCT(
  (bacnet)(service)(service), i_am,
  (uint32_t, i_am_device_identifier)
  (uint32_t, max_apdu_length_accepted)
  (uint8_t, segmentation_supported)
  (uint16_t, vendor_id)
)

namespace bacnet { namespace service { namespace detail {
  using namespace bacnet::service::service;

  template<>
  struct service_choice<i_am> {
    static constexpr uint8_t value = 0x00;
    typedef i_am type;
  };

  template<>
  struct is_broadcast_service<i_am> : std::true_type {
  };
}}}

BOOST_FUSION_DEFINE_STRUCT(
    (bacnet)(service), who_is,
    (uint32_t, device_instance_range_low_limit)
    (uint32_t, device_instance_range_high_limit)
)

namespace bacnet { namespace service { namespace detail {
  using namespace bacnet::service;
  template<>
  struct service_choice<who_is> {
    static constexpr uint8_t value = 0x08;
    typedef who_is type;
  };

  template<>
  struct is_broadcast_service<who_is> : std::true_type {
  };


}}}






namespace bacnet { namespace service { namespace unconfirmed {
  typedef boost::variant<
      who_is,
      i_am
  > possible_service;
}}}



#endif //NINJA_WOOKIE_SERVICES_HPP
