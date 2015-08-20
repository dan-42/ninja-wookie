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
 */

#ifndef NINJA_WOOKIE_TAG_GRAMMAR_HPP
#define NINJA_WOOKIE_TAG_GRAMMAR_HPP


#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>

namespace bacnet { namespace  apdu { namespace detail { namespace type {

struct tag {
    uint8_t number_                    : 4;
    uint8_t is_appliucation_tag_       : 1; //also call class in the standart
    uint8_t length_value_type_         : 3;

    inline uint8_t  number() { return number_;}
    inline bool  is_appliucation_tag() { return is_appliucation_tag_ == true;}
    inline uint8_t  length_value_type() { return length_value_type_;}

};

namespace  tag_number   {
    uint8_t null                     =  0;
    uint8_t boolean                  =  1;
    uint8_t unsigned_interger        =  2;
    uint8_t signed_integer           =  3; // (2's complement notation)
    uint8_t real                     =  4; //Real (ANSI/IEEE-754 floating point)
    uint8_t double_presision         =  5; //Double (ANSI/IEEE-754 double precision floating point)
    uint8_t octet_string             =  6;
    uint8_t character_string         =  7;
    uint8_t bit_string               =  8;
    uint8_t enumerated               =  9;
    uint8_t date                     = 10;
    uint8_t time                     = 11;
    uint8_t bacnet_object_identifier = 12;
    uint8_t reserved_13              = 13;
    uint8_t reserved_14              = 14;
    uint8_t reserved_15              = 15;
};

struct null_t;


}}}}



namespace bacnet { namespace  apdu { namespace detail { namespace type { namespace parser {

    using namespace boost::spirit;
    using namespace boost::spirit::qi;
    using namespace boost::phoenix;

    using boost::spirit::qi::bit_field;
    using boost::spirit::qi::rule;


    using namespace bacnet::apdu::detail::type;


    template<typename Iterator>
    struct null_grammar : grammar<Iterator, null_t() >{

        static constexpr uint8_t encoded_null = 0x00;

        rule<Iterator, null_t()>     null_rule;


        null_grammar() : null_grammar::base_type(null_rule){

            null_rule  = byte_(encoded_null);
            null_rule.name("null_rule");
            /*
               debug(null_rule);
            */
        }
    };

}}}}}


namespace bacnet { namespace  apdu { namespace detail { namespace type {  namespace generator {

    using namespace boost::spirit;
    using namespace boost::spirit::karma;
    using namespace boost::phoenix;

    using boost::spirit::karma::bit_field;
    using boost::spirit::karma::rule;
    using boost::spirit::karma::_1;

    using namespace bacnet::apdu::detail::type;


    template<typename Iterator>
    struct null_grammar : grammar<Iterator, null_t() >{

        static constexpr uint8_t encoded_null = 0x00;

        rule<Iterator, null_t()>     null_rule;


        null_grammar() : null_grammar::base_type(null_rule){

            null_rule  = byte_(encoded_null);
            null_rule.name("null_rule");
            /*
               debug(null_rule);
            */
        }
    };

 }}}}}





namespace bacnet { namespace  apdu { namespace detail { namespace type { namespace parser {

                    using namespace boost::spirit;
                    using namespace boost::spirit::qi;
                    using namespace boost::phoenix;

                    using boost::spirit::qi::bit_field;
                    using boost::spirit::qi::rule;
                    using boost::spirit::qi::_1;
                    using boost::phoenix::bind;




                    template<typename Iterator>
                    struct boolean_grammar : grammar<Iterator, bool()> {


                        rule<Iterator, bool()>     bool_rule;
                        rule<Iterator, bool()>     application_tagged_rule;
                        rule<Iterator, bool()>     application_tagged_true_rule;
                        rule<Iterator, bool()>     application_tagged_false_rule;

                        rule<Iterator, bool()>     context_tagged_rule;
                        rule<Iterator, bool()>     context_tagged_true_rule;
                        rule<Iterator, bool()>     context_tagged_false_rule;

                        boolean_grammar() : boolean_grammar::base_type(bool_rule){

                            constexpr uint8_t encoded_application_tagged_true  = 0x11;
                            constexpr uint8_t encoded_application_tagged_false = 0x10;

                            constexpr uint8_t encoded_context_tag_id       = 0x29;
                            constexpr uint8_t encoded_context_tagged_true  = 0x01;
                            constexpr uint8_t encoded_context_tagged_false = 0x00;



                            bool_rule  = application_tagged_rule
                                       | context_tagged_rule;

                            application_tagged_rule = application_tagged_true_rule
                                                    | application_tagged_false_rule;

                            application_tagged_true_rule = byte_(encoded_application_tagged_true)[_val = true];
                            application_tagged_true_rule = byte_(encoded_application_tagged_false)[_val = false];


                            context_tagged_rule = byte_(encoded_context_tag_id) >> (context_tagged_true_rule|context_tagged_false_rule);

                            context_tagged_true_rule = byte_(encoded_context_tagged_true)[_val = true];
                            context_tagged_false_rule = byte_(encoded_context_tagged_false)[_val = false];
                        }
                    };

                }}}}}

/*
namespace bacnet { namespace  apdu { namespace detail { namespace type {  namespace generator {

                    using namespace boost::spirit;
                    using namespace boost::spirit::karma;
                    using namespace boost::phoenix;

                    using boost::spirit::karma::bit_field;
                    using boost::spirit::karma::rule;
                    using boost::spirit::karma::_1;

                    using namespace bacnet::apdu::detail::type;


                    template<typename Iterator>
                    struct null_grammar : grammar<Iterator, null_t() >{

                        static constexpr uint8_t encoded_null = 0x00;

                        rule<Iterator, null_t()>     null_rule;


                        null_grammar() : null_grammar::base_type(null_rule){

                            null_rule  = byte_(encoded_null);
                            null_rule.name("null_rule");

                        }
                    };

                }}}}}

*/









#endif /* NINJA_WOOKIE_TAG_GRAMMAR_HPP */

