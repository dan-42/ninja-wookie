/*
 * address.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_NPDU_ADDRESS_HPP_
#define SRC_BACNET_NPDU_ADDRESS_HPP_


#include <iostream>

#include <boost/fusion/include/define_struct.hpp>

#include <bacnet/detail/common/types.hpp>

BOOST_FUSION_DEFINE_STRUCT(
    (bacnet)(npdu), address,
    (uint16_t, network_number)
    (bacnet::binary_data, binary_address)
)


std::ostream &operator<<(std::ostream &os, const bacnet::npdu::address &a);

#endif /* SRC_BACNET_NPDU_ADDRESS_HPP_ */
