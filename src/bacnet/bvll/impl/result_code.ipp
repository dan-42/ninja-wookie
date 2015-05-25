/*
 * result_code.hpp
 *
 *  Created on: May 16, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_BVLL_BVLC_RESULT_CODE_IMPL_
#define SRC_BACNET_BVLL_BVLC_RESULT_CODE_IMPL_

using namespace bacnet::bvll::result_code;


std::ostream &bacnet::bvll::result_code::operator<<(std::ostream &os, const uint16_t &rc) {
  switch (rc) {
    case result_code::successful_completion :
      os << "successful_completion(0x0000)";
      break;
    case result_code::write_broadcast_distribution_table_nak :
      os << "write_broadcast_distribution_table_nak(0x0010)";
      break;
    case result_code::read_broadcast_distribution_table_nak :
      os << "read_broadcast_distribution_table_nak(0x0020)";
      break;
    case result_code::register_foreign_device_nak :
      os << "register_foreign_device_nak(0x0030)";
      break;
    case result_code::read_foreign_device_table_nak :
      os << "read_foreign_device_table_nak(0x0040)";
      break;
    case result_code::delete_foreign_device_table_entry_nak :
      os << "delete_foreign_device_table_entry_nak(0x0050)";
      break;
    case result_code::distribute_broadcast_to_network_nak :
      os << "distribute_broadcast_to_network_nak(0x0060)";
      break;
    default:
      os << "unknown result_code  (0x" << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint32_t>(rc) <<
      ")";
  }
  return os;
}


#endif /* SRC_BACNET_BVLL_BVLC_RESULT_CODE_IMPL_ */
