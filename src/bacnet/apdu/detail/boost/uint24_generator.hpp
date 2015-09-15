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


#ifndef NINJA_WOOKIE_UINT24_GENERATOR_HPP
#define NINJA_WOOKIE_UINT24_GENERATOR_HPP


#include <boost/spirit/include/karma_generate.hpp>
#include <boost/spirit/include/qi_parse.hpp>


namespace boost { namespace spirit { namespace repository { namespace karma {
BOOST_SPIRIT_TERMINAL(big_24word);
}}}}


namespace boost { namespace spirit {

template <>
struct use_terminal<karma::domain, repository::karma::tag::big_24word> : mpl::true_
{};
}}

namespace boost { namespace spirit { namespace repository { namespace karma {

struct big_24word_generator : boost::spirit::karma::primitive_generator<big_24word_generator> {
    template <typename Context, typename Unused = unused_type>
    struct attribute {
        typedef uint32_t type;
    };

    template <typename OutputIterator, typename Context, typename Delimiter, typename Attribute>
    static bool generate(OutputIterator& sink, Context& context, Delimiter const& d, Attribute const& attr)     {
      if (!boost::spirit::traits::has_optional_value(attr))
        return false;

      typename attribute<Context>::type p;

#if defined(BOOST_MSVC)
      // warning C4244: 'argument' : conversion from 'const int' to 'foo', possible loss of data
#pragma warning(push)
#pragma warning(disable: 4244)
#endif
      typedef typename attribute<Context>::type attribute_type;
      p = traits::extract_from<attribute_type>(attr, context);
#if defined(BOOST_MSVC)
#pragma warning(pop)
#endif

      unsigned char const* bytes = reinterpret_cast<unsigned char const*>(&p);

      for (unsigned int i = 0; i < 3; ++i)  {
        if (!boost::spirit::karma::detail::generate_to(sink, *bytes++))
          return false;
      }
      return boost::spirit::karma::delimit_out(sink, d);     // always do post-delimiting
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
      return boost::spirit::info("uin24_generator");
    }
};


}}}}

namespace boost { namespace spirit { namespace karma {

template <typename Modifiers>
struct make_primitive<repository::karma::tag::big_24word, Modifiers> {
    typedef repository::karma::big_24word_generator result_type;

    result_type operator()(unused_type, unused_type) const {
      return result_type();
    }


};


}}}

#endif //NINJA_WOOKIE_UINT24_GENERATOR_HPP
