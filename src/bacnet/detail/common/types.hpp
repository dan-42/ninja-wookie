/*
 * types.hpp
 *
 *  Created on: May 20, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_TYPES_HPP_
#define SRC_BACNET_TYPES_HPP_

#include <vector>
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <mapbox/boost_spirit_qi.hpp>
#include <mapbox/boost_spirit_karma.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/home/support/unused.hpp>
#include <boost/spirit/home/support/attributes.hpp>


namespace bacnet { namespace detail { namespace common {

/**
 * used for holding binary data
 */
typedef std::vector<uint8_t> binary_data;

typedef std::back_insert_iterator<binary_data> generate_iterator;

typedef binary_data::iterator                   parse_iterator;


}}}


namespace bacnet {

/* make it accessable via bacnet namespace */
using detail::common::binary_data;
using detail::common::generate_iterator;
using detail::common::parse_iterator;

  struct hex_string{};
  struct binary_string{};

  template<typename T=binary_string>
  inline binary_data make_binary(const std::string& s){
    return binary_data(s.begin(), s.end());
  }

  template<>
  inline binary_data make_binary<hex_string>(const std::string& s){
    binary_data d;
    using boost::spirit::qi::parse;
    using boost::spirit::qi::repeat;
    using boost::spirit::qi::uint_parser;
    using boost::spirit::qi::phrase_parse;
    using boost::spirit::qi::ascii::space;
    uint_parser<uint8_t, 16, 2, 2> hex8;

    auto start = s.begin();
    auto end = s.end();

    auto success = phrase_parse(start, end, (*hex8), space, d);
    if(success) {
      return d;
    }
    else {
      throw std::runtime_error("can not parse string to binary");
    }
  }


  inline void print(const binary_data &data) {
    for(auto &c : data)
      std::cout << " 0x" << std::setfill('0') << std::setw(2) << std::hex << (int)c;
    std::cout << std::endl;
  }

}

namespace boost { namespace spirit { namespace traits {



    template <>
    struct token_printer_debug<bacnet::binary_data> {
        template<typename Out>
        static void print(Out& o, bacnet::binary_data const& val) {
          for(auto &c : val)
            o << " 0x" << std::setfill('0') << std::setw(2) << std::hex << (int)c;
        }
    };

    template <>
    struct token_printer_debug<uint8_t> {
        template<typename Out>
        static void print(Out& o, uint8_t const& val) {
            o << " 0x" << std::setfill('0') << std::setw(2) << std::hex << (int)val;
        }
    };

    template <>
    struct token_printer_debug<std::string> {
        template<typename Out>
        static void print(Out& o, std::string const& val) {
          for(auto &c : val)
            o << " 0x" << std::setfill('0') << std::setw(2) << std::hex << (int)c;
        }
    };

}}}

#endif /* SRC_BACNET_TYPES_HPP_ */
