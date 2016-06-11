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

#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_read_property_ack_grammar_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_read_property_ack_grammar_HPP

#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/optional/optional_io.hpp>
#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/type/tag.hpp>
#include <bacnet/apdu/type/detail/object_identifier_grammar.hpp>
#include <bacnet/apdu/type/detail/unsigned_integer_grammar.hpp>
#include <bacnet/apdu/type/detail/possible_type_grammar.hpp>
#include <bacnet/service/service/read_property_ack.hpp>
#include <bacnet/type/properties.hpp>
#include <bacnet/type/object_identifier.hpp>

/*
 * notes
 * http://stackoverflow.com/questions/23763233/boost-spirit-using-local-variables
 * http://stackoverflow.com/questions/12653407/runtime-value-to-type-mapping
 * http://gpfault.net/posts/mapping-types-to-values.txt.html
 */

namespace bacnet { namespace service { namespace service { namespace detail { namespace parser {
//
/*

typedef uint32_t                                                         property_t;
typedef uint32_t                                                          objct_t;
typedef boost::spirit::qi::rule<bacnet::parse_iterator, possible_type()> rule_t;

struct property_grammar {
    virtual ~property_grammar() {}
    virtual rule_t& rule() = 0;
};

template <typename T>
struct property_grammar_impl: public property_grammar {
public:
  property_grammar_impl() : t_(){
    rule_ = t_;
  }

  virtual rule_t& rule() {
    return rule_;
  }

private:
  rule_t rule_;
  T t_;
};

template <typename T>
std::unique_ptr<property_grammar> make_property_grammar() {
    return std::unique_ptr<property_grammar>(new property_grammar_impl<T>());
}


using maker = std::unique_ptr<property_grammar> (&)();
using property_grammar_map = std::map<property_t, maker>;
using object_property_map = std::map<objct_t, property_grammar_map>;

rule_t& select(const object_identifier& o_id, const property_t p)  {
    auto o = o_id.object_type;

    namespace prop = bacnet::type::property;
    namespace obj = bacnet::object_type;

    static property_grammar_impl<possible_type_grammar<bacnet::parse_iterator>> default_grammar;
    //static object_property_map opject_m;
    static property_grammar_map map;

    if (map.empty()) {
      map.insert(std::make_pair(77, make_property_grammar<character_string_grammar<bacnet::parse_iterator>>));
      map.insert(std::make_pair(76, make_property_grammar<character_string_grammar<bacnet::parse_iterator>>));
    //  opject_m.insert(std::make_pair(obj::device, std::move(map)));
    }

    auto it_obj = opject_m.find(o);
    if (it_obj == opject_m.end() || it_obj->second.empty()) {
      return default_grammar.rule();
    }

    property_grammar_map &prop_m  = it_obj->second;
    auto it_prop = prop_m.find(p);
    if (it_prop == prop_m.end() || it_prop->second == nullptr) {
      return default_grammar.rule();
    }
    return (*it_prop->second)()->rule();
 }

//*/
typedef boost::spirit::qi::rule<bacnet::parse_iterator, possible_type()>                           any_rule_t;

inline any_rule_t* select(const object_identifier& r1,const uint32_t& r2, const boost::optional<uint32_t>& r3) {
    std::cout << "r1 " << r1 << std::endl;
    std::cout << "r2 " << r2 << std::endl;
    std::cout << "r3 " << r3.value_or(0) << std::endl;
    static possible_type_grammar<bacnet::parse_iterator>                                   tag_3_rule_{3};
    static any_rule_t rule;

    rule %= tag_3_rule_;


    return &rule;

  }


using namespace boost::spirit;
using namespace boost::spirit::qi;

using namespace bacnet::apdu::type;
using namespace bacnet::apdu::type::detail::parser;

template<typename Iterator>
struct read_property_ack_grammar : grammar<Iterator, service::read_property_ack() , locals<object_identifier, uint32_t, boost::optional<uint32_t> > > {

  typedef rule<Iterator, possible_type()>                           any_rule_t;

  rule<Iterator, service::read_property_ack(),
                 locals<object_identifier,
                       uint32_t,
                       boost::optional<uint32_t> >>                 start_rule;

  rule<Iterator, object_identifier()>                               object_identifier_rule;
  rule<Iterator, uint32_t()>                                        property_identifier_rule;
  rule<Iterator, boost::optional<uint32_t>()>                       property_array_index_rule;
  rule<Iterator, bacnet::type::possible_type(
                                              object_identifier,
                                              uint32_t,
                                              boost::optional<uint32_t>
                                            ),
                                            locals< any_rule_t*> >  possible_type_grammar_rule;

  rule<Iterator>                                                    select_rule;
  any_rule_t                                                        any_rule;

  object_identifier_grammar<Iterator>                               tag_0_rule_{0};
  unsigned_integer_grammar<Iterator>                                tag_1_rule_{1};
  unsigned_integer_grammar<Iterator>                                tag_2_rule_{2};
  possible_type_grammar<Iterator>                                   tag_3_rule_{3};

  read_property_ack_grammar() : read_property_ack_grammar::base_type(start_rule) {

    start_rule                          %=  byte_(service_choice<service::read_property_ack>::value)
                                        >>  object_identifier_rule   [ _a = _1]
                                        >>  property_identifier_rule [ _b = _1]
                                        >>  property_array_index_rule[ _c = _1]
                                        >>  possible_type_grammar_rule(_a, _b, _c  )
                                        ;

    object_identifier_rule              =   tag_0_rule_;
    property_identifier_rule            =   tag_1_rule_;
    property_array_index_rule           =  -tag_2_rule_;

  //possible_type_grammar_rule          %=  (select_rule[_a = boost::phoenix::bind(&read_property_ack_grammar::select_grammr, this, _r1, _r2, _r3)]
    possible_type_grammar_rule          %=  (select_rule[_a = boost::phoenix::bind(&select, _r1, _r2, _r3)]
                                        >>  qi::lazy(*_a));

    any_rule                            %=  tag_3_rule_;

    select_rule                          =  eps;



    //    /*
    start_rule.name("read_property_ack_grammar_start_rule");
    object_identifier_rule.name("object_identifier_rule");
    property_identifier_rule.name("property_identifier_rule");
    property_array_index_rule.name("property_array_index_rule");
    possible_type_grammar_rule.name("possible_type_grammar_rule");
    select_rule.name("select_rule");
    any_rule.name("any_rule");
    select_rule.name("select_rule");

    debug(start_rule);
    debug(object_identifier_rule);
    debug(property_identifier_rule);
    debug(property_array_index_rule);
    debug(possible_type_grammar_rule);
    debug(select_rule);
    debug(any_rule);
    debug(select_rule);
    // */
  }

  inline any_rule_t* select_grammr(const object_identifier& r1,const uint32_t& r2, const boost::optional<uint32_t>& r3) {
    /*std::cout << "r1 " << r1 << std::endl;
    std::cout << "r2 " << r2 << std::endl;
    std::cout << "r3 " << r3.value_or(0) << std::endl;
    return &any_rule;*/

    return select(r1, r2,r3);

  }

};


}}}}}

namespace bacnet { namespace service { namespace service { namespace detail {  namespace generator {


using namespace boost::spirit;
using namespace boost::spirit::karma;
using namespace bacnet::apdu::type;
using namespace bacnet::apdu::type::detail::generator;

template<typename Iterator>
struct read_property_ack_grammar : grammar<Iterator, service::read_property_ack()> {
  rule<Iterator, service::read_property_ack()>      start_rule;
  rule<Iterator, object_identifier()>           object_identifier_rule;
  rule<Iterator, uint32_t()>                    property_identifier_rule;
  rule<Iterator, boost::optional<uint32_t>()>   property_array_index_rule;
  rule<Iterator, bacnet::binary_data()>         binary_data_rule;

  object_identifier_grammar<Iterator>      tag_0_rule_{0};
  unsigned_integer_grammar<Iterator>       tag_1_rule_{1};
  unsigned_integer_grammar<Iterator>       tag_2_rule_{2};

  read_property_ack_grammar() : read_property_ack_grammar::base_type(start_rule) {

    start_rule                          =  byte_(service_choice<service::read_property_ack>::value)
                                        << object_identifier_rule
                                        << property_identifier_rule
                                        << property_array_index_rule
                                        ;

    object_identifier_rule              =  tag_0_rule_;
    property_identifier_rule            =  tag_1_rule_;
    property_array_index_rule           = -tag_2_rule_;

  }
};


}}}}}


#endif //NINJA_WOOKIE_BACNET_SERVICE_SERCICE_DETAIL_read_property_ack_grammar_HPP
