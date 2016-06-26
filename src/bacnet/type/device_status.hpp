/*
 * device_status.hpp
 *
 *  Created on: Jun 25, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_DEVICE_STATUS_HPP_
#define SRC_BACNET_TYPE_DEVICE_STATUS_HPP_


#include <bacnet/type/enumerated.hpp>


namespace bacnet { namespace type {


struct device_status {
  typedef uint32_t type;
  static constexpr uint32_t operational             =  0;
  static constexpr uint32_t operational_read_only   =  1;
  static constexpr uint32_t download_required       =  2;
  static constexpr uint32_t download_in_progress    =  3;
  static constexpr uint32_t non_operational         =  4;
  static constexpr uint32_t non_backup_in_progress  =  5;
};

static inline enumerated make_device_status(device_status::type status) {
  return enumerated(enumerated::e::device_status, status);
}

template<>
inline std::string enumerated::to_string<device_status>() const {
  std::stringstream os;
  switch(value) {
    case device_status::operational             : os << "operational";              break;
    case device_status::operational_read_only   : os << "operational_read_only";    break;
    case device_status::download_required       : os << "download_required";        break;
    case device_status::download_in_progress    : os << "download_in_progress";     break;
    case device_status::non_operational         : os << "non_operational";          break;
    case device_status::non_backup_in_progress  : os << "non_backup_in_progress";   break;
    default                                     : os << "unknown";                  break;
  }
  os << "(" << value << ")";
  return os.str();
}


}}



#endif /* SRC_BACNET_TYPE_DEVICE_STATUS_HPP_ */
