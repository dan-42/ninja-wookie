/*
 * error.hpp
 *
 *  Created on: May 21, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_ERROR_HPP_
#define SRC_BACNET_TYPE_ERROR_HPP_

#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>
#include <bacnet/type/enumerated.hpp>
#include <bacnet/error/error.hpp>

namespace bacnet { namespace type {

struct error {

  error() = default;

  error(uint32_t e_class, uint32_t e_code) : error_class(enum_class_type, e_class ), error_code(enum_code_type, e_code) {

  }

  error(enumerated e_class, enumerated e_code) : error_class(std::move(e_class) ), error_code(std::move(e_code)) {

  }

  error(bacnet::error bacnet_error) : error_class(enum_class_type,  bacnet_error.error_class.get_value_or(0)),
                                      error_code(enum_code_type,    bacnet_error.value) {

  }

  static constexpr enumerated::e enum_class_type = enumerated::e::error_class;
  static constexpr enumerated::e enum_code_type  = enumerated::e::error_code;
  enumerated error_class;
  enumerated error_code;

};


}}

BOOST_FUSION_ADAPT_STRUCT(
  bacnet::type::error,
  error_class,
  error_code
);
#endif /* SRC_BACNET_TYPE_ERROR_HPP_ */
