# build the PIDController library
add_library(PIDController STATIC pid.cpp ${CMAKE_SOURCE_DIR}/include/pid.h)
target_include_directories(PIDController PUBLIC ${CMAKE_SOURCE_DIR}/include)

#add_library(MAX31865Driver STATIC max31865.cpp ${CMAKE_SOURCE_DIR}/include/max31865.h)
#target_include_directories(MAX31865Driver PUBLIC ${CMAKE_SOURCE_DIR}/include)