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

#ifndef SRC_BACNET_NPDU_MESSAGE_TYPE_HPP_
#define SRC_BACNET_NPDU_MESSAGE_TYPE_HPP_



namespace bacnet { namespace  npdu {


namespace message_type {

static constexpr uint8_t who_is_router_to_network         = 0x00;
static constexpr uint8_t i_am_router_to_network           = 0x01;
static constexpr uint8_t i_could_be_route_to_network      = 0x02;
static constexpr uint8_t reject_message_to_network        = 0x03;
static constexpr uint8_t router_busy_to_network           = 0x04;
static constexpr uint8_t router_available_to_network      = 0x05;
static constexpr uint8_t initialize_routing_table         = 0x06;
static constexpr uint8_t initialize_routing_table_ack     = 0x07;
static constexpr uint8_t establish_connection_to_network  = 0x08;
static constexpr uint8_t disconnect_connection_to_network = 0x09;
static constexpr uint8_t challenge_request                = 0x0A;
static constexpr uint8_t security_payload                 = 0x0B;
static constexpr uint8_t security_response                = 0x0C;
static constexpr uint8_t request_key_update               = 0x0D;
static constexpr uint8_t update_key_set                   = 0x0E;
static constexpr uint8_t update_distribution_key          = 0x0F;
static constexpr uint8_t request_master_key               = 0x10;
static constexpr uint8_t set_master_key                   = 0x11;
static constexpr uint8_t what_is_network_number           = 0x12;
static constexpr uint8_t network_number_is                = 0x13;

//xxx stream operator to string
}

}}


#endif /* SRC_BACNET_NPDU_MESSAGE_TYPE_HPP_ */
