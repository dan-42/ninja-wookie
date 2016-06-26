/*
 * restart_reason.hpp
 *
 *  Created on: Jun 26, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_RESTART_REASON_HPP_
#define SRC_BACNET_TYPE_RESTART_REASON_HPP_


#include <bacnet/type/enumerated.hpp>


namespace bacnet { namespace type {


struct restart_reason {
  typedef uint32_t type;
  static constexpr type unknown               =  0;
  static constexpr type coldstart             =  1;
  static constexpr type warmstart             =  2;
  static constexpr type detected_power_lost   =  3;
  static constexpr type detected_powered_off  =  4;
  static constexpr type hardware_watchdog     =  5;
  static constexpr type software_watchdog     =  6;
  static constexpr type suspended             =  7;
};

static inline enumerated make_restart_reason(restart_reason::type reason) {
  return enumerated(enumerated::e::restart_reason, reason);
}

template<>
inline std::string enumerated::to_string<restart_reason>() const {
  std::stringstream os;
  switch(value) {
    case restart_reason::unknown              : os << "unknown";              break;
    case restart_reason::coldstart            : os << "coldstart";            break;
    case restart_reason::warmstart            : os << "warmstart";            break;
    case restart_reason::detected_power_lost  : os << "detected_power_lost";  break;
    case restart_reason::detected_powered_off : os << "detected_powered_off"; break;
    case restart_reason::hardware_watchdog    : os << "hardware_watchdog";    break;
    case restart_reason::software_watchdog    : os << "software_watchdog";    break;
    case restart_reason::suspended            : os << "suspended";            break;
    default                                   : os << "unknown";              break;
  }
  os << "(" << value << ")";
  return os.str();
}


}}




#endif /* SRC_BACNET_TYPE_RESTART_REASON_HPP_ */
