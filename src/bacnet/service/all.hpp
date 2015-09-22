//
// Created by dan on 20.09.15.
//

#ifndef NINJA_WOOKIE_BACNET_SERVICE_CHOICE_ALL_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_CHOICE_ALL_HPP

#include <boost/variant.hpp>

#include <bacnet/service/who_is.hpp>
#include <bacnet/service/i_am.hpp>


namespace bacnet { namespace service {
      typedef boost::variant<
          who_is,
          i_am
      > possible_service;
}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_CHOICE_ALL_HPP
