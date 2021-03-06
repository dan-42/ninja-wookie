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

#include <mapbox/boost_spirit_karma.hpp>
#include <mapbox/boost_spirit_qi.hpp>

#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/bind.hpp>

#include <bacnet/bvll/frames.hpp>
#include <bacnet/bvll/frame/detail/combined.hpp>
#include <bacnet/bvll/detail/grammar.hpp>




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
    if(!result){
      std::cerr << "error: frames.hpp parse(Container &i, possible_bvll_frame &v) " << std::endl;
      return possible_bvll_frame{};
    }
    else {
      return frame;
    }
  }
  catch (std::exception &e) {
    std::cerr << "exception: frames.hpp parse(Container &i, possible_bvll_frame &v) " << e.what() << std::endl;
  }
  return possible_bvll_frame{};
}

}}}

namespace bacnet { namespace bvll { namespace generator {

bacnet::binary_data generate(const possible_bvll_frame& frame) {
    bacnet::binary_data binary_frame;

    frame_size fs;
    //uint32_t size = boost::apply_visitor( fs, frame );
    uint32_t size = mapbox::util::apply_visitor( fs, frame );
    std::back_insert_iterator<bacnet::binary_data> sink(binary_frame);
    bvll_grammar<decltype(sink)> generator(size);
    bool result = false;
    try{
      result = boost::spirit::karma::generate(sink, generator, frame);
    }
    catch (std::exception &e) {
      std::cerr << "exception: frames.hpp parse(Container &i, possible_bvll_frame &v) " << e.what() << std::endl;
    }
    if(!result){
      return bacnet::binary_data();
    }
    return binary_frame;
}



}}}





