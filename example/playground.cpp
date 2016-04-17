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

#include <bacnet/stack/factory.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <boost/asio.hpp>



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


namespace property {
  static const constexpr uint16_t object_name              =  77;
  static const constexpr uint16_t object_identifier        =  77;
  static const constexpr uint16_t present_value            =  85;
}

}

namespace type {

namespace property {

  template<uint32_t object_type, uint16_t property_t, typename Type >
  struct property_type {
    typedef Type type;
  };



    namespace o_id = bacnet::id::object;
    namespace p_id = bacnet::id::property;


    template<> struct property_type<o_id::analog_input, id::property::object_name,         std::string>;
    template<> struct property_type<o_id::analog_input, id::property::object_identifier,   std::string>;
    template<> struct property_type<o_id::analog_input, id::property::present_value,       std::string>;



  }



}




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


template<typename Derived>
class object : public detail::object_base {
public:

  object() {
    object_types_supported_.set(traits::supported_index<Derived>::value);

  }

  virtual ~object(){}

  Derived& self() { return static_cast<Derived&>(*this); }

  inline bacnet::binary_data read_prop(uint16_t property_id, boost::optional<uint16_t> index) {

    if(traits::has_read_property<Derived>::value) {
      std::cout << "object:: read_prop" << std::endl;
      return self().read_prop_impl(property_id, index);
    }
    std::cout << "object:: read_prop not supported" << std::endl;
    return bacnet::binary_data{};
  }
  inline void write_prop(uint16_t property_id, boost::optional<uint16_t> index, bacnet::binary_data data) {
    std::cout << "object:: write_prop" << std::endl;
    self().write_prop_impl(property_id, index, data);
  }


private:

  static std::bitset<54> object_types_supported_;

};





  struct analog_input final : public object<analog_input> {

    inline bacnet::binary_data read_prop_impl(uint16_t property_id, boost::optional<uint16_t> index) {
      std::cout << "analog_input:: read_prop_impl" << std::endl;
        return bacnet::binary_data{};
    }

    inline void write_prop_impl(uint16_t property_id, boost::optional<uint16_t> index, bacnet::binary_data data) {
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
