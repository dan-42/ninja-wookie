cmake_minimum_required(VERSION 3.2)

### Hunter snapshot that will be used ###
include("cmake/HunterGate.cmake")
HunterGate(
       # URL "https://github.com/dan-42/hunter/archive/v0.12.6-dan42.tar.gz"
       # SHA1 "a749367a24f25167f3b1f1712e45ad9a1f6a06e8"
       # LOCAL
       # URL "https://github.com/dan-42/hunter/archive/v0.12.43-dan.tar.gz"
       # SHA1 "db065c2f01e15d27207f9a3f37799b5b435f4c11"
       # URL "https://github.com/dan-42/hunter/archive/v0.12.44-dan.tar.gz"
       # SHA1 "b2c2510c34d89df7fb63d6f4e9454ea4f09464a6" 
        
       # URL "https://github.com/dan-42/hunter/archive/v0.16.9-beta.1.tar.gz"
       # SHA1 "43c4d031f15c4810e4f2e2cc990f3ea5c251028e"
        URL  "https://github.com/dan-42/hunter/archive/v0.16.15-beta.2.tar.gz"
        SHA1 "670c5234dfa2a785437e9afaf868861fd1f71188"
)


#SET (CMAKE_C_COMPILER       "/usr/bin/clang")    
#SET (CMAKE_CXX_COMPILER     "/usr/bin/clang++")
#SET (CMAKE_LINKER  "/home/dan/bin/ld")
#SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
#SET (CMAKE_AR      "/home/dan/bin/ar")
#SET (CMAKE_NM      "/home/dan/bin/nm")
#SET (CMAKE_RANLIB  "/home/dan/bin/ranlib")


project(wookie VERSION 0.0.1)

SET(CMAKE_BUILD_TYPE Release)

# If the user specifies -DCMAKE_BUILD_TYPE on the command line, take their definition
# and dump it in the cache along with proper documentation, otherwise set CMAKE_BUILD_TYPE
# to Debug prior to calling PROJECT()
# source: http://www.cmake.org/pipermail/cmake/2008-September/023808.html
IF(DEFINED CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "Choose the types of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release."  )
ELSE()
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the types of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release" )
ENDIF()


enable_testing()
add_subdirectory(src)
add_subdirectory(example)
add_subdirectory(test)


