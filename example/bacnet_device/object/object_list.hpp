/*
 * object_list.hpp
 *
 *  Created on: Jul 6, 2016
 *      Author: frieddan
 */

#ifndef EXAMPLE_BACNET_DEVICE_OBJECT_LIST_HPP_
#define EXAMPLE_BACNET_DEVICE_OBJECT_LIST_HPP_

#include <util/complex_return.hpp>

#include <bacnet/type/types.hpp>


namespace bacnet { namespace object { namespace detail {

  using read_prop_return_type = util::complex_return<bacnet::error, bacnet::type::possible_type>;

  class object_base {
  public:
    virtual ~object_base(){};
    virtual read_prop_return_type read_prop(uint32_t property_id, boost::optional<uint32_t> index) = 0;
   // virtual bacnet::error write_prop(uint16_t property_id, boost::optional<uint16_t> index, bacnet::type::possible_type data) = 0;

  };
  typedef std::shared_ptr<object_base> object_base_ptr_t;

} //detail

typedef std::map<uint32_t, detail::object_base_ptr_t> object_ptr_map_t;


namespace traits {

  template<typename T> struct has_read_property : std::false_type { };

} //traits


template<typename Derived>
class object : public detail::object_base {
public:




  object() {
   // object_types_supported_.set(traits::supported_index<Derived>::value);

  }

  virtual ~object(){}

  Derived& self() { return static_cast<Derived&>(*this); }


  virtual inline detail::read_prop_return_type read_prop(uint32_t property_id, boost::optional<uint32_t> index) final {

    if(!traits::has_read_property<Derived>::value) {
      std::cout << "object:: read_prop not supported" << std::endl;
      static auto error = bacnet::make_error(bacnet::err::error_class::object, bacnet::err::error_code::unknown_object);
      return {error, bacnet::type::null{}};
    }
    //xxx map uint16_t  to property_type
    switch(property_id) {


    case bacnet::type::property::acked_transitions::value : return self().read_prop_impl(bacnet::type::property::acked_transitions{} , index);
    case bacnet::type::property::ack_required::value : return self().read_prop_impl(bacnet::type::property::ack_required{} , index);
    case bacnet::type::property::action::value : return self().read_prop_impl(bacnet::type::property::action{} , index);
    case bacnet::type::property::action_text::value : return self().read_prop_impl(bacnet::type::property::action_text{} , index);
    case bacnet::type::property::active_text::value : return self().read_prop_impl(bacnet::type::property::active_text{} , index);
    case bacnet::type::property::active_vt_sessions::value : return self().read_prop_impl(bacnet::type::property::active_vt_sessions{} , index);
    case bacnet::type::property::alarm_value::value : return self().read_prop_impl(bacnet::type::property::alarm_value{} , index);
    case bacnet::type::property::alarm_values::value : return self().read_prop_impl(bacnet::type::property::alarm_values{} , index);
    case bacnet::type::property::all::value : return self().read_prop_impl(bacnet::type::property::all{} , index);
    case bacnet::type::property::all_writes_successful::value : return self().read_prop_impl(bacnet::type::property::all_writes_successful{} , index);
    case bacnet::type::property::apdu_segment_timeout::value : return self().read_prop_impl(bacnet::type::property::apdu_segment_timeout{} , index);
    case bacnet::type::property::apdu_timeout::value : return self().read_prop_impl(bacnet::type::property::apdu_timeout{} , index);
    case bacnet::type::property::application_software_version::value : return self().read_prop_impl(bacnet::type::property::application_software_version{} , index);
    case bacnet::type::property::archive::value : return self().read_prop_impl(bacnet::type::property::archive{} , index);
    case bacnet::type::property::bias::value : return self().read_prop_impl(bacnet::type::property::bias{} , index);
    case bacnet::type::property::change_of_state_count::value : return self().read_prop_impl(bacnet::type::property::change_of_state_count{} , index);
    case bacnet::type::property::change_of_state_time::value : return self().read_prop_impl(bacnet::type::property::change_of_state_time{} , index);
    case bacnet::type::property::notification_class::value : return self().read_prop_impl(bacnet::type::property::notification_class{} , index);
    /*                                        18     deleted   */
    case bacnet::type::property::controlled_variable_reference::value : return self().read_prop_impl(bacnet::type::property::controlled_variable_reference{} , index);
    case bacnet::type::property::controlled_variable_units::value : return self().read_prop_impl(bacnet::type::property::controlled_variable_units{} , index);
    case bacnet::type::property::controlled_variable_value::value : return self().read_prop_impl(bacnet::type::property::controlled_variable_value{} , index);
    case bacnet::type::property::cov_increment::value : return self().read_prop_impl(bacnet::type::property::cov_increment{} , index);
    case bacnet::type::property::date_list::value : return self().read_prop_impl(bacnet::type::property::date_list{} , index);
    case bacnet::type::property::daylight_savings_status::value : return self().read_prop_impl(bacnet::type::property::daylight_savings_status{} , index);
    case bacnet::type::property::deadband::value : return self().read_prop_impl(bacnet::type::property::deadband{} , index);
    case bacnet::type::property::derivative_constant::value : return self().read_prop_impl(bacnet::type::property::derivative_constant{} , index);
    case bacnet::type::property::derivative_constant_units::value : return self().read_prop_impl(bacnet::type::property::derivative_constant_units{} , index);
    case bacnet::type::property::description::value : return self().read_prop_impl(bacnet::type::property::description{} , index);
    case bacnet::type::property::description_of_halt::value : return self().read_prop_impl(bacnet::type::property::description_of_halt{} , index);
    case bacnet::type::property::device_address_binding::value : return self().read_prop_impl(bacnet::type::property::device_address_binding{} , index);
    case bacnet::type::property::device_type::value : return self().read_prop_impl(bacnet::type::property::device_type{} , index);
    case bacnet::type::property::effective_period::value : return self().read_prop_impl(bacnet::type::property::effective_period{} , index);
    case bacnet::type::property::elapsed_active_time::value : return self().read_prop_impl(bacnet::type::property::elapsed_active_time{} , index);
    case bacnet::type::property::error_limit::value : return self().read_prop_impl(bacnet::type::property::error_limit{} , index);
    case bacnet::type::property::event_enable::value : return self().read_prop_impl(bacnet::type::property::event_enable{} , index);
    case bacnet::type::property::event_state::value : return self().read_prop_impl(bacnet::type::property::event_state{} , index);
    case bacnet::type::property::event_type::value : return self().read_prop_impl(bacnet::type::property::event_type{} , index);
    case bacnet::type::property::exception_schedule::value : return self().read_prop_impl(bacnet::type::property::exception_schedule{} , index);
    case bacnet::type::property::fault_values::value : return self().read_prop_impl(bacnet::type::property::fault_values{} , index);
    case bacnet::type::property::feedback_value::value : return self().read_prop_impl(bacnet::type::property::feedback_value{} , index);
    case bacnet::type::property::file_access_method::value : return self().read_prop_impl(bacnet::type::property::file_access_method{} , index);
    case bacnet::type::property::file_size::value : return self().read_prop_impl(bacnet::type::property::file_size{} , index);
    case bacnet::type::property::file_type::value : return self().read_prop_impl(bacnet::type::property::file_type{} , index);
    case bacnet::type::property::firmware_revision::value : return self().read_prop_impl(bacnet::type::property::firmware_revision{} , index);
    case bacnet::type::property::high_limit::value : return self().read_prop_impl(bacnet::type::property::high_limit{} , index);
    case bacnet::type::property::inactive_text::value : return self().read_prop_impl(bacnet::type::property::inactive_text{} , index);
    case bacnet::type::property::in_process::value : return self().read_prop_impl(bacnet::type::property::in_process{} , index);
    case bacnet::type::property::instance_of::value : return self().read_prop_impl(bacnet::type::property::instance_of{} , index);
    case bacnet::type::property::integral_constant::value : return self().read_prop_impl(bacnet::type::property::integral_constant{} , index);
    case bacnet::type::property::integral_constant_units::value : return self().read_prop_impl(bacnet::type::property::integral_constant_units{} , index);
    /*  issue_confirmed_notifications,         51        removed in version 1 revision 4     */
    case bacnet::type::property::limit_enable::value : return self().read_prop_impl(bacnet::type::property::limit_enable{} , index);
    case bacnet::type::property::list_of_group_members::value : return self().read_prop_impl(bacnet::type::property::list_of_group_members{} , index);
    case bacnet::type::property::list_of_object_property_references::value : return self().read_prop_impl(bacnet::type::property::list_of_object_property_references{} , index);
    /*                                  value 55 is unassigned  */
    case bacnet::type::property::local_date::value : return self().read_prop_impl(bacnet::type::property::local_date{} , index);
    case bacnet::type::property::local_time::value : return self().read_prop_impl(bacnet::type::property::local_time{} , index);
    case bacnet::type::property::location::value : return self().read_prop_impl(bacnet::type::property::location{} , index);
    case bacnet::type::property::low_limit::value : return self().read_prop_impl(bacnet::type::property::low_limit{} , index);
    case bacnet::type::property::manipulated_variable_reference::value : return self().read_prop_impl(bacnet::type::property::manipulated_variable_reference{} , index);
    case bacnet::type::property::maximum_output::value : return self().read_prop_impl(bacnet::type::property::maximum_output{} , index);
    case bacnet::type::property::max_apdu_length_accepted::value : return self().read_prop_impl(bacnet::type::property::max_apdu_length_accepted{} , index);
    case bacnet::type::property::max_info_frames::value : return self().read_prop_impl(bacnet::type::property::max_info_frames{} , index);
    case bacnet::type::property::max_master::value : return self().read_prop_impl(bacnet::type::property::max_master{} , index);
    case bacnet::type::property::max_pres_value::value : return self().read_prop_impl(bacnet::type::property::max_pres_value{} , index);
    case bacnet::type::property::minimum_off_time::value : return self().read_prop_impl(bacnet::type::property::minimum_off_time{} , index);
    case bacnet::type::property::minimum_on_time::value : return self().read_prop_impl(bacnet::type::property::minimum_on_time{} , index);
    case bacnet::type::property::minimum_output::value : return self().read_prop_impl(bacnet::type::property::minimum_output{} , index);
    case bacnet::type::property::min_pres_value::value : return self().read_prop_impl(bacnet::type::property::min_pres_value{} , index);
    case bacnet::type::property::model_name::value : return self().read_prop_impl(bacnet::type::property::model_name{} , index);
    case bacnet::type::property::modification_date::value : return self().read_prop_impl(bacnet::type::property::modification_date{} , index);
    case bacnet::type::property::notify_type::value : return self().read_prop_impl(bacnet::type::property::notify_type{} , index);
    case bacnet::type::property::number_of_apdu_retries::value : return self().read_prop_impl(bacnet::type::property::number_of_apdu_retries{} , index);
    case bacnet::type::property::number_of_states::value : return self().read_prop_impl(bacnet::type::property::number_of_states{} , index);
    case bacnet::type::property::object_identifier::value : return self().read_prop_impl(bacnet::type::property::object_identifier{} , index);
    case bacnet::type::property::object_list::value : return self().read_prop_impl(bacnet::type::property::object_list{} , index);
    case bacnet::type::property::object_name::value : return self().read_prop_impl(bacnet::type::property::object_name{} , index);
    case bacnet::type::property::object_property_reference::value : return self().read_prop_impl(bacnet::type::property::object_property_reference{} , index);
    case bacnet::type::property::object_type::value : return self().read_prop_impl(bacnet::type::property::object_type{} , index);
    case bacnet::type::property::optional::value : return self().read_prop_impl(bacnet::type::property::optional{} , index);
    case bacnet::type::property::out_of_service::value : return self().read_prop_impl(bacnet::type::property::out_of_service{} , index);
    case bacnet::type::property::output_units::value : return self().read_prop_impl(bacnet::type::property::output_units{} , index);
    case bacnet::type::property::event_parameters::value : return self().read_prop_impl(bacnet::type::property::event_parameters{} , index);
    case bacnet::type::property::polarity::value : return self().read_prop_impl(bacnet::type::property::polarity{} , index);
    case bacnet::type::property::present::value : return self().read_prop_impl(bacnet::type::property::present{} , index);
    case bacnet::type::property::priority::value : return self().read_prop_impl(bacnet::type::property::priority{} , index);
    case bacnet::type::property::priority_array::value : return self().read_prop_impl(bacnet::type::property::priority_array{} , index);
    case bacnet::type::property::priority_for_writing::value : return self().read_prop_impl(bacnet::type::property::priority_for_writing{} , index);
    case bacnet::type::property::process_identifier::value : return self().read_prop_impl(bacnet::type::property::process_identifier{} , index);
    case bacnet::type::property::program_change::value : return self().read_prop_impl(bacnet::type::property::program_change{} , index);
    case bacnet::type::property::program_location::value : return self().read_prop_impl(bacnet::type::property::program_location{} , index);
    case bacnet::type::property::program_state::value : return self().read_prop_impl(bacnet::type::property::program_state{} , index);
    case bacnet::type::property::proportional_constant::value : return self().read_prop_impl(bacnet::type::property::proportional_constant{} , index);
    case bacnet::type::property::proportional_constant_units::value : return self().read_prop_impl(bacnet::type::property::proportional_constant_units{} , index);
    /*  protocol_conformance_class,           95     removed in version 1 revision 2. */
    case bacnet::type::property::protocol_object_types_supported::value : return self().read_prop_impl(bacnet::type::property::protocol_object_types_supported{} , index);
    case bacnet::type::property::protocol_services_supported::value : return self().read_prop_impl(bacnet::type::property::protocol_services_supported{} , index);
    case bacnet::type::property::protocol_version::value : return self().read_prop_impl(bacnet::type::property::protocol_version{} , index);
    case bacnet::type::property::read_only::value : return self().read_prop_impl(bacnet::type::property::read_only{} , index);
    case bacnet::type::property::reason_for_halt::value : return self().read_prop_impl(bacnet::type::property::reason_for_halt{} , index);
    /*  recipient,                            101        removed in version 1 revision 4.   */
    case bacnet::type::property::recipient_list::value : return self().read_prop_impl(bacnet::type::property::recipient_list{} , index);
    case bacnet::type::property::reliability::value : return self().read_prop_impl(bacnet::type::property::reliability{} , index);
    case bacnet::type::property::relinquish_default::value : return self().read_prop_impl(bacnet::type::property::relinquish_default{} , index);
    case bacnet::type::property::required::value : return self().read_prop_impl(bacnet::type::property::required{} , index);
    case bacnet::type::property::resolution::value : return self().read_prop_impl(bacnet::type::property::resolution{} , index);
    case bacnet::type::property::segmentation_supported::value : return self().read_prop_impl(bacnet::type::property::segmentation_supported{} , index);
    case bacnet::type::property::setpoint::value : return self().read_prop_impl(bacnet::type::property::setpoint{} , index);
    case bacnet::type::property::setpoint_reference::value : return self().read_prop_impl(bacnet::type::property::setpoint_reference{} , index);
    case bacnet::type::property::state_text::value : return self().read_prop_impl(bacnet::type::property::state_text{} , index);
    case bacnet::type::property::status_flags::value : return self().read_prop_impl(bacnet::type::property::status_flags{} , index);
    case bacnet::type::property::system_status::value : return self().read_prop_impl(bacnet::type::property::system_status{} , index);
    case bacnet::type::property::time_delay::value : return self().read_prop_impl(bacnet::type::property::time_delay{} , index);
    case bacnet::type::property::time_of_active_time_reset::value : return self().read_prop_impl(bacnet::type::property::time_of_active_time_reset{} , index);
    case bacnet::type::property::time_of_state_count_reset::value : return self().read_prop_impl(bacnet::type::property::time_of_state_count_reset{} , index);
    case bacnet::type::property::time_synchronization_recipients::value : return self().read_prop_impl(bacnet::type::property::time_synchronization_recipients{} , index);
    case bacnet::type::property::units::value : return self().read_prop_impl(bacnet::type::property::units{} , index);
    case bacnet::type::property::update_interval::value : return self().read_prop_impl(bacnet::type::property::update_interval{} , index);
    case bacnet::type::property::utc_offset::value : return self().read_prop_impl(bacnet::type::property::utc_offset{} , index);
    case bacnet::type::property::vendor_identifier::value : return self().read_prop_impl(bacnet::type::property::vendor_identifier{} , index);
    case bacnet::type::property::vendor_name::value : return self().read_prop_impl(bacnet::type::property::vendor_name{} , index);
    case bacnet::type::property::vt_classes_supported::value : return self().read_prop_impl(bacnet::type::property::vt_classes_supported{} , index);
    case bacnet::type::property::weekly_schedule::value : return self().read_prop_impl(bacnet::type::property::weekly_schedule{} , index);
    case bacnet::type::property::attempted_samples::value : return self().read_prop_impl(bacnet::type::property::attempted_samples{} , index);
    case bacnet::type::property::average_value::value : return self().read_prop_impl(bacnet::type::property::average_value{} , index);
    case bacnet::type::property::buffer_size::value : return self().read_prop_impl(bacnet::type::property::buffer_size{} , index);
    case bacnet::type::property::client_cov_increment::value : return self().read_prop_impl(bacnet::type::property::client_cov_increment{} , index);
    case bacnet::type::property::cov_resubscription_interval::value : return self().read_prop_impl(bacnet::type::property::cov_resubscription_interval{} , index);
    /*     current_notify_time,                  129     removed in version 1 revision 3.*/
    case bacnet::type::property::event_time_stamps::value : return self().read_prop_impl(bacnet::type::property::event_time_stamps{} , index);
    case bacnet::type::property::log_buffer::value : return self().read_prop_impl(bacnet::type::property::log_buffer{} , index);
    case bacnet::type::property::log_device_object_property::value : return self().read_prop_impl(bacnet::type::property::log_device_object_property{} , index);
    /*     enable,                               133     log_enable was renamed to enable in version 1 revision 5  */
    case bacnet::type::property::log_interval::value : return self().read_prop_impl(bacnet::type::property::log_interval{} , index);
    case bacnet::type::property::maximum_value::value : return self().read_prop_impl(bacnet::type::property::maximum_value{} , index);
    case bacnet::type::property::minimum_value::value : return self().read_prop_impl(bacnet::type::property::minimum_value{} , index);
    case bacnet::type::property::notification_threshold::value : return self().read_prop_impl(bacnet::type::property::notification_threshold{} , index);
    /*     previous_notify_time,                 138        removed in version 1 revision 3.  */
    case bacnet::type::property::protocol_revision::value : return self().read_prop_impl(bacnet::type::property::protocol_revision{} , index);
    case bacnet::type::property::records_since_notification::value : return self().read_prop_impl(bacnet::type::property::records_since_notification{} , index);
    case bacnet::type::property::record_count::value : return self().read_prop_impl(bacnet::type::property::record_count{} , index);
    case bacnet::type::property::start_time::value : return self().read_prop_impl(bacnet::type::property::start_time{} , index);
    case bacnet::type::property::stop_time::value : return self().read_prop_impl(bacnet::type::property::stop_time{} , index);
    case bacnet::type::property::stop_when_full::value : return self().read_prop_impl(bacnet::type::property::stop_when_full{} , index);
    case bacnet::type::property::total_record_count::value : return self().read_prop_impl(bacnet::type::property::total_record_count{} , index);
    case bacnet::type::property::valid_samples::value : return self().read_prop_impl(bacnet::type::property::valid_samples{} , index);
    case bacnet::type::property::window_interval::value : return self().read_prop_impl(bacnet::type::property::window_interval{} , index);
    case bacnet::type::property::window_samples::value : return self().read_prop_impl(bacnet::type::property::window_samples{} , index);
    case bacnet::type::property::maximum_value_timestamp::value : return self().read_prop_impl(bacnet::type::property::maximum_value_timestamp{} , index);
    case bacnet::type::property::minimum_value_timestamp::value : return self().read_prop_impl(bacnet::type::property::minimum_value_timestamp{} , index);
    case bacnet::type::property::variance_value::value : return self().read_prop_impl(bacnet::type::property::variance_value{} , index);
    case bacnet::type::property::active_cov_subscriptions::value : return self().read_prop_impl(bacnet::type::property::active_cov_subscriptions{} , index);
    case bacnet::type::property::backup_failure_timeout::value : return self().read_prop_impl(bacnet::type::property::backup_failure_timeout{} , index);
    case bacnet::type::property::configuration_files::value : return self().read_prop_impl(bacnet::type::property::configuration_files{} , index);
    case bacnet::type::property::database_revision::value : return self().read_prop_impl(bacnet::type::property::database_revision{} , index);
    case bacnet::type::property::direct_reading::value : return self().read_prop_impl(bacnet::type::property::direct_reading{} , index);
    case bacnet::type::property::last_restore_time::value : return self().read_prop_impl(bacnet::type::property::last_restore_time{} , index);
    case bacnet::type::property::maintenance_required::value : return self().read_prop_impl(bacnet::type::property::maintenance_required{} , index);
    case bacnet::type::property::member_of::value : return self().read_prop_impl(bacnet::type::property::member_of{} , index);
    case bacnet::type::property::mode::value : return self().read_prop_impl(bacnet::type::property::mode{} , index);
    case bacnet::type::property::operation_expected::value : return self().read_prop_impl(bacnet::type::property::operation_expected{} , index);
    case bacnet::type::property::setting::value : return self().read_prop_impl(bacnet::type::property::setting{} , index);
    case bacnet::type::property::silenced::value : return self().read_prop_impl(bacnet::type::property::silenced{} , index);
    case bacnet::type::property::tracking_value::value : return self().read_prop_impl(bacnet::type::property::tracking_value{} , index);
    case bacnet::type::property::zone_members::value : return self().read_prop_impl(bacnet::type::property::zone_members{} , index);
    case bacnet::type::property::life_safety_alarm_values::value : return self().read_prop_impl(bacnet::type::property::life_safety_alarm_values{} , index);
    case bacnet::type::property::max_segments_accepted::value : return self().read_prop_impl(bacnet::type::property::max_segments_accepted{} , index);
    case bacnet::type::property::profile_name::value : return self().read_prop_impl(bacnet::type::property::profile_name{} , index);
    case bacnet::type::property::auto_slave_discovery::value : return self().read_prop_impl(bacnet::type::property::auto_slave_discovery{} , index);
    case bacnet::type::property::manual_slave_address_binding::value : return self().read_prop_impl(bacnet::type::property::manual_slave_address_binding{} , index);
    case bacnet::type::property::slave_address_binding::value : return self().read_prop_impl(bacnet::type::property::slave_address_binding{} , index);
    case bacnet::type::property::slave_proxy_enable::value : return self().read_prop_impl(bacnet::type::property::slave_proxy_enable{} , index);
    case bacnet::type::property::last_notify_record::value : return self().read_prop_impl(bacnet::type::property::last_notify_record{} , index);
    case bacnet::type::property::schedule_default::value : return self().read_prop_impl(bacnet::type::property::schedule_default{} , index);
    case bacnet::type::property::accepted_modes::value : return self().read_prop_impl(bacnet::type::property::accepted_modes{} , index);
    case bacnet::type::property::adjust_value::value : return self().read_prop_impl(bacnet::type::property::adjust_value{} , index);
    case bacnet::type::property::count::value : return self().read_prop_impl(bacnet::type::property::count{} , index);
    case bacnet::type::property::count_before_change::value : return self().read_prop_impl(bacnet::type::property::count_before_change{} , index);
    case bacnet::type::property::count_change_time::value : return self().read_prop_impl(bacnet::type::property::count_change_time{} , index);
    case bacnet::type::property::cov_period::value : return self().read_prop_impl(bacnet::type::property::cov_period{} , index);
    case bacnet::type::property::input_reference::value : return self().read_prop_impl(bacnet::type::property::input_reference{} , index);
    case bacnet::type::property::limit_monitoring_interval::value : return self().read_prop_impl(bacnet::type::property::limit_monitoring_interval{} , index);
    case bacnet::type::property::logging_object::value : return self().read_prop_impl(bacnet::type::property::logging_object{} , index);
    case bacnet::type::property::logging_record::value : return self().read_prop_impl(bacnet::type::property::logging_record{} , index);
    case bacnet::type::property::prescale::value : return self().read_prop_impl(bacnet::type::property::prescale{} , index);
    case bacnet::type::property::pulse_rate::value : return self().read_prop_impl(bacnet::type::property::pulse_rate{} , index);
    case bacnet::type::property::scale::value : return self().read_prop_impl(bacnet::type::property::scale{} , index);
    case bacnet::type::property::scale_factor::value : return self().read_prop_impl(bacnet::type::property::scale_factor{} , index);
    case bacnet::type::property::update_time::value : return self().read_prop_impl(bacnet::type::property::update_time{} , index);
    case bacnet::type::property::value_before_change::value : return self().read_prop_impl(bacnet::type::property::value_before_change{} , index);
    case bacnet::type::property::value_set::value : return self().read_prop_impl(bacnet::type::property::value_set{} , index);
    case bacnet::type::property::value_change_time::value : return self().read_prop_impl(bacnet::type::property::value_change_time{} , index);
    case bacnet::type::property::align_intervals::value : return self().read_prop_impl(bacnet::type::property::align_intervals{} , index);
                                    /*  value 194  unassigned   */
    case bacnet::type::property::interval_offset::value : return self().read_prop_impl(bacnet::type::property::interval_offset{} , index);
    case bacnet::type::property::last_restart_reason::value : return self().read_prop_impl(bacnet::type::property::last_restart_reason{} , index);
    case bacnet::type::property::logging_type::value : return self().read_prop_impl(bacnet::type::property::logging_type{} , index);
    /*                                          198_201 unassigned   */
    case bacnet::type::property::restart_notification_recipients::value : return self().read_prop_impl(bacnet::type::property::restart_notification_recipients{} , index);
    case bacnet::type::property::time_of_device_restart::value : return self().read_prop_impl(bacnet::type::property::time_of_device_restart{} , index);
    case bacnet::type::property::time_synchronization_interval::value : return self().read_prop_impl(bacnet::type::property::time_synchronization_interval{} , index);
    case bacnet::type::property::trigger::value : return self().read_prop_impl(bacnet::type::property::trigger{} , index);
    case bacnet::type::property::utc_time_synchronization_recipients::value : return self().read_prop_impl(bacnet::type::property::utc_time_synchronization_recipients{} , index);
    case bacnet::type::property::node_subtype::value : return self().read_prop_impl(bacnet::type::property::node_subtype{} , index);
    case bacnet::type::property::node_type::value : return self().read_prop_impl(bacnet::type::property::node_type{} , index);
    case bacnet::type::property::structured_object_list::value : return self().read_prop_impl(bacnet::type::property::structured_object_list{} , index);
    case bacnet::type::property::subordinate_annotations::value : return self().read_prop_impl(bacnet::type::property::subordinate_annotations{} , index);
    case bacnet::type::property::subordinate_list::value : return self().read_prop_impl(bacnet::type::property::subordinate_list{} , index);
    case bacnet::type::property::actual_shed_level::value : return self().read_prop_impl(bacnet::type::property::actual_shed_level{} , index);
    case bacnet::type::property::duty_window::value : return self().read_prop_impl(bacnet::type::property::duty_window{} , index);
    case bacnet::type::property::expected_shed_level::value : return self().read_prop_impl(bacnet::type::property::expected_shed_level{} , index);
    case bacnet::type::property::full_duty_baseline::value : return self().read_prop_impl(bacnet::type::property::full_duty_baseline{} , index);
    /*                                  values 216_217 are unassigned */
    case bacnet::type::property::requested_shed_level::value : return self().read_prop_impl(bacnet::type::property::requested_shed_level{} , index);
    case bacnet::type::property::shed_duration::value : return self().read_prop_impl(bacnet::type::property::shed_duration{} , index);
    case bacnet::type::property::shed_level_descriptions::value : return self().read_prop_impl(bacnet::type::property::shed_level_descriptions{} , index);
    case bacnet::type::property::shed_levels::value : return self().read_prop_impl(bacnet::type::property::shed_levels{} , index);
    case bacnet::type::property::state_description::value : return self().read_prop_impl(bacnet::type::property::state_description{} , index);
    /*                                   values 223_225 are unassigned  */
    case bacnet::type::property::door_alarm_state::value : return self().read_prop_impl(bacnet::type::property::door_alarm_state{} , index);
    case bacnet::type::property::door_extended_pulse_time::value : return self().read_prop_impl(bacnet::type::property::door_extended_pulse_time{} , index);
    case bacnet::type::property::door_members::value : return self().read_prop_impl(bacnet::type::property::door_members{} , index);
    case bacnet::type::property::door_open_too_long_time::value : return self().read_prop_impl(bacnet::type::property::door_open_too_long_time{} , index);
    case bacnet::type::property::door_pulse_time::value : return self().read_prop_impl(bacnet::type::property::door_pulse_time{} , index);
    case bacnet::type::property::door_status::value : return self().read_prop_impl(bacnet::type::property::door_status{} , index);
    case bacnet::type::property::door_unlock_delay_time::value : return self().read_prop_impl(bacnet::type::property::door_unlock_delay_time{} , index);
    case bacnet::type::property::lock_status::value : return self().read_prop_impl(bacnet::type::property::lock_status{} , index);
    case bacnet::type::property::masked_alarm_values::value : return self().read_prop_impl(bacnet::type::property::masked_alarm_values{} , index);
    case bacnet::type::property::secured_status::value : return self().read_prop_impl(bacnet::type::property::secured_status{} , index);
    /*                                    Values 236-243 unassigned   */
    case bacnet::type::property::absentee_limit::value : return self().read_prop_impl(bacnet::type::property::absentee_limit{} , index);
    case bacnet::type::property::access_alarm_events::value : return self().read_prop_impl(bacnet::type::property::access_alarm_events{} , index);
    case bacnet::type::property::access_doors::value : return self().read_prop_impl(bacnet::type::property::access_doors{} , index);
    case bacnet::type::property::access_event::value : return self().read_prop_impl(bacnet::type::property::access_event{} , index);
    case bacnet::type::property::access_event_authentication_factor::value : return self().read_prop_impl(bacnet::type::property::access_event_authentication_factor{} , index);
    case bacnet::type::property::access_event_credential::value : return self().read_prop_impl(bacnet::type::property::access_event_credential{} , index);
    case bacnet::type::property::access_event_time::value : return self().read_prop_impl(bacnet::type::property::access_event_time{} , index);
    case bacnet::type::property::access_transaction_events::value : return self().read_prop_impl(bacnet::type::property::access_transaction_events{} , index);
    case bacnet::type::property::accompaniment::value : return self().read_prop_impl(bacnet::type::property::accompaniment{} , index);
    case bacnet::type::property::accompaniment_time::value : return self().read_prop_impl(bacnet::type::property::accompaniment_time{} , index);
    case bacnet::type::property::activation_time::value : return self().read_prop_impl(bacnet::type::property::activation_time{} , index);
    case bacnet::type::property::active_authentication_policy::value : return self().read_prop_impl(bacnet::type::property::active_authentication_policy{} , index);
    case bacnet::type::property::assigned_access_rights::value : return self().read_prop_impl(bacnet::type::property::assigned_access_rights{} , index);
    case bacnet::type::property::authentication_factors::value : return self().read_prop_impl(bacnet::type::property::authentication_factors{} , index);
    case bacnet::type::property::authentication_policy_list::value : return self().read_prop_impl(bacnet::type::property::authentication_policy_list{} , index);
    case bacnet::type::property::authentication_policy_names::value : return self().read_prop_impl(bacnet::type::property::authentication_policy_names{} , index);
    case bacnet::type::property::authentication_status::value : return self().read_prop_impl(bacnet::type::property::authentication_status{} , index);
    case bacnet::type::property::authorization_mode::value : return self().read_prop_impl(bacnet::type::property::authorization_mode{} , index);
    case bacnet::type::property::belongs_to::value : return self().read_prop_impl(bacnet::type::property::belongs_to{} , index);
    case bacnet::type::property::credential_disable::value : return self().read_prop_impl(bacnet::type::property::credential_disable{} , index);
    case bacnet::type::property::credential_status::value : return self().read_prop_impl(bacnet::type::property::credential_status{} , index);
    case bacnet::type::property::credentials::value : return self().read_prop_impl(bacnet::type::property::credentials{} , index);
    case bacnet::type::property::credentials_in_zone::value : return self().read_prop_impl(bacnet::type::property::credentials_in_zone{} , index);
    case bacnet::type::property::days_remaining::value : return self().read_prop_impl(bacnet::type::property::days_remaining{} , index);
    case bacnet::type::property::entry_points::value : return self().read_prop_impl(bacnet::type::property::entry_points{} , index);
    case bacnet::type::property::exit_points::value : return self().read_prop_impl(bacnet::type::property::exit_points{} , index);
    //   case bacnet::type::property::expiry_time::value : return self().read_prop_impl(bacnet::type::property::expiry_time{} , index);
    case bacnet::type::property::extended_time_enable::value : return self().read_prop_impl(bacnet::type::property::extended_time_enable{} , index);
    case bacnet::type::property::failed_attempt_events::value : return self().read_prop_impl(bacnet::type::property::failed_attempt_events{} , index);
    case bacnet::type::property::failed_attempts::value : return self().read_prop_impl(bacnet::type::property::failed_attempts{} , index);
    case bacnet::type::property::failed_attempts_time::value : return self().read_prop_impl(bacnet::type::property::failed_attempts_time{} , index);
    case bacnet::type::property::last_access_event::value : return self().read_prop_impl(bacnet::type::property::last_access_event{} , index);
    case bacnet::type::property::last_access_point::value : return self().read_prop_impl(bacnet::type::property::last_access_point{} , index);
    case bacnet::type::property::last_credential_added::value : return self().read_prop_impl(bacnet::type::property::last_credential_added{} , index);
    case bacnet::type::property::last_credential_added_time::value : return self().read_prop_impl(bacnet::type::property::last_credential_added_time{} , index);
    case bacnet::type::property::last_credential_removed::value : return self().read_prop_impl(bacnet::type::property::last_credential_removed{} , index);
    case bacnet::type::property::last_credential_removed_time::value : return self().read_prop_impl(bacnet::type::property::last_credential_removed_time{} , index);
    case bacnet::type::property::last_use_time::value : return self().read_prop_impl(bacnet::type::property::last_use_time{} , index);
    case bacnet::type::property::lockout::value : return self().read_prop_impl(bacnet::type::property::lockout{} , index);
    case bacnet::type::property::lockout_relinquish_time::value : return self().read_prop_impl(bacnet::type::property::lockout_relinquish_time{} , index);
    /*  master_exemption,                     284        removed in version 1 revision 13  */
    case bacnet::type::property::max_failed_attempts::value : return self().read_prop_impl(bacnet::type::property::max_failed_attempts{} , index);
    case bacnet::type::property::members::value : return self().read_prop_impl(bacnet::type::property::members{} , index);
    case bacnet::type::property::muster_point::value : return self().read_prop_impl(bacnet::type::property::muster_point{} , index);
    case bacnet::type::property::negative_access_rules::value : return self().read_prop_impl(bacnet::type::property::negative_access_rules{} , index);
    case bacnet::type::property::number_of_authentication_policies::value : return self().read_prop_impl(bacnet::type::property::number_of_authentication_policies{} , index);
    case bacnet::type::property::occupancy_count::value : return self().read_prop_impl(bacnet::type::property::occupancy_count{} , index);
    case bacnet::type::property::occupancy_count_adjust::value : return self().read_prop_impl(bacnet::type::property::occupancy_count_adjust{} , index);
    case bacnet::type::property::occupancy_count_enable::value : return self().read_prop_impl(bacnet::type::property::occupancy_count_enable{} , index);
    /*  occupancy_exemption,                  293         removed in version 1 revision 13  */
    case bacnet::type::property::occupancy_lower_limit::value : return self().read_prop_impl(bacnet::type::property::occupancy_lower_limit{} , index);
    case bacnet::type::property::occupancy_lower_limit_enforced::value : return self().read_prop_impl(bacnet::type::property::occupancy_lower_limit_enforced{} , index);
    case bacnet::type::property::occupancy_state::value : return self().read_prop_impl(bacnet::type::property::occupancy_state{} , index);
    case bacnet::type::property::occupancy_upper_limit::value : return self().read_prop_impl(bacnet::type::property::occupancy_upper_limit{} , index);
    case bacnet::type::property::occupancy_upper_limit_enforced::value : return self().read_prop_impl(bacnet::type::property::occupancy_upper_limit_enforced{} , index);
     /*  passback_exemption,                   299        removed in version 1 revision 13   */
    case bacnet::type::property::passback_mode::value : return self().read_prop_impl(bacnet::type::property::passback_mode{} , index);
    case bacnet::type::property::passback_timeout::value : return self().read_prop_impl(bacnet::type::property::passback_timeout{} , index);
    case bacnet::type::property::positive_access_rules::value : return self().read_prop_impl(bacnet::type::property::positive_access_rules{} , index);
    case bacnet::type::property::reason_for_disable::value : return self().read_prop_impl(bacnet::type::property::reason_for_disable{} , index);
    case bacnet::type::property::supported_formats::value : return self().read_prop_impl(bacnet::type::property::supported_formats{} , index);
    case bacnet::type::property::supported_format_classes::value : return self().read_prop_impl(bacnet::type::property::supported_format_classes{} , index);
    case bacnet::type::property::threat_authority::value : return self().read_prop_impl(bacnet::type::property::threat_authority{} , index);
    case bacnet::type::property::threat_level::value : return self().read_prop_impl(bacnet::type::property::threat_level{} , index);
    case bacnet::type::property::trace_flag::value : return self().read_prop_impl(bacnet::type::property::trace_flag{} , index);
    case bacnet::type::property::transaction_notification_class::value : return self().read_prop_impl(bacnet::type::property::transaction_notification_class{} , index);
    case bacnet::type::property::user_external_identifier::value : return self().read_prop_impl(bacnet::type::property::user_external_identifier{} , index);
    case bacnet::type::property::user_information_reference::value : return self().read_prop_impl(bacnet::type::property::user_information_reference{} , index);
    /*  Values 312_316 unassigned */
    case bacnet::type::property::user_name::value : return self().read_prop_impl(bacnet::type::property::user_name{} , index);
    case bacnet::type::property::user_type::value : return self().read_prop_impl(bacnet::type::property::user_type{} , index);
    case bacnet::type::property::uses_remaining::value : return self().read_prop_impl(bacnet::type::property::uses_remaining{} , index);
    case bacnet::type::property::zone_from::value : return self().read_prop_impl(bacnet::type::property::zone_from{} , index);
    case bacnet::type::property::zone_to::value : return self().read_prop_impl(bacnet::type::property::zone_to{} , index);
    case bacnet::type::property::access_event_tag::value : return self().read_prop_impl(bacnet::type::property::access_event_tag{} , index);
    case bacnet::type::property::global_identifier::value : return self().read_prop_impl(bacnet::type::property::global_identifier{} , index);
    /*  Values 324_325 unassigned*/
    case bacnet::type::property::verification_time::value : return self().read_prop_impl(bacnet::type::property::verification_time{} , index);
    case bacnet::type::property::base_device_security_policy::value : return self().read_prop_impl(bacnet::type::property::base_device_security_policy{} , index);
    case bacnet::type::property::distribution_key_revision::value : return self().read_prop_impl(bacnet::type::property::distribution_key_revision{} , index);
    case bacnet::type::property::do_not_hide::value : return self().read_prop_impl(bacnet::type::property::do_not_hide{} , index);
    case bacnet::type::property::key_sets::value : return self().read_prop_impl(bacnet::type::property::key_sets{} , index);
    case bacnet::type::property::last_key_server::value : return self().read_prop_impl(bacnet::type::property::last_key_server{} , index);
    case bacnet::type::property::network_access_security_policies::value : return self().read_prop_impl(bacnet::type::property::network_access_security_policies{} , index);
    case bacnet::type::property::packet_reorder_time::value : return self().read_prop_impl(bacnet::type::property::packet_reorder_time{} , index);
    case bacnet::type::property::security_pdu_timeout::value : return self().read_prop_impl(bacnet::type::property::security_pdu_timeout{} , index);
    case bacnet::type::property::security_time_window::value : return self().read_prop_impl(bacnet::type::property::security_time_window{} , index);
    case bacnet::type::property::supported_security_algorithms::value : return self().read_prop_impl(bacnet::type::property::supported_security_algorithms{} , index);
    case bacnet::type::property::update_key_set_timeout::value : return self().read_prop_impl(bacnet::type::property::update_key_set_timeout{} , index);
    case bacnet::type::property::backup_and_restore_state::value : return self().read_prop_impl(bacnet::type::property::backup_and_restore_state{} , index);
    case bacnet::type::property::backup_preparation_time::value : return self().read_prop_impl(bacnet::type::property::backup_preparation_time{} , index);
    case bacnet::type::property::restore_completion_time::value : return self().read_prop_impl(bacnet::type::property::restore_completion_time{} , index);
    case bacnet::type::property::restore_preparation_time::value : return self().read_prop_impl(bacnet::type::property::restore_preparation_time{} , index);
    case bacnet::type::property::bit_mask::value : return self().read_prop_impl(bacnet::type::property::bit_mask{} , index);
    case bacnet::type::property::bit_text::value : return self().read_prop_impl(bacnet::type::property::bit_text{} , index);
    case bacnet::type::property::is_utc::value : return self().read_prop_impl(bacnet::type::property::is_utc{} , index);
    case bacnet::type::property::group_members::value : return self().read_prop_impl(bacnet::type::property::group_members{} , index);
    case bacnet::type::property::group_member_names::value : return self().read_prop_impl(bacnet::type::property::group_member_names{} , index);
    case bacnet::type::property::member_status_flags::value : return self().read_prop_impl(bacnet::type::property::member_status_flags{} , index);
    case bacnet::type::property::requested_update_interval::value : return self().read_prop_impl(bacnet::type::property::requested_update_interval{} , index);
    case bacnet::type::property::covu_period::value : return self().read_prop_impl(bacnet::type::property::covu_period{} , index);
    case bacnet::type::property::covu_recipients::value : return self().read_prop_impl(bacnet::type::property::covu_recipients{} , index);
    case bacnet::type::property::event_message_texts::value : return self().read_prop_impl(bacnet::type::property::event_message_texts{} , index);
    case bacnet::type::property::event_message_texts_config::value : return self().read_prop_impl(bacnet::type::property::event_message_texts_config{} , index);
    case bacnet::type::property::event_detection_enable::value : return self().read_prop_impl(bacnet::type::property::event_detection_enable{} , index);
    case bacnet::type::property::event_algorithm_inhibit::value : return self().read_prop_impl(bacnet::type::property::event_algorithm_inhibit{} , index);
    case bacnet::type::property::event_algorithm_inhibit_ref::value : return self().read_prop_impl(bacnet::type::property::event_algorithm_inhibit_ref{} , index);
    case bacnet::type::property::time_delay_normal::value : return self().read_prop_impl(bacnet::type::property::time_delay_normal{} , index);
    case bacnet::type::property::reliability_evaluation_inhibit::value : return self().read_prop_impl(bacnet::type::property::reliability_evaluation_inhibit{} , index);
    case bacnet::type::property::fault_parameters::value : return self().read_prop_impl(bacnet::type::property::fault_parameters{} , index);
    case bacnet::type::property::fault_type::value : return self().read_prop_impl(bacnet::type::property::fault_type{} , index);
    case bacnet::type::property::local_forwarding_only::value : return self().read_prop_impl(bacnet::type::property::local_forwarding_only{} , index);
    case bacnet::type::property::process_identifier_filter::value : return self().read_prop_impl(bacnet::type::property::process_identifier_filter{} , index);
    case bacnet::type::property::subscribed_recipients::value : return self().read_prop_impl(bacnet::type::property::subscribed_recipients{} , index);
    case bacnet::type::property::port_filter::value : return self().read_prop_impl(bacnet::type::property::port_filter{} , index);
    case bacnet::type::property::authorization_exemptions::value : return self().read_prop_impl(bacnet::type::property::authorization_exemptions{} , index);
    case bacnet::type::property::allow_group_delay_inhibit::value : return self().read_prop_impl(bacnet::type::property::allow_group_delay_inhibit{} , index);
    case bacnet::type::property::channel_number::value : return self().read_prop_impl(bacnet::type::property::channel_number{} , index);
    case bacnet::type::property::control_groups::value : return self().read_prop_impl(bacnet::type::property::control_groups{} , index);
    case bacnet::type::property::execution_delay::value : return self().read_prop_impl(bacnet::type::property::execution_delay{} , index);
    case bacnet::type::property::last_priority::value : return self().read_prop_impl(bacnet::type::property::last_priority{} , index);
    case bacnet::type::property::write_status::value : return self().read_prop_impl(bacnet::type::property::write_status{} , index);
    case bacnet::type::property::property_list::value : return self().read_prop_impl(bacnet::type::property::property_list{} , index);
    case bacnet::type::property::serial_number::value : return self().read_prop_impl(bacnet::type::property::serial_number{} , index);
    case bacnet::type::property::blink_warn_enable::value : return self().read_prop_impl(bacnet::type::property::blink_warn_enable{} , index);
    case bacnet::type::property::default_fade_time::value : return self().read_prop_impl(bacnet::type::property::default_fade_time{} , index);
    case bacnet::type::property::default_ramp_rate::value : return self().read_prop_impl(bacnet::type::property::default_ramp_rate{} , index);
    case bacnet::type::property::default_step_increment::value : return self().read_prop_impl(bacnet::type::property::default_step_increment{} , index);
    case bacnet::type::property::egress_time::value : return self().read_prop_impl(bacnet::type::property::egress_time{} , index);
    case bacnet::type::property::in_progress::value : return self().read_prop_impl(bacnet::type::property::in_progress{} , index);
    case bacnet::type::property::instantaneous_power::value : return self().read_prop_impl(bacnet::type::property::instantaneous_power{} , index);
    case bacnet::type::property::lighting_command::value : return self().read_prop_impl(bacnet::type::property::lighting_command{} , index);
    case bacnet::type::property::lighting_command_default_priority::value : return self().read_prop_impl(bacnet::type::property::lighting_command_default_priority{} , index);
    case bacnet::type::property::max_actual_value::value : return self().read_prop_impl(bacnet::type::property::max_actual_value{} , index);
    case bacnet::type::property::min_actual_value::value : return self().read_prop_impl(bacnet::type::property::min_actual_value{} , index);
    case bacnet::type::property::power::value : return self().read_prop_impl(bacnet::type::property::power{} , index);
    case bacnet::type::property::transition::value : return self().read_prop_impl(bacnet::type::property::transition{} , index);
    case bacnet::type::property::egress_active::value : return self().read_prop_impl(bacnet::type::property::egress_active{} , index);




    }
    return self().read_prop_impl(property_id, index);

  }




private:

  static std::bitset<54> object_types_supported_;


  bacnet::type::object_identifier           object_identifier_;
  std::string                               object_name;
  std::vector<bacnet::type::property_type>  propetty_list_;

};




}}


#endif /* EXAMPLE_BACNET_DEVICE_OBJECT_LIST_HPP_ */
