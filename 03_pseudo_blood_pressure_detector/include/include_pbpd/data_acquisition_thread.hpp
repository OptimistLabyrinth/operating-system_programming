#ifndef DATA_ACQUISITION_THREAD__67c639ed_0028_43fa_aea8_5e52f61ba665__HPP___
#define DATA_ACQUISITION_THREAD__67c639ed_0028_43fa_aea8_5e52f61ba665__HPP___

#include "static_pbpd_variables.hpp"
#include "pseudo_blood_pressure_generator.hpp"
#include "enqueue_bp_queue.hpp"
#include "../include_ptttm/tt_thread_register.hpp"
#include "../include_ptttm/tt_thread_wait_invocation.hpp"



void enqueue_acquired_data(uint*);
void* data_acquisition_thread(void*);



#endif /* DATA_ACQUISITION_THREAD__67c639ed_0028_43fa_aea8_5e52f61ba665__HPP___ */