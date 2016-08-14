/*
 * complex_return.hpp
 *
 *  Created on: Aug 1, 2016
 *      Author: dan
 */

#ifndef SRC_UTIL_COMPLEX_RETURN_HPP_
#define SRC_UTIL_COMPLEX_RETURN_HPP_

#include <boost/core/explicit_operator_bool.hpp>

namespace util {


/**
 *
 *
 *
 */
template<typename Error, typename Value>
struct complex_return {

	Error error;
	Value value;


	BOOST_EXPLICIT_OPERATOR_BOOL()
	inline bool operator!() const  noexcept { // true if no error
	if(  error ) {
	  return true;
	}
	else {
	  return false;
	}
	}

};

}


#endif /* SRC_UTIL_COMPLEX_RETURN_HPP_ */
