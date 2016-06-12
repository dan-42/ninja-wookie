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
 *
 * bacnet::error_code based on boost::system::error_code
 *
 */

#ifndef NINJA_WOOKIE_BACNET_ERROR_ERROR_HPP
#define NINJA_WOOKIE_BACNET_ERROR_ERROR_HPP



#include <string>
#include <iostream>
#include <stdexcept>


#include <boost/core/explicit_operator_bool.hpp>
#include <boost/system/error_code.hpp>


#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/utility/enable_if.hpp>


#include <bacnet/error/error_class.hpp>
#include <bacnet/error/error_code.hpp>
#include <bacnet/error/category.hpp>

#include <bacnet/type/object_property_reference.hpp>
#include <bacnet/type/confirmed_private_transfer_error.hpp>
/**
 * bacnet::error  combines all kind of error messages in one class. it also can transform boost::system::error_co* into bacnet::error.
 *
 * As BACnet has three main frames for sending errors APDU-Error, APDU-Reject, APDU-Abort.
 * As all frames can contain the same kind( NOT VALUE!) of message so they are
 * merged into one for convenience
 *
 *
 * Categories:
 *   boost::system::*_category()
 *
 *   bacnet::reject_category
 *   bacnet::abort_category
 *
 *   bacnet::error_category,
 *   bacnet::change_list_error_category
 *   bacnet::create_object_error_category
 *   bacnet::write_property_multiple_error_category
 *   bacnet::confirmed_private_transfer_error_category
 *   bacnet::vt_close_error
 *
 *
 *
 *
 *
 * as JSON the format looks basically like this
 * {
 *    "error": {
 *      "category":       "bacnet::error",
 *      "value":          1337,
 *
 *      // optional depending on category
 *      "e_class":    42,
 *
 *    
 *      "first_failed_element_number": 1,
 *      
 *      
 *      "first_failed_write_attempt": {object_id, prop_id, index}, //object_property_reference
 *      
 *      
 *    
 *      "confirmed_private_transfer_error_": {vendor, service, data} ,//confirmed_private_transfer_error_t 
 *  
 *  
 *      "list_Of_vt_session_identifiers": [1,2,3]
 *  
 *    }
 * }
 *
 *
 */
namespace bacnet {

namespace err  {
//categories
enum class cat {
  system,
  generic,

  error,
  abort,
  reject,

  change_list,
  create_object,
  write_property_multiple,
  confirmed_private_transfer,
  vt_close
};


namespace detail {
  inline  err::cat cat_from_boost_system(const boost::system::error_category & c) {
      if(&c == &boost::system::system_category())  { return err::cat::system;  }
      return err::cat::generic;
    }
  } //detail
} //err


class error {
public:

  /// CONSTRUCTOR
  error()                                                                                                                noexcept  {}
  error(int v)                                                                                                           noexcept :
      value(v) {}
  error(err::cat c, int v)                                                                                               noexcept :
      category(c), value(v) {}
  error(err::cat c, int v, int class_)                                                                                   noexcept :
      category(c), value(v), error_class(class_) {}
  error( int v, int class_)                                                                                              noexcept :
        category(err::cat::error), value(v), error_class(class_) {}
  error(err::cat c, int v, int class_, uint32_t first_failed_element_number_)                                            noexcept :
      category(c), value(v), error_class(class_), first_failed_element_number(first_failed_element_number_) {}
  error(err::cat c, int v, int class_, bacnet::type::object_property_reference first_failed_write_attempt_)              noexcept :
      category(c), value(v), error_class(class_), first_failed_write_attempt(first_failed_write_attempt_) {}
  error(err::cat c, int v, int class_, bacnet::type::confirmed_private_transfer_error confirmed_private_transfer_error_) noexcept :
      category(c), value(v), error_class(class_), confirmed_private_transfer_error(confirmed_private_transfer_error_) {}
  error(err::cat c, int v, int class_, std::vector<uint8_t> list_of_vt_session_identifiers_)                             noexcept :
      category(c), value(v), error_class(class_), list_of_vt_session_identifiers(list_of_vt_session_identifiers_) {}

  /// CONSTRUCTOR FOR BOOST_SYSTEM
  template <class ErrorCodeEnum>
  error(ErrorCodeEnum e,  typename boost::enable_if<boost::system::is_error_code_enum<ErrorCodeEnum> >::type* = 0) noexcept      : category(err::cat::generic ), value(e) {}

  template <class ErrorCodeEnum>
  error(ErrorCodeEnum e,  typename boost::enable_if<boost::system::is_error_condition_enum<ErrorCodeEnum> >::type* = 0) noexcept : category(err::cat::generic ), value(e) {}


  template <class ErrorCodeEnum>
  error(ErrorCodeEnum e, const boost::system::error_category& c,  typename boost::enable_if<boost::system::is_error_code_enum<ErrorCodeEnum> >::type* = 0) noexcept      :
      category(err::detail::cat_from_boost_system( c ) ), value(e) {}

  template <class ErrorCodeEnum>
  error(ErrorCodeEnum e, const boost::system::error_category& c,  typename boost::enable_if<boost::system::is_error_condition_enum<ErrorCodeEnum> >::type* = 0) noexcept :
      category(err::detail::cat_from_boost_system( c ) ), value(e) {}


  error(const boost::system::error_code& ec)  noexcept :  category(err::detail::cat_from_boost_system( ec.category() ) ), value(ec.value()) {}
  error(boost::system::error_code&& ec)       noexcept :  category(err::detail::cat_from_boost_system( ec.category() ) ), value(ec.value()) {}




  /// OPERATORS
  BOOST_EXPLICIT_OPERATOR_BOOL()
  inline bool operator!() const  noexcept { // true if no error
    if(    (category == err::cat::error    &&  value == bacnet::err::error_code::success)
        || (category != err::cat::system   &&  value == 0)
        || (category != err::cat::generic  &&  value == 0) ) {
      return true;
    }
    else {
      return false;
    }
  }

  inline friend bool operator==( const error & lhs, const error & rhs ) noexcept {
    return lhs.category       == rhs.category
        && lhs.value          == rhs.value
        && lhs.error_class    == rhs.error_class;
  }

  inline friend bool operator<( const error & lhs, const error & rhs ) noexcept {
    return    lhs.category < rhs.category
          || (lhs.category == rhs.category && lhs.error_class < rhs.error_class)
          || (lhs.category == rhs.category && lhs.error_class == rhs.error_class && lhs.value < rhs.value);
  }

  /// OUTPUTS
  inline std::string message() const {
    if(category == err::cat::system                      ) {   return err::system::message(value);                             }
    if(category == err::cat::generic                     ) {   return err::generic::message(value);                            }
    if(category == err::cat::abort                       ) {   return err::abort::message(value);                              }
    if(category == err::cat::reject                      ) {   return err::reject::message(value);                             }
    if(category == err::cat::error                       ) {   return err::error::message(value, error_class.get_value_or(0)); }
    if(category == err::cat::change_list                 ) {   return err::change_list::message(value, error_class.get_value_or(0)); }
    if(category == err::cat::create_object               ) {   return err::create_object::message(value, error_class.get_value_or(0)); }
    if(category == err::cat::write_property_multiple     ) {   return err::write_property_multiple::message(value, error_class.get_value_or(0)); }
    if(category == err::cat::confirmed_private_transfer  ) {   return err::confirmed_private_transfer::message(value, error_class.get_value_or(0)); }
    if(category == err::cat::vt_close                    ) {   return err::vt_close::message(value, error_class.get_value_or(0)); }
    return "";
  }

//private:
  /// MEMBER
  err::cat category{err::cat::generic};
  int value{0};

  boost::optional<uint32_t>                                       error_class;
  boost::optional<uint32_t>                                       first_failed_element_number;
  boost::optional<bacnet::type::object_property_reference>        first_failed_write_attempt;
  boost::optional<bacnet::type::confirmed_private_transfer_error> confirmed_private_transfer_error;
  boost::optional<std::vector<uint8_t> >                          list_of_vt_session_identifiers;
};

} //bacnet

BOOST_FUSION_ADAPT_STRUCT( bacnet::error,
  category,
  value,
  error_class,
  first_failed_element_number,
  first_failed_write_attempt,
  confirmed_private_transfer_error,
  list_of_vt_session_identifiers
);

namespace bacnet {

  //  non-member functions  ------------------------------------------------//
  inline bool operator!=( const error & lhs, const error & rhs ) noexcept {
    return !(lhs == rhs);
  }

  template <class charT, class traits>
  inline std::basic_ostream<charT,traits>& operator<< (std::basic_ostream<charT,traits>& os, error ec) {
    os << ec.message();
    return os;
  }

  static inline std::size_t hash_value( const error & ec ) {
    //  return static_cast<std::size_t>(ec.) + static_cast<std::size_t>(ec.error_class()) + reinterpret_cast<std::size_t>(&ec.category());
    return 0;
  }

  static inline error make_success( ) noexcept {
    return error{};
  }
  static inline error make_error( int e, int c ) noexcept {
     return error(err::cat::error, e, c);
  }

  static inline error make_reject_reason( err::reject_reason::reject_reason_type reason ) noexcept {
     return error(err::cat::reject, reason );
  }

  static inline error make_abort_reason( err::abort_reason::abort_reason_type reason ) noexcept {
     return error(err::cat::abort, reason);
  }


} // bacnet



#endif //NINJA_WOOKIE_BACNET_ERROR_ERROR_HPP
