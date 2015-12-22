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


#ifndef NINJA_WOOKIE_UINT24_PARSER_HPP
#define NINJA_WOOKIE_UINT24_PARSER_HPP



#include <boost/spirit/include/qi_parse.hpp>
#include <boost/spirit/include/karma.hpp>


///////////////////////////////////////////////////////////////////////////////
// definition the place holder
namespace boost { namespace spirit { namespace repository { namespace qi {
BOOST_SPIRIT_TERMINAL(big_24word);
}}}}

///////////////////////////////////////////////////////////////////////////////
// implementation the enabler
namespace boost { namespace spirit {
// We want custom_parser::iter_pos to be usable as a terminal only,
// and only for parser expressions (qi::domain).
template <>
struct use_terminal<qi::domain, repository::qi::tag::big_24word>
    : mpl::true_
{};
}}

///////////////////////////////////////////////////////////////////////////////
// implementation of the parser
namespace boost { namespace spirit { namespace repository { namespace qi {
struct big_24word_parser
    : boost::spirit::qi::primitive_parser<big_24word_parser>
{
    // Define the attribute types exposed by this parser component
    template <typename Context, typename Iterator>
    struct attribute
    {
        typedef uint32_t type;
    };

    // This function is called during the actual parsing process
    template <typename Iterator, typename Context
        , typename Skipper, typename Attribute>
    bool parse(Iterator& first, Iterator const& last
        , Context&, Skipper const& skipper, Attribute& attr) const
    {
      boost::spirit::qi::skip_over(first, last, skipper);


      typename attribute<Context, Iterator>::type attr_;
      unsigned char* bytes = reinterpret_cast<unsigned char*>(&attr_);

      Iterator it = first;
      for (unsigned int i = 0; i < 3; ++i)
      {
        if (it == last)
          return false;
        *bytes++ = *it++;
      }

      first = it;

      spirit::traits::assign_to(attr_, attr);

      return true;
    }

    // This function is called during error handling to create
    // a human readable string for the error context.
    template <typename Context>
    boost::spirit::info what(Context&) const
    {
      return boost::spirit::info("big_24word_parser");
    }
};
}}}}

///////////////////////////////////////////////////////////////////////////////
// instantiation of the parser
namespace boost { namespace spirit { namespace qi {
// This is the factory function object invoked in order to create
// an instance of our iter_pos_parser.
template <typename Modifiers>
struct make_primitive<repository::qi::tag::big_24word, Modifiers>
{
    typedef repository::qi::big_24word_parser result_type;

    result_type operator()(unused_type, unused_type) const
    {
      return result_type();
    }
};


}}}



#endif //NINJA_WOOKIE_UINT24_PARSER_HPP
