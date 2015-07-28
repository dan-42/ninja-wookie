/*
 * error.hpp
 *
 *  Created on: Jul 28, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_FRAME_ERROR_HPP_
#define SRC_BACNET_APDU_FRAME_ERROR_HPP_



#include <cstdint>

#include <boost/fusion/include/define_struct.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/detail/headers.hpp>


BOOST_FUSION_DEFINE_STRUCT(
        (bacnet)(apdu)(frame), error,
        (bacnet::apdu::detail::header::pdu_type_and_control_information_t, pdu_type_and_control_information)
        (uint8_t, original_invoke_id)
        (uint8_t, error_choice)
        (bacnet::binary_data, error_data)
)



#endif /* SRC_BACNET_APDU_FRAME_ERROR_HPP_ */
