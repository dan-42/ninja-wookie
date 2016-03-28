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


#ifndef SRC_BACNET_BVLL_FOREIGN_DEVICE_TABLE_HPP_
#define SRC_BACNET_BVLL_FOREIGN_DEVICE_TABLE_HPP_

#include <bacnet/bvll/common/foreign_device_table_entry.hpp>

// xxx put it into a Fusion struct as well?
namespace bacnet { namespace bvll {
typedef std::vector<bacnet::bvll::foreign_device_table_entry> foreign_device_table;
}}

namespace bacnet { namespace bvll { namespace generator {

bool generate(bacnet::binary_data &c, foreign_device_table &v);

}}}

namespace bacnet { namespace bvll { namespace parser {

bool parse(bacnet::binary_data &i, foreign_device_table &v);

}}}


#endif /* SRC_BACNET_BVLL_FOREIGN_DEVICE_TABLE_HPP_ */
