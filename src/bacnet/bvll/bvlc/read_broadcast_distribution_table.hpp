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





#ifndef SRC_BACNET_BVLL_READ_BROADCAST_DISTRIBUTION_TABLE_HPP
#define SRC_BACNET_BVLL_READ_BROADCAST_DISTRIBUTION_TABLE_HPP


#include <boost/fusion/include/define_struct.hpp>



/* not working
BOOST_FUSION_DEFINE_STRUCT(
	(bacnet)(bvll)(frame),read_broadcast_distribution_table,
)*/
namespace bacnet { namespace bvll { namespace frame {
	struct read_broadcast_distribution_table {
	};
}}}

BOOST_FUSION_ADAPT_STRUCT(
		bacnet::bvll::frame::read_broadcast_distribution_table,
)


namespace bacnet { namespace bvll { namepsace frame { namespace generator {

struct read_broadcast_distribution_table_rule

}}}}


#endif
