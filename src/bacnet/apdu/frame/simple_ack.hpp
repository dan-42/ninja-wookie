/*
 * simple_ack.hpp
 *
 *  Created on: Jul 28, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_FRAME_SIMPLE_ACK_HPP_
#define SRC_BACNET_APDU_FRAME_SIMPLE_ACK_HPP_



#include <cstdint>

#include <boost/fusion/include/define_struct.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/detail/headers.hpp>


BOOST_FUSION_DEFINE_STRUCT(
        (bacnet)(apdu)(frame), simple_ack,
        (bacnet::apdu::detail::header::pdu_type_and_control_information_t, pdu_type_and_control_information)
        (uint8_t, original_invoke_id)
        (uint8_t, service_ack_choice)
)



#endif /* SRC_BACNET_APDU_FRAME_SIMPLE_ACK_HPP_ */
