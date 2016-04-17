/*
 * parser.hpp
 *
 *  Created on: Apr 17, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_SERVICE_SERVICE_DETAIL_PARSER_HPP_
#define SRC_BACNET_SERVICE_SERVICE_DETAIL_PARSER_HPP_


#include <bacnet/detail/common/types.hpp>

namespace bacnet { namespace service { namespace service { namespace detail {
  using namespace bacnet::service;
  static inline unconfirmed::possible_service parse(binary_data& data) {
    unconfirmed::possible_service parsed_service{};

    //todo make it nice and clean with boost spirit
    if(!data.empty()) {
      if(data.front() == uncomfirmed_service::who_is) {
        //std::cout << "unconfirmed::possible_service parse who_is " << std::endl;
        who_is service_;
        if(bacnet::service::service::detail::parse(data , service_)) {
          parsed_service = service_;
        }
        else {
          std::cout << "unconfirmed::possible_service parse who_is failed" << std::endl;
        }
      }
      else if(data.front() == uncomfirmed_service::i_am) {
        //std::cout << "unconfirmed::possible_service parse i_am " << std::endl;
        i_am service_;
        if(bacnet::service::service::detail::parse(data , service_)){
          parsed_service = service_;
        }
        else {
          std::cout << "unconfirmed::possible_service parse i_am failed" << std::endl;
        }
      }
      else {
        std::cout << "unconfirmed::possible_service parse undefined " << std::endl;
        bacnet::print(data);
      }
    }
    else {
      std::cout << "unconfirmed::possible_service parse data empty " << std::endl;
    }

    return parsed_service;
  }

}}}}



#endif /* SRC_BACNET_SERVICE_SERVICE_DETAIL_PARSER_HPP_ */
