/*
 * for_each.hpp
 *
 *  Created on: Mar 5, 2016
 *      Author: dan
 */

#ifndef SRC_UTIL_FOR_EACH_HPP_
#define SRC_UTIL_FOR_EACH_HPP_



namespace util {

 template<typename F, typename... Ts>
  F for_each_args(F f, Ts&&... a) {
    return std::initializer_list<int>{(std::ref(f)(std::forward<Ts>(a)),0)...}, f;
  }

}


#endif /* SRC_UTIL_FOR_EACH_HPP_ */
