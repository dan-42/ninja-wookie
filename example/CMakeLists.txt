

cmake_minimum_required(VERSION 3.2)
project(example-wookie)

if(TARGET wookie)
  add_library(wookie::wookie ALIAS wookie)
else()
  # Add NO_CMAKE_BUILDS_PATH for windows if using CMake-GUI to build packages
  # to avoid searching in temporary build directory of Foo project
  # See 5:
  #    * http://www.cmake.org/cmake/help/v3.0/command/find_package.html
  find_package(wookie CONFIG REQUIRED)
endif()




hunter_add_package(Boost COMPONENTS system)
set(BOOST_ALL_DYN_LINK         ON)
set(Boost_USE_MULTITHREADED    ON)
set(Boost_USE_STATIC_LIBS      OFF)
set(Boost_USE_STATIC_RUNTIME   OFF)

find_package(Boost 1.60 COMPONENTS system REQUIRED )
link_directories (${Boost_LIBRARY_DIRS})
include_directories (${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_LOG_DYN_LINK)

# pre
#hunter_add_package(lib-cpp-pre)
#find_package(lib-cpp-pre 1.3.2 REQUIRED)
#include_directories(AFTER ${LIB_CPP_PRE_INCLUDE_DIRS})

# Threads
find_package(Threads)

add_executable(reinitialize_device reinitialize_device.cpp)
target_link_libraries(reinitialize_device wookie::wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
set_target_properties(reinitialize_device PROPERTIES DEBUG_POSTFIX "d")


enable_testing()
add_test(NAME reinitialize_device COMMAND reinitialize_device)

#install(TARGETS boo DESTINATION bin)


