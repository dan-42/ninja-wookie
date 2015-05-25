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


#ifndef SRC_BACNET_BVLL_FRAME_DISTRIBUTE_BROADCAST_TO_NETWORK_GRAMMAR_HPP_
#define SRC_BACNET_BVLL_FRAME_DISTRIBUTE_BROADCAST_TO_NETWORK_GRAMMAR_HPP_


#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/detail/common/types.hpp>
#include<bacnet/bvll/frame/distribute_broadcast_to_network.hpp>

namespace bacnet {
namespace bvll {
namespace frame {
namespace detail {
namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll::generator;

template<typename Iterator>
struct distribute_broadcast_to_network_grammar : grammar<Iterator, distribute_broadcast_to_network()> {

  rule<Iterator, distribute_broadcast_to_network()> distribute_broadcast_to_network_rule;
  rule<Iterator, bacnet::binary_data()> npdu_data_rule;

  distribute_broadcast_to_network_grammar() : distribute_broadcast_to_network_grammar::base_type(
      distribute_broadcast_to_network_rule) {

    distribute_broadcast_to_network_rule = npdu_data_rule;
    npdu_data_rule = *byte_;

    distribute_broadcast_to_network_rule.name("distribute_broadcast_to_network_rule");
    npdu_data_rule.name("npdu_data_rule");
  }
};

}
}
}
}
} /* namespaces */


namespace bacnet {
namespace bvll {
namespace frame {
namespace detail {
namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace bacnet::bvll::frame;

template<typename Iterator>
struct distribute_broadcast_to_network_grammar : grammar<Iterator, distribute_broadcast_to_network()> {

  rule<Iterator, distribute_broadcast_to_network()> distribute_broadcast_to_network_rule;
  rule<Iterator, bacnet::binary_data()> npdu_data_rule;

  distribute_broadcast_to_network_grammar() : distribute_broadcast_to_network_grammar::base_type(
      distribute_broadcast_to_network_rule) {

    distribute_broadcast_to_network_rule = npdu_data_rule >> attr(0);
    npdu_data_rule = *byte_;

    distribute_broadcast_to_network_rule.name("distribute_broadcast_to_network_rule");
    npdu_data_rule.name("npdu_data_rule");
  }
};

}
}
}
}
} /* namespaces */

#endif /* SRC_BACNET_BVLL_FRAME_DISTRIBUTE_BROADCAST_TO_NETWORK_GRAMMAR_HPP_ */
