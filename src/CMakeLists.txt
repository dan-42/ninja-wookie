
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

find_package(Boost 1.55 COMPONENTS  system REQUIRED )
link_directories (${Boost_LIBRARY_DIRS})
include_directories (${Boost_INCLUDE_DIRS})
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)

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

file(GLOB_RECURSE SOURCES_CPP "*.cpp")


add_library(wookie ${SOURCES_CPP} bacnet/apdu/detail/type/tag_grammar.hpp)

add_executable(main  main.cpp)
target_link_libraries(main wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES}  pthread)


if(WIN32)
  target_link_libraries(main wsock32 ws2_32)
endif()
