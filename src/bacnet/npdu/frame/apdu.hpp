//
// Created by dan on 28.03.16.
//

#ifndef WOOKIE_BACNET_NPDU_FRAME_APDU_HPP
#define WOOKIE_BACNET_NPDU_FRAME_APDU_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <util/boost/spirit/unused_type.hpp>
#include <bacnet/detail/common/types.hpp>


namespace bacnet { namespace npdu {  namespace frame_body {

struct apdu {
  bacnet::binary_data data;
  unused_t unused_t_;
};

}}}

BOOST_FUSION_ADAPT_STRUCT(
    bacnet::npdu::frame_body::apdu,
    data,
	unused_t_
)

#endif //WOOKIE_BACNET_NPDU_FRAME_APDU_HPP
