/*
 * grammar.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_APDU_DETAIL_GRAMMAR_HPP_
#define SRC_BACNET_APDU_DETAIL_GRAMMAR_HPP_


#include <bacnet/detail/common/types.hpp>
#include <bacnet/apdu/frame/frames.hpp>

namespace bacnet { namespace apdu { namespace frame { namespace generator {

bacnet::binary_data generate(const apdu::frame::possible_frame &f);

}}}}


namespace bacnet { namespace apdu { namespace frame { namespace parser {

apdu::frame::possible_frame parse(const bacnet::binary_data &data);

}}}}




#endif /* SRC_BACNET_APDU_DETAIL_GRAMMAR_HPP_ */
