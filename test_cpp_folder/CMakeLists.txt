cmake_minimum_required (VERSION 3.0)

project(ANYTHING_TEST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=gnu++14 -Wall")

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/main_thread_executor.cpp
)

add_executable (09_test ${SOURCE_FILES})

target_link_libraries(09_test
    pthread
    rt
)
