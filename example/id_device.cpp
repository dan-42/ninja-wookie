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
#include <bacnet/type/types.hpp>
#include <exception>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <boost/asio.hpp>
#include <boost/program_options.hpp>

template<typename Controller>
struct worker {

  worker(Controller& con, std::string ip) : done(false), controller(con), ep(bacnet::common::protocol::mac::address_ip{ip, 0xBAC0}) {


  }

  void run() {

    bacnet::type::object_identifier object_id{bacnet::type::object_type::device, 4194303};

    auto request = bacnet::service::service::read_property_request{object_id, bacnet::type::property::vendor_name::value};

    controller.async_send(ep, request, [this](const bacnet::error &ec,  bacnet::service::service::read_property_ack response) {
                                                          if(ec) {
                                                            std::cerr << "error occurred: " << ec <<  std::endl;
                                                          }
                                                          else {
                                                            auto t = pre::json::to_json(response);
                                                            vendor =   (t).dump() ;
                                                            if( vendor.size() >1) {
                                                             std::cout << vendor << std::endl;
                                                           }
                                                          }
                                                          this->done = true;
                                                       }
    );

  }


  bool done;
  Controller& controller;
  bacnet::common::protocol::mac::endpoint ep;

  std::string vendor;
};







template<typename Controller>
struct dispatcher {

  dispatcher(Controller& con, std::string file, boost::asio::io_service& ios) : controller(con), ifs(file), start_timer(ios) {


  }


  void run() {

    std::string line;
   uint32_t count=0;
   while (std::getline(ifs, line)) {
     count++;
     if(count == 30) {
       break;
     }

     workers.emplace_back(controller, line);
     workers.back().run();
   }


   if(count < 30) {
     start_timer.get_io_service().stop();
     return;
   }

   start_timer.expires_from_now(std::chrono::milliseconds(500));
   start_timer.async_wait([this](const boost::system::error_code& ec){
       if(!ec) {
         this->run();
       }
   });

  }






  Controller& controller;
  std::ifstream ifs;
  boost::asio::steady_timer start_timer;

  using my_worker_t = worker<Controller>;

 std::list<my_worker_t> workers;
};


int main(int argc, char *argv[]) {
  namespace prop = bacnet::type::property;

    uint16_t    port{0xBAC0};
    std::string source{"0.0.0.0"};
    std::string file{"0.0.0.0"};
    std::string target;

    uint32_t                    object_instance{4194303};
    uint32_t                    object_type{bacnet::type::object_type::device};
    uint32_t                    property{bacnet::type::property::object_name::value};
    namespace po = boost::program_options;
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help",                "sending BACnet read property: e.g.  \n")
        ("source,s",             po::value<std::string>(&source)              ->default_value("0.0.0.0"),                     "listening ip")
        ("file,f",         po::value<std::string>(&file)         ->default_value("/tmp/"),                     "file ip")
        ("target,t",         po::value<std::string>(&target),                     "target ip")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help") || vm.count("file") == 0 ) {
        std::cout << desc << std::endl<< std::endl;
        return 1;
    }


    boost::asio::io_service io_service;
    bacnet::stack::factory<bacnet::stack::ip_v4_client> factory{io_service, source, port};
    auto &service_controller = factory.controller();

    service_controller.start();


    if(vm.count("target") == 1) {

      worker<decltype(service_controller)> w(service_controller, target);

      io_service.post([&w](){w.run();});

      io_service.run();
    }
    else {

      dispatcher<decltype(service_controller)> d(service_controller, file, io_service);

      io_service.post([&d](){d.run();});
      io_service.run();

      std::cout << "---------------------" << std::endl;
      for(auto const& w : d.workers) {
        if( w.vendor.size() >1) {
          std::cout << w.vendor << std::endl;
        }
      }

    }

  return 0;
}
