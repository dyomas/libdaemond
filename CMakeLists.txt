cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

IF (NOT ${CMAKE_BUILD_TYPE} STREQUAL "Debug"
AND NOT ${CMAKE_BUILD_TYPE} STREQUAL "Release"
AND NOT ${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo"
AND NOT ${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
  message (FATAL_ERROR "Unknown build type \"${CMAKE_BUILD_TYPE}\"
Possible build types is \"Debug\", \"Release\", \"RelWithDebInfo\" and \"MinSizeRel\", case sensitive")
ENDIF()

set(CMAKE_C_FLAGS_DEBUG "-g3 -Wall -Wuninitialized -O1 -fno-inline -D_DEBUG" CACHE STRING "Debug flags" FORCE)
set(CMAKE_C_FLAGS_RELEASE "-g0 -O3" CACHE STRING "Release flags" FORCE)

include_directories(src)
add_library(libdaemond src/libdaemond.c)
set_target_properties (libdaemond PROPERTIES DEBUG_POSTFIX _d)
set_target_properties (libdaemond PROPERTIES OUTPUT_NAME daemond)

add_executable(sample EXCLUDE_FROM_ALL ex/sample.cpp ex/strings_manip.cpp ex/io_wrapper.cpp)
target_link_libraries(sample libdaemond)
