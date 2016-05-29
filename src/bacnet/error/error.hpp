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


    class error {
      public:


      error() noexcept : category_(&boost::system::system_category()) {}

      error(const bacnet::error& ec) noexcept :
                value_(ec.value()), e_class_(ec.error_class()), category_(&ec.category()) {}

      error(bacnet::error&& ec) noexcept :
                value_(ec.value()),  e_class_(ec.error_class()),category_(&ec.category()) {}

      error(const boost::system::error_code& ec) noexcept :
                value_(ec.value()), category_(&ec.category()) {}
      error(boost::system::error_code&& ec) noexcept :
                value_(ec.value()), category_(&ec.category()) {}

      template <class ErrorCodeEnum>
      error(ErrorCodeEnum e,  typename boost::enable_if<boost::system::is_error_code_enum<ErrorCodeEnum> >::type* = 0) noexcept  :
                value_(e), category_(&boost::system::generic_category() ) {}

      template <class ErrorCodeEnum>
      error(ErrorCodeEnum e,  typename boost::enable_if<boost::system::is_error_condition_enum<ErrorCodeEnum> >::type* = 0) noexcept  :
                value_(e), category_(&boost::system::generic_category() ) {}


      error( int val, const boost::system::error_category & cat ) noexcept :
                value_(val), category_(&cat) {}
      error( int e_code, int e_class, const boost::system::error_category & cat ) noexcept :
                value_(e_code), e_class_(e_class), category_(&cat) {}
      error( int e_code, int e_class) noexcept :
                value_(e_code), e_class_(e_class), category_(&bacnet_error_category()) {}



      int code() const  noexcept {
        return value_;
      }
      int value() const  noexcept {
        return value_;
      }
      int error_class() const  noexcept {
        return e_class_;
      }
      const boost::system::error_category& category() const noexcept {
        return *category_;
      }


      std::string message() const  {
        if(category_ == &bacnet_error_category() ) {
          return error_category::message(code(), error_class());
        }
        else {
          return category_->message(code());
        }
      }


      BOOST_EXPLICIT_OPERATOR_BOOL()

      bool operator!() const  noexcept { // true if no error
        if(    (category_ == &bacnet_error_category() &&  value_ == err::error_code::success)
            || (category_ != &bacnet_error_category() &&  value_ == 0)  ) {
          return true;
        }
        else {
          return false;
        }
      }


      inline friend bool operator==( const error & lhs, const error & rhs ) noexcept {
        return lhs.category_ == rhs.category_
            && lhs.value_    == rhs.value_
            && lhs.e_class_  == rhs.e_class_;
      }

      inline friend bool operator<( const error & lhs, const error & rhs ) noexcept {
        return    lhs.category_ < rhs.category_
              || (lhs.category_ == rhs.category_ && lhs.e_class_ < rhs.e_class_)
              || (lhs.category_ == rhs.category_ && lhs.e_class_ == rhs.e_class_ && lhs.value_ < rhs.value_);
      }

    private:
      int                                   value_{0};
      int                                   e_class_{0};
      const boost::system::error_category * category_;

    };





    //  non-member functions  ------------------------------------------------//
    inline bool operator!=( const error & lhs, const error & rhs ) noexcept {
      return !(lhs == rhs);
    }

    template <class charT, class traits>
    inline std::basic_ostream<charT,traits>& operator<< (std::basic_ostream<charT,traits>& os, error ec) {
      os << ec.category().name() << ':' << ec.message();
      return os;
    }

    inline std::size_t hash_value( const error & ec ) {
      return static_cast<std::size_t>(ec.code()) + static_cast<std::size_t>(ec.error_class()) + reinterpret_cast<std::size_t>(&ec.category());
    }

    inline error make_error( int c, int e ) noexcept {
       return error( e, c, bacnet::bacnet_error_category() );
    }

    inline error make_reject_reason( err::reject_reason::reject_reason_type reason ) noexcept {
       return error( reason, 0, bacnet::bacnet_reject_category() );
    }

    inline error make_abort_reason( err::abort_reason::abort_reason_type reason ) noexcept {
       return error( reason, 0, bacnet::bacnet_abort_category() );
    }


} // namespace bacnet



#endif //NINJA_WOOKIE_BACNET_ERROR_ERROR_HPP
