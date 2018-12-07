#ifndef CREATE_PTHREAD__a80a435d_da41_4fbd_82e2_1a77995a4c1a__HPP___
#define CREATE_PTHREAD__a80a435d_da41_4fbd_82e2_1a77995a4c1a__HPP___

#include "static_ptttm_variables.hpp"
#include "../include_pbpd/data_acquisition_thread.hpp"
#include "../include_pbpd/bp_processing_thread.hpp"

#define DATA_ACQUISITION_THREAD_TYPE                4321U
#define BLOOD_PRESSURE_PROCESSING_THREAD_TYPE       9876U



void add_pthread_arguments(uint, size_t);
void create_new_thread(uint);



#endif /* CREATE_PTHREAD__a80a435d_da41_4fbd_82e2_1a77995a4c1a__HPP___ */