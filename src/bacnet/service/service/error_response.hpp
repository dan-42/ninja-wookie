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
#include <bacnet/service/service/traits.hpp>
#include <bacnet/type/error.hpp>
#include <util/boost/spirit/unused_type.hpp>


namespace bacnet { namespace service { namespace service {
struct error_response {

  error_response() = default;

  error_response(bacnet::type::error e) :  error(std::move(e)){
  }

  bacnet::type::error error;
  unused_t unused{0};

};

}}}


BOOST_FUSION_ADAPT_STRUCT(
  bacnet::service::service::error_response,
  error,
  unused
);



namespace bacnet { namespace service { namespace service {    
    
    template<> struct is_confirmed<error_response> :  boost::mpl::true_ {};
    
    template<> struct is_response<error_response> :   boost::mpl::true_ {};
    
}}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_ERROR_HPP_HPP
