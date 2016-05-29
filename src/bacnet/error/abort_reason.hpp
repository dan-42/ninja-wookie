//
// Created by dan on 30.01.16.
//

#ifndef NINJA_WOOKIE_BACNET_ERROR_ABORT_REASON_HPP
#define NINJA_WOOKIE_BACNET_ERROR_ABORT_REASON_HPP

#include <string>
#include <cstdint>

// @formatter:off

#define NW_ERROR_SWITCH_CASE_HELPER(id)             \
		case id: return #id; break;



namespace  bacnet { namespace  err {

  namespace abort_reason {
    typedef uint32_t abort_reason_type;

    /**
    * 0..63 is reserved by ASREA
    * 64..255 can be used as user defined
    */
    static constexpr  abort_reason_type    other                              =   0;
    static constexpr  abort_reason_type    buffer_overflow                    =   1;
    static constexpr  abort_reason_type    invalid_apdu_in_this_state         =   2;
    static constexpr  abort_reason_type    preempted_by_higher_priority_task  =   3;
    static constexpr  abort_reason_type    segmentation_not_supported         =   4;
    static constexpr  abort_reason_type    security_error                     =   5;
    static constexpr  abort_reason_type    insufficient_security              =   6;
    static constexpr  abort_reason_type    window_size_out_of_range           =   7;
    static constexpr  abort_reason_type    application_exceeded_reply_time    =   8;
    static constexpr  abort_reason_type    out_of_resources                   =   9;
    static constexpr  abort_reason_type    tsm_timeout                        =   10;
    static constexpr  abort_reason_type    apdu_too_long                      =   11;


    static inline std::string to_string(const abort_reason_type& r_reason) noexcept {
      switch(r_reason) {
        NW_ERROR_SWITCH_CASE_HELPER(other                               )
        NW_ERROR_SWITCH_CASE_HELPER(buffer_overflow                     )
        NW_ERROR_SWITCH_CASE_HELPER(invalid_apdu_in_this_state          )
        NW_ERROR_SWITCH_CASE_HELPER(preempted_by_higher_priority_task   )
        NW_ERROR_SWITCH_CASE_HELPER(segmentation_not_supported          )
        NW_ERROR_SWITCH_CASE_HELPER(security_error                      )
        NW_ERROR_SWITCH_CASE_HELPER(insufficient_security               )
        NW_ERROR_SWITCH_CASE_HELPER(window_size_out_of_range            )
        NW_ERROR_SWITCH_CASE_HELPER(application_exceeded_reply_time     )
        NW_ERROR_SWITCH_CASE_HELPER(out_of_resources                    )
        NW_ERROR_SWITCH_CASE_HELPER(tsm_timeout                         )
        NW_ERROR_SWITCH_CASE_HELPER(apdu_too_long                       )
        default: return "error_class(" + std::to_string(r_reason) + ")"; break;
      };
    }

}}}

// @formatter:on
#endif //NINJA_WOOKIE_BACNET_ERROR_ABORT_REASON_HPP
