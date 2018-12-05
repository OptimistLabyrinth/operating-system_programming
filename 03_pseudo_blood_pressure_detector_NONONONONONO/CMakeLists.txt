cmake_minimum_required (VERSION 3.0)

project(PSEUDO_BLOOD_PRESSURE_DETECTOR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -Wall")

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/print_functions.cpp
    ${PROJECT_SOURCE_DIR}/src/pthread_management_with_time_trigger.cpp
    ${PROJECT_SOURCE_DIR}/src/pseudo_blood_pressure_detector.cpp
    ${PROJECT_SOURCE_DIR}/src/main_controller.cpp
)

add_executable (03_pseudo_bp_detector ${SOURCE_FILES})

target_link_libraries(03_pseudo_bp_detector
    pthread
    rt
)
