/*
 * primitive_type.hpp
 *
 *  Created on: Jun 5, 2016
 *      Author: dan
 */

#ifndef WOOKIE_BACNET_APDU_TYPE_TYPES_CONSTRUCTED_TYPE_HPP_
#define WOOKIE_BACNET_APDU_TYPE_TYPES_CONSTRUCTED_TYPE_HPP_


#include <cstdint>
#include <bacnet/apdu/type/tag.hpp>

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

struct constructed_type {
  uint8_t   tag_number_expected_{0};
  bool      is_expecting_enclosing_{false};


  constructed_type() {
  }

  constructed_type(uint8_t t) : tag_number_expected_(t),
                                is_expecting_enclosing_(true){
  }

  void check_open_tag(tag& t, bool& pass) {
    if(   is_expecting_enclosing_
       && t.is_opening_tag()
       && t.number           == tag_number_expected_ ) {
      pass = true;
    }
    else {
      pass = false;
    }
  }

  void check_close_tag(tag& t, bool& pass) {
    if(   is_expecting_enclosing_
       && t.is_closing_tag()
       && t.number         == tag_number_expected_ ) {
      pass = true;
    }
    else {
      pass = false;
    }
  }
};

}}}}}


#endif /* WOOKIE_BACNET_APDU_TYPE_TYPES_CONSTRUCTED_TYPE_HPP_ */
