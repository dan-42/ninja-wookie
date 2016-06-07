/*
 * boolean.hpp
 *
 *  Created on: May 14, 2016
 *      Author: dan
 */

#ifndef NINJA_WOOKIE_BACNET_TYPE_UNKNOWN_DATA_HPP
#define NINJA_WOOKIE_BACNET_TYPE_UNKNOWN_DATA_HPP

#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>
#include <bacnet/detail/common/types.hpp>




namespace bacnet { namespace type {

  struct unsupported_type;

  typedef boost::variant<
          bacnet::binary_data,
          boost::recursive_wrapper< unsupported_type >
      > unknown_data_t;

  struct unsupported_type {
    uint32_t context_tag{0};
    unknown_data_t value;
  };

}}



BOOST_FUSION_ADAPT_STRUCT(
  bacnet::type::unsupported_type,
  context_tag,
  value
);



namespace bacnet { namespace type {

  static std::ostream& operator<<(std::ostream& os, const unsupported_type& v) {
    os << "context_tag:" << v.context_tag << ";    value: " ;//<< v.value << "; ";
 //   for(auto &c : v.value) {
 //      os << std::setfill('0') << std::setw(2) << std::hex << (int)c;
 //   }
    return os;
  }

}}


#endif /* NINJA_WOOKIE_BACNET_TYPE_UNKNOWN_DATA_HPP */
