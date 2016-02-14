



add_executable(reinitialize_device reinitialize_device.cpp)
target_link_libraries(reinitialize_device wookie ${Boost_LIBRARIES} ${PSAPI_LIBRARIES} pthread )

