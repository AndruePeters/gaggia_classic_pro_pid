if(NOT CMAKE_CROSSCOMPILING)
    add_executable(model_boiler model_boiler.cpp)
    target_link_libraries(model_boiler PRIVATE PIDController)
endif()