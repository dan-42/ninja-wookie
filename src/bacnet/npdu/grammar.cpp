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

#include <bacnet/npdu/grammar.hpp>

#include <bacnet/npdu/detail/frame_grammar.hpp>



bacnet::binary_data bacnet::npdu::generator::generate(const npdu::frame &f){

  bacnet::binary_data binary_frame;

  std::back_insert_iterator<bacnet::binary_data> sink(binary_frame);
  bacnet::npdu::detail::generator::npdu_grammar<decltype(sink)> generator;
  bool result = false;
  try{
    result = boost::spirit::karma::generate(sink, generator, f);
  }
  catch (std::exception &e) {
    std::cerr << "exception: frames.hpp parse(Container &i, possible_bvll_frame &v) " << e.what() << std::endl;
  }
  if(!result){
    return bacnet::binary_data();
  }
  return binary_frame;
}

bacnet::npdu::frame bacnet::npdu::parser::parse(const bacnet::binary_data &data){

	bacnet::npdu::frame f;
	auto start = data.begin();
	auto end = data.end();

	bacnet::npdu::detail::parser::npdu_grammar<decltype(start)> grammar;
	auto has_success = boost::spirit::qi::parse(start, end, grammar, f);

	if(!has_success){
	  std::cerr << "bacnet::npdu::parser::parse failed to parse"   << std::endl;

	}
	return f;
}
