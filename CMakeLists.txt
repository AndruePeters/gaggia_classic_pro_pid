# Andrue Peters
# 12/13/2020
cmake_minimum_required(VERSION 3.5)

project(single_boiler_pid CXX C)

# Include for ESP-IDF build system functions
include($ENV{IDF_PATH}/tools/cmake/idf.cmake)

add_subdirectory(src)

# build the main app that will be programmed on the esp32
add_subdirectory(app)
add_subdirectory(external)
add_subdirectory(tests)


set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
