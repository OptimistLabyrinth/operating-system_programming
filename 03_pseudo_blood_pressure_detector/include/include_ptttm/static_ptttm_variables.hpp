#ifndef STATIC_PTTTM_VARIABLES__11e7bb96_698c_43ee_8e2b_c3dd52e333c7__HPP___
#define STATIC_PTTTM_VARIABLES__11e7bb96_698c_43ee_8e2b_c3dd52e333c7__HPP___

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#include "../user_defined_types.hpp"
#include "../print_functions.hpp"
#include "../include_pbpd/static_pbpd_variables.hpp"

#define ZERO                0UL
#define ONE                 1UL
#define TEN                 10UL
#define HUNDRED             100UL
#define THOUSAND            1000UL
#define MILLION             1000000UL

struct TCB
{
    pthread_t       tid;
    long            period;
    long            time_left_to_invoke;
    // size_t          self_TCB_idx;
};
using TCB = struct TCB;

struct timer_args
{
    size_t ptimer_period;
};
using timer_args = struct timer_args;

struct thread_args
{
    size_t period;
};
using thread_args = struct thread_args;

struct Container_All
{
    pthread_mutex_t API_Mutex;
    std::vector<pthread_cond_t> API_Cond_Array;

    std::vector<timer_args> TM_Args;
    timer_t Timer;

    std::vector<thread_args> THR_Args;
    std::vector<pthread_t> Threads;
    std::vector<TCB> TCB_array;
    size_t TCB_position;
    std::unordered_map<pthread_t, size_t> IDX_Table;

};
using Container_All = struct Container_All;



#endif /* STATIC_PTTTM_VARIABLES__11e7bb96_698c_43ee_8e2b_c3dd52e333c7__HPP___ */