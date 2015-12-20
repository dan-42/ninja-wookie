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

typedef std::back_insert_iterator<binary_data> generate_iterator;

typedef binary_data::iterator parse_iterator;


}}}


namespace bacnet {

/* make it accessable via bacnet namespace */
using detail::common::binary_data;
using detail::common::generate_iterator;
using detail::common::parse_iterator;

  static void print(const binary_data &data) {
    for(auto &c : data)
      std::cout << " 0x" << std::setfill('0') << std::setw(2) << std::hex << (int)c;
    std::cout << std::endl;
  }
}

#endif /* SRC_BACNET_TYPES_HPP_ */
