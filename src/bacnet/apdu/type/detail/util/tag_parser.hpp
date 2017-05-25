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
 * based on http://boost-spirit.com/home/articles/qi-example/creating-your-own-parser-component-for-spirit-qi/
 */


#ifndef NINJA_WOOKIE_APDU_TYPE_TAG_PARSER_HPP
#define NINJA_WOOKIE_APDU_TYPE_TAG_PARSER_HPP



#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/endian/conversion.hpp>
#include <bacnet/apdu/type/tag.hpp>


///////////////////////////////////////////////////////////////////////////////
// definition the place holder
namespace boost { namespace spirit { namespace repository { namespace qi {
//BOOST_SPIRIT_TERMINAL(apdu_tag);

namespace tag {
  struct apdu_tag {
    typedef void is_spirit_tag;
  };
}

typedef boost::proto::terminal<tag::apdu_tag>::type apdu_tag_type;

apdu_tag_type const apdu_tag = {{}};

inline void silence_unused_warnings_apdu_tag() {
  (void) apdu_tag;
}

}}}}

///////////////////////////////////////////////////////////////////////////////
// implementation the enabler
namespace boost { namespace spirit {
// We want custom_parser::iter_pos to be usable as a terminal only,
// and only for parser expressions (qi::domain).
template <>
struct use_terminal<qi::domain, repository::qi::tag::apdu_tag>
    : mpl::true_
{};
}}


namespace boost { namespace spirit { namespace repository { namespace qi {

struct apdu_tag_parser : boost::spirit::qi::primitive_parser<apdu_tag_parser> {

  static const uint8_t tag_number_bit_offset                    = 4;
  static const uint8_t context_flag_bit_offset                  = 3;

  static const uint8_t extended_tag_number_indication           = 0x0F;
  static const uint8_t extended_length_value_indication         = 0x05;
  static const uint8_t opening_tag_indication                   = 0x06;
  static const uint8_t closing_tag_indication                   = 0x07;
  static const uint8_t extended_2_bytes_length_value_indication = 0xFE;
  static const uint8_t extended_4_bytes_length_value_indication = 0xFF;

  // Define the attribute types exposed by this parser component
  template <typename Context, typename Iterator>
  struct attribute {
      typedef ::bacnet::apdu::type::tag type;
  };

  template <typename Iterator, typename Context, typename Skipper, typename Attribute>
  bool parse(Iterator& first, Iterator const& last, Context&, Skipper const& skipper, Attribute& attr) const {

    /*
    first 1 byte
    length between 2 and 5 OK
    tag_number 0 to 15.
       7             4    3    2            0
    +----+----+----+----+----+----+----+----+
    | tag number        | C  | length       |
    +----+----+----+----+----+----+----+----+
    */

    typename attribute<Context, Iterator>::type apdu_tag_;
    auto it = first;
    uint8_t first_byte = *it;

    const uint8_t tag_number      = ( (first_byte & 0xf0) >> 4);
    const bool    is_context_tag  = ( (first_byte & 0x08) >> 3);
    const uint8_t length          = ( (first_byte & 0x07)     );

    it++;
    //extended tag number?
    if(tag_number >= extended_tag_number_indication) {
      if (it == last) {
        return false;
      }
      apdu_tag_.number = *it;
      it++;
    }
    else {
      apdu_tag_.number = tag_number;
    }

    //type
    if(is_context_tag) {
      if(length == opening_tag_indication) {
        apdu_tag_.type = ::bacnet::apdu::type::tag::tag_type::opening;
      }
      else if(length == closing_tag_indication) {
        apdu_tag_.type = ::bacnet::apdu::type::tag::tag_type::closing;
      }
      else {
        apdu_tag_.type = ::bacnet::apdu::type::tag::tag_type::context;
      }
    }
    else {
      apdu_tag_.type = ::bacnet::apdu::type::tag::tag_type::application;
    }

    //extended length?
    if(length == extended_length_value_indication) {
      std::cout << " 1 " << std::endl;
      if (it == last) {
        return false;
      }
      const uint8_t extended_length = *it;
      it++;

      std::cout << " 2 " << std::endl;
      if(extended_length == extended_2_bytes_length_value_indication) {
        std::cout << " 3 " << extended_length << std::endl;
        uint16_t l{};
        unsigned char* bytes = reinterpret_cast<unsigned char*>(&l);
        for (unsigned int i = 0; i < 2; ++i) {
          if (it == last) {
            return false;
          }
          *bytes++ = *it;
          it++;
        }
        apdu_tag_.length_value_type = boost::endian::big_to_native(l);
      }

      else if(extended_length == extended_4_bytes_length_value_indication) {
        std::cout << " 4 " << std::endl;
        uint32_t l{};
        unsigned char* bytes = reinterpret_cast<unsigned char*>(&l);
        for (unsigned int i = 0; i < 4; ++i) {
          if (it == last) {
            return false;
          }
          *bytes++ = *it;
          it++;
        }
        apdu_tag_.length_value_type = boost::endian::big_to_native(l);
      }
      else {
        apdu_tag_.length_value_type = extended_length;
      }

    }
    else {
      apdu_tag_.length_value_type = length;
    }

    first = it++;
    spirit::traits::assign_to(apdu_tag_, attr);

    return true;
  }


  template <typename Context>
  boost::spirit::info what(Context&) const  {
    return boost::spirit::info("apdu_tag_parser");
  }
};

}}}}

///////////////////////////////////////////////////////////////////////////////
// instantiation of the parser
namespace boost { namespace spirit { namespace qi {

template <typename Modifiers>
struct make_primitive<repository::qi::tag::apdu_tag, Modifiers>
{
    typedef repository::qi::apdu_tag_parser result_type;

    result_type operator()(unused_type, unused_type) const {
      return result_type();
    }
};


}}}



#endif //NINJA_WOOKIE_APDU_TYPE_TAG_PARSER_HPP
