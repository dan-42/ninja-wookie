/*
 * property_impl.hpp
 *
 *  Created on: May 15, 2016
 *      Author: dan
 */

#ifndef WOOKIE_BACNET_TYPE_DETAIL_PROPERTY_IMPL_HPP_
#define WOOKIE_BACNET_TYPE_DETAIL_PROPERTY_IMPL_HPP_

#include <cstdint>
#include <string>
#include <type_traits>

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/punctuation/comma.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/mpl/vector.hpp>


namespace bacnet { namespace type {
  typedef uint32_t property_type;
}}

namespace bacnet { namespace type { namespace property {

//generic trait
  template<typename T>  struct id { static constexpr property_type value = T::value; };


  template<typename T>  struct is_standard_property : std::true_type { };

  template<typename T>  struct is_special_property : std::false_type { };

  template<typename T>  struct is_property : std::false_type { };


// must be implemented for each

  template<typename T>  struct name {
    static constexpr const char* const value = "undefined_name";
  };



}}}

template<bacnet::type::property_type T>
using integral_constant_ = std::integral_constant<bacnet::type::property_type, T>;

#define COMMA ,

#define WOOKIE_BACNET_IS_STANDARD_PROPERTY 1
#define WOOKIE_BACNET_IS_PROPRIETARY_PROPERTY 0

#define WOOKIE_BACNET_IS_NORMAL_PROPERTY 1
#define WOOKIE_BACNET_IS_SPECIAL_PROPERTY 0



#define WOOKIE_CREATE_TRAIT_IS_PROP_TRUE_TYPE(property_name) \
    template<> struct is_property<property_name> : std::true_type { };

#define WOOKIE_CREATE_TRAIT_IS_STD_PROP_TRUE_TYPE(property_name) \
    template<> struct is_standard_property<property_name> : std::true_type { };

#define WOOKIE_CREATE_TRAIT_IS_STD_PROP_FALSE_TYPE(property_name) \
    template<> struct is_standard_property<property_name> : std::false_type { };




#define WOOKIE_CREATE_TRAIT_IS_NORMAL_PROP_TRUE_TYPE(property_name) \
    template<> struct is_special_property<property_name> : std::true_type { };

#define WOOKIE_CREATE_TRAIT_IS_NORMAL_PROP_FALSE_TYPE(property_name) \
    template<> struct is_special_property<property_name> : std::false_type { };



#define WOOKIE_DEFINE_BACNET_PROPERTY_SIMPLE_ARGS(property_id)       \
    bacnet::type::property_type , property_id

#define WOOKIE_DEFINE_BACNET_PROPERTY_SIMPLE(property_name, property_id)       \
   typedef integral_constant_<property_id>   \
   property_name;                                                                            \
    template<>                                                                 \
    struct name<property_name> {                                               \
      static constexpr const char* const value = #property_name;               \
    };                                                                         \
                                                                               \

#define my_args(id) int COMMA id

//#define consttant_(id) typedef std::integral_constant< my_args(id)>
#define consttant_(id) typedef integral_constant_< id >

#define WOOKIE_DEFINE_BACNET_PROPERTY_SIMPLE_1(property_name, property_id)         \
    consttant_(property_id)   property_name;                                    \
    template<>                                                                 \
    struct name<property_name> {                                               \
      static constexpr const char* const value = #property_name;               \
    };                                                                         \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            \


#define WOOKIE_DEFINE_BACNET_PROPERTY(property_name, property_id, is_standard, is_normal) \
    WOOKIE_DEFINE_BACNET_PROPERTY_SIMPLE_1(property_name, property_id)           \
                                                                               \
    WOOKIE_CREATE_TRAIT_IS_PROP_TRUE_TYPE(property_name)                       \
    BOOST_PP_IF(is_standard,                                                   \
       WOOKIE_CREATE_TRAIT_IS_STD_PROP_TRUE_TYPE(property_name) ,              \
       WOOKIE_CREATE_TRAIT_IS_STD_PROP_FALSE_TYPE(property_name)               \
    )                                                                          \
    BOOST_PP_IF(is_normal,                                                     \
      WOOKIE_CREATE_TRAIT_IS_NORMAL_PROP_TRUE_TYPE(property_name) ,            \
      WOOKIE_CREATE_TRAIT_IS_NORMAL_PROP_FALSE_TYPE(property_name)             \
    )                                                                          \



/*
 * Many thanks to damien buhl (https://github.com/daminetreg)
 * who provided me with this awesome macro solution
 */

#define NM_BACNET_FILLER_0(X)                                                  \
   WOOKIE_DEFINE_BACNET_PROPERTY X                                             \
    NM_BACNET_FILLER_1

#define NM_BACNET_FILLER_1(X)                                                  \
    WOOKIE_DEFINE_BACNET_PROPERTY X                                            \
    NM_BACNET_FILLER_0

#define NM_BACNET_FILLER_0_END
#define NM_BACNET_FILLER_1_END

#define WOOKIE_DEFINE_BACNET_PROPERTIES(elems)                                 \
            BOOST_PP_CAT( NM_BACNET_FILLER_0 elems ,_END)                      \





/*  typedef boost::mpl::vector<                                                \

      BOOST_PP_SEQ_FOR_EACH(  EXTRACT_PROPERTY_NAME_WITH_COMMA,                \
                              unused,                                          \
                              BOOST_PP_SEQ_POP_BACK(property_seq)  )           \
                                                                               \
     BOOST_PP_TUPLE_ELEM(0,                                                    \
       BOOST_PP_SEQ_ELEM(                                                      \
         BOOST_PP_DEC(  BOOST_PP_SEQ_SIZE(  property_seq   ) )  ,              \
         property_seq                                                          \
       )                                                                       \
     )                                                                         \
  > supported_properties;
*/



#endif /* WOOKIE_BACNET_TYPE_DETAIL_PROPERTY_IMPL_HPP_ */
