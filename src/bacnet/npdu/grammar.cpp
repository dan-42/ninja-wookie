/*
 * grammar.cpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
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
