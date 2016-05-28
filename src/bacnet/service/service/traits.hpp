
#ifndef NINJA_WOOKIE_BACNET_SERVICE_SERCICE_TRAITS_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_SERCICE_TRAITS_HPP

#include <boost/mpl/bool.hpp>









namespace bacnet { namespace service { namespace service {
    
    template  <typename T> struct is_confirmed :    boost::mpl::false_ {};
    template  <typename T> struct is_unconfirmed :  boost::mpl::false_ {};
    
    template  <typename T> struct is_request :      boost::mpl::false_ {};
    template  <typename T> struct is_response :     boost::mpl::false_ {};

    template  <typename T> struct is_supported :    boost::mpl::true_ {};        
    
    template  <typename T> struct has_complex_response :    boost::mpl::false_ {};

}}}



#endif /* NINJA_WOOKIE_BACNET_SERVICE_SERCICE_TRAITS_HPP */
