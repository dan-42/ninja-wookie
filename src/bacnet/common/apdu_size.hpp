/*
 * apdu_size.hpp
 *
 *  Created on: Oct 22, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_COMMON_APDU_SIZE_HPP_
#define SRC_BACNET_COMMON_APDU_SIZE_HPP_

namespace bacnet { namespace common { namespace apdu_size {

using apdu_size_type = uint32_t;

static constexpr apdu_size_type _50_bytes     =    50;
static constexpr apdu_size_type _128_bytes    =   128;
static constexpr apdu_size_type _206_bytes    =   206;
static constexpr apdu_size_type _480_bytes    =   480;
static constexpr apdu_size_type _1024_bytes   =  1024;
static constexpr apdu_size_type _1476_bytes   =  1476;






}}}



#endif /* SRC_BACNET_COMMON_APDU_SIZE_HPP_ */
