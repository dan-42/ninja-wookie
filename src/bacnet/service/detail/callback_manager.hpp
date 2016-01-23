//
// Created by dan on 10.10.15.
//

#ifndef NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP
#define NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP

#include <stdexcept>

#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <boost/fusion/algorithm.hpp>

#include <bacnet/detail/common/types.hpp>
#include <bacnet/service/api.hpp>


//xxx use lib-pre!!!

namespace pre {

template<typename F>
struct function_traits : public function_traits<decltype(&F::operator())> {
};

template<typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const> {
    enum {
        arity = sizeof...(Args)
    };

    using result_type = ReturnType;

    using function_type = std::function<ReturnType(Args...)>;

private:
    template<size_t i>
    struct arg_ {
        typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
    };

public:
    template<size_t i>
    using arg = typename arg_<i>::type;
};

template<typename F, typename... Ts>
F for_each_args(F f, Ts&&... a) {
  return std::initializer_list<int>{(std::ref(f)(std::forward<Ts>(a)),0)...}, f;
}

} /*namespace pre*/



namespace bacnet { namespace service { namespace detail {

typedef boost::fusion::map<
    boost::fusion::pair<service::who_is, callback_service_who_is_t>,
    boost::fusion::pair<service::i_am,   callback_service_i_am_t  >
    //boost::fusion::pair<service::reinit, callback_service_i_am_t >
> callback_map_type;

      using namespace bacnet::service;
      using namespace bacnet::service::service;
      struct callback_manager {

        template<typename... Callbacks>
        void set_service_callbacks(Callbacks... callbacks) {
          pre::for_each_args([this](auto callback ) {
            typedef pre::function_traits<decltype(callback)> callback_traits;
            typedef typename callback_traits::template arg<0> arg_0_t;
            boost::fusion::at_key<arg_0_t>(callback_map) = callback;
          }, callbacks...);
        }

        template<typename Service>
        void invoke(const boost::system::error_code &ec, const bacnet::common::protocol::meta_information &mi, const Service &service) {
          boost::fusion::at_key<Service>(callback_map)(ec, mi, service);
        }

      private:
          callback_map_type callback_map;
      };
    }}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP
