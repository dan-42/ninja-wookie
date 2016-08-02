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

namespace bacnet {


struct device final : public object<device> {


	template<typename T1, typename T2>
	inline detail::read_prop_return_type read_prop_impl(T1, T2) {
		return { bacnet::make_error(bacnet::err::error_class::property, bacnet::err::error_code::unknown_property) , bacnet::type::null{} };
	}



	template<>
	inline detail::read_prop_return_type read_prop_impl(bacnet::type::property::object_identifier, boost::optional<uint16_t> index) {
	    return { bacnet::error{} , object_identifier_ };
  }






  template<typename T1, typename T2, typename T3 >
  inline bacnet::error write_prop_impl(bacnet::type::property::alarm_value, boost::optional<uint16_t> index, type::possible_type data) {
      std::cout << "analog_input:: write_prop_impl" << std::endl;
  }



  inline bacnet::error write_prop_impl(bacnet::type::property::alarm_value, boost::optional<uint16_t> index, type::possible_type data) {
      std::cout << "analog_input:: write_prop_impl" << std::endl;
  }


  inline bacnet::error write_prop_impl(bacnet::type::property::action, boost::optional<uint16_t> index, type::possible_type data) {
      std::cout << "analog_input:: write_prop_impl" << std::endl;
  }


};
namespace traits {
  template<>  struct has_read_property<device> : std::true_type { };
}



}





#endif /* EXAMPLE_BACNET_DEVICE_OBJECT_DEVICE_HPP_ */
