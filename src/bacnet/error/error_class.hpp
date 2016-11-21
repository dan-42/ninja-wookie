//
// Created by dan on 30.01.16.
//

#ifndef NINJA_WOOKIE_BACNET_ERROR_ERROR_CLASS_HPP
#define NINJA_WOOKIE_BACNET_ERROR_ERROR_CLASS_HPP

// @formatter:off

#define NW_ERROR_SWITCH_CASE_HELPER(id)             \
		case id: return #id; break;



namespace  bacnet { namespace  err {

    namespace error_class {
      /**
       * 0..63 is reserved by ASREA
       * 64..65535 can be used as user defined
       */
      static constexpr  uint16_t    device        =  0;
      static constexpr  uint16_t    object        =  1;
      static constexpr  uint16_t    property      =  2;
      static constexpr  uint16_t    resources     =  3;
      static constexpr  uint16_t    security      =  4;
      static constexpr  uint16_t    services      =  5;
      static constexpr  uint16_t    vt            =  6;
      static constexpr  uint16_t    communication =  7;

      static constexpr  uint16_t    internal      = 64;


      static inline std::string to_string(const uint16_t& e_class) noexcept {
        switch(e_class) {
          NW_ERROR_SWITCH_CASE_HELPER(device          )
          NW_ERROR_SWITCH_CASE_HELPER(object          )
          NW_ERROR_SWITCH_CASE_HELPER(property        )
          NW_ERROR_SWITCH_CASE_HELPER(resources       )
          NW_ERROR_SWITCH_CASE_HELPER(security        )
          NW_ERROR_SWITCH_CASE_HELPER(services        )
          NW_ERROR_SWITCH_CASE_HELPER(communication   )
          NW_ERROR_SWITCH_CASE_HELPER(internal        )
          default: return "error_class(" + std::to_string(e_class) + ")"; break;
        };
      }

}}}

// @formatter:on
#endif //NINJA_WOOKIE_BACNET_ERROR_ERROR_CLASS_HPP
