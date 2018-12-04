#ifndef ___PTHREAD_MANAGEMENT_WITH_TIME_TRIGGER__83f68d7d_2525_4a77_ac5a_1c28d54241bc__H___
#define ___PTHREAD_MANAGEMENT_WITH_TIME_TRIGGER__83f68d7d_2525_4a77_ac5a_1c28d54241bc__H___

#include <vector>
#include <unordered_map>
#include <cstring>
#include <ctime>

#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>

#include "print_functions.h"

#define MAX_THREAD_NUM     10
#define MILLISECOND        1000000L

// timer type
#define TIMER_FOR_COND_SIGNAL_HANDLER       1U

// thread type





// Global Variables - POSIX Mutex & Condition Variables
pthread_mutex_t API_Mutex;
std::vector<pthread_cond_t> COND_array;







using period_t = long;
using event = struct sigevent;
using t_spec = struct itimerspec;

using TCB = struct TCB;
typedef struct TCB {

    pthread_t     tid;
    long          period;
    long          time_left_to_invoke;
} TCB;

std::vector<TCB> TCB_array;
std::unordered_map<pthread_t, uint> index_table;
uint position_in_array;
pthread_mutex_t mutex_TCB;
pthread_cond_t cond_TCB;



using data_for_cond_signal = struct arg_create_posix_timer_for_cond_signal_handler;
struct arg_create_posix_timer_for_cond_signal_handler {
    int index;
    uint which_type;
};

using data_for_mgd_thr = struct arg_pthread_create_time_trigger_managed;
struct arg_pthread_create_time_trigger_managed {
    period_t new_period;
};


// --------------------------------- //

// --------------------------------- //

// function prototypes 
int initialize_variables(void);

void execution(void);

int create_posix_timer(void*);

void* thread_to_be_managed(void*);
int tt_thread_register(int64_t, pthread_t);
int tt_thread_wait_invocation(pthread_t);

void periodic_handler(sigval_t);

// test function for PTHREAD
// void* test_thread(void*);


#endif /* ___PTHREAD_MANAGEMENT_WITH_TIME_TRIGGER__83f68d7d_2525_4a77_ac5a_1c28d54241bc__H___ */

// #define _POSIX_C_SOURCE 200809L
