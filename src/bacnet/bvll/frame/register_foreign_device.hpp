/**
 * ninja-wooki, is a BACnet stack C++ library
 *
 * Copyright (C) 2015 Daniel Friedrich
 *
 * This file is part of ninja-wooki.
 *
 * ninja-wooki is free software: you can redistribute it and/or modify it under the terms of the
 * GNU General Public License as published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * ninja-wooki is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * See the GNU General Public License for more details. You should have received a copy of the GNU
 * General Public License along with Mupen64PlusAE. If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Daniel Friedrich
 */


#ifndef SRC_BACNET_BVLL_FRAME_REGISTER_FOREIGN_DEVICE_HPP_
#define SRC_BACNET_BVLL_FRAME_REGISTER_FOREIGN_DEVICE_HPP_


#include <utility>
#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>
#include <util/boost/spirit/unused_type.hpp>

namespace bacnet { namespace bvll { namespace frame {
struct register_foreign_device {
	explicit register_foreign_device(uint16_t d) : time_to_live_in_sec(std::move(d))  { }
	register_foreign_device() = default;

	uint16_t time_to_live_in_sec;
	unused_t unused;
};
}}}

BOOST_FUSION_ADAPT_STRUCT(
		bacnet::bvll::frame::register_foreign_device,
		(uint16_t, time_to_live_in_sec)
		(unused_t, unused)
)

#endif /* SRC_BACNET_BVLL_FRAME_REGISTER_FOREIGN_DEVICE_HPP_ */
