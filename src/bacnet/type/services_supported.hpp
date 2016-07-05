/*
 * services_supported.hpp
 *
 *  Created on: Jun 26, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_SERVICES_SUPPORTED_HPP_
#define SRC_BACNET_TYPE_SERVICES_SUPPORTED_HPP_



#include <bacnet/type/bit_string.hpp>

namespace bacnet { namespace type {

/**
 * \brief the values represent the index of the bit-string indicating the supported services
 */
struct services_supported {
  typedef bit_string::size_type type;


  services_supported(bit_string bs) : value_(std::move(bs)) {
  }


  static constexpr type acknowledge_alarm                       =  0;
  static constexpr type confirmed_change_of_value_notification  =  1;
  static constexpr type confirmed_event_notification            =  2;
  static constexpr type get_alarm_summary                       =  3;
  static constexpr type get_enrollment_summary                  =  4;
  static constexpr type subscribe_change_of_value               =  5;
  static constexpr type atomic_read_file                        =  6;
  static constexpr type atomic_write_file                       =  7;
  static constexpr type add_list_element                        =  8;
  static constexpr type remove_list_element                     =  9;

  static constexpr type create_object                           = 10;
  static constexpr type delete_object                           = 11;
  static constexpr type read_property                           = 12;
  static constexpr type read_property_conditional               = 13;//, removed in version 1 revision 12
  static constexpr type read_property_multiple                  = 14;
  static constexpr type write_property                          = 15;
  static constexpr type write_property_multiple                 = 16;
  static constexpr type device_communication_control            = 17;
  static constexpr type confirmed_private_transfer              = 18;
  static constexpr type confirmed_text_message                  = 19;

  static constexpr type reinitialize_device                     = 20;
  static constexpr type vt_open                                 = 21;
  static constexpr type vt_close                                = 22;
  static constexpr type vt_data                                 = 23;
  static constexpr type authenticate                            = 24;//, removed in version 1 revision 11
  static constexpr type request_key                             = 25;//, removed in version 1 revision 11
  static constexpr type i_am                                    = 26;
  static constexpr type i_have                                  = 27;
  static constexpr type unconfirmed_change_of_value_notification= 28;
  static constexpr type unconfirmed_event_notification          = 29;

  static constexpr type unconfirmed_private_transfer            = 30;
  static constexpr type unconfirmed_text_message                = 31;
  static constexpr type time_synchronization                    = 32;
  static constexpr type who_has                                 = 33;
  static constexpr type who_is                                  = 34;
  static constexpr type read_range                              = 35;
  static constexpr type utc_time_synchronization                = 36;
  static constexpr type life_safety_operation                   = 37;
  static constexpr type subscribe_change_of_value_property      = 38;
  static constexpr type get_event_information                   = 39;
  static constexpr type write_group                             = 40;

  static constexpr type revision_14_size                        = 40;



  inline std::string to_string() const {

    std::stringstream os;
      os << "\"services_supported\" = {";
      for(bit_string::size_type idx = 0; idx < value_.size(); ++idx) {
        if(value_[idx]) {
          os << "\"";
          switch(idx) {
            case services_supported::acknowledge_alarm                            : os << "acknowledge_alarm";                        break;
            case services_supported::confirmed_change_of_value_notification       : os << "confirmed_change_of_value_notification";   break;
            case services_supported::confirmed_event_notification                 : os << "confirmed_event_notification";             break;
            case services_supported::get_alarm_summary                            : os << "get_alarm_summary";                        break;
            case services_supported::get_enrollment_summary                       : os << "get_enrollment_summary";                   break;
            case services_supported::subscribe_change_of_value                    : os << "subscribe_change_of_value";                break;
            case services_supported::atomic_read_file                             : os << "atomic_read_file";                         break;
            case services_supported::atomic_write_file                            : os << "atomic_write_file";                        break;
            case services_supported::add_list_element                             : os << "add_list_element";                         break;
            case services_supported::remove_list_element                          : os << "remove_list_element";                      break;

            case services_supported::create_object                                : os << "create_object";                            break;
            case services_supported::delete_object                                : os << "delete_object";                            break;
            case services_supported::read_property                                : os << "read_property";                            break;
            case services_supported::read_property_conditional                    : os << "read_property_conditional";                break;
            case services_supported::read_property_multiple                       : os << "read_property_multiple";                   break;
            case services_supported::write_property                               : os << "write_property";                           break;
            case services_supported::write_property_multiple                      : os << "write_property_multiple";                  break;
            case services_supported::device_communication_control                 : os << "device_communication_control";             break;
            case services_supported::confirmed_private_transfer                   : os << "confirmed_private_transfer";               break;
            case services_supported::confirmed_text_message                       : os << "confirmed_text_message";                   break;

            case services_supported::reinitialize_device                          : os << "reinitialize_device";                      break;
            case services_supported::vt_open                                      : os << "vt_open";                                  break;
            case services_supported::vt_close                                     : os << "vt_close";                                 break;
            case services_supported::vt_data                                      : os << "vt_data";                                  break;
            case services_supported::authenticate                                 : os << "authenticate";                             break;
            case services_supported::request_key                                  : os << "request_key";                              break;
            case services_supported::i_am                                         : os << "i_Am";                                     break;
            case services_supported::i_have                                       : os << "i_have";                                   break;
            case services_supported::unconfirmed_change_of_value_notification     : os << "unconfirmed_change_of_value_notification"; break;
            case services_supported::unconfirmed_event_notification               : os << "unconfirmed_event_notification";           break;

            case services_supported::unconfirmed_private_transfer                 : os << "unconfirmed_private_transfer";             break;
            case services_supported::unconfirmed_text_message                     : os << "unconfirmed_text_message";                 break;
            case services_supported::time_synchronization                         : os << "time_synchronization";                     break;
            case services_supported::who_has                                      : os << "who_has";                                  break;
            case services_supported::who_is                                       : os << "who_is";                                   break;
            case services_supported::read_range                                   : os << "read_range";                               break;
            case services_supported::utc_time_synchronization                     : os << "utc_time_synchronization";                 break;
            case services_supported::life_safety_operation                        : os << "life_safety_operation";                    break;
            case services_supported::subscribe_change_of_value_property           : os << "subscribe_change_of_value_property";       break;
            case services_supported::get_event_information                        : os << "get_event_information";                    break;
            case services_supported::write_group                                  : os << "write_group";                              break;

            default                                                               : os << "unknown_service(" << idx << ")";           break;
          }
          os << "\",";
        }
      }
      os << "}";
      return os.str();
  }

  template<typename OStream>
  friend OStream& operator<<(OStream& os, const services_supported& ss) {
    os << ss.to_string();
    return os;
  }

private:
  bit_string value_;
};

static inline bit_string make_services_supported() {
  bit_string bs(services_supported::revision_14_size, false);
  return bs;
}

static inline bit_string make_services_supported(const std::vector<bit_string::size_type>& supported) {
  bit_string bs(services_supported::revision_14_size, false);

  for(auto& s : supported) {
    if(s < bs.size()) {
      bs[s] = true;
    }
  }
  return bs;
}


}}



#endif /* SRC_BACNET_TYPE_SERVICES_SUPPORTED_HPP_ */
