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

#include <bacnet/npdu/detail/grammar.hpp>

#include <bacnet/npdu/detail/frame_grammar.hpp>


using namespace bacnet::npdu;
using namespace bacnet::npdu::detail;

bacnet::binary_data generator::generate(frame &&f){

  bacnet::binary_data binary_frame;
  bacnet::generate_iterator sink(binary_frame);

  bool result = false;
  try{
    result = boost::spirit::karma::generate(sink, detail::generator::npdu_grammar_instance, f);
  }
  catch (std::exception &e) {
    std::cerr << "exception: frames.hpp parse(Container &i, possible_bvll_frame &v) " << e.what() << std::endl;
  }
  if(!result){
    return bacnet::binary_data();
  }
  return binary_frame;
}

frame parser::parse(bacnet::binary_data &&data){

	frame f;
	auto start = data.begin();
	auto end = data.end();
	auto has_success = boost::spirit::qi::parse(start, end, detail::parser::npdu_grammar_instance, f);

	if(!has_success){
	  std::cerr << "bacnet::npdu::parser::parse failed to parse"   << std::endl;

	}
	return f;
}
