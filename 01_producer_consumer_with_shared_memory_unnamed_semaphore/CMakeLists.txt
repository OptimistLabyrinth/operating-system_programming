cmake_minimum_required (VERSION 2.6)

set (project_title "producer_consumer_shared_memory")
set (project_author "yks93")
set (project_revised_data "2018-10-16")

set (INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)

project ($(project_title))
# The version number.
set (${project_title}_VERSION_MAJOR 1)
set (${project_title}_VERSION_MINOR 0)
set (${project_title}_VERSION_PATCH 1)

# language standard, compiler settings
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

# Bring the headers into the project
include_directories(${INCLUDE_DIRS})

set (SRCs
    src/consumer_semaphore.c
    src/producer_semaphore.c
    src/print_functions.c
    src/producer_consumer_shared_memory_main.c
)

add_executable (01_Producer_Consumer ${SRCs})

# link with libraries
target_link_libraries(01_Producer_Consumer 
    pthread
    rt
)
