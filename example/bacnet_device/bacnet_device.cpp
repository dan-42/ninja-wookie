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

#include <bacnet/stack/factory.hpp>
#include <bacnet/type/properties.hpp>
#include <exception>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include <bacnet_device/object/device.hpp>


namespace bacnet {


template<typename ServiceController>
struct device {

	device(ServiceController& sc) : service_controller_(sc) {

	}
	virtual ~device(){}


	void start() {
		service_controller_.start();
	}


	void init() {
		service_controller_.async_receive(
		      [&](bacnet::service::i_am s, bacnet::error ec, bacnet::common::protocol::meta_information mi){
		        std::cout << "received i_am" << std::endl;
		        // no action needed
		      },
		      [&](bacnet::service::who_is s, bacnet::error ec, bacnet::common::protocol::meta_information mi){
		        std::cout << "received who_is" << std::endl;
		        //no response needed, done automatically in the service-layer
		      },
		      [&](bacnet::service::reinitialize_device s, bacnet::error ec, bacnet::common::protocol::meta_information mi){

		        if(    s.password
		            && s.password.get().value == "12345"
		            && s.reinitialize_state_of_device.value == 3            ) {
		          std::cout << "received reinit  success invoked_id " << (int)mi.invoke_id << "  " << mi.address.to_string() << std::endl;
		          auto success = bacnet::make_success();
		          service_controller_.async_send_response(success, mi, [](bacnet::error e){
		            std::cout << "received reinit  response "  << e << std::endl;
		          });
		        }
		        else {
		          std::cout << "received reinit  error "  << mi.address.to_string() << std::endl;
		          auto error = bacnet::make_error(bacnet::err::error_code::password_failure, bacnet::err::error_class::device);
		          service_controller_.async_send_response(error, mi, [](bacnet::error e){
		            std::cout << "received reinit  response "  << e << std::endl;
		          });
		        }
		      },


		      [&](bacnet::service::read_property_request s, bacnet::error ec, bacnet::common::protocol::meta_information mi) {

		    	 auto object_itr = object_map_.find(s.object_identifier.to_native());
		    	 if(object_itr == object_map_.end() || (*object_itr).second == nullptr ) {
		    		 auto error = bacnet::make_error(bacnet::err::error_class::object, bacnet::err::error_code::unknown_object);
		    		 service_controller_.async_send_response(error, mi, [](bacnet::error e){      });
		    		 return;
		    	 }
		    	 else {
		    		 auto object_ptr = (*object_itr).second;
		    		 auto result =  object_ptr->read_prop(s.property_identifier, s.property_array_index);

		    		 if(result) {
		    		   service_controller_.async_send_response(result.error, mi, [](bacnet::error e){      });
             }
		    		 else {
		    		   bacnet::service::read_property_ack ack{s, result.value};
		    		   service_controller_.async_send_response(ack, mi, [](bacnet::error e){      });
		    		 }

		    	 }

		      }
		    );

	}









	ServiceController &service_controller_;
	object::object_ptr_map_t object_map_;

};


}//bacnet








int main(int argc, char *argv[]) {


  try {
    uint16_t    doi{2};
    uint16_t    port{0xBAC0};
  //  std::string ip{"192.168.10.204"};
    std::string ip{"0.0.0.0"};


    if(argc == 2 ) {
      doi       = (uint16_t)std::stoi(argv[1]);
    }
    else {
      std::cout
      << "error wrong parameters" << std::endl
      << "usage: " << std::endl
      << "\t" << argv[0] << " [doi] " << std::endl
      << std::endl
      << std::endl;

      return 1;
    }


    std::cout
    << "starting device  "
    << " doi: "     << doi
    << " on " << ip << ":"  << port
    << std::endl;

    boost::asio::io_service io_service;
    bacnet::config config;

    config.device_object_id = doi;
    config.network_number 	= 1;
    config.send_i_am_frames = true;


    bacnet::stack::factory<bacnet::stack::ip_v4_server> factory{io_service, ip, port, config};
    auto device_ = bacnet::device<bacnet::stack::detail::ip_v4::service_controller_t>(factory.controller() );
    device_.init();
    device_.start();


    io_service.run();
  }
  catch (const std::exception &e) {
    std::cerr << "Exception: " << e.what() << "\n";
    throw;
  }

  return 0;
}
