/*
 * object_type.hpp
 *
 *  Created on: Jun 25, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_TYPE_OBJECT_TYPE_HPP_
#define SRC_BACNET_TYPE_OBJECT_TYPE_HPP_



#include <bacnet/type/enumerated.hpp>


namespace bacnet { namespace type {


struct object_type {
  typedef uint32_t type;

  static constexpr uint32_t analog_input              = 0;
  static constexpr uint32_t analog_output             = 1;
  static constexpr uint32_t analog_value              = 2;
  static constexpr uint32_t binary_input              = 3;
  static constexpr uint32_t binary_output             = 4;
  static constexpr uint32_t binary_value              = 5;
  static constexpr uint32_t calendar                  = 6;
  static constexpr uint32_t command                   = 7;
  static constexpr uint32_t device                    = 8;
  static constexpr uint32_t event_enrollment          = 9;
  static constexpr uint32_t file                      = 10;
  static constexpr uint32_t group                     = 11;
  static constexpr uint32_t loop                      = 12;
  static constexpr uint32_t multi_state_input         = 13;
  static constexpr uint32_t multi_state_output        = 14;
  static constexpr uint32_t notification_class        = 15;
  static constexpr uint32_t program                   = 16;
  static constexpr uint32_t schedule                  = 17;
  static constexpr uint32_t averaging                 = 18;
  static constexpr uint32_t multi_state_value         = 19;
  static constexpr uint32_t trend_log                 = 20;
  static constexpr uint32_t life_safety_point         = 21;
  static constexpr uint32_t life_safety_zone          = 22;
  static constexpr uint32_t accumulator               = 23;
  static constexpr uint32_t pulse_converter           = 24;
  static constexpr uint32_t event_log                 = 25;
  static constexpr uint32_t global_group              = 26;
  static constexpr uint32_t trend_log_multiple        = 27;
  static constexpr uint32_t load_control              = 28;
  static constexpr uint32_t structured_view           = 29;
  static constexpr uint32_t access_door               = 30;
  static constexpr uint32_t unassigned_31             = 31;
  static constexpr uint32_t access_credential         = 32;
  static constexpr uint32_t access_point              = 33;
  static constexpr uint32_t access_rights             = 34;
  static constexpr uint32_t access_user               = 35;
  static constexpr uint32_t access_zone               = 36;
  static constexpr uint32_t credential_data_input     = 37;
  static constexpr uint32_t network_security          = 38;
  static constexpr uint32_t bitstring_value           = 39;
  static constexpr uint32_t characterstring_value     = 40;
  static constexpr uint32_t date_pattern_value        = 41;
  static constexpr uint32_t date_value                = 42;
  static constexpr uint32_t datetime_pattern_value    = 43;
  static constexpr uint32_t datetime_value            = 44;
  static constexpr uint32_t integer_value             = 45;
  static constexpr uint32_t large_analog_value        = 46;
  static constexpr uint32_t octetstring_value         = 47;
  static constexpr uint32_t positive_integer_value    = 48;
  static constexpr uint32_t time_pattern_value        = 49;
  static constexpr uint32_t time_value                = 50;
  static constexpr uint32_t notification_forwarder    = 51;
  static constexpr uint32_t alert_enrollment          = 52;
  static constexpr uint32_t channel                   = 53;
  static constexpr uint32_t lighting_output           = 54;
};


template<>
inline std::string enumerated::to_string<object_type>() const {
  std::stringstream os;
  switch(value) {
    case object_type::analog_input              :  os << "analog_input";                break;
    case object_type::analog_output             :  os << "analog_output";               break;
    case object_type::analog_value              :  os << "analog_value";                break;
    case object_type::binary_input              :  os << "binary_input";                break;
    case object_type::binary_output             :  os << "binary_output";               break;
    case object_type::binary_value              :  os << "binary_value";                break;
    case object_type::calendar                  :  os << "calendar";                    break;
    case object_type::command                   :  os << "command";                     break;
    case object_type::device                    :  os << "device";                      break;
    case object_type::event_enrollment          :  os << "event_enrollment";            break;
    case object_type::file                      :  os << "file";                        break;
    case object_type::group                     :  os << "group";                       break;
    case object_type::loop                      :  os << "loop";                        break;
    case object_type::multi_state_input         :  os << "multi_state_input";           break;
    case object_type::multi_state_output        :  os << "multi_state_output";          break;
    case object_type::notification_class        :  os << "notification_class";          break;
    case object_type::program                   :  os << "program";                     break;
    case object_type::schedule                  :  os << "schedule";                    break;
    case object_type::averaging                 :  os << "averaging";                   break;
    case object_type::multi_state_value         :  os << "multi_state_value";           break;
    case object_type::trend_log                 :  os << "multi_state_value";           break;
    case object_type::life_safety_point         :  os << "life_safety_point";           break;
    case object_type::life_safety_zone          :  os << "life_safety_zone";            break;
    case object_type::accumulator               :  os << "accumulator";                 break;
    case object_type::pulse_converter           :  os << "pulse_converter";             break;
    case object_type::event_log                 :  os << "event_log";                   break;
    case object_type::global_group              :  os << "global_group";                break;
    case object_type::trend_log_multiple        :  os << "trend_log_multiple";          break;
    case object_type::load_control              :  os << "load_control";                break;
    case object_type::structured_view           :  os << "structured_view";             break;
    case object_type::access_door               :  os << "access_door";                 break;
    case object_type::unassigned_31             :  os << "unassigned_31";               break;
    case object_type::access_credential         :  os << "access_credential";           break;
    case object_type::access_point              :  os << "access_point";                break;
    case object_type::access_rights             :  os << "access_rights";               break;
    case object_type::access_user               :  os << "access_user";                 break;
    case object_type::access_zone               :  os << "access_zone";                 break;
    case object_type::credential_data_input     :  os << "credential_data_input";       break;
    case object_type::network_security          :  os << "network_security";            break;
    case object_type::bitstring_value           :  os << "bitstring_value";             break;
    case object_type::characterstring_value     :  os << "characterstring_value";       break;
    case object_type::date_pattern_value        :  os << "date_pattern_value";          break;
    case object_type::date_value                :  os << "date_value";                  break;
    case object_type::datetime_pattern_value    :  os << "datetime_pattern_value";      break;
    case object_type::datetime_value            :  os << "datetime_value";              break;
    case object_type::integer_value             :  os << "integer_value";               break;
    case object_type::large_analog_value        :  os << "large_analog_value";          break;
    case object_type::octetstring_value         :  os << "octetstring_value";           break;
    case object_type::positive_integer_value    :  os << "positive_integer_value";      break;
    case object_type::time_pattern_value        :  os << "time_pattern_value";          break;
    case object_type::time_value                :  os << "time_value";                  break;
    case object_type::notification_forwarder    :  os << "notification_forwarder";      break;
    case object_type::alert_enrollment          :  os << "alert_enrollment";            break;
    case object_type::channel                   :  os << "channel";                     break;
    case object_type::lighting_output           :  os << "lighting_output";             break;
    default                                     :  os << "object";                      break;
  }
  os << "(" << value << ")";
  return os.str();
}


}}



#endif /* SRC_BACNET_TYPE_OBJECT_TYPE_HPP_ */
