hunter_add_package(Boost COMPONENTS system)


set(BOOST_ALL_DYN_LINK ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)



# boost

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
