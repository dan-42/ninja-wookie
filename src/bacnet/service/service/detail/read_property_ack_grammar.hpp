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
#include <bacnet/apdu/type/detail/primitive/object_identifier_grammar.hpp>
#include <bacnet/apdu/type/detail/primitive/unsigned_integer_grammar.hpp>
#include <bacnet/apdu/type/detail/possible_type_grammar.hpp>
#include <bacnet/apdu/type/detail/constructed_type.hpp>
#include <bacnet/service/service/read_property_ack.hpp>
#include <bacnet/type/properties.hpp>
#include <bacnet/type/object_identifier.hpp>
#include <bacnet/object/mapping.hpp>

namespace bacnet { namespace service { namespace service { namespace detail { namespace parser {

namespace type = bacnet::type;
typedef uint32_t                                                          property_t;
typedef uint32_t                                                          objct_t;
typedef boost::spirit::qi::rule<bacnet::parse_iterator, type::possible_type()>  rule_t;

struct property_grammar {
    virtual ~property_grammar() {}
    virtual rule_t* rule() = 0;
};

template <typename T>
struct property_grammar_impl: public property_grammar {
public:
  property_grammar_impl() : t_(){
    rule_ %= t_;
  }

  virtual rule_t* rule() final {
    return &rule_;
  }

private:
  rule_t rule_;
  T t_;
};


typedef std::unique_ptr<property_grammar> property_grammar_ptr;

template <typename T>
property_grammar_ptr make_property_grammar() {
    return property_grammar_ptr(new property_grammar_impl<T>());
}

using property_grammar_map = std::map<mapping::type, property_grammar_ptr>;




template<typename Iterator>
rule_t* select(const object_identifier& r1,const uint32_t& p, const boost::optional<uint32_t>& r3) {

    namespace prop    = bacnet::type::property;
    namespace obj     = bacnet::object_type;
    namespace grammar = bacnet::apdu::type::detail::parser;

    static property_grammar_ptr default_rule;
    if(default_rule == nullptr) {
      default_rule = make_property_grammar<grammar::possible_type_grammar<Iterator> >();
    }

    static property_grammar_map map;

    if (map.empty()) {
        // primitive types
        map.insert(  std::make_pair( mapping::type::application_tagged_type,           make_property_grammar<grammar::possible_type_grammar<Iterator>>()             ));
        map.insert(  std::make_pair( mapping::type::null,                              make_property_grammar<grammar::null_grammar<Iterator>>()                      ));
        map.insert(  std::make_pair( mapping::type::boolean,                           make_property_grammar<grammar::boolean_grammar<Iterator>>()                   ));
        map.insert(  std::make_pair( mapping::type::unsigned_integer,                  make_property_grammar<grammar::unsigned_integer_grammar<Iterator>>()          ));
        map.insert(  std::make_pair( mapping::type::signed_integer,                    make_property_grammar<grammar::signed_integer_grammar<Iterator>>()            ));
        map.insert(  std::make_pair( mapping::type::real,                              make_property_grammar<grammar::real_grammar<Iterator>>()                      ));
        map.insert(  std::make_pair( mapping::type::double_pressision,                 make_property_grammar<grammar::double_presision_grammar<Iterator>>()          ));
        map.insert(  std::make_pair( mapping::type::octet_string,                      make_property_grammar<grammar::octet_string_grammar<Iterator>>()              ));
        map.insert(  std::make_pair( mapping::type::character_string,                  make_property_grammar<grammar::character_string_grammar<Iterator>>()          ));
        map.insert(  std::make_pair( mapping::type::bit_string,                        make_property_grammar<grammar::bit_string_grammar<Iterator>>()                ));
        map.insert(  std::make_pair( mapping::type::enumerated,                        make_property_grammar<grammar::enumeration_grammar<Iterator>>()               ));
        map.insert(  std::make_pair( mapping::type::date,                              make_property_grammar<grammar::date_grammar<Iterator>>()                      ));
        map.insert(  std::make_pair( mapping::type::time,                              make_property_grammar<grammar::time_grammar<Iterator>>()                      ));
        map.insert(  std::make_pair( mapping::type::object_identifier,                 make_property_grammar<grammar::object_identifier_grammar<Iterator>>()         ));
        //special / constructed types
//      map.insert(  std::make_pair( mapping::type::error,                             make_property_grammar<grammar::error_grammar<Iterator>>()                     ));
//      map.insert(  std::make_pair( mapping::type::date_time,                         make_property_grammar<grammar::date_time_grammar<Iterator>>()                 ));
    }

    auto t = mapping::select(r1.object_type, p);

    auto it_obj = map.find(t);
    if (it_obj == map.end()  || it_obj->second == nullptr) {
      std::cout << "using default grammar for objt_t " << r1.object_type << "  and prop " << p << std::endl;
      return default_rule->rule();
    }
    std::cout << "using mapped grammar for objt_t " << r1.object_type << "  and prop " << p << std::endl;
    return (it_obj->second)->rule();

 }

//*/







using namespace boost::spirit;
using namespace boost::spirit::qi;

using namespace bacnet::apdu::type::detail::parser;

template<typename Iterator>
struct read_property_ack_grammar : grammar<Iterator, service::read_property_ack() , locals<object_identifier, uint32_t, boost::optional<uint32_t> > >, constructed_type {

  typedef rule<Iterator, type::possible_type()>                     any_rule_t;

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
                          locals< any_rule_t*> >                    possible_type_grammar_rule;

  rule<Iterator>                                                    select_rule;
  rule<Iterator>                                                    open_tag_3_rule;
  rule<Iterator>                                                    close_tag_3_rule;

  object_identifier_grammar<Iterator>                               tag_0_rule_{0};
  unsigned_integer_grammar<Iterator>                                tag_1_rule_{1};
  unsigned_integer_grammar<Iterator>                                tag_2_rule_{2};
  tag_grammar<Iterator>                                             tag_grammar_;

  read_property_ack_grammar() : read_property_ack_grammar::base_type(start_rule), constructed_type(3) {

    start_rule                          %=  byte_(service_choice<service::read_property_ack>::value)
                                        >>  object_identifier_rule   [ _a = _1]
                                        >>  property_identifier_rule [ _b = _1]
                                        >>  property_array_index_rule[ _c = _1]
                                        >>  possible_type_grammar_rule(_a, _b, _c  )
                                        ;

    object_identifier_rule              =   tag_0_rule_;
    property_identifier_rule            =   tag_1_rule_;
    property_array_index_rule           =  -tag_2_rule_;

    possible_type_grammar_rule          %=  open_tag_3_rule
                                        >>  (
                                              select_rule[_a = boost::phoenix::bind(&select<Iterator>, _r1, _r2, _r3)]
                                        >>   (   (*qi::lazy(*_a))
                                              |   qi::lazy(*_a)
                                             )
                                            )
                                        >>  close_tag_3_rule
                                        ;

    select_rule                         =   eps;

    open_tag_3_rule                     =  tag_grammar_[ boost::phoenix::bind(&read_property_ack_grammar::check_open_tag,  this, _1, _pass) ];
    close_tag_3_rule                    =  tag_grammar_[ boost::phoenix::bind(&read_property_ack_grammar::check_close_tag, this, _1, _pass) ];

    //
    /*
    start_rule                  .name("read_property_ack_grammar_start_rule");
    object_identifier_rule      .name("object_identifier_rule");
    property_identifier_rule    .name("property_identifier_rule");
    property_array_index_rule   .name("property_array_index_rule");
    possible_type_grammar_rule  .name("possible_type_grammar_rule");
    select_rule                 .name("select_rule");
    debug(start_rule);
    debug(object_identifier_rule);
    debug(property_identifier_rule);
    debug(property_array_index_rule);
    debug(possible_type_grammar_rule);
    debug(select_rule);
    // */
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
