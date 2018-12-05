#ifndef ___PSEUDO_BLOOD_PRESSURE_DETECTOR__12561215_6b02_45f0_afad_22bc849cbc94__HPP___
#define ___PSEUDO_BLOOD_PRESSURE_DETECTOR__12561215_6b02_45f0_afad_22bc849cbc94__HPP___

#include <queue>
#include <chrono>
#include <random>

#include "../include/pthread_management_with_time_trigger.hpp"

#define MAX_Q_SIZE 100

void init_everything(void);

void create_timer(void);
void alarm_clock(sigval_t arg);

void run_threads(void);

void* data_acquisition_thread(void* arg);
void enqueue_acquired_data(void* arg);

void* bp_processing_thread(void* arg);
void dequeue_data_to_process(void* arg);
// void display_10_data_and_dequeue_from(void*); // only for error check

#endif /* ___PSEUDO_BLOOD_PRESSURE_DETECTOR__12561215_6b02_45f0_afad_22bc849cbc94__HPP___ */