# This CMakeLists.txt is responsible for setting up external libraries
include(ExternalProject)

#ExternalProject_Add(fmt
#        GIT_REPOSITORY    https://github.com/fmtlib/fmt
#        GIT_TAG           7.1.3
#        INSTALL_COMMAND cmake -E echo "Skipping install step."
#        CMAKE_ARGS
#            -DCMAKE_TOOLCHAIN_FILE=$ENV{IDF_PATH}/tools/cmake/toolchain-esp32.cmake
#        )

add_library(maxController ESP32-MAX31865/src/Max31865.cpp ESP32-MAX31865/src/numerics.cpp)
target_include_directories(maxController PUBLIC ESP32-MAX31865/include/)
target_link_libraries(maxController PUBLIC idf::esp32 idf::freertos idf::spi_flash )