cmake_minimum_required(VERSION 2.6.0 FATAL_ERROR)

include_directories(src)
add_library(libdaemond src/libdaemond.c)
add_executable(sample ex/sample.c)
target_link_libraries(sample libdaemond)
set_target_properties (libdaemond PROPERTIES OUTPUT_NAME daemond)
