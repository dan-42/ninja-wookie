/*
 * property_impl.hpp
 *
 *  Created on: May 15, 2016
 *      Author: dan
 */

#ifndef WOOKIE_BACNET_TYPE_DETAIL_PROPERTY_IMPL_HPP_
#define WOOKIE_BACNET_TYPE_DETAIL_PROPERTY_IMPL_HPP_


#include <boost/mpl/vector.hpp>


namespace bacnet { namespace type {
  typedef uint32_t property_type;
}}

namespace bacnet { namespace type { namespace property {

//generic trait
  template<typename T>  struct id { static constexpr property_type value = T::value; };


  template<typename T>  struct is_standard_property : std::true_type { };

  template<typename T>  struct is_special_operation_property : std::false_type { };


// must be implemented for each

  template<typename T>  struct name { const std::string value{""}; };



}}}


#define WOOKIE_BACNET_IS_STANDARD_PROPERTY 1
#define WOOKIE_BACNET_IS_PROPRIETARY_PROPERTY 0

#define WOOKIE_BACNET_IS_NORMAL_PROPERTY 1
#define WOOKIE_BACNET_IS_SPECIAL_PROPERTY 0



#define WOOKIE_CREATE_TRAIT_IS_STD_PROP_TRUE_TYPE(property_name) \
    template<> struct is_standard_property<property_name> : std::true_type { };   \

#define WOOKIE_CREATE_TRAIT_IS_STD_PROP_FALSE_TYPE(property_name) \
    template<> struct is_standard_property<property_name> : std::false_type { };    \




#define WOOKIE_CREATE_TRAIT_IS_NORMAL_PROP_TRUE_TYPE(property_name) \
    template<> struct is_special_operation_property<property_name> : std::true_type { };   \

#define WOOKIE_CREATE_TRAIT_IS_NORMAL_PROP_FALSE_TYPE(property_name) \
    template<> struct is_special_operation_property<property_name> : std::false_type { };    \



#define WOOKIE_DEFINE_BACNET_PROPERTY_SIMPLE(property_name, property_id)       \
   typedef std::integral_constant<bacnet::type::property_type, property_id>    \
            property_name;                                                     \
    template<>                                                                 \
    struct name<property_name> {                                               \
        const std::string value{#property_name};                               \
    };                                                                         \
                                                                               \



#define WOOKIE_DEFINE_BACNET_PROPERTY_ALL(property_name, property_id, is_standard, is_normal) \
    WOOKIE_DEFINE_BACNET_PROPERTY_SIMPLE(property_name, property_id)           \
                                                                               \
                                                                               \
    BOOST_PP_IF(is_standard,                                                   \
       WOOKIE_CREATE_TRAIT_IS_STD_PROP_TRUE_TYPE(property_name) ,              \
       WOOKIE_CREATE_TRAIT_IS_STD_PROP_FALSE_TYPE(property_name)               \
    )                                                                          \
    BOOST_PP_IF(is_normal,                                                     \
      WOOKIE_CREATE_TRAIT_IS_NORMAL_PROP_TRUE_TYPE(property_name) ,            \
      WOOKIE_CREATE_TRAIT_IS_NORMAL_PROP_FALSE_TYPE(property_name)             \
    )                                                                          \


/*
#define EACH_PROP_TUPLE_SIMPLE(property_entry)                                 \
  WOOKIE_DEFINE_BACNET_PROPERTY_SIMPLE(                                        \
    BOOST_PP_TUPLE_ELEM(0, property_entry),                                    \
    BOOST_PP_TUPLE_ELEM(1, property_entry),                                    \
  )
*/

#define EACH_PROP_TUPLE_ALL(property_entry)                                    \
  WOOKIE_DEFINE_BACNET_PROPERTY_ALL(                                           \
    BOOST_PP_TUPLE_ELEM(0, property_entry),                                    \
    BOOST_PP_TUPLE_ELEM(1, property_entry),                                    \
    BOOST_PP_TUPLE_ELEM(2, property_entry),                                    \
    BOOST_PP_TUPLE_ELEM(3, property_entry)                                     \
 )

#define EACH_PROP_TUPLE(R, unused, property_entry)                             \
  EACH_PROP_TUPLE_ALL(property_entry)

/*
#define EACH_PROP_TUPLE(R, unused, property_entry)                             \
    BOOST_PP_IF(                                                               \
      BOOST_PP_EQUAL(                                                          \
        2,                                                                     \
        BOOST_PP_TUPLE_SIZE(property_entry)                                    \
      ),                                                                       \
      EACH_PROP_TUPLE_SIMPLE(property_entry),                                  \
      EACH_PROP_TUPLE_ALL(property_entry)                                      \
    )                                                                          \
*/

#define EXTRACT_PROPERTY_NAME_WITH_COMMA(R, unused, property_entry)            \
  BOOST_PP_TUPLE_ELEM(0, property_entry),

#define EXTRACT_PROPERTY_NAME(R, unused, property_entry)                       \
  BOOST_PP_TUPLE_ELEM(0, property_entry)


#define WOOKIE_DEFINE_BACNET_PROPERTIES(property_seq)                          \
    BOOST_PP_SEQ_FOR_EACH(  EACH_PROP_TUPLE,                                   \
                            unused,                                            \
                            property_seq  )                                    \
                                                                               \
  typedef boost::mpl::vector<                                                  \
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




#endif /* WOOKIE_BACNET_TYPE_DETAIL_PROPERTY_IMPL_HPP_ */
