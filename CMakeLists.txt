cmake_minimum_required(VERSION 3.0)

### Hunter snapshot that will be used ###
include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/dan-42/hunter/archive/v0.12.6-dan42.tar.gz"
        SHA1 "a749367a24f25167f3b1f1712e45ad9a1f6a06e8"
        LOCAL
)


# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their definition
# and dump it in the cache along with proper documentation, otherwise set CMAKE_BUILD_TYPE
# to Debug prior to calling PROJECT()
# source: http://www.cmake.org/pipermail/cmake/2008-September/023808.html
IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the types of build, options are:
                                                           None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release."
       )
ELSE()
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the types of build, options are:
                                             None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release"
    )
ENDIF()


project(ninja-wookie)
enable_testing ()

set(NINJA_WOOKIE_LIBRARY_NAME "wookie")
set(NINJA_WOOKIE_EXEC_NAME "ninja-wookie")
set(NINJA_WOOKIE_TEST_NAME "test-wookie")


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Werror")
# needed for boost library
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function -Wno-unused-local-typedefs -Wno-unused-variable -Wno-deprecated-declarations")

#-DBOOST_NO_CXX11_CONSTEXPR -DBOOST_PP_VARIADICS=0
IF(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -gdwarf-2 ")
ELSE()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --visibility=hidden -os")
    set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
ENDIF()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(src)
add_subdirectory(test)

