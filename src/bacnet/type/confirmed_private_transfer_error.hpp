/*
 * object_property_reference.hpp
 *
 *  Created on: May 30, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_CONFIRMED_PRIVATE_TRANSFER_ERROR_HPP_
#define SRC_BACNET_TYPE_CONFIRMED_PRIVATE_TRANSFER_ERROR_HPP_


#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <bacnet/detail/common/types.hpp>


namespace bacnet { namespace type {


  struct confirmed_private_transfer_error {

	  confirmed_private_transfer_error() = default;

	  uint16_t vendor_id{0};
	  uint32_t service_number{0};
	  boost::optional<bacnet::binary_data> error_parameter;

  };

}}

BOOST_FUSION_ADAPT_STRUCT(
    bacnet::type::confirmed_private_transfer_error,
	vendor_id,
	service_number,
	service_number
);

namespace bacnet { namespace type {


  static std::ostream& operator<<(std::ostream& os, const confirmed_private_transfer_error& v) {

    return os;
  }

}}


#endif /* SRC_BACNET_TYPE_CONFIRMED_PRIVATE_TRANSFER_ERROR_HPP_ */
