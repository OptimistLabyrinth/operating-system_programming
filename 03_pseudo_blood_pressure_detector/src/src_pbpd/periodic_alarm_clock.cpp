#include "../../include/include_pbpd/periodic_alarm_clock.hpp"



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



void periodic_alarm_clock(sigval_t)
{
    pthread_mutex_lock(&(*API_Mutex));
    TCB_storage->time_left_to_invoke -= 10;
    if ((TCB_storage->time_left_to_invoke -= 10) <= 0) {
        TCB_storage->time_left_to_invoke = TCB_storage->period;
        pthread_cond_signal(&(*API_cond_data_acqusition));
    }
    pthread_mutex_unlock(&(*API_Mutex));
}
