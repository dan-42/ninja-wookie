/*
 * property_identifier.hpp
 *
 *  Created on: Jun 25, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_PROPERTY_IDENTIFIER_HPP_
#define SRC_BACNET_TYPE_PROPERTY_IDENTIFIER_HPP_

#include <boost/mpl/range_c.hpp>
#include <boost/mpl/for_each.hpp>

#include <bacnet/type/enumerated.hpp>
#include <bacnet/type/properties.hpp>


namespace bacnet { namespace type {

static inline enumerated make_property_identifier(device_status::type status) {
  return enumerated(enumerated::e::property_identifier, status);
}

namespace detail {

  typedef boost::mpl::range_c<bacnet::type::property_type, 0, max_standard_property_id> possible_numbers;

  struct value_printer {
    std::stringstream &os;
    bool &is_supported;
    int wished;
    value_printer(std::stringstream &os, bool &is_supported, int wished ) : os(os), is_supported(is_supported), wished(wished) { }

    template< typename U >
    constexpr void operator()(const U& x)  const {
      if(x == wished) {
        typedef std::integral_constant<bacnet::type::property_type, x> X;
        if(bacnet::type::property::is_property<X>::value ) {
          os << bacnet::type::property::name<X>::value;
          is_supported = true;
        }
      }
    }
  };

}//detail

struct property_identifier {
  static constexpr auto device_type = property::device_type::value;

};




template<>
inline std::string enumerated::to_string<property_identifier>() const {
  std::stringstream os;
  bool is_supported{false};

  boost::mpl::for_each<detail::possible_numbers>( detail::value_printer(os, is_supported, value) );
  if(!is_supported) {
    os << "unknown_property";
  }

  os << "(" << value << ")";
  return os.str();
}

}}



#endif /* SRC_BACNET_TYPE_PROPERTY_IDENTIFIER_HPP_ */
