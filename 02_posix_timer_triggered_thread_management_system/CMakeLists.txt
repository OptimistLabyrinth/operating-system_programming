cmake_minimum_required (VERSION 3.0)

project(PTHREAD_MANAGEMENT_WITH_TIME_TRIGGER)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=gnu++14 -Wall")

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIRS})

set(SOURCE_FILES 
    ${PROJECT_SOURCE_DIR}/src/create_posix_timer.cpp
    ${PROJECT_SOURCE_DIR}/src/create_pthread.cpp
    ${PROJECT_SOURCE_DIR}/src/initialize_variables.cpp
    ${PROJECT_SOURCE_DIR}/src/main_executor.cpp
    ${PROJECT_SOURCE_DIR}/src/periodic_handler.cpp
    ${PROJECT_SOURCE_DIR}/src/print_functions.cpp
    ${PROJECT_SOURCE_DIR}/src/static_variables.cpp
    ${PROJECT_SOURCE_DIR}/src/thread_to_be_managed.cpp
    ${PROJECT_SOURCE_DIR}/src/tt_thread_register.cpp
    ${PROJECT_SOURCE_DIR}/src/tt_thread_wait_invocation.cpp
)

add_executable (02_pm_tt ${SOURCE_FILES})

target_link_libraries(02_pm_tt
    pthread
    rt
)
