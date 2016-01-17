//
// Created by dan on 16.01.16.
//

#ifndef NINJA_WOOKIE_UTILS_HPP
#define NINJA_WOOKIE_UTILS_HPP

#include <bacnet/detail/common/types.hpp>

namespace test {
  namespace utils {

    bool compare_binary_data(const bacnet::binary_data&  a, const bacnet::binary_data& b) {
      if( a.size() != b.size() ) {
        return false;
      }

      for(std::size_t idx = 0; idx < a.size(); ++idx) {
        if( a[idx] != b[idx] ) {
          return false;
        }
      }
      return true;
    }

  }
}


#endif //NINJA_WOOKIE_UTILS_HPP
