/*
 * types.hpp
 *
 *  Created on: May 14, 2016
 *      Author: dan
 */

#ifndef NINJA_WOOKIE_BACNET_TYPE_TYPES_HPP_
#define NINJA_WOOKIE_BACNET_TYPE_TYPES_HPP_

#include <bacnet/type/null.hpp>
#include <bacnet/type/boolean.hpp>
#include <bacnet/type/unsigned_integer.hpp>
#include <bacnet/type/signed_integer.hpp>
#include <bacnet/type/real.hpp>

#include <bacnet/type/octet_string.hpp>
#include <bacnet/type/character_string.hpp>
#include <bacnet/type/bit_string.hpp>
#include <bacnet/type/enumerated.hpp>
#include <bacnet/type/date.hpp>
#include <bacnet/type/time.hpp>
#include <bacnet/type/object_identifier.hpp>


namespace bacnet { namespace type {


/**
 * Sequence Of, means all types must be the same
 * and is the underlying type of BACnetList and BACnetArray
 *
 */
template<typename T>
struct sequence_of {
  std::vector<T> value;
};


//typedef boost::variant<
typedef boost::make_recursive_variant<
    null,
    boolean,
    unsigned_integer,
    signed_integer,
    real,
    double,
    octet_string,
    character_string,
    bit_string,
    enumerated,
    date,
    time,
    object_identifier,

    sequence_of<boost::recursive_variant_ >

                        > possible_type;


struct sequence {
  std::vector<possible_type> value;
};


struct choice {
  possible_type value;
};




}}


#endif /* SRC_BACNET_TYPE_TYPES_HPP_ */
