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
#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_ERROR_HPP_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_ERROR_HPP_HPP


#include <cstdint>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <bacnet/service/service/detail/service_choice.hpp>
#include <bacnet/service/service/traits.hpp>

#include <bacnet/type/enumerated.hpp>


//see page 656 chapter 21 Error ::= SEQUENCE {

/*

 NOTE: The valid combinations of error-class and error-code are defined in Clauerror-class
 ENUMERATED {
device  (0),
object  (1),
property (2),
resources (3),
security (4),
services (5),
vt (6),
communication (7),
...
},


 */

namespace bacnet { namespace service { namespace service {
struct error {

  error() = default;

  error(uint32_t code_) :  error_class(device_instance),
                          error_code(code_) {
  }

  error(uint32_t class_, uint32_t code_) :  error_class(class_),
                                            error_code(code_) {
  }

  static constexpr auto enum_type_class = bacnet::type::enumerated::e::error_class;
  static constexpr auto enum_type_code = bacnet::type::enumerated::e::error_code;

  bacnet::type::enumerated error_class;
  bacnet::type::enumerated error_code;

};

}}}


BOOST_FUSION_ADAPT_STRUCT(
  bacnet::service::service::error,
  error_class,
  error_code
)



namespace bacnet { namespace service { namespace service {    
    
    template<> struct is_unconfirmed<error> :  boost::mpl::true_ {};
    
    template<> struct is_response<error> :     boost::mpl::true_ {};
    
}}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_ERROR_HPP_HPP
