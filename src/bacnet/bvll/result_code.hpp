/*
 * result_code.hpp
 *
 *  Created on: May 16, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_BVLL_BVLC_RESULT_CODE_HPP_
#define SRC_BACNET_BVLL_BVLC_RESULT_CODE_HPP_

#include <iostream>
#include <cstdint>

namespace bacnet { namespace bvll {

/**
 *  having  this as enum class would be create,
 *  but I cant parse  an uint16_t with spirit::big_word to an enum class,
 *  a enum class with char works somehow,
 *  src: http://stackoverflow.com/questions/25175629/parse-enum-using-boost-spirit-qi-parser
 */
namespace result_code   {
	constexpr uint16_t successful_completion									=	0x0000;
	constexpr uint16_t write_broadcast_distribution_table_nak	= 0x0010;
	constexpr uint16_t read_broadcast_distribution_table_nak	= 0x0020;
	constexpr uint16_t register_foreign_device_nak						= 0x0030;
	constexpr uint16_t read_foreign_device_table_nak					= 0x0040;
	constexpr uint16_t delete_foreign_device_table_entry_nak	= 0x0050;
	constexpr uint16_t distribute_broadcast_to_network_nak		= 0x0060;

	static std::ostream &operator<<(std::ostream &os, const uint16_t &rc);
}

}}

#include <bacnet/bvll/impl/result_code.ipp>

#endif /* SRC_BACNET_BVLL_BVLC_RESULT_CODE_HPP_ */
