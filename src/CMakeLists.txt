# build the PIDController library
add_library(PIDController STATIC pid.cpp ${CMAKE_SOURCE_DIR}/include/pid.h)
target_include_directories(PIDController PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_library(MAX31865Driver INTERFACE)
target_sources(MAX31865Driver INTERFACE ${CMAKE_SOURCE_DIR}/include/max31865.h ${CMAKE_SOURCE_DIR}/include/max31865_impl.hpp)
target_include_directories(MAX31865Driver INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(MAX31865Driver INTERFACE idf::esp32)