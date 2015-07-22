/*
 * network_priority.hpp
 *
 *  Created on: Jul 21, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_NPDU_NETWORK_PRIORITY_HPP_
#define SRC_BACNET_NPDU_NETWORK_PRIORITY_HPP_

#include <cstdint>

namespace bacnet { namespace  npdu {



enum class network_priority : uint8_t {
  normal_message             = 0b00000000,
  urgent_message             = 0b00000001,
  critical_equitment_message = 0b00000010,
  life_safety_message        = 0b00000011
};

}}


#endif /* SRC_BACNET_NPDU_NETWORK_PRIORITY_HPP_ */
