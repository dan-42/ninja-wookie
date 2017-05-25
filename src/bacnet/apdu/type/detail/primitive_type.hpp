/*
 * primitive_type.hpp
 *
 *  Created on: Jun 5, 2016
 *      Author: dan
 */

#ifndef WOOKIE_BACNET_APDU_TYPE_DETAIL_PARSER_PRIMITIVE_TYPE_HPP_
#define WOOKIE_BACNET_APDU_TYPE_DETAIL_PARSER_PRIMITIVE_TYPE_HPP_


#include <cstdint>
#include <bacnet/apdu/type/tag.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using bacnet::apdu::type::application_tag;

struct primitive_type {
  uint32_t  length_value_type_{0};
  uint8_t   tag_number_expected_{0};
  bool      is_expecting_context_tag_{false};


  primitive_type(application_tag t) : tag_number_expected_(static_cast<decltype(tag_number_expected_)>(t)) {
  }

  primitive_type(uint8_t t) : tag_number_expected_(static_cast<decltype(tag_number_expected_)>(t)), is_expecting_context_tag_(true) {
  }


  void extract_size_and_check_tag(tag& t, bool& pass) {
    if(   t.is_context_tag()    == is_expecting_context_tag_
       && t.number              == tag_number_expected_ ) {
      length_value_type_ =  t.length_value_type;
      pass = true;
    }
    else {
      pass = false;
    }
  }

  void extract_size_check_tag_and_add_offset(tag& t, bool& pass, uint32_t diff) {
    extract_size_and_check_tag(t, pass);
    if(pass) {
      length_value_type_ = length_value_type_ + diff;
    }
  }

  void check_tag(tag& t, bool& pass) {
    if(   t.is_context_tag()    == is_expecting_context_tag_
       && t.number              == tag_number_expected_
       && t.length_value_type   == length_value_type_) {
      pass = true;
    }
    else {
      pass = false;
    }
  }
};

}}}}}


#endif /* WOOKIE_BACNET_APDU_TYPE_DETAIL_PARSER_PRIMITIVE_TYPE_HPP_ */
