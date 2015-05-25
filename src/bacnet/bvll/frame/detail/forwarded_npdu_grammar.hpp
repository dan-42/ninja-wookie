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


#ifndef SRC_BACNET_BVLL_FRAME_FORWARDED_NPDU_GRAMMAR_HPP_
#define SRC_BACNET_BVLL_FRAME_FORWARDED_NPDU_GRAMMAR_HPP_

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>

#include <bacnet/bvll/frame/forwarded_npdu.hpp>
#include <bacnet/bvll/bacnet_ip_address.hpp>


namespace bacnet {
namespace bvll {
namespace frame {
namespace detail {
namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::bvll::frame;
using namespace bacnet::bvll::generator;

template<typename Iterator>
struct forwarded_npdu_grammar : grammar<Iterator, forwarded_npdu()> {

  rule<Iterator, forwarded_npdu()> forwarded_npdu_rule;
  rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
  rule<Iterator, bacnet::binary_data()> npdu_data_from_origin_device_rule;

  forwarded_npdu_grammar() : forwarded_npdu_grammar::base_type(forwarded_npdu_rule) {

    bacnet_ip_address_grammar <Iterator> bacnet_ip_address_grammar;

    forwarded_npdu_rule = bacnet_ip_address_rule << npdu_data_from_origin_device_rule;
    bacnet_ip_address_rule = bacnet_ip_address_grammar;
    npdu_data_from_origin_device_rule = *byte_;

    forwarded_npdu_rule.name("forwarded_npdu_rule");
    bacnet_ip_address_rule.name("bacnet_ip_address_rule");
    npdu_data_from_origin_device_rule.name("npdu_data_from_origin_device_rule");
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
using namespace bacnet::bvll::parser;

template<typename Iterator>
struct forwarded_npdu_grammar : grammar<Iterator, forwarded_npdu()> {

  rule<Iterator, forwarded_npdu()> forwarded_npdu_rule;
  rule<Iterator, bacnet_ip_address()> bacnet_ip_address_rule;
  rule<Iterator, bacnet::binary_data()> npdu_data_from_origin_device_rule;

  forwarded_npdu_grammar() : forwarded_npdu_grammar::base_type(forwarded_npdu_rule) {

    bacnet_ip_address_grammar <Iterator> bacnet_ip_address_grammar;

    forwarded_npdu_rule = bacnet_ip_address_rule > npdu_data_from_origin_device_rule;
    bacnet_ip_address_rule = bacnet_ip_address_grammar;
    npdu_data_from_origin_device_rule = *byte_;

    forwarded_npdu_rule.name("forwarded_npdu_rule");
    bacnet_ip_address_rule.name("bacnet_ip_address_rule");
    npdu_data_from_origin_device_rule.name("npdu_data_from_origin_device_rule");
  }
};


}
}
}
}
}

#endif /* SRC_BACNET_BVLL_FRAME_FORWARDED_NPDU_GRAMMAR_HPP_ */
