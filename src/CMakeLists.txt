# This file creates project 'wookie' with library targets 'wookie'.
# After installation this project can be found
# by 'find_package(... CONFIG)' command:
#
#    find_package(wookie CONFIG REQUIRED)
#    target_link_libraries(... wookie::wookie)
#
# Note that requirements propagated automatically, for example:
#   * dependancies will be linked automatically
#   * <prefix>/include added to header search path
#   * WOOKIE_DEBUG=1 added on Debug
#   * WOOKIE_DEBUG=0 added on other configurations

####
# Set minimum version of CMake. Since command 'project' use
cmake_minimum_required(VERSION 3.2)


# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their definition
# and dump it in the cache along with proper documentation, otherwise set CMAKE_BUILD_TYPE
# to Debug prior to calling PROJECT()
# source: http://www.cmake.org/pipermail/cmake/2008-September/023808.html
IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the types of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release."  )
ELSE()
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the types of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release" )
ENDIF()




list (INSERT WOOKIE_COMPILE_FLAGS 0
                    -std=c++14 
                    -Wall 
                    -Werror
                    -fPIC
                  #  -Wpedantic
                    # needed for boost library
                    -Wno-unused-function 
                    -Wno-unused-local-typedefs 
                    -Wno-unused-variable 
                    -Wno-unused-value                   
                    -Wno-deprecated-declarations
                    -Wno-placement-new # needed for gcc6 and boost 1.61 boost.function
                    )


IF(CMAKE_BUILD_TYPE STREQUAL Debug)

    list (APPEND WOOKIE_COMPILE_FLAGS  
                    -g
                    -gdwarf-2)
                    
     if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        set (CMAKE_EXE_LINKER_FLAGS " -Wl,--gc-sections ")       

        list(APPEND WOOKIE_COMPILE_FLAGS                     
                -ffunction-sections
                -fdata-sections                             
        )
    endif()
    
ELSE()
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        #set (CMAKE_EXE_LINKER_FLAGS " -Wl,--gc-sections -flto")
        set (CMAKE_EXE_LINKER_FLAGS " -Wl,--gc-sections ")

        list(APPEND WOOKIE_COMPILE_FLAGS
                -fvisibility=hidden                
                -ffunction-sections
                -fdata-sections
               # -flto 
               # -fuse-linker-plugin                        
        )

        
        
    endif()
    list(APPEND WOOKIE_COMPILE_FLAGS        
                -Os         
                -s                       
        )    
ENDIF()






hunter_add_package(Boost COMPONENTS system filesystem)
#set(BOOST_ALL_DYN_LINK         ON)
#set(Boost_USE_MULTITHREADED    ON)
#set(Boost_USE_STATIC_LIBS      OFF)
#set(Boost_USE_STATIC_RUNTIME   OFF)

find_package(Boost CONFIG REQUIRED system filesystem)
#find_package(Boost 1.61 COMPONENTS system REQUIRED )
#link_directories (${Boost_LIBRARY_DIRS})
#include_directories (${Boost_INCLUDE_DIRS})
#add_definitions(-DBOOST_LOG_DYN_LINK)

# pre
hunter_add_package(lib-cpp-pre)
find_package(lib-cpp-pre  REQUIRED)
include_directories(AFTER ${LIB_CPP_PRE_INCLUDE_DIRS})

# Threads
find_package(Threads)


####
# Create targets
file(GLOB_RECURSE SOURCES_BACNET_CPP "bacnet/*.cpp")
file(GLOB_RECURSE SOURCES_UTIL_CPP "util/*.cpp")

add_library(wookie ${SOURCES_BACNET_CPP} ${SOURCES_UTIL_CPP} )



####
# Properties of targets

# Add definitions for targets
# Values:
#   * Debug:   -DWOOKIE_DEBUG=1
#   * Release: -DWOOKIE_DEBUG=0
#   * other:   -DWOOKIE_DEBUG=0
#target_compile_definitions(wookie PUBLIC "WOOKIE_DEBUG=$<CONFIG:Debug>")
add_definitions(${WOOKIE_COMPILE_FLAGS})

# Generate:
#   * ${CMAKE_CURRENT_BINARY_DIR}/wookie_export.h with WOOKIE_EXPORT
include(GenerateExportHeader)
generate_export_header(wookie)


# Global includes. Used by all targets
# Note:
#   * header location in project: src/bacnet/.../.hpp
#   * header can be included by C++ code `#include <bacnet/.../.hpp>`
#   * header location in project: ${CMAKE_CURRENT_BINARY_DIR}/wookie_export.hpp
#   * header can be included by: `#include <wookie_export.hpp>`
target_include_directories(
    wookie PUBLIC
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>"
    "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>"
)

# Link required library
target_link_libraries(wookie INTERFACE  
                                    ${Boost_FILESYSTEM_LIBRARY}
                                    ${Boost_SYSTEM_LIBRARY}                                    
                                    )

set_target_properties(wookie
  PROPERTIES
  INTERFACE_COMPILE_OPTIONS "${WOOKIE_COMPILE_FLAGS}")

####
# Installation (https://github.com/forexample/package-example)

# Layout. This works for all platforms:
#   * <prefix>/lib/cmake/<PROJECT-NAME>
#   * <prefix>/lib/
#   * <prefix>/include/
set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# Configuration
set(version_config "${generated_dir}/${PROJECT_NAME}ConfigVersion.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}Config.cmake")
set(targets_export_name "${PROJECT_NAME}Targets")
set(namespace "${PROJECT_NAME}::")

# Include module with fuction 'write_basic_package_version_file'
include(CMakePackageConfigHelpers)

# Configure '<PROJECT-NAME>ConfigVersion.cmake'
# Note: PROJECT_VERSION is used as a VERSION
write_basic_package_version_file(
    "${version_config}" COMPATIBILITY SameMajorVersion
)

# Configure '<PROJECT-NAME>Config.cmake'
# Use variables:
#   * targets_export_name
#   * PROJECT_NAME
configure_package_config_file(
    "cmake/Config.cmake.in"
    "${project_config}"
    INSTALL_DESTINATION "${config_install_dir}"
)

# Targets:
#   * <prefix>/lib/libbar.a
#   * <prefix>/lib/libbaz.a
#   * header location after install: <prefix>/include/foo/Bar.hpp
#   * headers can be included by C++ code `#include <foo/Bar.hpp>`
install(
    TARGETS wookie
    EXPORT "${targets_export_name}"
    LIBRARY DESTINATION "lib"
    ARCHIVE DESTINATION "lib"
    RUNTIME DESTINATION "bin"
    INCLUDES DESTINATION "${include_install_dir}"
)

# Headers:
#   * src/*.hpp -> <prefix>/include/*.hpp
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bacnet"
    DESTINATION "${include_install_dir}/bacnet"
    FILES_MATCHING PATTERN "*.hpp"
)
install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/util"
    DESTINATION "${include_install_dir}/util"
    FILES_MATCHING PATTERN "*.hpp"
)

# Export headers:
#   * ${CMAKE_CURRENT_BINARY_DIR}/bar_export.h -> <prefix>/include/bar_export.h
#   * ${CMAKE_CURRENT_BINARY_DIR}/baz_export.h -> <prefix>/include/baz_export.h
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/wookie_export.h"
    DESTINATION "${include_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooConfig.cmake
#   * <prefix>/lib/cmake/Foo/FooConfigVersion.cmake
install(
    FILES "${project_config}" "${version_config}"
    DESTINATION "${config_install_dir}"
)

# Config
#   * <prefix>/lib/cmake/Foo/FooTargets.cmake
install(
    EXPORT "${targets_export_name}"
    NAMESPACE "${namespace}"
    DESTINATION "${config_install_dir}"
)







