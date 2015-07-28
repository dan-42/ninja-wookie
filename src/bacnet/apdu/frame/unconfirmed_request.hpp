/*
 * unconfirmed_request.hpp
 *
 *  Created on: Jul 28, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_FRAME_UNCONFIRMED_REQUEST_HPP_
#define SRC_BACNET_APDU_FRAME_UNCONFIRMED_REQUEST_HPP_



#include <cstdint>

#include <boost/fusion/include/define_struct.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/detail/headers.hpp>

//using namespace bacnet::apdu::detail::header;

BOOST_FUSION_DEFINE_STRUCT(
        (bacnet)(apdu)(frame), unconfirmed_request,
        (bacnet::apdu::detail::header::pdu_type_and_control_information_t, pdu_type_and_control_information)
        (uint8_t, service_choice)
        (bacnet::binary_data, service_data)
)


#endif /* SRC_BACNET_APDU_FRAME_UNCONFIRMED_REQUEST_HPP_ */
