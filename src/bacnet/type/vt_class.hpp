/*
 * vt_class.hpp
 *
 *  Created on: Jun 26, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_VT_CLASS_HPP_
#define SRC_BACNET_TYPE_VT_CLASS_HPP_



#include <bacnet/type/enumerated.hpp>


namespace bacnet { namespace type {


struct vt_class {
  typedef uint32_t type;
  static constexpr type default_terminal  = 0;
  static constexpr type ansi_x3_64        = 1;
  static constexpr type dec_vt52          = 2;
  static constexpr type dec_vt100         = 3;
  static constexpr type dec_vt220         = 4;
  static constexpr type hp_700_94         = 5;
  static constexpr type ibm_3130          = 6;
};

static inline enumerated make_vt_class(vt_class::type vt_class_) {
  return enumerated(enumerated::e::vt_class, vt_class_);
}

template<>
inline std::string enumerated::to_string<vt_class>() const {
  std::stringstream os;
  switch(value) {
    case vt_class::default_terminal : os << "default_terminal"; break;
    case vt_class::ansi_x3_64       : os << "ansi_x3_64";       break;
    case vt_class::dec_vt52         : os << "dec_vt52";         break;
    case vt_class::dec_vt100        : os << "dec_vt100";        break;
    case vt_class::dec_vt220        : os << "dec_vt220";        break;
    case vt_class::hp_700_94        : os << "dec_vt220";        break;
    case vt_class::ibm_3130         : os << "ibm_3130";         break;
    default                         : os << "unknown";          break;
  }
  os << "(" << value << ")";
  return os.str();
}


}}


#endif /* SRC_BACNET_TYPE_VT_CLASS_HPP_ */
