/*
 * boolean.hpp
 *
 *  Created on: May 14, 2016
 *      Author: dan
 */

#ifndef NINJA_WOOKIE_BACNET_TYPE_UNKNOWN_DATA_HPP
#define NINJA_WOOKIE_BACNET_TYPE_UNKNOWN_DATA_HPP

#include <bacnet/detail/common/types.hpp>


#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>


namespace bacnet { namespace type {
  struct unknown_data;
  inline unknown_data make_unknown_data(uint32_t tag, bacnet::binary_data bd);

  struct unknown_data {

    uint32_t    context_tag{0};
    bacnet::binary_data value;
  };

  inline unknown_data make_unknown_data(uint32_t tag, bacnet::binary_data bd) {
    unknown_data ud;
    ud.context_tag = tag;
    std::stringstream ss;
    for(auto &c : bd) {
       ss << std::setfill('0') << std::setw(2) << std::hex << (int)c;
    }
    //ud.value = ss.str();
    ud.value = bd;
    return ud;
  }

}}



BOOST_FUSION_ADAPT_STRUCT(
    bacnet::type::unknown_data,
    context_tag,
//   size,
    value
);

namespace bacnet { namespace type {


  static std::ostream& operator<<(std::ostream& os, const unknown_data& v) {
    os << "context_tag:" << v.context_tag << ";  size:" << v.value.size() << ";  value: " ;//<< v.value << "; ";
    for(auto &c : v.value) {
       os << std::setfill('0') << std::setw(2) << std::hex << (int)c;
    }
    return os;
  }

}}


#endif /* NINJA_WOOKIE_BACNET_TYPE_UNKNOWN_DATA_HPP */
