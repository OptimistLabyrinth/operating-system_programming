cmake_minimum_required (VERSION 3.0)

project(PTHREAD_MANAGEMENT_WITH_TIME_TRIGGER)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -Wall")

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/print_functions.cpp
    ${PROJECT_SOURCE_DIR}/src/pthread_management_with_time_trigger.cpp
)

add_executable (02_trig_pth_mgnt ${SOURCE_FILES})

target_link_libraries(02_trig_pth_mgnt
    pthread
    rt
)
