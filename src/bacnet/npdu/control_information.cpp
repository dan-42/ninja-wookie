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

#include <string>
#include <iomanip>

#include <bacnet/npdu/control_information.hpp>

namespace  bacnet { namespace npdu {


control_information::control_information() : priority_(0), has_confirmedReq_or_ComplxAck_or_expectingReply_(0),
					  has_source_specifier_(0), bit4_unused_(0), has_destination_specifier_(0),
					  bit6_unused_(0), has_network_layer_message_(0) {
}

bool control_information::has_confirmedReq_or_ComplxAck_or_expectingReply(){
	return has_confirmedReq_or_ComplxAck_or_expectingReply_==true;
}

bool control_information::has_source_specifier(){
	return has_source_specifier_==true;
}

bool control_information::has_destination_specifier(){
	return has_destination_specifier_==true;
}

bool control_information::has_network_layer_message_type(){
	return has_network_layer_message_==true;
}


std::ostream &operator<<(std::ostream &os, const bacnet::npdu::control_information &ci) {
  os << "\thas_network_layer_message: ";
  if(ci.has_network_layer_message_) { os << "true";  }
  else { os << "false" ;  }
  os << "\n";

  os << "\t  has_destination_specifier: ";
  if(ci.has_destination_specifier_) { os << "true";  }
  else { os << "false" ;  }
  os << "\n";

  os << "\t  has_source_specifier: ";
  if(ci.has_source_specifier_) { os << "true";  }
  else { os << "false" ;  }
  os << "\n";

  os << "\t  has_confirmedReq_or_ComplxAck_or_expectingReply: ";
  if(ci.has_confirmedReq_or_ComplxAck_or_expectingReply_) { os << "true";  }
  else { os << "false" ;  }
  os << "\n";

  os << "\t  priority: ";
  os << std::to_string((int) ci.priority_) ;
  os << "\n";

  return os;
}

}}


