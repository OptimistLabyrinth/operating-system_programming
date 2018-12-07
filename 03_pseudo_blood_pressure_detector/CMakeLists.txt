cmake_minimum_required (VERSION 3.0)

project(PSEUDO_BLOOD_PRESSURE_DETECTOR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++14 -Wall")

set(INCLUDE_ROOT_DIRS ${PROJECT_SOURCE_DIR}/include)
set(INCLUDE_PTTTM_DIRS ${PROJECT_SOURCE_DIR}/include/include_ptttm)
set(INCLUDE_PBPD_DIRS ${PROJECT_SOURCE_DIR}/include/include_pbpd)
set(INCLUDE_DIRS 
    ${INCLUDE_ROOT_DIRS} 
    ${INCLUDE_PTTTM_DIRS} 
    ${INCLUDE_PBPD_DIRS} 
)
include_directories(${INCLUDE_DIRS})

set(SOURCE_ROOT_DIR ${PROJECT_SOURCE_DIR}/src)
set(SOURCE_PBPD_DIR ${PROJECT_SOURCE_DIR}/src/src_pbpd)
set(SOURCE_PTTTM_DIR ${PROJECT_SOURCE_DIR}/src/src_ptttm)
set(SOURCE_FILES
    ${SOURCE_ROOT_DIR}/main_executor.cpp 
    ${SOURCE_ROOT_DIR}/print_functions.cpp 
    
    ${SOURCE_PBPD_DIR}/bp_processing_thread.cpp 
    ${SOURCE_PBPD_DIR}/data_acquisition_thread.cpp 
    ${SOURCE_PBPD_DIR}/dequeue_bp_queue.cpp 
    ${SOURCE_PBPD_DIR}/enqueue_bp_queue.cpp 
    ${SOURCE_PBPD_DIR}/initialize_pbpd_variables.cpp 
    ${SOURCE_PBPD_DIR}/periodic_alarm_clock.cpp 
    ${SOURCE_PBPD_DIR}/pseudo_blood_pressure_generator.cpp 
    ${SOURCE_PBPD_DIR}/static_pbpd_variables.cpp 

    ${SOURCE_PTTTM_DIR}/create_posix_timer.cpp 
    ${SOURCE_PTTTM_DIR}/create_pthread.cpp 
    ${SOURCE_PTTTM_DIR}/initialize_ptttm_variables.cpp 
    ${SOURCE_PTTTM_DIR}/static_ptttm_variables.cpp 
    ${SOURCE_PTTTM_DIR}/tt_thread_register.cpp 
    ${SOURCE_PTTTM_DIR}/tt_thread_wait_invocation.cpp 
)

add_executable(03_pseudo_blood_pressure_detector ${SOURCE_FILES})

target_link_libraries(03_pseudo_blood_pressure_detector
    pthread
    rt
)