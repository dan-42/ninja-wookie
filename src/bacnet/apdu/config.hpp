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

namespace bacnet { namespace apdu { namespace config {


//20.1.2.5  max-APDU-length-accepted, 4bit value
enum  max_apdu_length_accepted : uint8_t {
  up_to_50_bytes    = 0b0000, //minimum
  up_to_128_bytes   = 0b0001,
  up_to_206_bytes   = 0b0010, //(fits in a LonTalk frame)
  up_to_480_bytes   = 0b0011, //(fits in an ARCNET frame)
  up_to_1024_bytes  = 0b0100,
  up_to_1476_bytes  = 0b0101, //(fits in an ISO 8802-3 frame/ ETHERNET/UDP/IP)
  reserved_value_07 = 0b0110,
  reserved_value_08 = 0b0111,
  reserved_value_09 = 0b1001,
  reserved_value_10 = 0b1010,
  reserved_value_11 = 0b1011,
  reserved_value_12 = 0b1100,
  reserved_value_13 = 0b1101,
  reserved_value_14 = 0b1110,
  reserved_value_15 = 0b1111
};


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

  template<uint32_t Size, max_apdu_length_accepted Enum>
  struct apdu_size_t {
     static constexpr decltype(Size) size_in_bytes = Size;
     static constexpr decltype(Enum) size_as_enum = Enum;
  };

  typedef apdu_size_t<50,   max_apdu_length_accepted::up_to_50_bytes>     _50_bytes_minimal;
  typedef apdu_size_t<128,  max_apdu_length_accepted::up_to_128_bytes>    _128_bytes;
  typedef apdu_size_t<206,  max_apdu_length_accepted::up_to_206_bytes>    _206_bytes_lon_talk;
  typedef apdu_size_t<480,  max_apdu_length_accepted::up_to_480_bytes>    _480_bytes_arcnet;
  typedef apdu_size_t<1024, max_apdu_length_accepted::up_to_1024_bytes>   _1024_bytes;
  typedef apdu_size_t<1476, max_apdu_length_accepted::up_to_1476_bytes>   _1476_bytes_ipv4;

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
