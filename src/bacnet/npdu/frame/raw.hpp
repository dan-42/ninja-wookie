//
// Created by dan on 28.03.16.
//

#ifndef WOOKIE_BACNET_NPDU_FRAME_RAW_HPP
#define WOOKIE_BACNET_NPDU_FRAME_RAW_HPP

#include <boost/fusion/include/adapt_struct.hpp>
#include <bacnet/detail/common/types.hpp>


namespace bacnet { namespace npdu {  namespace frame_body {

struct raw {
  bacnet::binary_data data;
};

}}}

BOOST_FUSION_ADAPT_STRUCT(
    bacnet::npdu::frame_body::raw,
    data
)

#endif //WOOKIE_BACNET_NPDU_FRAME_RAW_HPP
