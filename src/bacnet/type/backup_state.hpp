/*
 * backup_state.hpp
 *
 *  Created on: Jun 26, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_BACKUP_STATE_HPP_
#define SRC_BACNET_TYPE_BACKUP_STATE_HPP_



#include <bacnet/type/enumerated.hpp>


namespace bacnet { namespace type {


struct backup_state {
  typedef uint32_t type;
  static constexpr type idle                  = 0;
  static constexpr type preparing_for_backup  = 1;
  static constexpr type preparing_for_restore = 2;
  static constexpr type performing_a_backup   = 3;
  static constexpr type performing_a_restore  = 4;
  static constexpr type backup_failure        = 5;
  static constexpr type restore_failure       = 6;

};

static inline enumerated make_backup_state(backup_state::type state) {
  return enumerated(enumerated::e::backup_state, state);
}

template<>
inline std::string enumerated::to_string<backup_state>() const {
  std::stringstream os;
  switch(value) {
    case backup_state::idle                   : os << "idle";                 break;
    case backup_state::preparing_for_backup   : os << "preparing_for_backup"; break;
    case backup_state::preparing_for_restore  : os << "preparing_for_restore";break;
    case backup_state::performing_a_backup    : os << "performing_a_backup";  break;
    case backup_state::performing_a_restore   : os << "performing_a_restore"; break;
    case backup_state::backup_failure         : os << "backup_failure";       break;
    case backup_state::restore_failure        : os << "restore_failure";      break;
    default                                   : os << "unknown";              break;
  }
  os << "(" << value << ")";
  return os.str();
}


}}


#endif /* SRC_BACNET_TYPE_BACKUP_STATE_HPP_ */
