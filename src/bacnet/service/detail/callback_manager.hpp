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
            typedef typename callback_traits::template arg<2> arg_2_t;
            boost::fusion::at_key<typename std::decay<arg_2_t>::type>(callback_map) = callback;
          }, callbacks...);
        }

        template<typename Service>
        void invoke(const boost::system::error_code &ec, const bacnet::common::protocol::meta_information &mi, const Service &service) {
          if(!boost::fusion::at_key<Service>(callback_map)) {
            std::cerr << "bacnet::service::callback_manager no callback set: " << typeid(Service).name() << std::endl;
            return;
          }
          boost::fusion::at_key<Service>(callback_map)(ec, mi, service);
        }

        std::size_t set_i_am_service_callback(callback_service_i_am_t callback) {
          callbacks_service_i_am_idx_last++;
          callbacks_service_i_am[callbacks_service_i_am_idx_last] = callback;
          return callbacks_service_i_am_idx_last;
        }

        void clear_i_am_service_callback(std::size_t idx) {
          if(idx <= callbacks_service_i_am_idx_last) {
            callbacks_service_i_am.erase(idx);
            callbacks_service_i_am_idx_last--;
          }
         }

      private:
          callback_map_type callback_map;
          std::map<std::size_t, callback_service_i_am_t> callbacks_service_i_am;
          std::size_t  callbacks_service_i_am_idx_last;
      };



///////////////////////////////////

      template<>
      void callback_manager::invoke<service::i_am>(const boost::system::error_code &ec, const bacnet::common::protocol::meta_information &mi, const service::i_am &service) {
        for(auto &callback :  callbacks_service_i_am) {
          if(callback.second) {
            callback.second(ec, mi, service);
          }
        }

        if(!boost::fusion::at_key<service::i_am>(callback_map)) {
          std::cerr << "bacnet::service::callback_manager no callback set: service::i_am"  << std::endl;
          return;
        }
        boost::fusion::at_key<service::i_am>(callback_map)(ec, mi, service);
      }
    }}}

#endif //NINJA_WOOKIE_BACNET_SERVICE_DETAIL_CALLBACK_MANAGER_HPP
