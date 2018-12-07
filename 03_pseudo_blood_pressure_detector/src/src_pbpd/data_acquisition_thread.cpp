#include "../../include/include_pbpd/data_acquisition_thread.hpp"



// static PTTTM variables
extern std::shared_ptr<pthread_mutex_t> API_Mutex;
extern std::shared_ptr<timer_args> TM_Arg;
extern std::shared_ptr<timer_t> Timer;

extern std::shared_ptr<thread_args> THR_Arg__acq_thread;
extern std::shared_ptr<thread_args> THR_Arg__proc_thread;

extern std::shared_ptr<TCB> TCB_storage;

// static PBPD variables
extern std::shared_ptr<pthread_cond_t> API_cond_data_acqusition;
extern std::shared_ptr<pthread_cond_t> API_cond_bp_processing;

extern std::shared_ptr<pthread_t> acq_thread;
extern std::shared_ptr<pthread_t> proc_thread;

extern std::shared_ptr<std::queue<int>> bp_queue;
extern std::shared_ptr<pthread_mutex_t> Q_MUtex;
extern std::shared_ptr<pthread_cond_t> Q_Cond;



void enqueue_acquired_data(uint* ptr_turn)
{
    if (*ptr_turn % 2 == 0) {
        enqueue_bp_queue(pseudo_distolic_blood_pressure());
    }
    else {
        enqueue_bp_queue(pseudo_systolic_blood_pressure());
    }
}

void* data_acquisition_thread(void* arg)
{
    auto period_value = (reinterpret_cast<thread_args*>(arg))->period;
    tt_thread_register(period_value);

    uint turn = 0;
    while (1) 
    {
        ++turn;
        tt_thread_wait_invocation();

        // posix timer overrun detection
        auto overrun_n_prev = timer_getoverrun(*Timer);
        enqueue_acquired_data(&turn);
        auto overrun_n_after = timer_getoverrun(*Timer);
        if (overrun_n_prev < overrun_n_after) {
            print("overrun detected!");
        }

        if (turn == 10) {
            pthread_cond_signal(&(*API_cond_bp_processing));
            turn = 0;
        }
        pthread_mutex_unlock(&(*API_Mutex));
    }
    
    return nullptr;
}
