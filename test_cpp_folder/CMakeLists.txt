cmake_minimum_required (VERSION 3.0)

project(TIMER_TEST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -Wall")

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/posix_thread_test.cpp
)

add_executable (pthread_test ${SOURCE_FILES})

target_link_libraries(pthread_test
    pthread
    rt
)
