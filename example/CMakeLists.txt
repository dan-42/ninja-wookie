cmake_minimum_required(VERSION 3.2)


project(example-wookie)

if(TARGET wookie)
  add_library(wookie::wookie ALIAS wookie)
else()  
  #find_package(wookie CONFIG REQUIRED)  
endif()

hunter_add_package(Boost COMPONENTS system filesystem program_options)


#hunter_add_package(Boost COMPONENTS system filesystem program_options)
set(BOOST_ALL_DYN_LINK         ON)
set(Boost_USE_MULTITHREADED    ON)
set(Boost_USE_STATIC_LIBS      OFF)
set(Boost_USE_STATIC_RUNTIME   OFF)

find_package(Boost CONFIG REQUIRED system filesystem program_options)
#find_package(Boost 1.61 COMPONENTS filesystem program_options system  REQUIRED )
#find_package(Boost 1.61 COMPONENTS system REQUIRED )
link_directories (${Boost_LIBRARY_DIRS})
include_directories (${Boost_INCLUDE_DIRS})
add_definitions(-DBOOST_LOG_DYN_LINK)



add_executable(pg_run_time_mapping pg_run_time_mapping.cpp)
target_link_libraries(pg_run_time_mapping wookie Boost::boost ${PSAPI_LIBRARIES} pthread)
install(TARGETS pg_run_time_mapping DESTINATION bin)

add_executable(playground playground.cpp)
target_link_libraries(playground wookie Boost::boost ${PSAPI_LIBRARIES} pthread) 
install(TARGETS playground DESTINATION bin)

add_executable(read_property read_property.cpp)
target_link_libraries(read_property wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
install(TARGETS read_property DESTINATION bin)

add_executable(read_property_services_supported read_property_services_supported.cpp)
target_link_libraries(read_property_services_supported wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
install(TARGETS read_property_services_supported DESTINATION bin)

add_executable(reinitialize_device reinitialize_device.cpp)
target_link_libraries(reinitialize_device wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
install(TARGETS reinitialize_device DESTINATION bin)

add_executable(who_is who_is.cpp)
target_link_libraries(who_is wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
install(TARGETS who_is DESTINATION bin)

add_executable(who_is_unicast who_is_unicast.cpp)
target_link_libraries(who_is_unicast wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
install(TARGETS who_is_unicast DESTINATION bin)

include_directories (${CMAKE_CURRENT_SOURCE_DIR})
add_executable(bacnet_device bacnet_device/bacnet_device.cpp)
target_link_libraries(bacnet_device wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
install(TARGETS bacnet_device DESTINATION bin)


add_executable(id_device id_device.cpp)
target_link_libraries(id_device wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread)
install(TARGETS id_device DESTINATION bin)
