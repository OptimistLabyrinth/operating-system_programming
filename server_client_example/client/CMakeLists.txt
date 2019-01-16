cmake_minimum_required (VERSION 3.0)

project(client_program_for_socket_programming_in_c)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall")

set(INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
include_directories(${INCLUDE_DIRS})

set(SOURCE_FILE_DIR ${PROJECT_SOURCE_DIR}/src)
set(SOURCE_FILES
		${SOURCE_FILE_DIR}/client_old_02.c
)
add_executable(client_program ${SOURCE_FILES})

target_link_libraries(client_program
	
)

