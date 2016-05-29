//
// Created by dan on 30.01.16.
//

#ifndef NINJA_WOOKIE_BACNET_ERROR_ERROR_CODE_HPP
#define NINJA_WOOKIE_BACNET_ERROR_ERROR_CODE_HPP

// @formatter:off

#define NW_ERROR_SWITCH_CASE_HELPER(id)             \
		case id: return #id; break;



namespace  bacnet { namespace  err {   namespace error_code {
      /**
       * 0..254 is reserved by ASREA
       * 255..65535 can be used as user defined
       */
      static constexpr  uint16_t    other                                   =   0;
      static constexpr  uint16_t    formerly_authentication_failed          =   1;   // removed version 1 revision 11
      static constexpr  uint16_t    configuration_in_progress               =   2;
      static constexpr  uint16_t    device_busy                             =   3;
      static constexpr  uint16_t    dynamic_creation_not_supported          =   4;
      static constexpr  uint16_t    file_access_denied                      =   5;
      static constexpr  uint16_t    formerly_incompatible_security_levels   =   6;   // removed in version 1 revision 11
      static constexpr  uint16_t    inconsistent_parameters                 =   7;
      static constexpr  uint16_t    inconsistent_selection_criterion        =   8;
      static constexpr  uint16_t    invalid_data_type                       =   9;
      static constexpr  uint16_t    invalid_file_access_method              =  10;
      static constexpr  uint16_t    invalid_file_start_position             =  11;
      static constexpr  uint16_t    formerly_invalid_operator_name          =  12;   // removed in version 1 revision 11
      static constexpr  uint16_t    invalid_parameter_data_type             =  13;
      static constexpr  uint16_t    invalid_time_stamp                      =  14;
      static constexpr  uint16_t    formerly_key_generation_error           =  15;   // removed in version 1 revision 11
      static constexpr  uint16_t    missing_required_parameter              =  16;
      static constexpr  uint16_t    no_objects_of_specified_type            =  17;
      static constexpr  uint16_t    no_space_for_object                     =  18;
      static constexpr  uint16_t    no_space_to_add_list_element            =  19;
      static constexpr  uint16_t    no_space_to_write_property              =  20;
      static constexpr  uint16_t    no_vt_sessions_available                =  21;
      static constexpr  uint16_t    property_is_not_a_list                  =  22;
      static constexpr  uint16_t    object_deletion_not_permitted           =  23;
      static constexpr  uint16_t    object_identifier_already_exists        =  24;
      static constexpr  uint16_t    operational_problem                     =  25;
      static constexpr  uint16_t    password_failure                        =  26;
      static constexpr  uint16_t    read_access_denied                      =  27;
      static constexpr  uint16_t    formerly_security_not_supported         =  28;   // removed in version 1 revision 11
      static constexpr  uint16_t    service_request_denied                  =  29;
      static constexpr  uint16_t    timeout                                 =  30;
      static constexpr  uint16_t    unknown_object                          =  31;
      static constexpr  uint16_t    unknown_property                        =  32;
      static constexpr  uint16_t    removed_value_33                        =  33;
      static constexpr  uint16_t    unknown_vt_class                        =  34;
      static constexpr  uint16_t    unknown_vt_session                      =  35;
      static constexpr  uint16_t    unsupported_object_type                 =  36;
      static constexpr  uint16_t    value_out_of_range                      =  37;
      static constexpr  uint16_t    vt_session_already_closed               =  38;
      static constexpr  uint16_t    vt_session_termination_failure          =  39;
      static constexpr  uint16_t    write_access_denied                     =  40;
      static constexpr  uint16_t    character_set_not_supported             =  41;
      static constexpr  uint16_t    invalid_array_index                     =  42;
      static constexpr  uint16_t    cov_subscription_failed                 =  43;
      static constexpr  uint16_t    not_cov_property                        =  44;
      static constexpr  uint16_t    optional_functionality_not_supported    =  45;
      static constexpr  uint16_t    invalid_configuration_data              =  46;
      static constexpr  uint16_t    datatype_not_supported                  =  47;
      static constexpr  uint16_t    duplicate_name                          =  48;
      static constexpr  uint16_t    duplicate_object_id                     =  49;
      static constexpr  uint16_t    property_is_not_an_array                =  50;
      static constexpr  uint16_t    abort_buffer_overflow                   =  51;
      static constexpr  uint16_t    abort_invalid_apdu_in_this_state        =  52;
      static constexpr  uint16_t    abort_preempted_by_higher_priority_task =  53;
      static constexpr  uint16_t    abort_segmentation_not_supported        =  54;
      static constexpr  uint16_t    abort_proprietary                       =  55;
      static constexpr  uint16_t    abort_other                             =  56;
      static constexpr  uint16_t    invalid_tag                             =  57;
      static constexpr  uint16_t    network_down                            =  58;
      static constexpr  uint16_t    reject_buffer_overflow                  =  59;
      static constexpr  uint16_t    reject_inconsistent_parameters          =  60;
      static constexpr  uint16_t    reject_invalid_parameter_data_type      =  61;
      static constexpr  uint16_t    reject_invalid_tag                      =  62;
      static constexpr  uint16_t    reject_missing_required_parameter       =  63;
      static constexpr  uint16_t    reject_parameter_out_of_range           =  64;
      static constexpr  uint16_t    reject_too_many_arguments               =  65;
      static constexpr  uint16_t    reject_undefined_enumeration            =  66;
      static constexpr  uint16_t    reject_unrecognized_service             =  67;
      static constexpr  uint16_t    reject_proprietary                      =  68;
      static constexpr  uint16_t    reject_other                            =  69;
      static constexpr  uint16_t    unknown_device                          =  70;
      static constexpr  uint16_t    unknown_route                           =  71;
      static constexpr  uint16_t    value_not_initialized                   =  72;
      static constexpr  uint16_t    invalid_event_state                     =  73;
      static constexpr  uint16_t    no_alarm_configured                     =  74;
      static constexpr  uint16_t    log_buffer_full                         =  75;
      static constexpr  uint16_t    logged_value_purged                     =  76;
      static constexpr  uint16_t    no_property_specified                   =  77;
      static constexpr  uint16_t    not_configured_for_triggered_logging    =  78;
      static constexpr  uint16_t    unknown_subscription                    =  79;
      static constexpr  uint16_t    parameter_out_of_range                  =  80;
      static constexpr  uint16_t    list_element_not_found                  =  81;
      static constexpr  uint16_t    busy                                    =  82;
      static constexpr  uint16_t    communication_disabled                  =  83;
      static constexpr  uint16_t    success                                 =  84;
      static constexpr  uint16_t    access_denied                           =  85;
      static constexpr  uint16_t    bad_destination_address                 =  86;
      static constexpr  uint16_t    bad_destination_device_id               =  87;
      static constexpr  uint16_t    bad_signature                           =  88;
      static constexpr  uint16_t    bad_source_address                      =  89;
      static constexpr  uint16_t    bad_timestamp                           =  90;
      static constexpr  uint16_t    cannot_use_key                          =  91;
      static constexpr  uint16_t    cannot_verify_message_id                =  92;
      static constexpr  uint16_t    correct_key_revision                    =  93;
      static constexpr  uint16_t    destination_device_id_required          =  94;
      static constexpr  uint16_t    duplicate_message                       =  95;
      static constexpr  uint16_t    encryption_not_configured               =  96;
      static constexpr  uint16_t    encryption_required                     =  97;
      static constexpr  uint16_t    incorrect_key                           =  98;
      static constexpr  uint16_t    invalid_key_data                        =  99;
      static constexpr  uint16_t    key_update_in_progress                  = 100;
      static constexpr  uint16_t    malformed_message                       = 101;
      static constexpr  uint16_t    not_key_server                          = 102;
      static constexpr  uint16_t    security_not_configured                 = 103;
      static constexpr  uint16_t    source_security_required                = 104;
      static constexpr  uint16_t    too_many_keys                           = 105;
      static constexpr  uint16_t    unknown_authentication_type             = 106;
      static constexpr  uint16_t    unknown_key                             = 107;
      static constexpr  uint16_t    unknown_key_revision                    = 108;
      static constexpr  uint16_t    unknown_source_message                  = 109;
      static constexpr  uint16_t    not_router_to_dnet                      = 110;
      static constexpr  uint16_t    router_busy                             = 111;
      static constexpr  uint16_t    unknown_network_message                 = 112;
      static constexpr  uint16_t    message_too_long                        = 113;
      static constexpr  uint16_t    security_error                          = 114;
      static constexpr  uint16_t    addressing_error                        = 115;
      static constexpr  uint16_t    write_bdt_failed                        = 116;
      static constexpr  uint16_t    read_bdt_failed                         = 117;
      static constexpr  uint16_t    register_foreign_device_failed          = 118;
      static constexpr  uint16_t    read_fdt_failed                         = 119;
      static constexpr  uint16_t    delete_fdt_entry_failed                 = 120;
      static constexpr  uint16_t    distribute_broadcast_failed             = 121;
      static constexpr  uint16_t    unknown_file_size                       = 122;
      static constexpr  uint16_t    abort_apdu_too_long                     = 123;
      static constexpr  uint16_t    abort_application_exceeded_reply_time   = 124;
      static constexpr  uint16_t    abort_out_of_resources                  = 125;
      static constexpr  uint16_t    abort_tsm_timeout                       = 126;
      static constexpr  uint16_t    abort_window_size_out_of_range          = 127;
      static constexpr  uint16_t    file_full                               = 128;
      static constexpr  uint16_t    inconsistent_configuration              = 129;
      static constexpr  uint16_t    inconsistent_object_type                = 130;
      static constexpr  uint16_t    internal_error                          = 131;
      static constexpr  uint16_t    not_configured                          = 132;
      static constexpr  uint16_t    out_of_memory                           = 133;
      static constexpr  uint16_t    value_too_long                          = 134;
      static constexpr  uint16_t    abort_insufficient_security             = 135;
      static constexpr  uint16_t    abort_security_error                    = 136;





      static inline std::string to_string(const uint16_t& e_code) noexcept {
        switch(e_code) {
          NW_ERROR_SWITCH_CASE_HELPER(other                                   )
          NW_ERROR_SWITCH_CASE_HELPER(formerly_authentication_failed          )
          NW_ERROR_SWITCH_CASE_HELPER(configuration_in_progress               )
          NW_ERROR_SWITCH_CASE_HELPER(device_busy                             )
          NW_ERROR_SWITCH_CASE_HELPER(dynamic_creation_not_supported          )
          NW_ERROR_SWITCH_CASE_HELPER(file_access_denied                      )
          NW_ERROR_SWITCH_CASE_HELPER(formerly_incompatible_security_levels   )
          NW_ERROR_SWITCH_CASE_HELPER(inconsistent_parameters                 )
          NW_ERROR_SWITCH_CASE_HELPER(inconsistent_selection_criterion        )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_data_type                       )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_file_access_method              )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_file_start_position             )
          NW_ERROR_SWITCH_CASE_HELPER(formerly_invalid_operator_name          )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_parameter_data_type             )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_time_stamp                      )
          NW_ERROR_SWITCH_CASE_HELPER(formerly_key_generation_error           )
          NW_ERROR_SWITCH_CASE_HELPER(missing_required_parameter              )
          NW_ERROR_SWITCH_CASE_HELPER(no_objects_of_specified_type            )
          NW_ERROR_SWITCH_CASE_HELPER(no_space_for_object                     )
          NW_ERROR_SWITCH_CASE_HELPER(no_space_to_add_list_element            )
          NW_ERROR_SWITCH_CASE_HELPER(no_space_to_write_property              )
          NW_ERROR_SWITCH_CASE_HELPER(no_vt_sessions_available                )
          NW_ERROR_SWITCH_CASE_HELPER(property_is_not_a_list                  )
          NW_ERROR_SWITCH_CASE_HELPER(object_deletion_not_permitted           )
          NW_ERROR_SWITCH_CASE_HELPER(object_identifier_already_exists        )
          NW_ERROR_SWITCH_CASE_HELPER(operational_problem                     )
          NW_ERROR_SWITCH_CASE_HELPER(password_failure                        )
          NW_ERROR_SWITCH_CASE_HELPER(read_access_denied                      )
          NW_ERROR_SWITCH_CASE_HELPER(formerly_security_not_supported         )
          NW_ERROR_SWITCH_CASE_HELPER(service_request_denied                  )
          NW_ERROR_SWITCH_CASE_HELPER(timeout                                 )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_object                          )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_property                        )
          NW_ERROR_SWITCH_CASE_HELPER(removed_value_33                        )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_vt_class                        )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_vt_session                      )
          NW_ERROR_SWITCH_CASE_HELPER(unsupported_object_type                 )
          NW_ERROR_SWITCH_CASE_HELPER(value_out_of_range                      )
          NW_ERROR_SWITCH_CASE_HELPER(vt_session_already_closed               )
          NW_ERROR_SWITCH_CASE_HELPER(vt_session_termination_failure          )
          NW_ERROR_SWITCH_CASE_HELPER(write_access_denied                     )
          NW_ERROR_SWITCH_CASE_HELPER(character_set_not_supported             )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_array_index                     )
          NW_ERROR_SWITCH_CASE_HELPER(cov_subscription_failed                 )
          NW_ERROR_SWITCH_CASE_HELPER(not_cov_property                        )
          NW_ERROR_SWITCH_CASE_HELPER(optional_functionality_not_supported    )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_configuration_data              )
          NW_ERROR_SWITCH_CASE_HELPER(datatype_not_supported                  )
          NW_ERROR_SWITCH_CASE_HELPER(duplicate_name                          )
          NW_ERROR_SWITCH_CASE_HELPER(duplicate_object_id                     )
          NW_ERROR_SWITCH_CASE_HELPER(property_is_not_an_array                )
          NW_ERROR_SWITCH_CASE_HELPER(abort_buffer_overflow                   )
          NW_ERROR_SWITCH_CASE_HELPER(abort_invalid_apdu_in_this_state        )
          NW_ERROR_SWITCH_CASE_HELPER(abort_preempted_by_higher_priority_task )
          NW_ERROR_SWITCH_CASE_HELPER(abort_segmentation_not_supported        )
          NW_ERROR_SWITCH_CASE_HELPER(abort_proprietary                       )
          NW_ERROR_SWITCH_CASE_HELPER(abort_other                             )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_tag                             )
          NW_ERROR_SWITCH_CASE_HELPER(network_down                            )
          NW_ERROR_SWITCH_CASE_HELPER(reject_buffer_overflow                  )
          NW_ERROR_SWITCH_CASE_HELPER(reject_inconsistent_parameters          )
          NW_ERROR_SWITCH_CASE_HELPER(reject_invalid_parameter_data_type      )
          NW_ERROR_SWITCH_CASE_HELPER(reject_invalid_tag                      )
          NW_ERROR_SWITCH_CASE_HELPER(reject_missing_required_parameter       )
          NW_ERROR_SWITCH_CASE_HELPER(reject_parameter_out_of_range           )
          NW_ERROR_SWITCH_CASE_HELPER(reject_too_many_arguments               )
          NW_ERROR_SWITCH_CASE_HELPER(reject_undefined_enumeration            )
          NW_ERROR_SWITCH_CASE_HELPER(reject_unrecognized_service             )
          NW_ERROR_SWITCH_CASE_HELPER(reject_proprietary                      )
          NW_ERROR_SWITCH_CASE_HELPER(reject_other                            )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_device                          )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_route                           )
          NW_ERROR_SWITCH_CASE_HELPER(value_not_initialized                   )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_event_state                     )
          NW_ERROR_SWITCH_CASE_HELPER(no_alarm_configured                     )
          NW_ERROR_SWITCH_CASE_HELPER(log_buffer_full                         )
          NW_ERROR_SWITCH_CASE_HELPER(logged_value_purged                     )
          NW_ERROR_SWITCH_CASE_HELPER(no_property_specified                   )
          NW_ERROR_SWITCH_CASE_HELPER(not_configured_for_triggered_logging    )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_subscription                    )
          NW_ERROR_SWITCH_CASE_HELPER(parameter_out_of_range                  )
          NW_ERROR_SWITCH_CASE_HELPER(list_element_not_found                  )
          NW_ERROR_SWITCH_CASE_HELPER(busy                                    )
          NW_ERROR_SWITCH_CASE_HELPER(communication_disabled                  )
          NW_ERROR_SWITCH_CASE_HELPER(success                                 )
          NW_ERROR_SWITCH_CASE_HELPER(access_denied                           )
          NW_ERROR_SWITCH_CASE_HELPER(bad_destination_address                 )
          NW_ERROR_SWITCH_CASE_HELPER(bad_destination_device_id               )
          NW_ERROR_SWITCH_CASE_HELPER(bad_signature                           )
          NW_ERROR_SWITCH_CASE_HELPER(bad_source_address                      )
          NW_ERROR_SWITCH_CASE_HELPER(bad_timestamp                           )
          NW_ERROR_SWITCH_CASE_HELPER(cannot_use_key                          )
          NW_ERROR_SWITCH_CASE_HELPER(cannot_verify_message_id                )
          NW_ERROR_SWITCH_CASE_HELPER(correct_key_revision                    )
          NW_ERROR_SWITCH_CASE_HELPER(destination_device_id_required          )
          NW_ERROR_SWITCH_CASE_HELPER(duplicate_message                       )
          NW_ERROR_SWITCH_CASE_HELPER(encryption_not_configured               )
          NW_ERROR_SWITCH_CASE_HELPER(encryption_required                     )
          NW_ERROR_SWITCH_CASE_HELPER(incorrect_key                           )
          NW_ERROR_SWITCH_CASE_HELPER(invalid_key_data                        )
          NW_ERROR_SWITCH_CASE_HELPER(key_update_in_progress                  )
          NW_ERROR_SWITCH_CASE_HELPER(malformed_message                       )
          NW_ERROR_SWITCH_CASE_HELPER(not_key_server                          )
          NW_ERROR_SWITCH_CASE_HELPER(security_not_configured                 )
          NW_ERROR_SWITCH_CASE_HELPER(source_security_required                )
          NW_ERROR_SWITCH_CASE_HELPER(too_many_keys                           )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_authentication_type             )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_key                             )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_key_revision                    )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_source_message                  )
          NW_ERROR_SWITCH_CASE_HELPER(not_router_to_dnet                      )
          NW_ERROR_SWITCH_CASE_HELPER(router_busy                             )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_network_message                 )
          NW_ERROR_SWITCH_CASE_HELPER(message_too_long                        )
          NW_ERROR_SWITCH_CASE_HELPER(security_error                          )
          NW_ERROR_SWITCH_CASE_HELPER(addressing_error                        )
          NW_ERROR_SWITCH_CASE_HELPER(write_bdt_failed                        )
          NW_ERROR_SWITCH_CASE_HELPER(read_bdt_failed                         )
          NW_ERROR_SWITCH_CASE_HELPER(register_foreign_device_failed          )
          NW_ERROR_SWITCH_CASE_HELPER(read_fdt_failed                         )
          NW_ERROR_SWITCH_CASE_HELPER(delete_fdt_entry_failed                 )
          NW_ERROR_SWITCH_CASE_HELPER(distribute_broadcast_failed             )
          NW_ERROR_SWITCH_CASE_HELPER(unknown_file_size                       )
          NW_ERROR_SWITCH_CASE_HELPER(abort_apdu_too_long                     )
          NW_ERROR_SWITCH_CASE_HELPER(abort_application_exceeded_reply_time   )
          NW_ERROR_SWITCH_CASE_HELPER(abort_out_of_resources                  )
          NW_ERROR_SWITCH_CASE_HELPER(abort_tsm_timeout                       )
          NW_ERROR_SWITCH_CASE_HELPER(abort_window_size_out_of_range          )
          NW_ERROR_SWITCH_CASE_HELPER(file_full                               )
          NW_ERROR_SWITCH_CASE_HELPER(inconsistent_configuration              )
          NW_ERROR_SWITCH_CASE_HELPER(inconsistent_object_type                )
          NW_ERROR_SWITCH_CASE_HELPER(internal_error                          )
          NW_ERROR_SWITCH_CASE_HELPER(not_configured                          )
          NW_ERROR_SWITCH_CASE_HELPER(out_of_memory                           )
          NW_ERROR_SWITCH_CASE_HELPER(value_too_long                          )
          NW_ERROR_SWITCH_CASE_HELPER(abort_insufficient_security             )
          NW_ERROR_SWITCH_CASE_HELPER(abort_security_error                    )

        default: return "error_code(" + std::to_string(e_code) + ")"; break;
      };
    }

}}}

// @formatter:on
#endif //NINJA_WOOKIE_BACNET_ERROR_ERROR_CODE_HPP
