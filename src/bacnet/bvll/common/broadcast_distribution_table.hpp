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


#ifndef SRC_BACNET_BVLL_BROADCAST_DISTRIBUTION_TABLE_HPP_
#define SRC_BACNET_BVLL_BROADCAST_DISTRIBUTION_TABLE_HPP_


#include <vector>
#include <bacnet/detail/common/types.hpp>
#include <bacnet/bvll/common/broadcast_distribution_table_entry.hpp>

namespace bacnet { namespace bvll {
	typedef std::vector<bacnet::bvll::broadcast_distribution_table_entry> broadcast_distribution_table;
}}

namespace bacnet { namespace bvll { namespace generator {
  bool generate(bacnet::binary_data &c, broadcast_distribution_table &v);
}}}


namespace bacnet { namespace bvll { namespace parser {
  bool parse(bacnet::binary_data &i, broadcast_distribution_table &v);
}}}

#endif /* SRC_BACNET_BVLL_BROADCAST_DISTRIBUTION_TABLE_HPP_ */
