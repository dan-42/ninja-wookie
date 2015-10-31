# Copyright (c) 2013-2015, Ruslan Baratov
# All rights reserved.

# Do not place header guards here

# Unset:
#   * ${PACKAGE_NAME}_ROOT (CMake variable)
#   * ${PACKAGE_NAME}_ROOT (CMake cache variable)
#   * ${PACKAGE_NAME}_ROOT (environment variable)

# Set CMake variables:
#   * HUNTER_${PACKAGE_NAME}_VERSION
#   * HUNTER_${PACKAGE_NAME}_CMAKE_ARGS (optionally)

# Usage:
#   hunter_config(Foo VERSION 1.0.0)
#   hunter_config(Boo VERSION 1.2.3z CMAKE_ARGS BOO_WITH_A=ON)

# Wiki:
#   * https://github.com/ruslo/hunter/wiki/dev.modules#hunter_config

include(hunter_config)
include(hunter_user_error)
include(hunter_add_version)

# NOTE: no names with spaces!


hunter_add_version(
    PACKAGE_NAME
    Boost
    VERSION
    "1.59.0"
    URL
    "http://sourceforge.net/projects/boost/files/boost/1.59.0/boost_1_59_0.tar.bz2/download"
    SHA1
    b94de47108b2cdb0f931833a7a9834c2dd3ca46e 
)

hunter_config(Boost VERSION 1.59.0)



