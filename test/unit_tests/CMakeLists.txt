

cmake_minimum_required(VERSION 3.2)
project(test-wookie)
enable_testing()

if(TARGET wookie)
  add_library(wookie::wookie ALIAS wookie)
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

include_directories(${CMAKE_CURRENT_LIST_DIR} )


function(add_new_test test_name file_path)
    set(executable_name "${PROJECT_NAME}-${test_name}")

    file(GLOB NINJA_WOOKIE_TEST_SOURCE_CPP "${CMAKE_CURRENT_SOURCE_DIR}/${file_path}")

    add_executable ("${executable_name}"  "${NINJA_WOOKIE_TEST_SOURCE_CPP}")
    target_link_libraries (${executable_name}
                                wookie::wookie 
                                ${Boost_LIBRARIES} 
                                ${PSAPI_LIBRARIES} 
                                pthread
                                #${Boost_FILESYSTEM_LIBRARY}
                                #${Boost_SYSTEM_LIBRARY}
                                #${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
                                )

    set_target_properties(${executable_name} PROPERTIES DEBUG_POSTFIX "d")

    add_test (NAME ${executable_name} COMMAND ${executable_name})

endfunction(add_new_test)


add_subdirectory(bacnet/transport)
add_subdirectory(bacnet/bvll)
add_subdirectory(bacnet/npdu)
add_subdirectory(bacnet/apdu)
add_subdirectory(bacnet/service)





