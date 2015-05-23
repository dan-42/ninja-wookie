/*
 * types.hpp
 *
 *  Created on: May 20, 2015
 *      Author: schoko
 */

#ifndef SRC_BACNET_TYPES_HPP_
#define SRC_BACNET_TYPES_HPP_

#include <boost/spirit/home/support/unused.hpp>
namespace bacnet { namespace detail { namespace common {

/* this is used for BOOST_FUSION_DEFINE_STRUCT and boost::spirit
 * structs with only one memeber cant be parsed
 */
typedef boost::spirit::unused_type unused_type;


/**
 * used for holding binary data
 */
typedef std::vector<uint8_t> binary_data;


}}}


namespace bacnet {

/* make it accessable via bacnet namespace */
using detail::common::unused_type;
using detail::common::binary_data;
}

#endif /* SRC_BACNET_TYPES_HPP_ */
