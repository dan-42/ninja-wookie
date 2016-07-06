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

#include <bacnet/type/properties.hpp>
#include <bacnet/stack/factory.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/dynamic_bitset.hpp>
#include <bacnet/type/bit_string.hpp>
#include <bacnet/type/types.hpp>
#include <iostream>
#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>


#include <boost/fusion/adapted/mpl.hpp>
#include <boost/fusion/include/mpl.hpp>


#include <bacnet/type/types.hpp>

typedef boost::mpl::range_c<bacnet::type::property_type, 0, 850> possible_numbers;

struct value_printer {
  int wished;
  value_printer(int wished ) : wished(wished) { }

  template< typename U >
  constexpr void operator()(const U& x)  const {
    if(x == wished) {
      typedef std::integral_constant<bacnet::type::property_type, x> X;
      if(bacnet::type::property::is_property<X>::value ) {
        std::cout << "property: " << bacnet::type::property::name<X>::value << " id: " << X::value << std::endl;
      }
    }
  }
};

int main(int argc, char** argv) {
  int x = std::atoi(argv[1]);
  boost::mpl::for_each<possible_numbers>( value_printer(x) );
  return 0;
}

