/*
 * grammar.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */

#include <iterator>
#include <exception>

#include <bacnet/apdu/frame/grammar.hpp>

#include <bacnet/apdu/frame/detail/frame_grammar.hpp>

using namespace bacnet::apdu;
using namespace bacnet::apdu::frame;

bacnet::binary_data generator::generate(const possible_frame &f){


  bacnet::binary_data binary_frame;

  std::back_insert_iterator<bacnet::binary_data> sink(binary_frame);
  detail::generator::frame_grammar<decltype(sink)> generator;
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

possible_frame parser::parse(const bacnet::binary_data &data){

	possible_frame f;
	auto start = data.begin();
	auto end = data.end();

	detail::parser::frame_grammar<decltype(start)> grammar;
	auto has_success = boost::spirit::qi::parse(start, end, grammar, f);

	if(!has_success){
	  std::cerr << "bacnet::npdu::parser::parse failed to parse"   << std::endl;

	}
	return f;
}
