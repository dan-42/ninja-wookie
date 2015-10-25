#hunter_add_package(Boost COMPONENTS system unit_test_framework)

set(BOOST_ALL_DYN_LINK ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)


set(Boost_NO_SYSTEM_PATHS TRUE)
if (Boost_NO_SYSTEM_PATHS)
    set(BOOST_ROOT "/opt/boost_1_59_0")
    set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
    set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS)

#find_package(Boost 1.59 COMPONENTS  system unit_test_framework  REQUIRED )
#add_definitions (-DBOOST_TEST_DYN_LINK)
#link_directories (${Boost_LIBRARY_DIRS})
#include_directories (${Boost_INCLUDE_DIRS})
#ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

find_package(Boost 1.59 COMPONENTS  system  REQUIRED )
link_directories (${Boost_LIBRARY_DIRS})
include_directories (${Boost_INCLUDE_DIRS})

# Threads
find_package(Threads)

if(WIN32)
    find_library(PSAPI_LIBRARIES psapi)
endif()

#------------------------------------
# Project Setup
#------------------------------------
#### Project Files

include_directories("../../src")
include_directories(${CMAKE_CURRENT_LIST_DIR} )

file(GLOB_RECURSE TEST_SOURCES_CPP "*.cpp")


add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (${NINJA_WOOKIE_TEST_NAME} ${TEST_SOURCES_CPP})
target_link_libraries (${NINJA_WOOKIE_TEST_NAME}
        ${NINJA_WOOKIE_LIBRARY_NAME}
        ${Boost_FILESYSTEM_LIBRARY}
        ${Boost_SYSTEM_LIBRARY}
        ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)


if(WIN32)
    target_link_libraries(${NINJA_WOOKIE_TEST_NAME} wsock32 ws2_32)
endif()
