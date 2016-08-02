/*
 * object_list.hpp
 *
 *  Created on: Jul 6, 2016
 *      Author: frieddan
 */

#ifndef EXAMPLE_BACNET_DEVICE_OBJECT_LIST_HPP_
#define EXAMPLE_BACNET_DEVICE_OBJECT_LIST_HPP_

#include <util/complex_return.hpp>

#include <bacnet/type/types.hpp>


namespace bacnet { namespace detail {

  using read_prop_return_type = util::complex_return<bacnet::error, bacnet::type::possible_type>;

  class object_base {
  public:
    virtual ~object_base(){};
    virtual read_prop_return_type read_prop(uint16_t property_id, boost::optional<uint16_t> index) = 0;
   // virtual bacnet::error write_prop(uint16_t property_id, boost::optional<uint16_t> index, bacnet::type::possible_type data) = 0;

  };
  typedef std::shared_ptr<object_base> object_base_ptr_t;

}

typedef std::map<uint32_t, detail::object_base_ptr_t> object_ptr_map_t;


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


  virtual inline detail::read_prop_return_type read_prop(uint16_t property_id, boost::optional<uint16_t> index) final {

    if(!traits::has_read_property<Derived>::value) {
      std::cout << "object:: read_prop not supported" << std::endl;
      static auto error = bacnet::make_error(bacnet::err::error_class::object, bacnet::err::error_code::unknown_object);
      return {error, bacnet::type::null{}};
    }
    //xxx map uint16_t  to property_type
    switch(property_id) {
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value, index);
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value, index);
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value, index);
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value, index);
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value, index);
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value, index);
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value, index);
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value, index);
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value, index);


    }
    return self().read_prop_impl(property_id, index);

  }




private:

  static std::bitset<54> object_types_supported_;


  bacnet::type::object_identifier           object_identifier_;
  std::string                               object_name;
  std::vector<bacnet::type::property_type>  propetty_list_;

};









}


#endif /* EXAMPLE_BACNET_DEVICE_OBJECT_LIST_HPP_ */
