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

#ifndef SRC_BACNET_BVLL_BVLC_RESULT_HPP_
#define SRC_BACNET_BVLL_BVLC_RESULT_HPP_


#include <cstdint>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/spirit/home/qi/detail/assign_to.hpp>
#include <boost/spirit/home/support/attributes.hpp>
#include <boost/spirit/include/karma_domain.hpp>

namespace bacnet { namespace bvll { namespace frame {

struct bvlc_result{
  uint16_t result_code;
};

}}}

BOOST_FUSION_ADAPT_STRUCT(
  bacnet::bvll::frame::bvlc_result,
  result_code
)



namespace boost { namespace spirit { namespace traits {
    template <>
    struct transform_attribute<uint16_t const, bacnet::bvll::frame::bvlc_result, boost::spirit::karma::domain>  {
        typedef bacnet::bvll::frame::bvlc_result type;
        static bacnet::bvll::frame::bvlc_result pre(uint16_t const& attr) {
          bacnet::bvll::frame::bvlc_result val;
          val.result_code = attr;
          return val;
        }
    };

    template <>
    struct assign_to_attribute_from_value<uint16_t, bacnet::bvll::frame::bvlc_result, void> {
        static void call(bacnet::bvll::frame::bvlc_result const& val, uint16_t& attr) {
             attr = val.result_code;
        }
    };
}}}


#endif /* SRC_BACNET_BVLL_BVLC_RESULT_HPP_ */
