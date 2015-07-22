/*
 * frame.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */



#include <iomanip>

#include <bacnet/npdu/frame.hpp>

std::ostream &operator<<(std::ostream &os, const bacnet::npdu::frame &f) {

  os << "bacnet::npdu::frame version: " <<  std::setfill ('0') << std::setw(2) << std::hex << (int)f.protocol_version << "\n";
  os << "\t control_information: " << f.control_field << "\n";
  os << "\t destination: " << f.destination << "\n";
  os << "\t source: " << f.source << "\n";
  os << "\t hop_count: " <<  std::setfill ('0') << std::setw(2) << std::hex << (int)f.hop_count << "\n";
  os << "\t message_type: " <<  std::setfill ('0') << std::setw(2) << std::hex << (int)f.message_type << "\n";
  os << "\t vendor_id: " <<  std::setfill ('0') << std::setw(2) << std::hex << (int)f.vendor_id << "\n";
  os << "\t apdu_data: ";

  for(auto &b : f.apdu_data){
    os <<  std::setfill ('0') << std::setw(2) << std::hex << (int)b << " ";
  }
  os << "\n";

  return os;
}

