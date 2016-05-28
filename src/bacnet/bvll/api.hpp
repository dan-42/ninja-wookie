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

#ifndef NINJA_WOOKIE_BVLL_API_HPP
#define NINJA_WOOKIE_BVLL_API_HPP

#include <functional>

#include <bacnet/bvll/frames.hpp>
#include <bacnet/common/protocol/meta_information.hpp>


namespace bacnet { namespace bvll {
typedef  std::function<void (frame::bvlc_result,                            bacnet::common::protocol::meta_information )> receive_bvlc_result_callback_t;
typedef  std::function<void (frame::write_broadcast_distribution_table,     bacnet::common::protocol::meta_information )> receive_write_broadcast_distribution_table_callback_t;
typedef  std::function<void (frame::read_broadcast_distribution_table,      bacnet::common::protocol::meta_information )> receive_read_broadcast_distribution_table_callback_t;
typedef  std::function<void (frame::read_broadcast_distribution_table_ack,  bacnet::common::protocol::meta_information )> receive_read_broadcast_distribution_table_ack_callback_t;
typedef  std::function<void (frame::forwarded_npdu,                         bacnet::common::protocol::meta_information )> receive_forwarded_npdu_callback_t;
typedef  std::function<void (frame::register_foreign_device,                bacnet::common::protocol::meta_information )> receive_register_foreign_device_callback_t;
typedef  std::function<void (frame::read_foreign_device_table,              bacnet::common::protocol::meta_information )> receive_read_foreign_device_table_callback_t;
typedef  std::function<void (frame::read_foreign_device_table_ack,          bacnet::common::protocol::meta_information )> receive_read_foreign_device_table_ack_callback_t;
typedef  std::function<void (frame::delete_foreign_device_table_entry,      bacnet::common::protocol::meta_information )> receive_delete_foreign_device_table_entry_callback_t;
typedef  std::function<void (frame::distribute_broadcast_to_network,        bacnet::common::protocol::meta_information )> receive_distribute_broadcast_to_network_callback_t;
typedef  std::function<void (frame::original_unicast_npdu,                  bacnet::common::protocol::meta_information )> receive_original_unicast_npdu_callback_t;
typedef  std::function<void (frame::original_broadcast_npdu,                bacnet::common::protocol::meta_information )> receive_original_broadcast_npdu_callback_t;
typedef  std::function<void (frame::original_secure_bvll,                   bacnet::common::protocol::meta_information )> receive_original_secure_bvll_callback_t;
typedef  std::function<void (frame::raw,                                    bacnet::common::protocol::meta_information )> receive_raw_callback_t;
}}



#endif //NINJA_WOOKIE_BVLL_API_HPP
