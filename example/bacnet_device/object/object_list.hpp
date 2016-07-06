/*
 * object_list.hpp
 *
 *  Created on: Jul 6, 2016
 *      Author: frieddan
 */

#ifndef EXAMPLE_BACNET_DEVICE_OBJECT_LIST_HPP_
#define EXAMPLE_BACNET_DEVICE_OBJECT_LIST_HPP_


#include <bacnet/type/types.hpp>

namespace bacnet { namespace detail {

  class object_base {
  public:
    virtual ~object_base(){};
    virtual bacnet::type::possible_type read_prop(uint16_t property_id, boost::optional<uint16_t> index) = 0;
    virtual bacnet::error write_prop(uint16_t property_id, boost::optional<uint16_t> index, bacnet::type::possible_type data) = 0;

  };
  typedef std::shared_ptr<object_base> object_base_ptr_t;

}

typedef std::vector<detail::object_base_ptr_t> object_ptr_list_t;


namespace traits {

  template<typename T> struct has_read_property : std::false_type { };

}


template<typename Derived>
class object : public detail::object_base {
public:



  object() {
   // object_types_supported_.set(traits::supported_index<Derived>::value);

  }

  virtual ~object(){}

  Derived& self() { return static_cast<Derived&>(*this); }


  virtual inline bacnet::type::possible_type read_prop(uint16_t property_id, boost::optional<uint16_t> index) final {

    if(traits::has_read_property<Derived>::value) {
      std::cout << "object:: read_prop" << std::endl;
      //xxx map uint16_t  to property_type
      //return self().read_prop_impl(property_id, index);
    }
    std::cout << "object:: read_prop not supported" << std::endl;
    return bacnet::binary_data{};
  }



  virtual inline bacnet::error write_prop(uint16_t property_id, boost::optional<uint16_t> index, bacnet::type::possible_type data) final {
    std::cout << "object:: write_prop" << std::endl;
    //self().write_prop_impl(property_id, index, data);
  }


private:

  static std::bitset<54> object_types_supported_;


  bacnet::type::object_identifier           object_identifier_;
  std::string                               object_name;
  std::vector<bacnet::type::property_type>  propetty_list_;

};







struct device final : public object<device> {


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


#endif /* EXAMPLE_BACNET_DEVICE_OBJECT_LIST_HPP_ */
