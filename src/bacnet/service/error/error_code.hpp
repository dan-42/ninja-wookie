//
// Created by dan on 10.10.15.
//

#ifndef NINJA_WOOKIE_BACNET_SERVICE_ERROR_CODE_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_ERROR_CODE_HPP

#include <string>
#include <iostream>

#include <boost/system/error_code.hpp>

namespace  bacnet { namespace service { namespace  error {


namespace errc {
  enum errc_t {
    success = 0,
    error = 1
  };

} // namespace errc

class error_category : public boost::system::error_category {
public:
  const char *name() const noexcept {
    return "bacnet::service::";
  }

  std::string message(int ev) const {

    switch (ev) {
      case (errc::success) :
        return "success";
      case (errc::error) :
        return "generic error";
    }

    return "undefined error";
  }
};

const error_category& get_error_category() {
  static error_category error_category_;
  return error_category_;
}

}}}



      /*


}}}

namespace  boost { namespace system {
  static  error_category &boost::system::bacnet_category() {
    return bacnet::service::error::get_error_category();
  }
}}
       */
#endif //NINJA_WOOKIE_BACNET_SERVICE_ERROR_CODE_HPP
