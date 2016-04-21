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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_DETAIL_I_AM_GRAMMAR_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_DETAIL_I_AM_GRAMMAR_HPP

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/service/i_am.hpp>

#include <boost/spirit/include/karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/phoenix.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

#include <bacnet/apdu/type/detail/unsigned_integer_grammar.hpp>
#include <bacnet/apdu/type/detail/enumeration_grammar.hpp>

namespace bacnet { namespace  service { namespace service { namespace detail { namespace parser {

using namespace boost::spirit;
using namespace boost::spirit::qi;
using namespace boost::phoenix;

using boost::spirit::qi::rule;
using boost::spirit::qi::_1;
using boost::phoenix::bind;

using bacnet::apdu::type::application_tag;

/**

 bacnet::common::object_identifier i_am_device_identifier;
    uint32_t                        max_apdu_length_accepted;
    bacnet::common::segmentation    segmentation_supported;
    uint16_t                        vendor_id;

 // */

using bacnet::service::service::i_am;

template<typename Iterator>
struct i_am_grammar : grammar<Iterator, i_am()> {


    rule<Iterator, i_am()>                     start_rule;
    object_identifier_grammar<Iterator>        i_am_device_identifier_rule;
    unsigned_integer_grammar<Iterator>         max_apdu_length_accepted_rule(application_tag::unsigned_interger);
    rule<Iterator, segmentation_supported()>   segmentation_supported_rule;
    unsigned_integer_grammar<Iterator>         vendor_id_rule(application_tag::unsigned_interger);

    unsigned_integer_grammar<Iterator> unsigned_integer_grammar_;
    object_identifier_grammar<Iterator> object_identifier_grammar_;

   i_am_grammar() : i_am_grammar::base_type(start_rule), size_(0) {

      start_rule  =  i_am_device_identifier_rule
                  >> max_apdu_length_accepted_rule
                  >> segmentation_supported_rule
                  >> vendor_id_rule
                  ;



      segmentation_supported_rule = unsigned_integer_grammar_;




      start_rule.name("start_rule");
      i_am_device_identifier_rule.name("i_am_device_identifier_rule");
      max_apdu_length_accepted_rule.name("max_apdu_length_accepted_rule");
      segmentation_supported_rule.name("segmentation_supported_rule");
      vendor_id_rule.name("vendor_id_rule");

/*
      debug(start_rule);
      debug(i_am_device_identifier_rule);
      debug(max_apdu_length_accepted_rule);
      debug(segmentation_supported_rule);
      debug(vendor_id_rule);
// */
    }
private:


};

}}}}}

namespace bacnet { namespace  apdu { namespace type { namespace detail { namespace generator {

using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace boost::phoenix;

using boost::spirit::karma::bit_field;
using boost::spirit::karma::rule;
using boost::spirit::karma::_1;
using boost::phoenix::bind;

using boost::spirit::repository::karma::big_24word;

using bacnet::apdu::type::tag;
using bacnet::apdu::type::unsigned_integer;


template<typename Iterator>
struct unsigned_integer_grammar : grammar<Iterator, unsigned_integer()> {

    rule<Iterator, unsigned_integer()>  start_rule;
    rule<Iterator, tag()>               tag_rule;
    rule<Iterator, uint32_t()>          value_rule;

    tag_grammar<Iterator> tag_grammar_;

    unsigned_integer_grammar() : unsigned_integer_grammar::base_type(start_rule) {

      start_rule  = tag_rule << value_rule ;

      tag_rule = eps[boost::phoenix::bind(&unsigned_integer_grammar::extract_size, this, _val)] << tag_grammar_[_1 = _val];

      value_rule  = eps(ref(size_) == 1) << byte_
                    | eps(ref(size_) == 2) << big_word
                    | eps(ref(size_) == 3) << big_24word
                    | eps(ref(size_) == 4) << big_dword;

      start_rule.name("start_rule");
      tag_rule.name("tag_rule");
      value_rule.name("value_rule");

     // /*
      debug(start_rule);
      debug(value_rule);
      debug(tag_rule);
     // */

    }
private:

    void extract_size(const tag &tag_) {
      size_ = tag_.length_value_type();
    }

    uint8_t size_;
};

}}}}}













namespace bacnet { namespace service { namespace service { namespace detail {

template<>
bacnet::binary_data generate<i_am>(const i_am& i_am_service) {

  namespace service = bacnet::service::service;
  namespace apdu    = bacnet::apdu::type;


  bacnet::binary_data binary;
  auto service_choice_command = service_choice<service::i_am>::value;
  binary.push_back(service_choice_command);

  auto max_apdu_length_accepted = i_am_service.max_apdu_length_accepted;


  apdu::tag tag_object_identifier(apdu::application_tag::bacnet_object_identifier, 4);
  apdu::tag tag_max_apdu_accepted(apdu::application_tag::unsigned_interger, apdu::detail::length_helper(max_apdu_length_accepted));
  apdu::tag tag_segmentation_supported(apdu::application_tag::enumerated, apdu::detail::length_helper(i_am_service.segmentation_supported.to_native()));
  apdu::tag tag_vendor_id(apdu::application_tag::unsigned_interger, apdu::detail::length_helper(i_am_service.vendor_id));


  apdu::object_identifier oi(tag_object_identifier, i_am_service.i_am_device_identifier);
  auto oi_binary = apdu::generate(oi);
  binary.insert(binary.end(), oi_binary.begin(), oi_binary.end());


  apdu::unsigned_integer max_apdu_accepted(tag_max_apdu_accepted, max_apdu_length_accepted);
  auto max_apdu_accepted_binary = apdu::generate(max_apdu_accepted);
  binary.insert(binary.end(), max_apdu_accepted_binary.begin(), max_apdu_accepted_binary.end());

  apdu::enumeration segmentation_supported(tag_segmentation_supported, i_am_service.segmentation_supported.to_native());
  auto segmentation_supported_binary = apdu::generate(segmentation_supported);
  binary.insert(binary.end(), segmentation_supported_binary.begin(), segmentation_supported_binary.end());

  apdu::unsigned_integer vendor_id(tag_vendor_id, i_am_service.vendor_id);
  auto vendor_id_binary = apdu::generate(vendor_id);
  binary.insert(binary.end(), vendor_id_binary.begin(), vendor_id_binary.end());



  return binary;
}


template<>
bool parse<i_am>(bacnet::binary_data& data, i_am &service) {
/*

    (bacnet)(service)(service), i_am,
    (bacnet::common::object_identifier, i_am_device_identifier)
    (uint32_t, max_apdu_length_accepted)
    (bacnet::common::segmentation, segmentation_supported)
    (uint16_t, vendor_id)


X'00'       Service Choice=0 (I-Am-Request)

X'C4'       Application Tag 12 (Object Identifier, L=4) (I-Am Device Identifier)
X'02000001' Device, Instance Number=1

X'22'       Application Tag 2 (Unsigned Integer, L=2) (Max APDU Length Accepted)
X'01E0'     480

X'91'       Application Tag 9 (Enumerated, L=1) (Segmentation Supported)
X'01'1      (SEGMENTED_TRANSMIT)

X'21'       Application Tag 2 (Unsigned Integer, L=1) (Vendor ID)
X'63'       99
 */

  if(data.empty()) {
    return false;
  }
  data.erase(data.begin(), data.begin()+1);

  apdu::unsigned_integer tmp_unsigned;
  apdu::object_identifier tmp_oi;
  apdu::enumeration tmp_enumeration;
  bool has_succeeded = false;

  has_succeeded = apdu::parse(data, tmp_oi);
  if(!has_succeeded) {
    std::cout << "parse<service::i_am> fail tag 0" << std::endl;
    return false;
  }
  service.i_am_device_identifier = tmp_oi.object_identifier_;
  service.i_am_device_identifier.object_typ(bacnet::object_type::device);

  has_succeeded = apdu::parse(data, tmp_unsigned);
  if(!has_succeeded) {
    std::cout << "parse<service::i_am> fail tag 1" << std::endl;
    return false;
  }
  service.max_apdu_length_accepted = tmp_unsigned.value_;


  has_succeeded = apdu::parse(data, tmp_enumeration);
  if(!has_succeeded) {
    std::cout << "parse<service::i_am> fail tag 2" << std::endl;
    return false;
  }
  service.segmentation_supported.from_native(tmp_enumeration.value_);

  has_succeeded = apdu::parse(data, tmp_unsigned);
  if(!has_succeeded) {
    std::cout << "parse<service::i_am> fail tag 3" << std::endl;
    return false;
  }
  service.vendor_id = tmp_unsigned.value_;

  return true;
}


}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_DETAIL_I_AM_GRAMMAR_HPP
