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

#include <bacnet/error/code.hpp>


namespace bacnet {

    class error_category :   public boost::system::error_category   {
    public:
      const char *name() const noexcept { return "bacnet"; }
      std::string message(int ev) const { return error::error_code::to_string(ev); }

      static inline std::string message(int e_code, int e_class) {
        return error::error_class::to_string(e_class) + ":" + error::error_code::to_string(e_code);
      }

    };

    //Singleton access to the category
    inline const boost::system::error_category & bacnet_category() noexcept  {
      static const error_category bacnet_category_const;
      return bacnet_category_const;
    }


    class error_code {
      public:


      error_code() noexcept : error_category_(&boost::system::system_category()) {}

      error_code(const bacnet::error_code& ec) noexcept :
                error_code_value_(ec.value()), error_category_(&ec.category()) {}
      error_code(bacnet::error_code&& ec) noexcept :
                error_code_value_(ec.value()), error_category_(&ec.category()) {}

      error_code(const boost::system::error_code& ec) noexcept :
                error_code_value_(ec.value()), error_category_(&ec.category()) {}
      error_code(boost::system::error_code&& ec) noexcept :
                error_code_value_(ec.value()), error_category_(&ec.category()) {}

      template <class ErrorCodeEnum>
      error_code(ErrorCodeEnum e,  typename boost::enable_if<boost::system::is_error_code_enum<ErrorCodeEnum> >::type* = 0) noexcept  :
                error_code_value_(e), error_category_(&boost::system::generic_category() ) {}

      template <class ErrorCodeEnum>
      error_code(ErrorCodeEnum e,  typename boost::enable_if<boost::system::is_error_condition_enum<ErrorCodeEnum> >::type* = 0) noexcept  :
                error_code_value_(e), error_category_(&boost::system::generic_category() ) {}


      error_code( int val, const boost::system::error_category & cat ) noexcept :
                error_code_value_(val), error_category_(&cat) {}
      error_code( int e_code, int e_class, const boost::system::error_category & cat ) noexcept :
                error_code_value_(e_code), error_class_value_(e_class), error_category_(&cat) {}
      error_code( int e_code, int e_class) noexcept :
                error_code_value_(e_code), error_class_value_(e_class), error_category_(&bacnet_category()) {}





      // modifiers:
      void assign( int e_code, int e_class, const boost::system::error_category & cat  ) noexcept  {
        error_code_value_   = e_code;;
        error_class_value_  = e_class;
        error_category_     = &cat;
      }

      void clear() noexcept {
        error_code_value_   = 0;
        error_class_value_  = 0;
        error_category_     = &boost::system::system_category();
      }


      int                     code() const  noexcept          { return error_code_value_; }
      int                     value() const  noexcept         { return error_code_value_; }
      int                     error_class() const  noexcept   { return error_class_value_; }
      const boost::system::error_category &  category() const noexcept { return *error_category_; }

      std::string             message() const  {
        if(error_category_ == &bacnet_category() ) {
          return error_category::message(code(), error_class());
        }
        else {
          return error_category_->message(code());
        }
      }


      BOOST_EXPLICIT_OPERATOR_BOOL()
      //BOOST_CONSTEXPR_EXPLICIT_OPERATOR_BOOL()

      bool operator!() const  noexcept { // true if no error
        if(    (error_category_ == &bacnet_category() &&  error_code_value_ == error::error_code::success)
            || (error_category_ != &bacnet_category() &&  error_code_value_ == 0)  ) {
          return true;
        }
        else {
          return false;
        }
      }


      inline friend bool operator==( const error_code & lhs, const error_code & rhs ) noexcept {
        return    lhs.error_category_ == rhs.error_category_
            &&  lhs.error_code_value_ == rhs.error_code_value_
            && lhs.error_class_value_ == rhs.error_class_value_;
      }

      inline friend bool operator<( const error_code & lhs, const error_code & rhs ) noexcept {
        return    lhs.error_category_ < rhs.error_category_
              || (lhs.error_category_ == rhs.error_category_ && lhs.error_class_value_ < rhs.error_class_value_)
              || (lhs.error_category_ == rhs.error_category_ && lhs.error_class_value_ == rhs.error_class_value_ && lhs.error_code_value_ < rhs. error_code_value_);
      }

    private:
      int                                   error_code_value_{0};
      int                                   error_class_value_{0};
      const boost::system::error_category * error_category_;

    };





    //  non-member functions  ------------------------------------------------//
    inline bool operator!=( const error_code & lhs, const error_code & rhs ) noexcept {
      return !(lhs == rhs);
    }

    template <class charT, class traits>
    inline std::basic_ostream<charT,traits>& operator<< (std::basic_ostream<charT,traits>& os, error_code ec) {
      os << ec.category().name() << ':' << ec.message();
      return os;
    }

    inline std::size_t hash_value( const error_code & ec ) {
      return static_cast<std::size_t>(ec.code()) + static_cast<std::size_t>(ec.error_class()) + reinterpret_cast<std::size_t>(&ec.category());
    }

    inline error_code make_error_code( int c, int e ) noexcept {
       return error_code( e, c, bacnet::bacnet_category() );
    }


} // namespace bacnet



#endif //NINJA_WOOKIE_BACNET_ERROR_ERROR_HPP
