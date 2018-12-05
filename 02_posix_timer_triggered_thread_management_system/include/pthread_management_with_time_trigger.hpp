#ifndef PTHREAD_MANAGEMENT_WITH_TIME_TRIGGER__64b2becc_4d42_43ce_92ac_e3c72d73159a__HPP___
#define PTHREAD_MANAGEMENT_WITH_TIME_TRIGGER__64b2becc_4d42_43ce_92ac_e3c72d73159a__HPP___

#include <cstdlib>
#include <vector>
#include <unordered_map>
#include <cstring>
#include <ctime>

#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>

#include "print_functions.hpp"
#include "error_codes.hpp"

#define MAX_THREAD_NUM     4
#define MILLISECOND        1000000L

// timer type
#define TIMER_FOR_COND_SIGNAL_HANDLER       1U

// thread type


using period_t = long;
using event = struct sigevent;
using t_spec = struct itimerspec;

using TCB = struct TCB;
typedef struct TCB {

    pthread_t     tid;
    long          period;
    long          time_left_to_invoke;
} TCB;

using data_for_cond_signal = struct arg_create_posix_timer_for_cond_signal_handler;
struct arg_create_posix_timer_for_cond_signal_handler {
    uint which_type;
};

using data_for_mgd_thr = struct arg_pthread_create_time_trigger_managed;
struct arg_pthread_create_time_trigger_managed {
    period_t new_period;
};

using ret_type_of_tt_w_invk = struct ret_type_of_tt_thread_wait_invocation;
struct ret_type_of_tt_thread_wait_invocation {
    int error_code;
    int index;
};





// function prototypes 
int initialize_variables(void);

int execution(void);

int create_posix_timer(void*);

void* thread_to_be_managed(void*);
int tt_thread_register(int64_t, pthread_t);
ret_type_of_tt_w_invk tt_thread_wait_invocation(pthread_t);

void periodic_handler(sigval_t);

#endif /* PTHREAD_MANAGEMENT_WITH_TIME_TRIGGER__64b2becc_4d42_43ce_92ac_e3c72d73159a__HPP___ */