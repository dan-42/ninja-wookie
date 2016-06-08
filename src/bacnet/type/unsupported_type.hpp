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

  struct unsupported_type {
    uint32_t tag_number{0};
    bacnet::binary_data value;
    //std::string value;

    template<typename Out>
    inline friend Out& operator<<(Out& os, const unsupported_type& v) {
        os << "context_tag:" << (int)v.tag_number << ";    value: " ;
        for(auto &c : v.value) {
           os << std::setfill('0') << std::setw(2) << std::hex << (int)c;
        }
        return os;
      }
  };

}}



BOOST_FUSION_ADAPT_STRUCT(
  bacnet::type::unsupported_type,
  tag_number,
  value
);





#endif /* NINJA_WOOKIE_BACNET_TYPE_UNKNOWN_DATA_HPP */
