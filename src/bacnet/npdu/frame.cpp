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

