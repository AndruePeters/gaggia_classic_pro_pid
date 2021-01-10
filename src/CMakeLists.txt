# build the PIDController library
add_library(PIDController STATIC pid.cpp ${CMAKE_SOURCE_DIR}/include/pid.h)
target_include_directories(PIDController PUBLIC ${CMAKE_SOURCE_DIR}/include)
