//
// Created by dan on 30.01.16.
//


//  boost/system/error_code.hpp  ---------------------------------------------//

//  Copyright Beman Dawes 2006, 2007
//  Copyright Christoper Kohlhoff 2007

//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See library home page at http://www.boost.org/libs/system

#ifndef NINJA_WOOKIE_BACNET_ERROR_ERROR_HPP
#define NINJA_WOOKIE_BACNET_ERROR_ERROR_HPP


/*
#include <string>
#include <iostream>
#include <stdexcept>
#include <functional>



#include <bacnet/error/code.hpp>

#include <boost/cstdint.hpp>
#include <boost/assert.hpp>
#include <boost/noncopyable.hpp>
#include <boost/utility/enable_if.hpp>


namespace bacnet { namespace error  {

    class error_code;
    class error_condition;

    //  "Concept" helpers  ---------------------------------------------------//
    template< class T >
    struct is_error_code_enum {
      static const bool value = false;
    };

    template< class T >
    struct is_error_class_enum {
      static const bool value = false;
    };

    template<>
    struct is_error_condition_enum<error_code::errc_t> {
      static const bool value = true;
    };

    template<>
    struct is_error_class_enum<error_class::errc_t > {
      static const bool value = true;
    };


    //  class error_category  ------------------------------------------------//
    class error_category : public noncopyable   {
    public:
      virtual ~error_category(){}

      virtual const char *     name() const noexcept = 0;
      virtual std::string      message( int ev ) const = 0;

      bool operator==(const error_category & rhs) const noexcept {
        return this == &rhs;
      }

      bool operator!=(const error_category & rhs) const noexcept {
        return this != &rhs;
      }

      bool operator<( const error_category & rhs ) const noexcept {
        return std::less<const error_category*>()( this, &rhs );
      }
    };

    //  predefined error categories  -----------------------------------------//

    inline const error_category &  system_category() noexcept;
    inline const error_category &  generic_category() noexcept;



    class error_code {
    public:

      // constructors:
      error_code() noexcept : m_val(0), m_cat(&system_category()) {}
      error_code( int val, const error_category & cat ) noexcept : m_val(val), m_cat(&cat) {}

      template <class ErrorCodeEnum>
      error_code(ErrorCodeEnum e, typename boost::enable_if<is_error_code_enum<ErrorCodeEnum> >::type* = 0) noexcept  {
        *this = make_error_code(e);
      }

      // modifiers:
      void assign( int val, const error_category & cat ) noexcept  {
        m_val = val;
        m_cat = &cat;
      }

      template<typename ErrorCodeEnum>
      typename boost::enable_if<is_error_code_enum<ErrorCodeEnum>, error_code>::type & operator=( ErrorCodeEnum val ) noexcept {
        *this = make_error_code(val);
        return *this;
      }

      void clear() noexcept {
        m_val = 0;
        m_cat = &system_category();
      }

      // observers:
      int                     value() const  noexcept   { return m_val; }
      const error_category &  category() const noexcept { return *m_cat; }
      error_condition         default_error_condition() const noexcept  { return m_cat->default_error_condition(value()); }
      std::string             message() const  { return m_cat->message(value()); }

      typedef void (*unspecified_bool_type)();
      static void unspecified_bool_true() {}

      operator unspecified_bool_type() const  noexcept { // true if error
        return m_val == 0 ? 0 : unspecified_bool_true;
      }

      bool operator!() const  noexcept { // true if no error
        return m_val == 0;
      }

      // relationals:
      inline friend bool operator==( const error_code & lhs, const error_code & rhs ) noexcept {
        //  the more symmetrical non-member syntax allows enum
        //  conversions work for both rhs and lhs.
        return lhs.m_cat == rhs.m_cat && lhs.m_val == rhs.m_val;
      }

      inline friend bool operator<( const error_code & lhs, const error_code & rhs ) noexcept {
        //  the more symmetrical non-member syntax allows enum
        //  conversions work for both rhs and lhs.
        return lhs.m_cat < rhs.m_cat   || (lhs.m_cat == rhs.m_cat && lhs.m_val < rhs.m_val);
      }

    private:
      int                     m_val;
      const error_category *  m_cat;

    };


    typedef extern error_code throws;


    //  Moving from a "throws" object to a "throws" function without breaking
    //  existing code is a bit of a problem. The workaround is to place the
    //  "throws" function in namespace boost rather than namespace boost::system.

  }  // namespace error

  namespace detail {
    inline error::error_code * throws() {
      return 0;
    }
  }
    //  Misuse of the error_code object is turned into a noisy failure by
    //  poisoning the reference. This particular implementation doesn't
    //  produce warnings or errors from popular compilers, is very efficient
    //  (as determined by inspecting generated code), and does not suffer
    //  from order of initialization problems. In practice, it also seems
    //  cause user function error handling implementation errors to be detected
    //  very early in the development cycle.
  inline error::error_code & throws() {
      return *detail::throws();
  }

  namespace error {

    //  non-member functions  ------------------------------------------------//
    inline bool operator!=( const error_code & lhs, const error_code & rhs ) noexcept {
      return !(lhs == rhs);
    }

    template <class charT, class traits>
    inline std::basic_ostream<charT,traits>& operator<< (std::basic_ostream<charT,traits>& os, error_code ec) {
      os << ec.category().name() << ':' << ec.value();
      return os;
    }

    inline std::size_t hash_value( const error_code & ec ) {
      return static_cast<std::size_t>(ec.value()) + reinterpret_cast<std::size_t>(&ec.category());
    }

    //  make_* functions for errc::errc_t  -----------------------------//
    namespace errc {
      //  explicit conversion:
      inline error_code make_error_code( errc_t e ) noexcept {
        return error_code( e, generic_category() );
      }
    }

  } // namespace system
} // namespace boost


# ifdef BOOST_ERROR_CODE_HEADER_ONLY
#   include <boost/system/detail/error_code.ipp>
# endif

*/

#endif //NINJA_WOOKIE_BACNET_ERROR_ERROR_HPP
