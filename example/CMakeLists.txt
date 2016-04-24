

cmake_minimum_required(VERSION 3.2)

project(example-wookie)

if(TARGET wookie)
 # add_library(wookie::wookie ALIAS wookie)
else()  
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


add_executable(playground playground.cpp)
target_link_libraries(playground wookie::wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
set_target_properties(playground PROPERTIES DEBUG_POSTFIX "d")
install(TARGETS playground DESTINATION bin)

add_executable(reinitialize_device reinitialize_device.cpp)
target_link_libraries(reinitialize_device wookie::wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
set_target_properties(reinitialize_device PROPERTIES DEBUG_POSTFIX "d")
install(TARGETS reinitialize_device DESTINATION bin)



add_executable(who_is who_is.cpp)
target_link_libraries(who_is wookie::wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
set_target_properties(who_is PROPERTIES DEBUG_POSTFIX "d")
install(TARGETS who_is DESTINATION bin)



add_executable(bacnet_device bacnet_device.cpp)
target_link_libraries(bacnet_device wookie::wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
set_target_properties(bacnet_device PROPERTIES DEBUG_POSTFIX "d")
install(TARGETS bacnet_device DESTINATION bin)
