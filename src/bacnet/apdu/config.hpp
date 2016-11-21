/*
 * config.hpp
 *
 *  Created on: Oct 16, 2016
 *      Author: dan
 */

#ifndef SRC_BACNET_APDU_CONFIG_HPP_
#define SRC_BACNET_APDU_CONFIG_HPP_

#include <cstdint>
#include <bacnet/common/segment.hpp>
#include <bacnet/common/apdu_size.hpp>

namespace bacnet { namespace apdu { namespace config {




//   20.1.2.4   max-segments-accepted
enum class max_segments_accepted : uint8_t {
  unspecified           = 0b000,
  segments_2            = 0b001,
  segments_4            = 0b010,
  segments_8            = 0b011,
  segments_16           = 0b100,
  segments_32           = 0b101,
  segments_64           = 0b110,
  more_then_64          = 0b111
};




namespace apdu_size {

  namespace common = bacnet::common::apdu_size;

  template<common::apdu_size_type Size, common::length_accepted Enum>
  struct apdu_size_t {
     static constexpr decltype(Size) size_in_bytes = Size;
     static constexpr decltype(Enum) size_as_enum = Enum;
  };

  typedef apdu_size_t<common::_50_bytes,    common::length_accepted::up_to_50_bytes>    _50_bytes_minimal;
  typedef apdu_size_t<common::_128_bytes,   common::length_accepted::up_to_128_bytes>   _128_bytes;
  typedef apdu_size_t<common::_206_bytes,   common::length_accepted::up_to_206_bytes>   _206_bytes_lon_talk;
  typedef apdu_size_t<common::_480_bytes,   common::length_accepted::up_to_480_bytes>   _480_bytes_arcnet;
  typedef apdu_size_t<common::_1024_bytes,  common::length_accepted::up_to_1024_bytes>  _1024_bytes;
  typedef apdu_size_t<common::_1476_bytes,  common::length_accepted::up_to_1476_bytes>  _1476_bytes_ipv4;

}



namespace segmentation_config {

  template<bacnet::common::segmentation::segment SegmentSupported, max_segments_accepted NumberOfSegments>
  struct segmentation_config_t {
    static constexpr decltype(SegmentSupported) segment_supported  = SegmentSupported;
    static constexpr decltype(NumberOfSegments) number_of_segments = NumberOfSegments;
  };

  using both_max_segments       = segmentation_config_t<bacnet::common::segmentation::segment::both, bacnet::apdu::config::max_segments_accepted::more_then_64>;
  using both_64_segments        = segmentation_config_t<bacnet::common::segmentation::segment::both, bacnet::apdu::config::max_segments_accepted::segments_64>;
  using both_32_segments        = segmentation_config_t<bacnet::common::segmentation::segment::both, bacnet::apdu::config::max_segments_accepted::segments_32>;
  using both_16_segments        = segmentation_config_t<bacnet::common::segmentation::segment::both, bacnet::apdu::config::max_segments_accepted::segments_16>;
  using both_8_segments         = segmentation_config_t<bacnet::common::segmentation::segment::both, bacnet::apdu::config::max_segments_accepted::segments_8>;
  using both_4_segments         = segmentation_config_t<bacnet::common::segmentation::segment::both, bacnet::apdu::config::max_segments_accepted::segments_4>;
  using both_2_segments         = segmentation_config_t<bacnet::common::segmentation::segment::both, bacnet::apdu::config::max_segments_accepted::segments_2>;
  using both_undefined_segments = segmentation_config_t<bacnet::common::segmentation::segment::both, bacnet::apdu::config::max_segments_accepted::unspecified>;

  using none = segmentation_config_t<bacnet::common::segmentation::segment::none, bacnet::apdu::config::max_segments_accepted::unspecified>;
}



template<typename ApduSize, typename SegmentationConfig>
struct config_t {
  using apdu_size           = ApduSize;
  using segmentation_config = SegmentationConfig;
};

  using default_ = config_t<apdu_size::_1476_bytes_ipv4, segmentation_config::both_max_segments>;


}}}


#endif /* SRC_BACNET_APDU_CONFIG_HPP_ */
