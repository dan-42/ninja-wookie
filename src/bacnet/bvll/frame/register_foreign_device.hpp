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

#include <cstdint>
#include <boost/fusion/include/define_struct.hpp>

#include <bacnet/detail/common/types.hpp>

BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),register_foreign_device,
	(uint16_t, time_to_live_in_sec)
	(bacnet::unused_type,  unused)
)

#endif /* SRC_BACNET_BVLL_FRAME_REGISTER_FOREIGN_DEVICE_HPP_ */
