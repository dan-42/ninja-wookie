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

#ifndef SRC_BACNET_APDU_DETAIL_GRAMMAR_HPP_
#define SRC_BACNET_APDU_DETAIL_GRAMMAR_HPP_


#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/frame/frames.hpp>

namespace bacnet { namespace apdu { namespace frame { namespace generator {

bacnet::binary_data generate(const apdu::frame::possible_frame &f);

}}}}


namespace bacnet { namespace apdu { namespace frame { namespace parser {

apdu::frame::possible_frame parse(const bacnet::binary_data &data);

}}}}




#endif /* SRC_BACNET_APDU_DETAIL_GRAMMAR_HPP_ */
