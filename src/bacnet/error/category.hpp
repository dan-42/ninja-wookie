/*
 * category.hpp
 *
 *  Created on: May 29, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_ERROR_CATEGORY_HPP_
#define SRC_BACNET_ERROR_CATEGORY_HPP_

#include <boost/system/error_code.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/error/error_class.hpp>
#include <bacnet/error/error_code.hpp>
#include <bacnet/error/reject_reason.hpp>
#include <bacnet/error/abort_reason.hpp>

#include <bacnet/type/enumerated.hpp>
#include <bacnet/type/object_identifier.hpp>
namespace bacnet {



namespace err {

  namespace system {    static inline std::string message(int i)  {
      return "system::" + boost::system::system_category().message(i);
  }}


  namespace generic {   static inline std::string message(int i) {
    return "generic::" + boost::system::generic_category().message(i);
  }}


  namespace abort {   static inline std::string message(int code)  {
    return "bacnet::abort::" + error_code::to_string(code) ;
  }}


  namespace reject {    static inline std::string message(int code)  {
    return "bacnet::reject::" + error_code::to_string(code) ;
  }}

  namespace error {    static inline std::string message(int code, int class_)  {
      return "bacnet::error::" + error_class::to_string(class_) + "::" + error_code::to_string(code) ;
  }}

  namespace change_list {   static inline std::string message(int code, int class_)  {
    return "bacnet::change_list::" + error_class::to_string(class_) + "::" + error_code::to_string(code) ;
  }}


  namespace create_object {    static inline std::string message(int code, int class_)  {
    return "bacnet::create_object::" + error_class::to_string(class_) + "::" + error_code::to_string(code) ;
  }}


  namespace write_property_multiple {    static inline std::string message(int code, int class_)  {
    return "bacnet::write_property_multiple::" + error_class::to_string(class_) + "::" + error_code::to_string(code) ;
  }}


  namespace confirmed_private_transfer {    static inline std::string message(int code, int class_)  {
    return "bacnet::confirmed_private_transfer::" + error_class::to_string(class_) + "::" + error_code::to_string(code) ;
  }}


  namespace vt_close {    static inline std::string message(int code, int class_)  {
    return "bacnet::vt_close::" + error_class::to_string(class_) + "::" + error_code::to_string(code) ;
  }}
}


}


#endif /* SRC_BACNET_ERROR_CATEGORY_HPP_ */
