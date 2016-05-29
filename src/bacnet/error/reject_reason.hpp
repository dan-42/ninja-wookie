//
// Created by dan on 30.01.16.
//

#ifndef NINJA_WOOKIE_BACNET_ERROR_REJECT_REASON_HPP
#define NINJA_WOOKIE_BACNET_ERROR_REJECT_REASON_HPP

#include <string>
#include <cstdint>

// @formatter:off

#define NW_ERROR_SWITCH_CASE_HELPER(id)             \
		case id: return #id; break;



namespace  bacnet { namespace  err {

  namespace reject_reason {
    typedef uint32_t reject_reason_type;

    /**
    * 0..63 is reserved by ASREA
    * 64..255 can be used as user defined
    */
    static constexpr  reject_reason_type    other                          =  0;
    static constexpr  reject_reason_type    buffer_overflow                =  1;
    static constexpr  reject_reason_type    inconsistent_parameters        =  2;
    static constexpr  reject_reason_type    invalid_parameter_data_type    =  3;
    static constexpr  reject_reason_type    invalid_tag                    =  4;
    static constexpr  reject_reason_type    missing_required_parameter     =  5;
    static constexpr  reject_reason_type    parameter_out_of_range         =  6;
    static constexpr  reject_reason_type    too_many_arguments             =  7;
    static constexpr  reject_reason_type    undefined_enumeration          =  8;
    static constexpr  reject_reason_type    unrecognized_service           =  9;


    static inline std::string to_string(const reject_reason_type& r_reason) noexcept {
      switch(r_reason) {
        NW_ERROR_SWITCH_CASE_HELPER(other                           )
        NW_ERROR_SWITCH_CASE_HELPER(buffer_overflow                 )
        NW_ERROR_SWITCH_CASE_HELPER(inconsistent_parameters         )
        NW_ERROR_SWITCH_CASE_HELPER(invalid_parameter_data_type     )
        NW_ERROR_SWITCH_CASE_HELPER(invalid_tag                     )
        NW_ERROR_SWITCH_CASE_HELPER(missing_required_parameter      )
        NW_ERROR_SWITCH_CASE_HELPER(parameter_out_of_range          )
        NW_ERROR_SWITCH_CASE_HELPER(too_many_arguments              )
        NW_ERROR_SWITCH_CASE_HELPER(undefined_enumeration           )
        NW_ERROR_SWITCH_CASE_HELPER(unrecognized_service            )
        default: return "error_class(" + std::to_string(r_reason) + ")"; break;
      };
    }

}}}

// @formatter:on
#endif //NINJA_WOOKIE_BACNET_ERROR_REJECT_REASON_HPP
