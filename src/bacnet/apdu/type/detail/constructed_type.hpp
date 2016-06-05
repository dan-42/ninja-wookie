/*
 * primitive_type.hpp
 *
 *  Created on: Jun 5, 2016
 *      Author: dan
 */

#ifndef TEST_UNIT_TESTS_BACNET_APDU_TYPES_CONSTRUCTED_TYPE_HPP_
#define TEST_UNIT_TESTS_BACNET_APDU_TYPES_CONSTRUCTED_TYPE_HPP_


#include <cstdint>
#include <bacnet/apdu/type/tag.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using bacnet::apdu::type::application_tag;

struct constructed_type {
  uint8_t   tag_number_expected_{0};
  bool      is_expecting_context_tag_{false};
  bool      is_expecting_enclosing_{false};


  constructed_type() {
  }

  constructed_type(uint8_t t) : tag_number_expected_(t),
                                is_expecting_context_tag_(true),
                                is_expecting_enclosing_(true){
  }

  void check_open_tag(tag& t, bool& pass) {
    if(   is_expecting_enclosing_
       && t.is_opening_tag()
       && t.is_context_tag() == is_expecting_context_tag_
       && t.number()         == tag_number_expected_ ) {
      pass = true;
    }
    else {
      pass = false;
    }
  }

  void check_close_tag(tag& t, bool& pass) {
    if(   is_expecting_enclosing_
       && t.is_closing_tag()
       && t.is_context_tag() == is_expecting_context_tag_
       && t.number()         == tag_number_expected_ ) {
      pass = true;
    }
    else {
      pass = false;
    }
  }
};

}}}}}


#endif /* TEST_UNIT_TESTS_BACNET_APDU_TYPES_PRIMITIVE_TYPE_HPP_ */
