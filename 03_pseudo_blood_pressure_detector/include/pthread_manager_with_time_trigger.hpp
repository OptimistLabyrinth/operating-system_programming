#ifndef PTHREAD_MANAGER_WITH_TIME_TRIGGER__16e69b73_a566_4b40_b1de_56e99cd04902__HPP___
#define PTHREAD_MANAGER_WITH_TIME_TRIGGER__16e69b73_a566_4b40_b1de_56e99cd04902__HPP___

#include <vector>
#include <unordered_map>
#include <string>
#include <ctime>

#include <pthread.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/types.h>

#include "print_functions.hpp"
#include "error_codes_for_pth_mgr_with_time_trigger.hpp"

#define MILLION             1000000L





class Pthread_Manager_with_Time_Trigger
{
public:
    // type definitions
    using period_t = long;
    using event = struct sigevent;
    using t_spec = struct itimerspec;

    using TCB = struct TCB;
    typedef struct TCB {

        pthread_t     tid;
        long          period;
        long          time_left_to_invoke;
    } TCB;

    using data_for_cond_signal = 
        struct arg_create_posix_timer_for_cond_signal_handler;
    struct arg_create_posix_timer_for_cond_signal_handler {
        uint which_type;
    };

    using data_for_mgd_thr = 
        struct arg_pthread_create_time_trigger_managed;
    struct arg_pthread_create_time_trigger_managed {
        period_t new_period;
    };

    using ret_type_of_tt_w_invk = 
        struct ret_type_of_tt_thread_wait_invokation;
    struct ret_type_of_tt_thread_wait_invokation {
        int error_code;
        int index;
    };



    // Constructor
    Pthread_Manager_with_Time_Trigger();



    // class function prototypes 
    int initialize_variables(void);

    int execution(void);

    int create_posix_timer(void*);

    int tt_thread_register(int64_t, pthread_t);
    ret_type_of_tt_w_invk tt_thread_wait_invocation(pthread_t);



private:
    // class variables 
    pthread_mutex_t API_Mutex;
    std::vector<pthread_cond_t> COND_array;

    std::vector<TCB> TCB_array;
    std::unordered_map<pthread_t, int> index_table;
    int position_in_array;
    pthread_mutex_t mutex_TCB;
    pthread_cond_t cond_TCB;

    // pthread_t threads[MAX_THREAD_NUM];
    // data_for_mgd_thr d_thread[MAX_THREAD_NUM];

    timer_t TM_thread;
    data_for_cond_signal d_arg;

    int err_chk;

};



// global function prototypes
void* thread_to_be_managed(void*);

void periodic_handler(sigval_t);



#endif /* PTHREAD_MANAGER_WITH_TIME_TRIGGER__16e69b73_a566_4b40_b1de_56e99cd04902__HPP___ */