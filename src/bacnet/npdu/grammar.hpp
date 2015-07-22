/*
 * grammar.hpp
 *
 *  Created on: Jul 22, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_NPDU_DETAIL_GRAMMAR_HPP_
#define SRC_BACNET_NPDU_DETAIL_GRAMMAR_HPP_


#include <bacnet/detail/common/types.hpp>
#include <bacnet/npdu/frame.hpp>

namespace bacnet { namespace npdu { namespace generator {

bacnet::binary_data generate(const npdu::frame &f);

}}}


namespace bacnet { namespace npdu { namespace parser {

npdu::frame parse(const bacnet::binary_data &data);

}}}




#endif /* SRC_BACNET_NPDU_DETAIL_GRAMMAR_HPP_ */
