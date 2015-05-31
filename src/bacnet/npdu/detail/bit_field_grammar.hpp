//
// Created by schoko on 5/31/15.
//

#ifndef NINJA_WOOKIE_BIT_FIELD_GRAMMAR_HPP
#define NINJA_WOOKIE_BIT_FIELD_GRAMMAR_HPP


#include <cstdint>

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>

#include <boost/phoenix/bind/bind_member_variable.hpp>


namespace boost { namespace spirit { namespace detail {

template<typename ReturnType>
union bit_field_container {
  static_assert((sizeof(ReturnType) == 1), "size of ReturnType must be 1 byte in size!");
  static_assert((std::is_class<ReturnType>::value), "ReturnType must be struct or class!");

  bit_field_container() : _native(0) {    }
  bit_field_container(const uint8_t& native_value): _native(native_value){   }
  bit_field_container(const ReturnType& type) : _bit_field(type) {    }

  uint8_t _native;
  ReturnType _bit_field;
};

}}}


namespace boost { namespace spirit { namespace qi {

using boost::spirit::detail::bit_field_container;

template<typename Iterator, typename ReturnType>
struct bit_field : grammar<Iterator, ReturnType()> {
  static_assert((sizeof(ReturnType) == 1), "size of ReturnType must be 1 byte in size!");
  static_assert((std::is_class<ReturnType>::value), "ReturnType must be struct or class!");


  bit_field() : bit_field::base_type(start) {

    _8bits = byte_;
    start = _8bits[_val = boost::phoenix::bind(&bit_field_container<ReturnType>::_bit_field, _1) ];

  }

  rule<Iterator,ReturnType()> start;
  rule<Iterator, bit_field_container<ReturnType>()> _8bits;

};

}}}



namespace boost { namespace spirit { namespace karma {

using boost::spirit::detail::bit_field_container;

template<typename Iterator, typename ReturnType>
struct bit_field : grammar<Iterator, ReturnType()> {
  static_assert((sizeof(ReturnType) == 1), "size of ReturnType must be 1 byte in size!");
  static_assert((std::is_class<ReturnType>::value), "ReturnType must be struct or class!");

  bit_field() : bit_field::base_type(start) {

    _8bits = byte_[_1 = boost::phoenix::bind(&bit_field_container<ReturnType>::_native, _val) ];

    start = _8bits;
  }

  rule<Iterator, ReturnType()> start;
  rule<Iterator, bit_field_container<ReturnType>()> _8bits;

};

}}}


#endif //NINJA_WOOKIE_BIT_FIELD_GRAMMAR_HPP
