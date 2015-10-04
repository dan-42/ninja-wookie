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


#ifndef NINJA_WOOKIE_BACNET_APDU_TYPE_OBJECT_IDENTIFIER_HPP
#define NINJA_WOOKIE_BACNET_APDU_TYPE_OBJECT_IDENTIFIER_HPP


#include <cstdint>
#include <boost/fusion/include/define_struct.hpp>
#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/common/object_identifier.hpp>


BOOST_FUSION_DEFINE_STRUCT(
    (bacnet)(apdu)(type), object_identifier,
    (bacnet::apdu::type::tag, tag_)
    (bacnet::common::object_identifier, object_identifier_)
)

namespace bacnet { namespace apdu { namespace type {

static inline std::ostream& operator<<(std::ostream& os, const object_identifier &oi) {
    os << " tag: "   << std::dec << oi.tag_
    << " object_identifier: " << std::dec << oi.object_identifier_;
    return os;
}

}}}



#endif //NINJA_WOOKIE_BACNET_APDU_TYPE_OBJECT_IDENTIFIER_HPP
