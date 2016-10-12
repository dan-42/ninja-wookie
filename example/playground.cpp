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


#include <iostream>

#include <string>
#include <vector>
#include <cstdint>



struct parser_int32 {

  template<typename Iter >
  inline bool parse(Iter& begin, Iter const& end, uint32_t& attr) {
    Iter iter = begin;
    for(int i = 32; i > 0; i-=8 ) {
      if(iter == end) { return false; }
      attr |= (*iter) << i;
      iter++;
    }
    begin = iter;
    return true;
  }

};





struct my_ints {

  uint32_t a{};
  uint32_t b{};
  uint32_t c{};

};


struct my_ints_parser {

  template<typename Iter >
  inline bool parse(Iter& begin, Iter const& end, my_ints& attr) {
    static parser_int32 parser{};

    if(     parser.parse(begin, end, attr.a)
        &&  parser.parse(begin, end, attr.b)
        &&  parser.parse(begin, end, attr.c) ) {

      return true;
    }
    return  false;
  }

};


int main(int argc, char *argv[]) {


  std::vector<uint8_t> binary_data;
  binary_data.emplace_back(0x01);
  binary_data.emplace_back(0x01);
  binary_data.emplace_back(0x01);
  binary_data.emplace_back(0x01);

  {
      uint32_t value{0};
      parser_int32 parser;
      auto b = binary_data.begin();
      auto e = binary_data.end();
      if(parser.parse(b, e, value)) {
        std::cout << "success value " << value << std::endl;
      }
      else {
        std::cout << "failed" << std::endl;
      }
  }


  binary_data.emplace_back(0x02);
  binary_data.emplace_back(0x02);
  binary_data.emplace_back(0x02);
  binary_data.emplace_back(0x02);
  binary_data.emplace_back(0x03);
  binary_data.emplace_back(0x03);
  binary_data.emplace_back(0x03);
  binary_data.emplace_back(0x03);

  {
      my_ints value;
      my_ints_parser parser;
      auto b = binary_data.begin();
      auto e = binary_data.end();
      if(parser.parse(b, e, value)) {
        std::cout << "success value.a " << value.a <<  std::endl;
        std::cout << "success value.b " << value.b <<  std::endl;
        std::cout << "success value.c " << value.c <<  std::endl;
      }
      else {
        std::cout << "failed" << std::endl;
      }
    }





  //bacnet::type::property::supported_properties t;

/*
  bacnet::object_ptr_list_t object_list;

  auto ai_ptr = std::make_shared<bacnet::analog_input>();
  auto ao_ptr = std::make_shared<bacnet::analog_output>();
  object_list.push_back(ai_ptr);
  object_list.push_back(ao_ptr);

  uint16_t property_id{0};
  boost::optional<uint16_t> index;
  bacnet::binary_data data{};

  for(auto& o : object_list) {
    o->write_prop(property_id, index, data);
    o->read_prop(property_id, index);
  }
*/



}
