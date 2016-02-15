cmake_minimum_required(VERSION 3.2)


### Hunter snapshot that will be used ###
include("cmake/HunterGate.cmake")
HunterGate(
       # URL "https://github.com/dan-42/hunter/archive/v0.12.6-dan42.tar.gz"
       # SHA1 "a749367a24f25167f3b1f1712e45ad9a1f6a06e8"
       # LOCAL
        URL "https://github.com/dan-42/hunter/archive/v0.12.42-dan.tar.gz"
        SHA1 "e20106adbd1dfe0f437515d0bd4152ecd755b0a7"
)


####
# Set variables:
#   * PROJECT_NAME
#   * PROJECT_VERSION
project(wookie VERSION 0.0.1)

add_subdirectory(src)
#add_subdirectory(test)
add_subdirectory(example)

