/*
 * types.hpp
 *
 *  Created on: May 14, 2016
 *      Author: dan
 */

#ifndef NINJA_WOOKIE_BACNET_TYPE_TYPES_HPP_
#define NINJA_WOOKIE_BACNET_TYPE_TYPES_HPP_

#include <boost/fusion/include/adapt_struct.hpp>

#include <bacnet/type/null.hpp>
#include <bacnet/type/boolean.hpp>
#include <bacnet/type/unsigned_integer.hpp>
#include <bacnet/type/signed_integer.hpp>
#include <bacnet/type/real.hpp>
//#include <bacnet/type/double_presision.hpp>
#include <bacnet/type/octet_string.hpp>
#include <bacnet/type/character_string.hpp>
#include <bacnet/type/bit_string.hpp>
#include <bacnet/type/enumerated.hpp>
#include <bacnet/type/date.hpp>
#include <bacnet/type/time.hpp>
#include <bacnet/type/object_identifier.hpp>
#include <util/boost/spirit/unused_type.hpp>

namespace bacnet { namespace type {


/**
 * Sequence Of, means all types must be the same
 * and is the underlying type of BACnetList and BACnetArray
 *
 */

struct sequence;

typedef boost::variant<
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

    boost::recursive_wrapper<sequence>

                        > possible_type;

struct sequence {
    std::vector<possible_type> values;
    unused_t unused;
};

//>::type possible_type;


/*
struct sequence {
  std::vector<possible_primitive_type> value;
};





typedef boost::variant <
                          possible_primitive_type,
                          boost::recursive_wrapper<sequence>
    > possible_type;








struct choice {
  possible_primitive_type value;
};
*/

}}










BOOST_FUSION_ADAPT_STRUCT(
  bacnet::type::sequence,
  values,
  unused
);



#endif /* SRC_BACNET_TYPE_TYPES_HPP_ */
