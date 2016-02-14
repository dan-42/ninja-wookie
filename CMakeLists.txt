cmake_minimum_required(VERSION 3.0)

### Hunter snapshot that will be used ###
include("cmake/HunterGate.cmake")
HunterGate(
       # URL "https://github.com/dan-42/hunter/archive/v0.12.6-dan42.tar.gz"
       # SHA1 "a749367a24f25167f3b1f1712e45ad9a1f6a06e8"
       # LOCAL
        URL "https://github.com/dan-42/hunter/archive/v0.12.42-dan.tar.gz"
        SHA1 "e20106adbd1dfe0f437515d0bd4152ecd755b0a7"
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


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Werror")
# needed for boost library
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function -Wno-unused-local-typedefs -Wno-unused-variable -Wno-unused-value -Wno-deprecated-declarations")

#-DBOOST_NO_CXX11_CONSTEXPR -DBOOST_PP_VARIADICS=0
IF(CMAKE_BUILD_TYPE STREQUAL Debug)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -gdwarf-2 ")
ELSE()
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set (CMAKE_EXE_LINKER_FLAGS " -Wl,--gc-sections")

        add_definitions(
                -fvisibility=hidden
                -Os
                -ffunction-sections
                -fdata-sections)
    endif()

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os")
    set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
ENDIF()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})



hunter_add_package(Boost COMPONENTS system)

set(BOOST_ALL_DYN_LINK ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# boost
find_package(Boost 1.60 COMPONENTS system REQUIRED )
link_directories (${Boost_LIBRARY_DIRS})
include_directories (${Boost_INCLUDE_DIRS})
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
#ADD_DEFINITIONS(-DBOOST_ERROR_CODE_HEADER_ONLY)

# pre
#hunter_add_package(lib-cpp-pre)
#find_package(lib-cpp-pre 1.3.2 REQUIRED)
#include_directories(AFTER ${LIB_CPP_PRE_INCLUDE_DIRS})

# Threads
find_package(Threads)

include_directories("${CMAKE_CURRENT_LIST_DIR}/src" )

file(GLOB_RECURSE SOURCES_BACNET_CPP "src/bacnet/*.cpp")
file(GLOB_RECURSE SOURCES_UTIL_CPP "src/util/*.cpp")

add_library(wookie ${SOURCES_BACNET_CPP} ${SOURCES_UTIL_CPP} )

#add_executable(main main.cpp)
#target_link_libraries(main wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread )


add_subdirectory(example)
add_subdirectory(test)

