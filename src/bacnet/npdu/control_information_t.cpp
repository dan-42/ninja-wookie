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

#include <bacnet/npdu/control_information_t.hpp>
#include <string>
#include <iomanip>


namespace  bacnet { namespace npdu {


control_information_t::control_information_t() : priority_(0), has_confirmedReq_or_ComplxAck_or_expectingReply_(0),
					  has_source_specifier_(0), bit4_unused_(0), has_destination_specifier_(0),
					  bit6_unused_(0), has_network_layer_message_(0) {
}

bacnet::npdu::network_priority_t control_information_t::network_priority() const {
  return static_cast<bacnet::npdu::network_priority_t>(priority_);
}

bool control_information_t::has_confirmed_req_OR_Complx_ack_OR_expecting_reply() const {
	return has_confirmedReq_or_ComplxAck_or_expectingReply_==true;
}

bool control_information_t::has_source_specifier() const {
	return has_source_specifier_==true;
}

bool control_information_t::has_destination_specifier() const {
	return has_destination_specifier_==true;
}

bool control_information_t::has_network_layer_message_type() const {
	return has_network_layer_message_==true;
}


std::ostream &operator<<(std::ostream &os, const bacnet::npdu::control_information_t &ci) {
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


