cmake_minimum_required (VERSION 3.0)

project(pthread_management_time_trigger)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES
    &{PROJECT_SOURCE_DIR}/src/print_functions.cpp
    &{PROJECT_SOURCE_DIR}/src/pthread_management.cpp
)

add_executable(02_pthread_management ${SOURCE_FILES})

target_link_libraries(02_pthread_management
    pthread
    rt
)
