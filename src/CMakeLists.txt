
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

if(WIN32)
    find_library(PSAPI_LIBRARIES psapi)
endif()

#------------------------------------
# Project Setup
#------------------------------------
#### Project Files

include_directories(${CMAKE_CURRENT_LIST_DIR} )

file(GLOB_RECURSE SOURCES_BACNET_CPP "bacnet/*.cpp")
file(GLOB_RECURSE SOURCES_UTIL_CPP "util/*.cpp")


add_library(wookie ${SOURCES_BACNET_CPP} ${SOURCES_UTIL_CPP} )

add_executable(main main.cpp)
target_link_libraries(main wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread )


if(WIN32)
  target_link_libraries(main wsock32 ws2_32)
endif()
