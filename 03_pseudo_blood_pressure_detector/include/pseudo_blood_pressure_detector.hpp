#ifndef PSEUDO_BP_DETECTOR_WITH_PTHREAD_MANAGEDMENT_USING_CUSTOM_TIME_TRIGGER__e60eda2e_c2ae_4454_bcfe_d3504852f58a__HPP___
#define PSEUDO_BP_DETECTOR_WITH_PTHREAD_MANAGEDMENT_USING_CUSTOM_TIME_TRIGGER__e60eda2e_c2ae_4454_bcfe_d3504852f58a__HPP___

#include <queue>
#include <chrono>
#include <random>

#include "pthread_manager_with_time_trigger.hpp"

#define MAX_Q_SIZE 100

void init_mutex_cond(void);

void create_timer(void);
void alarm_clock(sigval_t arg);

void run_threads(void);

void* data_acquisition_thread(void* arg);
void enqueue_acquired_data(void* arg);

void* bp_processing_thread(void* arg);
void dequeue_data_to_process(void* arg);

#endif /* PSEUDO_BP_DETECTOR_WITH_PTHREAD_MANAGEDMENT_USING_CUSTOM_TIME_TRIGGER__e60eda2e_c2ae_4454_bcfe_d3504852f58a__HPP___ */