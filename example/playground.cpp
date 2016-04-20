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

#include <boost/dynamic_bitset.hpp>
#include <boost/variant.hpp>
#include <boost/type_index.hpp>

namespace bacnet {


namespace id {

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
	  static const constexpr uint16_t object_identifier        =  78;
	  static const constexpr uint16_t present_value            =  85;
	}

}//id

namespace type {



  template<uint32_t object_type, uint16_t property_type>
  struct property {
    typedef void type;
  };

  namespace o_id = bacnet::id::object;
  namespace p_id = bacnet::id::property;

  template<> struct property<o_id::analog_input, id::property::object_name>{typedef std::string type; };
  template<> struct property<o_id::analog_input, id::property::object_identifier>{typedef std::string type; };
  template<> struct property<o_id::analog_input, id::property::present_value>{typedef std::string type; };


  struct            null_{};
  typedef bool      boolean_;
  typedef uint32_t  unsigned_;
  typedef uint8_t   unsigned8_;
  typedef uint16_t  unsigned16_;
  typedef int32_t   integer_;
  typedef int16_t   integer16_;


  typedef float     real_;
  typedef double    double_;
  typedef std::vector<uint8_t>       octet_string_;
  typedef std::string                character_string_;
  typedef boost::dynamic_bitset<>    bit_string_;
  typedef uint32_t                   enumerated_;

  struct date_ {
     //much  more complicated! see page 662 in chapter 21
    uint8_t year_minus_1900;
    uint8_t month;
    uint8_t day_of_month;
    uint8_t day_of_week; // 1=monday; 7=sunday
  };

  struct time_ {
       //much  more complicated! see page 662 in chapter 21
      uint8_t hour;
      uint8_t minute;
      uint8_t second;
      uint8_t hundredths;
    };

  typedef boost::variant<
        null_,
        boolean_,
        unsigned_,
        unsigned8_,
        unsigned16_,
        integer_,
        integer16_,
        real_,
        double_,
        octet_string_,
        character_string_,
        bit_string_,
        enumerated_,
        date_,
        time_

      > property_value_t;

}//type



  struct analog_output {
     static const constexpr auto object_id = id::object::analog_input;

     type::property<object_id, id::property::object_name>::type object_name;
     type::property<object_id, id::property::object_identifier>::type object_identifier;
  };








  namespace service {


          struct read_property_request {
            common::object_identifier object_identifier;
            uint16_t property;
            boost::optional<type::property_value_t> array_index;


          };

          struct read_property_ack {
            common::object_identifier object_identifier;
            uint16_t property;
            boost::optional<uint32_t> array_index;
            type::property_value_t property_value;
          };

          struct who_is {
            boost::optional<uint32_t> low_range;
            boost::optional<uint32_t> hi_range;
          };

          struct i_am {
            boost::optional<uint32_t> low_range;
            boost::optional<uint32_t> hi_range;
          };

          struct reinitialize_device {
            boost::optional<uint32_t> low_range;
            boost::optional<uint32_t> hi_range;
          };



  }


}


namespace bacnet { namespace application {


/**
 *
 */



}}



class test_visit  : public boost::static_visitor<>
{
public:

    template<typename T>
    void operator()(T  t) {
      std::cout << "test_visit " << boost::typeindex::type_id_runtime(t).pretty_name() << std::endl;
    }


    void operator()(bacnet::type::enumerated_  t) {
      std::cout << "test_visit enumerated_ " << boost::typeindex::type_id_runtime(t).pretty_name() << std::endl;
    }


   void operator()(bacnet::type::unsigned_  t) {
     std::cout << "test_visit unsigned_ " << boost::typeindex::type_id_runtime(t).pretty_name() << std::endl;
   }



};



int main(int argc, char *argv[]) {


  test_visit visiter;

  bacnet::type::property_value_t v;
  v = bacnet::type::enumerated_{1337};
  v.apply_visitor(visiter);

  v = bacnet::type::unsigned_{42};
  v.apply_visitor(visiter);

  bacnet::service::read_property_ack rpa;

  uint32_t object_type{1};
  uint16_t property{85};

  //bacnet::type::property<object_type, property>::type prop_v;



  return 0;
}
