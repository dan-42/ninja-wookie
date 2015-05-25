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

#include <bacnet/bvll/frames.hpp>

namespace bacnet { namespace bvll { namespace parser {

using namespace bacnet::bvll::frame;

possible_bvll_frame parse(bacnet::binary_data data) {
  auto start = data.begin();
  auto end = data.end();
  possible_bvll_frame frame;
  bvll_grammar<decltype(start)> grammar;
  bool result = false;
  try {
    result = boost::spirit::qi::parse(start, end, grammar, frame);
  }
  catch (std::exception &e) {
    std::cerr << "exception: frames.hpp parse(Container &i, possible_bvll_frame &v) " << e.what() << std::endl;
  }
  return frame;
}

}}}





