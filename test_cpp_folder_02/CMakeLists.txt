cmake_minimum_required (VERSION 3.0)

project(PSEUDO_BLOOD_PRESSURE_DETECTOR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -Wall")

set(A_HDR_DIR ${PROJECT_SOURCE_DIR}/include/a_f)
set(B_HDR_DIR ${PROJECT_SOURCE_DIR}/include/b_f)
set(INCLUDE_DIRS 
    ${A_HDR_DIR} 
    ${B_HDR_DIR} 
)
include_directories(${INCLUDE_DIRS})

set(SOURCE_A_DIR ${PROJECT_SOURCE_DIR}/src/a_f)
set(SOURCE_B_DIR ${PROJECT_SOURCE_DIR}/src/b_f)
set(SOURCE_C_DIR ${PROJECT_SOURCE_DIR}/src/c_f)
set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/main_.cpp 
    ${PROJECT_SOURCE_DIR}/src/print.cpp 
    
    ${SOURCE_A_DIR}/AAA.cpp 
    ${SOURCE_B_DIR}/BBB.cpp 
)

add_executable(0202_cpp_test ${SOURCE_FILES})

target_link_libraries(0202_cpp_test
    pthread
)