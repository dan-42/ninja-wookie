/*
 * mapping.hpp
 *
 *  Created on: Jun 11, 2016
 *      Author: dan
 */

#ifndef NINJA_WOOKIE_BACNET_OBJECT_MAPPING_HPP_
#define NINJA_WOOKIE_BACNET_OBJECT_MAPPING_HPP_

#include <bacnet/type/object_identifier.hpp>
#include <bacnet/type/properties.hpp>

namespace bacnet { namespace mapping {


enum class type {
  application_tagged_type,


  null,
  boolean,
  unsigned_integer,
  signed_integer,
  real,
  double_pressision,
  octet_string,
  character_string,
  bit_string,
  enumerated,
  date,
  time,
  object_identifier,



  date_time,

  error,
  /*..*/


};



typedef std::map<uint32_t, type> property_type_map;
typedef std::map<uint32_t, property_type_map> object_property_type_map;

static type select(uint32_t object_type_id, uint32_t property_id) {
   using namespace bacnet::type;

   static object_property_type_map map;
   static type default_fallback_type{type::application_tagged_type};

   if(map.empty()) {

     map = object_property_type_map {
         std::make_pair(object_type::device, property_type_map{
             std::make_pair( bacnet::type::property::object_identifier::value,          type::object_identifier         ),
             std::make_pair( bacnet::type::property::object_name::value,                type::character_string          ),
             std::make_pair( bacnet::type::property::object_type::value,                type::enumerated                ),
             std::make_pair( bacnet::type::property::property_list::value,              type::application_tagged_type   )
            // std::make_pair( bacnet::type::property::protocol_services_supported::value,type::bit_string   )
                           }),

       std::make_pair(object_type::binary_input, property_type_map{
             std::make_pair( bacnet::type::property::object_identifier::value,          type::object_identifier         ),
             std::make_pair( bacnet::type::property::object_name::value,                type::character_string          ),
             std::make_pair( bacnet::type::property::object_type::value,                type::enumerated                ),
             std::make_pair( bacnet::type::property::property_list::value,              type::application_tagged_type   )
                            })

     };

   }

   auto it_obj = map.find(object_type_id);
   if (it_obj == map.end() ) {
     return default_fallback_type;
   }

   property_type_map& prop_map = it_obj->second;
   auto it_prop = prop_map.find(property_id);
   if (it_prop == prop_map.end() ) {
     return default_fallback_type;
   }
   return it_prop->second;

}


}}

#endif /* SRC_BACNET_OBJECT_MAPPING_HPP_ */
