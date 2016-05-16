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


#define BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#define BOOST_MPL_LIMIT_VECTOR_SIZE 600


#include <bacnet/type/properties.hpp>
#include <bacnet/stack/factory.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/dynamic_bitset.hpp>
#include <bacnet/type/bit_string.hpp>
#include <bacnet/type/types.hpp>



#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>

namespace bacnet { namespace id {



namespace object {
  static const constexpr uint32_t analog_input      =  0;
  static const constexpr uint32_t analog_output     =  1;
  static const constexpr uint32_t analog_value      =  2;
  static const constexpr uint32_t binary_input      =  3;
  static const constexpr uint32_t binar_output      =  4;
  static const constexpr uint32_t binary_value      =  5;
  static const constexpr uint32_t calendar          =  6;
  static const constexpr uint32_t command           =  7;
  static const constexpr uint32_t device            =  8;
}

}}










namespace bacnet {
namespace detail {

  class object_base {
  public:
    virtual ~object_base(){};
    virtual bacnet::binary_data read_prop(uint16_t property_id, boost::optional<uint16_t> index) = 0;
    virtual void write_prop(uint16_t property_id, boost::optional<uint16_t> index, bacnet::binary_data data) = 0;

  };
  typedef std::shared_ptr<object_base> object_base_ptr_t;
}//detail

typedef std::vector<detail::object_base_ptr_t> object_ptr_list_t;


namespace traits {

  template<typename T> struct has_read_property : std::false_type { };

}


template<typename Derived, typename PropertieMap>
class object : public detail::object_base {
public:

  boost::mpl::vector<>

  object() {
   // object_types_supported_.set(traits::supported_index<Derived>::value);

  }

  virtual ~object(){}

  Derived& self() { return static_cast<Derived&>(*this); }

  template<typename Property, typename PropertyType>
  inline bacnet::binary_data read_prop(Property property_id, boost::optional<uint16_t> index) final {

    if(traits::has_read_property<Derived>::value) {
      std::cout << "object:: read_prop" << std::endl;
      return self().read_prop_impl(property_id, index);
    }
    std::cout << "object:: read_prop not supported" << std::endl;
    return bacnet::binary_data{};
  }


  template<typename Property, typename PropertyType>
  inline void write_prop(Property property_id, boost::optional<uint16_t> index, bacnet::binary_data data) final {
    std::cout << "object:: write_prop" << std::endl;
    self().write_prop_impl(property_id, index, data);
  }


private:

  static std::bitset<54> object_types_supported_;

};


namespace object_properties {
using namespace bacnet::type;

  typedef boost::fusion::map<
      boost::fusion::pair<property::all,  unsigned_integer>

    > analog_input_type_map;
}





  struct analog_input final : public object<analog_input, object_properties::analog_input_type_map> {
    namespace property = bacnet::type::property;
    using namespace bacnet::type;

    inline bacnet::binary_data read_prop_impl(uint16_t property_id, boost::optional<uint16_t> index) {
      std::cout << "analog_input:: read_prop_impl" << std::endl;
        return bacnet::binary_data{};
    }





    inline void write_prop_impl(property::alarm_value, boost::optional<uint16_t> index, type::possible_type data) {
        std::cout << "analog_input:: write_prop_impl" << std::endl;
    }


    inline void write_prop_impl(property::action, boost::optional<uint16_t> index, bacnet::binary_data data) {
        std::cout << "analog_input:: write_prop_impl" << std::endl;
    }


  };
  namespace traits {
    template<>  struct has_read_property<analog_input> : std::true_type { };
  }



  struct analog_output final : public object<analog_output> {

      inline bacnet::binary_data read_prop_impl(uint16_t property_id, boost::optional<uint16_t> index) {
        std::cout << "analog_output:: read_prop_impl" << std::endl;
          return bacnet::binary_data{};
      }


      inline void write_prop_impl(uint16_t property_id, boost::optional<uint16_t> index, bacnet::binary_data data) {
          std::cout << "analog_output:: write_prop_impl" << std::endl;
      }

  };
}


int main(int argc, char *argv[]) {


  bacnet::type::property::supported_properties t;


  bacnet::object_ptr_list_t object_list;

  auto ai_ptr = std::make_shared<bacnet::analog_input>();
  auto ao_ptr = std::make_shared<bacnet::analog_output>();
  object_list.push_back(ai_ptr);
  object_list.push_back(ao_ptr);

  uint16_t property_id{0};
  boost::optional<uint16_t> index;
  bacnet::binary_data data{};

  for(auto& o : object_list) {
    o->write_prop(property_id, index, data);
    o->read_prop(property_id, index);
  }

}
