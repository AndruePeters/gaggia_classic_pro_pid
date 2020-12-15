# This CMakeLists.txt is responsible for setting up external libraries
include(ExternalProject)

#ExternalProject_Add(fmt
#        GIT_REPOSITORY    https://github.com/fmtlib/fmt
#        GIT_TAG           7.1.3
#        INSTALL_COMMAND cmake -E echo "Skipping install step."
#        CMAKE_ARGS
#            -DCMAKE_TOOLCHAIN_FILE=$ENV{IDF_PATH}/tools/cmake/toolchain-esp32.cmake
#        )