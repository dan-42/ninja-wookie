/*
 * object_property_reference.hpp
 *
 *  Created on: May 30, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_OBJECT_PROPERTY_REFERENCE_HPP_
#define SRC_BACNET_TYPE_OBJECT_PROPERTY_REFERENCE_HPP_


#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/optional.hpp>
#include <bacnet/type/object_identifier.hpp>
#include <bacnet/type/enumerated.hpp>


namespace bacnet { namespace type {


  struct object_property_reference {

	  object_property_reference() = default;

	  type::object_identifier 	object_identifier;
	  type::enumerated			    propetry_identifier;
	  boost::optional<uint32_t> array_index;
  };

}}

BOOST_FUSION_ADAPT_STRUCT(
    bacnet::type::object_property_reference,
	object_identifier,
	propetry_identifier,
	array_index
);

namespace bacnet { namespace type {


  static std::ostream& operator<<(std::ostream& os, const object_property_reference& v) {

    return os;
  }

}}


#endif /* SRC_BACNET_TYPE_OBJECT_PROPERTY_REFERENCE_HPP_ */
