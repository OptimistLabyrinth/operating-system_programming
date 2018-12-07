#ifndef CREATE_POSIX_TIMER__52cd9a48_c37b_4e78_9ef8_1e7874516e55__HPP___
#define CREATE_POSIX_TIMER__52cd9a48_c37b_4e78_9ef8_1e7874516e55__HPP___

#define TIMER_FREQUENCY_FROM_INTERNAL       101
#define TIMER_FREQUENCY_FROM_FILE           202
#define TIMER_FREQUENCY_FROM_STDIN          303

#include "static_variables.hpp"
#include "periodic_handler.hpp"
#include "print_functions.hpp"



size_t get_timer_frequency(void);
void set_timer_arguments(void);
void create_posix_timer(void);



#endif /* CREATE_POSIX_TIMER__52cd9a48_c37b_4e78_9ef8_1e7874516e55__HPP___ */