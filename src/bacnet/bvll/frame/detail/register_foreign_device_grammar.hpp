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


#ifndef SRC_BACNET_BVLL_FRAME_REGISTER_FOREIGN_DEVICE_GRAMMAR_HPP_
#define SRC_BACNET_BVLL_FRAME_REGISTER_FOREIGN_DEVICE_GRAMMAR_HPP_

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/frame/register_foreign_device.hpp>


namespace bacnet {
namespace bvll {
namespace frame {
namespace detail {
namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll::frame;

template<typename Iterator>
struct register_foreign_device_grammar : grammar<Iterator, register_foreign_device()> {

  rule<Iterator, register_foreign_device()> register_foreign_device_rule;
  rule<Iterator, uint16_t()> time_to_live_in_sec_rule;


  register_foreign_device_grammar() : register_foreign_device_grammar::base_type(register_foreign_device_rule) {

    register_foreign_device_rule = time_to_live_in_sec_rule;
    time_to_live_in_sec_rule = big_word;

    register_foreign_device_rule.name("register_foreign_device_rule");
    time_to_live_in_sec_rule.name("time_to_live_in_sec_rule");
  }
};

}
}
}
}
}


namespace bacnet {
namespace bvll {
namespace frame {
namespace detail {
namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll::frame;

template<typename Iterator>
struct register_foreign_device_grammar : grammar<Iterator, register_foreign_device()> {

  rule<Iterator, register_foreign_device()> register_foreign_device_rule;
  rule<Iterator, uint16_t()> time_to_live_in_sec_rule;


  register_foreign_device_grammar() : register_foreign_device_grammar::base_type(register_foreign_device_rule) {

    register_foreign_device_rule = time_to_live_in_sec_rule >> attr(0);
    time_to_live_in_sec_rule = big_word;

    register_foreign_device_rule.name("register_foreign_device_rule");
    time_to_live_in_sec_rule.name("time_to_live_in_sec_rule");
  }
};


}
}
}
}
}

#endif /* SRC_BACNET_BVLL_FRAME_REGISTER_FOREIGN_DEVICE_GRAMMAR_HPP_ */
