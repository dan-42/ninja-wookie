hunter_add_package(Boost COMPONENTS system)


set(BOOST_ALL_DYN_LINK ON)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)



# boost
find_package(Boost 1.59 COMPONENTS  system  REQUIRED )
link_directories (${Boost_LIBRARY_DIRS})
include_directories (${Boost_INCLUDE_DIRS})
add_definitions (-DBOOST_TEST_DYN_LINK)

# Threads
find_package(Threads)

if(WIN32)
    find_library(PSAPI_LIBRARIES psapi)
endif()

include_directories("../../src")
include_directories(${CMAKE_CURRENT_LIST_DIR} )


function(add_new_test test_name file_path)
    set(executable_name "${NINJA_WOOKIE_TEST_NAME}_${test_name}")

    file(GLOB NINJA_WOOKIE_TEST_SOURCE_CPP "${file_path}/*.cpp")

    message(INFO "TEST ${NINJA_WOOKIE_TEST_SOURCE_CPP}")
    message(INFO "TEST ${file_path}")

    add_executable ("${executable_name}"  "${NINJA_WOOKIE_TEST_SOURCE_CPP}")
    target_link_libraries (${executable_name}
            ${NINJA_WOOKIE_LIBRARY_NAME}
            ${Boost_FILESYSTEM_LIBRARY}
            ${Boost_SYSTEM_LIBRARY}
            ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
            )

    if(WIN32)
        target_link_libraries(${executable_name} wsock32 ws2_32)
    endif()

    add_test (NAME ${executable_name} COMMAND ${executable_name})

endfunction(add_new_test)
# todo make path absolut 
add_new_test("bacnet_ip_address" "./bacnet/bvll/types")



