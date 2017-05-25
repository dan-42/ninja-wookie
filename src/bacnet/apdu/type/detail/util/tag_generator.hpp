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


#ifndef NINJA_WOOKIE_APDU_TYPE_TAG_GENERATOR_HPP
#define NINJA_WOOKIE_APDU_TYPE_TAG_GENERATOR_HPP


#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/endian/conversion.hpp>
#include <bacnet/apdu/type/tag.hpp>

namespace boost { namespace spirit { namespace repository { namespace karma {

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


namespace boost { namespace spirit {

template <>
struct use_terminal<karma::domain, repository::karma::tag::apdu_tag> : mpl::true_
{};
}}

namespace boost { namespace spirit { namespace repository { namespace karma {

struct apdu_tag_generator : boost::spirit::karma::primitive_generator<apdu_tag_generator> {


  template <typename Context, typename Unused = unused_type>
    struct attribute {
        typedef ::bacnet::apdu::type::tag type;
    };

    template <typename OutputIterator, typename Context, typename Delimiter, typename Attribute>
    static bool generate(OutputIterator& sink, Context& context, Delimiter const& d, Attribute const& attr)     {

      static const uint8_t tag_number_bit_offset                    = 4;
      static const uint8_t context_flag_bit_offset                  = 3;

      static const uint8_t extended_tag_number_indication           = 0x0F;
      static const uint8_t extended_length_value_indication         = 0x05;
      static const uint8_t opening_tag_indication                   = 0x06;
      static const uint8_t closing_tag_indication                   = 0x07;
      static const uint8_t extended_2_bytes_length_value_indication = 0xFE;
      static const uint8_t extended_4_bytes_length_value_indication = 0xFF;

      if (!boost::spirit::traits::has_optional_value(attr)) {
        return false;
      }

      typedef typename attribute<Context>::type attribute_type;
      decltype(auto) apdu_tag_ = traits::extract_from<attribute_type>(attr, context);

      /*
      first 1 byte
      length between 2 and 5 OK
      tag_number 0 to 15.
         7             4    3    2            0
      +----+----+----+----+----+----+----+----+
      | tag number        | C  | length       |
      +----+----+----+----+----+----+----+----+
      */
      uint8_t tag_first_byte = 0x00;


      // 1st byte tag
      if(apdu_tag_.number >= extended_tag_number_indication) {
        tag_first_byte = extended_tag_number_indication << tag_number_bit_offset;
      }
      else {
        tag_first_byte = apdu_tag_.number << tag_number_bit_offset;
      }

      if(apdu_tag_.is_context_tag() ) {
        tag_first_byte |= 0x01 << context_flag_bit_offset;
      }

      auto is_extended_length = false;
      if(apdu_tag_.is_opening_tag()) {
        tag_first_byte |= opening_tag_indication;
      }
      else if(apdu_tag_.is_closing_tag()) {
        tag_first_byte |= closing_tag_indication;
      }
      else if(apdu_tag_.length_value_type >= extended_length_value_indication) {
        tag_first_byte |= extended_length_value_indication;
        is_extended_length = true;
      }
      else {
        tag_first_byte |= apdu_tag_.length_value_type;
      }

      if (!boost::spirit::karma::detail::generate_to(sink, tag_first_byte)) {
        return false;
      }

      // extended tag number?
      if(apdu_tag_.number >= extended_tag_number_indication) {
        if (!boost::spirit::karma::detail::generate_to(sink, apdu_tag_.number)) {
            return false;
        }
      }

      // extended length?
      if(is_extended_length) {

        static constexpr uint32_t min_value_2bytes = 254;
        static constexpr uint32_t max_value_2bytes = 65535;
        static constexpr uint32_t min_value_4bytes = 65535;

        //extended by 1 bytes?
        if(apdu_tag_.length_value_type < min_value_2bytes) {
          const auto l = static_cast<uint8_t>(apdu_tag_.length_value_type);
          if (!boost::spirit::karma::detail::generate_to(sink, l)) {
            return false;
          }
        }

        //extended by 2 bytes?
        else if (apdu_tag_.length_value_type >= min_value_2bytes && apdu_tag_.length_value_type <= max_value_2bytes) {

          if (!boost::spirit::karma::detail::generate_to(sink, extended_2_bytes_length_value_indication)) {
            return false;
          }

          const auto length = static_cast<uint16_t>(apdu_tag_.length_value_type);
          const auto length_big = boost::endian::native_to_big(length);

          unsigned char const* bytes = reinterpret_cast<unsigned char const*>(&length_big);

          for (unsigned int i = 0; i < 2; ++i)  {
            if (!boost::spirit::karma::detail::generate_to(sink, *bytes++)) {
              return false;
            }
          }
        }

        // extended by 4 bytes?
        else if (apdu_tag_.length_value_type > min_value_4bytes) {

          if (!boost::spirit::karma::detail::generate_to(sink, extended_4_bytes_length_value_indication)) {
            return false;
          }

          const auto length = static_cast<uint32_t>(apdu_tag_.length_value_type);
          const auto length_big = boost::endian::native_to_big(length);

          unsigned char const* bytes = reinterpret_cast<unsigned char const*>(&length_big);

          for (unsigned int i = 0; i < 4; ++i)  {
            if (!boost::spirit::karma::detail::generate_to(sink, *bytes++)) {
              return false;
            }
          }
        }
        else {
          return false;
        }
      } //extended length

      return true;
    }


    template <typename OutputIterator, typename Context, typename Delimiter>
    static bool generate(OutputIterator&, Context&, Delimiter const&, unused_type) {
      // It is not possible (doesn't make sense) to use binary generators
      // without providing any attribute, as the generator doesn't 'know'
      // what to output. The following assertion fires if this situation
      // is detected in your code.
      BOOST_SPIRIT_ASSERT_FAIL(OutputIterator,
                               binary_generator_not_usable_without_attribute, ());
      return false;
    }

    template <typename Context>
    static info what(Context const& ctx) {
      return boost::spirit::info("apdu_tag_generator");
    }
};


}}}}

namespace boost { namespace spirit { namespace karma {

template <typename Modifiers>
struct make_primitive<repository::karma::tag::apdu_tag, Modifiers> {
    typedef repository::karma::apdu_tag_generator result_type;

    result_type operator()(unused_type, unused_type) const {
      return result_type();
    }
};


}}}

#endif //NINJA_WOOKIE_APDU_TYPE_TAG_GENERATOR_HPP
