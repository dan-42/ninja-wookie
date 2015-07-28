/*
 * frame_grammar.hpp
 *
 *  Created on: Jul 28, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_FRAME_DETAIL_FRAME_GRAMMAR_HPP_
#define SRC_BACNET_APDU_FRAME_DETAIL_FRAME_GRAMMAR_HPP_



#include <bacnet/apdu/frame/frames.hpp>
#include <bacnet/apdu/frame/detail/confirmed_request_grammar.hpp>


namespace bacnet { namespace  apdu { namespace frame { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;

using namespace bacnet::apdu;
using namespace bacnet::apdu::frame;


using boost::spirit::qi::rule;




template<typename Iterator>
struct frame_grammar : grammar<Iterator, possible_frame() >{

  rule<Iterator, possible_frame()>                     possible_frame_rule;


  confirmed_request_grammar<Iterator> confirmed_request_grammar_;


  frame_grammar() : frame_grammar::base_type(possible_frame_rule){

    possible_frame_rule  = confirmed_request_grammar_
                         | eps;

    possible_frame_rule.name("possible_frame_rule");

    /*
       debug(possible_frame_rule);
     */
  }

};

}}}}}





namespace bacnet { namespace  apdu { namespace frame {  namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;

using boost::spirit::karma::rule;

using namespace bacnet::apdu;
using namespace bacnet::apdu::frame;

template<typename Iterator>
struct frame_grammar : grammar<Iterator, possible_frame() >{

  rule<Iterator, possible_frame()>                     possible_frame_rule;


  confirmed_request_grammar<Iterator> confirmed_request_grammar_;


  frame_grammar() : frame_grammar::base_type(possible_frame_rule){

    possible_frame_rule  = confirmed_request_grammar_
                         | eps;

    possible_frame_rule.name("possible_frame_rule");

    /*
       debug(possible_frame_rule);
     */
  }

};


}}}}}




#endif /* SRC_BACNET_APDU_FRAME_DETAIL_FRAME_GRAMMAR_HPP_ */
