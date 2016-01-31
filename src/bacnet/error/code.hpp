//
// Created by dan on 30.01.16.
//

#ifndef NINJA_WOOKIE_BACNET_ERROR_CODE_HPP
#define NINJA_WOOKIE_BACNET_ERROR_CODE_HPP

// @formatter:off

namespace  bacnet { namespace  error {

    namespace error_class {
      /**
       * 0..63 is reserved by ASREA
       * 64..65535 can be used as user defined
       */
      enum errc_t : uint16_t  {
          device        = 0,
          object        = 1,
          property      = 2,
          resources     = 3,
          security      = 4,
          services      = 5,
          vt            = 6,
          communication = 7,
        };
    }

    namespace error_code {
      /**
       * 0..254 is reserved by ASREA
       * 255..65535 can be used as user defined
       */
      enum errc_t : uint16_t {
        other                                   = 0,
        formerly_authentication_failed          = 1,   // removed version 1 revision 11
        configuration_in_progress               = 2,
        device_busy                             = 3,
        dynamic_creation_not_supported          = 4,
        file_access_denied                      = 5,
        formerly_incompatible_security_levels   = 6,   // removed in version 1 revision 11
        inconsistent_parameters                 = 7,
        inconsistent_selection_criterion        = 8,
        invalid_data_type                       = 9,
        invalid_file_access_method              = 10,
        invalid_file_start_position             = 11,
        formerly_invalid_operator_name          = 12,   // removed in version 1 revision 11
        invalid_parameter_data_type             = 13,
        invalid_time_stamp                      = 14,
        formerly_key_generation_error           = 15,   // removed in version 1 revision 11
        missing_required_parameter              = 16,
        no_objects_of_specified_type            = 17,
        no_space_for_object                     = 18,
        no_space_to_add_list_element            = 19,
        no_space_to_write_property              = 20,
        no_vt_sessions_available                = 21,
        property_is_not_a_list                  = 22,
        object_deletion_not_permitted           = 23,
        object_identifier_already_exists        = 24,
        operational_problem                     = 25,
        password_failure                        = 26,
        read_access_denied                      = 27,
        formerly_security_not_supported         = 28,   // removed in version 1 revision 11
        service_request_denied                  = 29,
        timeout                                 = 30,
        unknown_object                          = 31,
        unknown_property                        = 32,
        removed_                                = 33,
        unknown_vt_class                        = 34,
        unknown_vt_session                      = 35,
        unsupported_object_type                 = 36,
        value_out_of_range                      = 37,
        vt_session_already_closed               = 38,
        vt_session_termination_failure          = 39,
        write_access_denied                     = 40,
        character_set_not_supported             = 41,
        invalid_array_index                     = 42,
        cov_subscription_failed                 = 43,
        not_cov_property                        = 44,
        optional_functionality_not_supported    = 45,
        invalid_configuration_data              = 46,
        datatype_not_supported                  = 47,
        duplicate_name                          = 48,
        duplicate_object_id                     = 49,
        property_is_not_an_array                = 50,
        abort_buffer_overflow                   = 51,
        abort_invalid_apdu_in_this_state        = 52,
        abort_preempted_by_higher_priority_task = 53,
        abort_segmentation_not_supported        = 54,
        abort_proprietary                       = 55,
        abort_other                             = 56,
        invalid_tag                             = 57,
        network_down                            = 58,
        reject_buffer_overflow                  = 59,
        reject_inconsistent_parameters          = 60,
        reject_invalid_parameter_data_type      = 61,
        reject_invalid_tag                      = 62,
        reject_missing_required_parameter       = 63,
        reject_parameter_out_of_range           = 64,
        reject_too_many_arguments               = 65,
        reject_undefined_enumeration            = 66,
        reject_unrecognized_service             = 67,
        reject_proprietary                      = 68,
        reject_other                            = 69,
        unknown_device                          = 70,
        unknown_route                           = 71,
        value_not_initialized                   = 72,
        invalid_event_state                     = 73,
        no_alarm_configured                     = 74,
        log_buffer_full                         = 75,
        logged_value_purged                     = 76,
        no_property_specified                   = 77,
        not_configured_for_triggered_logging    = 78,
        unknown_subscription                    = 79,
        parameter_out_of_range                  = 80,
        list_element_not_found                  = 81,
        busy                                    = 82,
        communication_disabled                  = 83,
        success                                 = 84,
        access_denied                           = 85,
        bad_destination_address                 = 86,
        bad_destination_device_id               = 87,
        bad_signature                           = 88,
        bad_source_address                      = 89,
        bad_timestamp                           = 90,
        cannot_use_key                          = 91,
        cannot_verify_message_id                = 92,
        correct_key_revision                    = 93,
        destination_device_id_required          = 94,
        duplicate_message                       = 95,
        encryption_not_configured               = 96,
        encryption_required                     = 97,
        incorrect_key                           = 98,
        invalid_key_data                        = 99,
        key_update_in_progress                  = 100,
        malformed_message                       = 101,
        not_key_server                          = 102,
        security_not_configured                 = 103,
        source_security_required                = 104,
        too_many_keys                           = 105,
        unknown_authentication_type             = 106,
        unknown_key                             = 107,
        unknown_key_revision                    = 108,
        unknown_source_message                  = 109,
        not_router_to_dnet                      = 110,
        router_busy                             = 111,
        unknown_network_message                 = 112,
        message_too_long                        = 113,
        security_error                          = 114,
        addressing_error                        = 115,
        write_bdt_failed                        = 116,
        read_bdt_failed                         = 117,
        register_foreign_device_failed          = 118,
        read_fdt_failed                         = 119,
        delete_fdt_entry_failed                 = 120,
        distribute_broadcast_failed             = 121,
        unknown_file_size                       = 122,
        abort_apdu_too_long                     = 123,
        abort_application_exceeded_reply_time   = 124,
        abort_out_of_resources                  = 125,
        abort_tsm_timeout                       = 126,
        abort_window_size_out_of_range          = 127,
        file_full                               = 128,
        inconsistent_configuration              = 129,
        inconsistent_object_type                = 130,
        internal_error                          = 131,
        not_configured                          = 132,
        out_of_memory                           = 133,
        value_too_long                          = 134,
        abort_insufficient_security             = 135,
        abort_security_error                    = 136
      };

    } // namespace errc

}}

// @formatter:on
#endif //NINJA_WOOKIE_BACNET_ERROR_CODE_HPP
