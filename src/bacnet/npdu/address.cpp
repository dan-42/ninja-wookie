/*
 * address.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */



#include <iostream>
#include <iomanip>


#include <bacnet/npdu/address.hpp>



std::ostream &operator<<(std::ostream &os, const bacnet::npdu::address &a) {
  os << "bacnet::npdu::address " << (int)a.network_number << ":";
  for(auto &b : a.binary_address){
    os <<  std::setfill ('0') << std::setw(2) << std::hex << (int)b << " ";
  }
  return os;
}

