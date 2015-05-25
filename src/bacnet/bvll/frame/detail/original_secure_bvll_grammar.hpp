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

#ifndef SRC_BACNET_BVLL_ORIGINAL_SECURE_BVLL_GRAMMAR_HPP_
#define SRC_BACNET_BVLL_ORIGINAL_SECURE_BVLL_GRAMMAR_HPP_

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/frame/original_secure_bvll.hpp>


namespace bacnet {
namespace bvll {
namespace frame {
namespace detail {
namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll::frame;

template<typename Iterator>
struct original_secure_bvll_grammar : grammar<Iterator, original_secure_bvll()> {

  rule<Iterator, original_secure_bvll()> original_secure_bvll_rule;
  rule<Iterator, bacnet::binary_data()> binary_data_rule;

  original_secure_bvll_grammar() : original_secure_bvll_grammar::base_type(original_secure_bvll_rule) {

    original_secure_bvll_rule = binary_data_rule;
    binary_data_rule = *byte_;

    original_secure_bvll_rule.name("original_secure_bvll_rule");
    binary_data_rule.name("binary_data_rule");
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
struct original_secure_bvll_grammar : grammar<Iterator, original_secure_bvll()> {

  rule<Iterator, original_secure_bvll()> original_secure_bvll_rule;
  rule<Iterator, bacnet::binary_data()> binary_data_rule;

  original_secure_bvll_grammar() : original_secure_bvll_grammar::base_type(original_secure_bvll_rule) {

    original_secure_bvll_rule = binary_data_rule >> attr(0);
    binary_data_rule = *byte_;

    original_secure_bvll_rule.name("original_secure_bvll_rule");
    binary_data_rule.name("binary_data_rule");
  }
};


}
}
}
}
}

#endif /* SRC_BACNET_BVLL_ORGINAL_SECURE_BVLL_GRAMMAR_HPP_ */
