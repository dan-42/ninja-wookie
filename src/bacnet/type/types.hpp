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
// double
#include <bacnet/type/octet_string.hpp>
#include <bacnet/type/character_string.hpp>
#include <bacnet/type/bit_string.hpp>
#include <bacnet/type/enumerated.hpp>
#include <bacnet/type/date.hpp>
#include <bacnet/type/time.hpp>
#include <bacnet/type/object_identifier.hpp>
#include <bacnet/type/unsupported_type.hpp>
#include <util/boost/spirit/unused_type.hpp>

// enumerated values
#include <bacnet/type/device_status.hpp>
#include <bacnet/type/object_type.hpp>
#include <bacnet/type/property_identifier.hpp>
#include <bacnet/type/restart_reason.hpp>
#include <bacnet/type/segmentation.hpp>
#include <bacnet/type/vt_class.hpp>
#include <bacnet/type/backup_state.hpp>


// bit_string based types
#include <bacnet/type/services_supported.hpp>

namespace bacnet { namespace type {



struct constructed_type;


typedef boost::make_recursive_variant<
    std::vector< boost::recursive_variant_>,
    boost::recursive_wrapper< constructed_type >,

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

    unsupported_type
    > ::type
possible_type;


struct constructed_type {
   uint8_t tag_number{0};
   std::vector< possible_type> value ;
 };


}}


BOOST_FUSION_ADAPT_STRUCT(
  bacnet::type::constructed_type,
  tag_number,
  value
);



#endif /* SRC_BACNET_TYPE_TYPES_HPP_ */
