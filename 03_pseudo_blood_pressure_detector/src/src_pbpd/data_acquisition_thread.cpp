#include "../../include/include_pbpd/data_acquisition_thread.hpp"



// static PTTTM variables
extern std::unique_ptr<pthread_mutex_t> API_Mutex;
extern std::unique_ptr<timer_args> TM_Arg;
extern std::unique_ptr<timer_t> Timer;

extern std::unique_ptr<thread_args> THR_Arg__acq_thread;
extern std::unique_ptr<thread_args> THR_Arg__proc_thread;

extern std::unique_ptr<TCB> TCB_storage;

// static PBPD variables
extern std::unique_ptr<pthread_cond_t> API_cond_data_acqusition;
extern std::unique_ptr<pthread_cond_t> API_cond_bp_processing;

extern std::unique_ptr<pthread_t> acq_thread;
extern std::unique_ptr<pthread_t> proc_thread;

extern std::unique_ptr<std::queue<int>> bp_queue;
extern std::unique_ptr<pthread_mutex_t> Q_MUtex;
extern std::unique_ptr<pthread_cond_t> Q_Cond;



inline void enqueue_acquired_data(uint* ptr_turn)
{
    try {
        if (*ptr_turn % 2 == 0) {
            enqueue_bp_queue(pseudo_distolic_blood_pressure());
        }
        else {
            enqueue_bp_queue(pseudo_systolic_blood_pressure());
        }
    }
    catch (std::exception e) {
        throw e;
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
        auto overrun_n = timer_getoverrun(*Timer);
        if (overrun_n > 0) {
            perr("overrun detected!");
        }
        else if (overrun_n == -1) {
            perr("ERROR : timer_getoverrun in data_acquisition_thread");
        }
        
        try {
            enqueue_acquired_data(&turn);
        }
        catch (std::exception e) {
            perr("ERROR : from enqueue_acquired_data() inside data_acquisition_thread");
            e.what();
        }

        if (turn == 10) {
            if (pthread_mutex_lock(&(*API_Mutex)) != 0) {
                perr("ERROR : mutex_lock in data_acquisition_thread");
            }
            if (pthread_cond_signal(&(*API_cond_bp_processing)) != 0) {
                perr("ERROR : cond_signal in data_acquisition_thread");
            }
            if (pthread_mutex_unlock(&(*API_Mutex)) != 0) {
                perr("ERROR : mutex_UNlock in data_acquisition_thread");
            }
            turn = 0;
        }
    }
    
    return nullptr;
}
