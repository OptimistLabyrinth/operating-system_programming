cmake_minimum_required (VERSION 3.0)

project(TIMER_TEST)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -Wall")

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/class_test.cpp
    ${PROJECT_SOURCE_DIR}/src/main_runner.cpp
    ${PROJECT_SOURCE_DIR}/src/print_functions.cpp
    ${PROJECT_SOURCE_DIR}/src/pthread_manager.cpp
)

add_executable (00_pthread_test_with_class ${SOURCE_FILES})

target_link_libraries(00_pthread_test_with_class
    pthread
    rt
)
