#ifndef STATIC_VARIABLES__83bfa9ef_1e45_4e25_81e8_ecac1c6a3ad1__HPP___
#define STATIC_VARIABLES__83bfa9ef_1e45_4e25_81e8_ecac1c6a3ad1__HPP___

#include <memory>
#include <vector>
#include <unordered_map>

#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

#define MAX_THREAD_NUM      5

#define THOUSAND            1000UL
#define MILLION             1000000UL

using event = struct sigevent;
using t_spec = struct itimerspec;

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




#endif /* STATIC_VARIABLES__83bfa9ef_1e45_4e25_81e8_ecac1c6a3ad1__HPP___ */