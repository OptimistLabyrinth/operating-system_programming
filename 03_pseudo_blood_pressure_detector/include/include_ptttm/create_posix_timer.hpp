#ifndef CREATE_POSIX_TIMER__eb2daa61_5eec_4e91_8f17_fd21d5312ee8__HPP___
#define CREATE_POSIX_TIMER__eb2daa61_5eec_4e91_8f17_fd21d5312ee8__HPP___

#define TIMER_FREQUENCY_FROM_INTERNAL       101
#define TIMER_FREQUENCY_FROM_FILE           202
#define TIMER_FREQUENCY_FROM_STDIN          303

#include "static_ptttm_variables.hpp"
// #include "periodic_handler.hpp"
#include "../include_pbpd/periodic_alarm_clock.hpp"



size_t get_timer_frequency(void);
void set_timer_arguments(void);
void create_posix_timer(void);



#endif /* CREATE_POSIX_TIMER__eb2daa61_5eec_4e91_8f17_fd21d5312ee8__HPP___ */