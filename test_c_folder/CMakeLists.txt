cmake_minimum_required (VERSION 3.0) 

project(POSIX_TIMER_SIMPLE_EXAMPLE)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

set (INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

set (SOURCE_FILES
    src/posix_timer_example.c
)

add_executable (ptmr_ex ${SOURCE_FILES})

target_link_libraries(ptmr_ex
    rt
)
