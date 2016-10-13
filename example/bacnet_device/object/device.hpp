/*
 * device.hpp
 *
 *  Created on: Jul 6, 2016
 *      Author: frieddan
 */

#ifndef EXAMPLE_BACNET_DEVICE_OBJECT_DEVICE_HPP_
#define EXAMPLE_BACNET_DEVICE_OBJECT_DEVICE_HPP_




#include <bacnet/type/types.hpp>
#include <bacnet_device/object/object_list.hpp>

namespace bacnet { namespace object {


struct device final : public object<device> {


	template<typename T1, typename T2>
	inline detail::read_prop_return_type read_prop_impl(T1, T2) {

	  uint32_t value = 0;
	  for(int i = 0; i < 10000; ++i) {
	    value += T1::value;
	  }
	  auto v = bacnet::type::unsigned_integer{value};

	  return { bacnet::make_error(bacnet::err::error_class::property, bacnet::err::error_code::unknown_property) , v };
		//return { bacnet::make_error(bacnet::err::error_class::property, bacnet::err::error_code::unknown_property) , bacnet::type::null{} };
	}


/*
	template<>
	inline detail::read_prop_return_type read_prop_impl<bacnet::type::property::object_identifier, boost::optional<uint16_t> >(bacnet::type::property::object_identifier, boost::optional<uint16_t> index) {
	    return { bacnet::error{} , object_identifier_ };
  }
  */
};



namespace traits {
  template<>  struct has_read_property<device> : std::true_type { };
}



}}





#endif /* EXAMPLE_BACNET_DEVICE_OBJECT_DEVICE_HPP_ */
