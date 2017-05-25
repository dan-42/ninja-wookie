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



#include <bacnet/apdu/type/detail/util/tag_generator.hpp>
#include <bacnet/apdu/type/detail/util/tag_parser.hpp>/*

 possibilities of tags
  simple 1 byte
    length between 2 and 5 OK
    tag_number 0 to 15.
       7             4    3    2            0
    +----+----+----+----+----+----+----+----+
    | tag number        | C  | length       |
    +----+----+----+----+----+----+----+----+


  extended tag_number
    the 4-bit tag_number in the first byte are all one, and indicating one byte following containing the extendet tag_number
    from 0 to 254 decoded,  value 255 is reserved.

         7             4    3    2          0
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
    | 1    1    1    1  | C  | length       |  |  uint8_t extended_tag_number          |
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+

 extended length value
    for data length bigger then 4 bytes, e.g. double or BACnet-bit-Strings and so on
    the length is encoded as bx101 indicating one following byte
    if the following byte contains 254 then it indicates two following bytes
    if the following byte contains 255 then it indicates four following bytes


    length from 15 to 254

       7             4    3    2           0    7                                    0
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
    |  tag_number       | C  |  1    0    1 |  |  uint8_t extended_length_value        |
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+


    length from 254 to 65535
     7             4    3    2           0      7                                    0      15                                  8   7                                    0
    +----+----+----+----+----+----+----+----+ +----+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+
    |  tag_number       | C  |  1    0    1 | |  1    1    1    1   1    1    1    0  |   |    uint16_t extended_length_value                                            |
    +----+----+----+----+----+----+----+----+ +----+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+----+


    length from 65535 to 2^32-1
      7             4    3    2           0      7                                    0      32                                  [...]                                   0
    +----+----+----+----+----+----+----+----+ +----+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+---[...]+----+----+----+----+----+----+----+
    |  tag_number       | C  |  1    0    1 | |  1    1    1    1   1    1    1    1  |   |    uint32_t extended_length_value    [...]                                   |
    +----+----+----+----+----+----+----+----+ +----+----+----+----+----+----+----+----+   +----+----+----+----+----+----+----+---[...]+----+----+----+----+----+----+----+

 combinations

    if the tag_number is extended and the length, then the extended_tag_number comes bevore the extended_length

        7             4    3    2          0     7                                     0    7                                     0
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+
    | 1    1    1    1  | C  |  1    0    1 |  |  uint8_t extended_tag_number          |  |   uint8_t extended_length_value       |
    +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+  +----+----+----+----+----+----+----+----+


 summary, the tag_part can be of size between 1 byte and 7 bytes


 */




namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;

using boost::spirit::qi::rule;
using boost::spirit::repository::qi::apdu_tag;

using bacnet::apdu::type::tag;


template<typename Iterator>
struct tag_grammar : grammar<Iterator, tag()> {


    rule<Iterator, tag()>               start_rule;

    tag_grammar() : tag_grammar::base_type(start_rule) {

      start_rule  =  apdu_tag
                  ;
    }
};


}}}}}



namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;

using boost::spirit::karma::rule;
using boost::spirit::repository::karma::apdu_tag;
using bacnet::apdu::type::tag;

template<typename Iterator>
struct tag_grammar : grammar<Iterator, tag()> {

    rule<Iterator, tag()>               start_rule;

    tag_grammar() : tag_grammar::base_type(start_rule) {

      start_rule =  apdu_tag
                 ;
    }

};

}}}}}


#endif //NINJA_WOOKIE_TAG_GRAMMAR_HPP
