/*
 * segmentation.hpp
 *
 *  Created on: Jun 26, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_SEGMENTATION_HPP_
#define SRC_BACNET_TYPE_SEGMENTATION_HPP_




#include <bacnet/type/enumerated.hpp>


namespace bacnet { namespace type {


struct segmentation {
  typedef uint32_t type;
  static constexpr type segmented_both      = 0;
  static constexpr type segmented_transmit  = 1;
  static constexpr type segmented_receive   = 2;
  static constexpr type no_segmentation     = 3;
};

static inline enumerated make_segmentation(segmentation::type status) {
  return enumerated(enumerated::e::segmentation, status);
}

template<>
inline std::string enumerated::to_string<segmentation>() const {
  std::stringstream os;
  switch(value) {
    case segmentation::segmented_both     : os << "segmented_both";     break;
    case segmentation::segmented_transmit : os << "segmented_transmit"; break;
    case segmentation::segmented_receive  : os << "segmented_receive";  break;
    case segmentation::no_segmentation    : os << "no_segmentation";    break;
    default                               : os << "unknown";            break;
  }
  os << "(" << value << ")";
  return os.str();
}


}}



#endif /* SRC_BACNET_TYPE_SEGMENTATION_HPP_ */
