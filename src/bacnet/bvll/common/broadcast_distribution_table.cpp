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

#include <bacnet/bvll/common/broadcast_distribution_table.hpp>
#include <bacnet/bvll/detail/broadcast_distribution_table_grammar.hpp>


namespace bacnet { namespace bvll { namespace generator {

  bool generate(bacnet::binary_data &c, broadcast_distribution_table &v) {
    std::back_insert_iterator<std::decay<decltype(c)>::type> sink(c);
    bacnet::bvll::detail::generator::broadcast_distribution_table_grammar<decltype(sink)> g;
    return boost::spirit::karma::generate(sink, g, v);
  }

}}}


namespace bacnet { namespace bvll { namespace parser {


  bool parse(bacnet::binary_data &i, broadcast_distribution_table &v){
    auto start = i.begin(); auto end = i.end();
    bacnet::bvll::detail::parser::broadcast_distribution_table_grammar<decltype(start)> grammar;
    return boost::spirit::qi::parse(start, end, grammar, v);
  }

}}}


