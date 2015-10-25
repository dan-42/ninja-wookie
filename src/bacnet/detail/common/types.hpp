/*
 * types.hpp
 *
 *  Created on: May 20, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_TYPES_HPP_
#define SRC_BACNET_TYPES_HPP_

#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>

#include <boost/spirit/home/support/unused.hpp>
namespace bacnet { namespace detail { namespace common {

/**
 * used for holding binary data
 */
typedef std::vector<uint8_t> binary_data;




}}}


namespace bacnet {

/* make it accessable via bacnet namespace */
using detail::common::binary_data;

  static void print(const binary_data &data) {
    for(auto &c : data)
      std::cout << " 0x" << std::setfill('0') << std::setw(2) << std::hex << (int)c;
    std::cout << std::endl;
  }
}

#endif /* SRC_BACNET_TYPES_HPP_ */
