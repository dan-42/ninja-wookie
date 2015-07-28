/*
 * confirmed_request_grammar.hpp
 *
 *  Created on: Jul 28, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_FRAME_DETAIL_CONFIRMED_REQUEST_GRAMMAR_HPP_
#define SRC_BACNET_APDU_FRAME_DETAIL_CONFIRMED_REQUEST_GRAMMAR_HPP_



#include <bitset>


#include <util/boost/spirit/detail/bit_field_grammar.hpp>

#include <bacnet/detail/common/types.hpp>

#include <bacnet/apdu/frame/confirmed_request.hpp>
#include <bacnet/apdu/detail/pdu_type.hpp>




namespace bacnet { namespace  apdu { namespace frame { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using namespace bacnet::apdu;
using namespace bacnet::apdu::frame;
using namespace bacnet::apdu::detail;
using namespace bacnet::apdu::detail::header;

using boost::spirit::qi::bit_field;
using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::spirit::qi::_2;
using boost::spirit::qi::_3;
using boost::phoenix::bind;



template<typename Iterator>
struct confirmed_request_grammar : grammar<Iterator, confirmed_request() >{

  rule<Iterator, confirmed_request()>                     confirmed_request_rule;
  rule<Iterator, pdu_type_and_control_information_t()>    pdu_header_rule;
  rule<Iterator, segmentation_t()>                        segmentation_rule;

  rule<Iterator, uint8_t()>             invoke_id_rule;
  rule<Iterator, uint8_t()>             sequence_number_rule;
  rule<Iterator, uint8_t()>             proposed_window_size_rule;
  rule<Iterator, uint8_t()>             service_choice_rule;

  rule<Iterator>                        pdu_type_check_rule;

  rule<Iterator, bacnet::binary_data()> service_data_rule;


  bit_field<Iterator, pdu_type_and_control_information_t> pdu_type_and_control_information_grammar;
  bit_field<Iterator, segmentation_t>                     segmentation_grammar;

  confirmed_request_grammar() : confirmed_request_grammar::base_type(confirmed_request_rule){

    confirmed_request_rule  = pdu_header_rule
                           >> segmentation_rule
                           >> invoke_id_rule
                           >> sequence_number_rule
                           >> proposed_window_size_rule
                           >> service_choice_rule
                           >> service_data_rule;


    pdu_header_rule           = (pdu_header_rule[ref(pdu_header_) = _1])[_val = _1]  >> pdu_type_check_rule;


    segmentation_rule         = segmentation_grammar;

    invoke_id_rule            = byte_;

    sequence_number_rule      = ( (eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_segmented, ref(pdu_header_)) == true) >> byte_            )
                              | ( attr(uint8_t{0})) );

    proposed_window_size_rule = ( (eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_segmented, ref(pdu_header_)) == true) >> byte_            )
                              | ( attr(uint8_t{0})) );

    service_choice_rule       = byte_;

    service_data_rule         = repeat[byte_];


    pdu_type_check_rule       = (eps(boost::phoenix::bind(&pdu_type_and_control_information_t::pdu_type, ref(pdu_header_)) == pdu_type::confirmed_request) );


    confirmed_request_rule.name("confirmed_request_rule");
    pdu_header_rule.name("pdu_header_rule");
    segmentation_rule.name("segmentation_rule");
    invoke_id_rule.name("invoke_id_rule");
    sequence_number_rule.name("sequence_number_rule");
    proposed_window_size_rule.name("proposed_window_size_rule");
    service_choice_rule.name("service_choice_rule");
    service_data_rule.name("service_data_rule");
    pdu_type_check_rule.name("pdu_type_check_rule");

    /*
       debug(confirmed_request_rule);
       debug(pdu_header_rule);
       debug(segmentation_rule);
       debug(invoke_id_rule);
       debug(sequence_number_rule);
       debug(proposed_window_size_rule);
       debug(service_choice_rule);
       debug(service_data_rule);
       debug(pdu_type_check_rule);
     */
  }


  pdu_type_and_control_information_t pdu_header_;
};

}}}}}





namespace bacnet { namespace  apdu { namespace frame {  namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;

using boost::spirit::karma::bit_field;
using boost::spirit::karma::rule;
using boost::spirit::karma::_1;


using namespace bacnet::apdu;
using namespace bacnet::apdu::frame;
using namespace bacnet::apdu::detail;
using namespace bacnet::apdu::detail::header;




template<typename Iterator>
struct confirmed_request_grammar : grammar<Iterator, confirmed_request() >{

  rule<Iterator, confirmed_request()>                     confirmed_request_rule;
  rule<Iterator, pdu_type_and_control_information_t()>    pdu_header_rule;
  rule<Iterator, segmentation_t()>                        segmentation_rule;

  rule<Iterator, uint8_t()>             invoke_id_rule;
  rule<Iterator, uint8_t()>             sequence_number_rule;
  rule<Iterator, uint8_t()>             proposed_window_size_rule;
  rule<Iterator, uint8_t()>             service_choice_rule;

  rule<Iterator>                        pdu_type_check_rule;

  rule<Iterator, bacnet::binary_data()> service_data_rule;


  bit_field<Iterator, pdu_type_and_control_information_t> pdu_type_and_control_information_grammar;
  bit_field<Iterator, segmentation_t>                     segmentation_grammar;

  confirmed_request_grammar() : confirmed_request_grammar::base_type(confirmed_request_rule){

    confirmed_request_rule  = pdu_header_rule
                           << segmentation_rule
                           << invoke_id_rule
                           << sequence_number_rule
                           << proposed_window_size_rule
                           << service_choice_rule
                           << service_data_rule;


    pdu_header_rule           = (pdu_header_rule[ref(pdu_header_) = _val])[_1 = _val]  << pdu_type_check_rule;


    segmentation_rule         = segmentation_grammar;

    invoke_id_rule            = byte_;

    sequence_number_rule      = ( (eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_segmented, ref(pdu_header_)) == true) << byte_            )
                              |  eps );

    proposed_window_size_rule = ( (eps(boost::phoenix::bind(&pdu_type_and_control_information_t::is_segmented, ref(pdu_header_)) == true) << byte_            )
                              |  eps );

    service_choice_rule       = byte_;

    service_data_rule         = repeat[byte_];


    pdu_type_check_rule       = (eps(boost::phoenix::bind(&pdu_type_and_control_information_t::pdu_type, ref(pdu_header_)) == pdu_type::confirmed_request) );


    confirmed_request_rule.name("confirmed_request_rule");
    pdu_header_rule.name("pdu_header_rule");
    segmentation_rule.name("segmentation_rule");
    invoke_id_rule.name("invoke_id_rule");
    sequence_number_rule.name("sequence_number_rule");
    proposed_window_size_rule.name("proposed_window_size_rule");
    service_choice_rule.name("service_choice_rule");
    service_data_rule.name("service_data_rule");
    pdu_type_check_rule.name("pdu_type_check_rule");

    /*
       debug(confirmed_request_rule);
       debug(pdu_header_rule);
       debug(segmentation_rule);
       debug(invoke_id_rule);
       debug(sequence_number_rule);
       debug(proposed_window_size_rule);
       debug(service_choice_rule);
       debug(service_data_rule);
       debug(pdu_type_check_rule);
     */
  }

  pdu_type_and_control_information_t pdu_header_;

};


}}}}}


#endif /* SRC_BACNET_APDU_FRAME_DETAIL_CONFIRMED_REQUEST_GRAMMAR_HPP_ */
