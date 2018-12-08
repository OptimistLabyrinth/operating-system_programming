#include "../../include/include_pbpd/periodic_alarm_clock.hpp"



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



void periodic_alarm_clock(sigval_t)
{
    if (pthread_mutex_lock(&(*API_Mutex)) != 0) {
        perr("ERROR : mutex_lock in periodic_alarm_clock");
    }
    TCB_storage->time_left_to_invoke -= 10;
    if ((TCB_storage->time_left_to_invoke -= 10) <= 0) {
        TCB_storage->time_left_to_invoke = TCB_storage->period;
        if (pthread_cond_signal(&(*API_cond_data_acqusition)) != 0) {
            perr("ERROR : cond_signal in periodic_alarm_clock");
        }
    }
    if (pthread_mutex_unlock(&(*API_Mutex)) != 0) {
        perr("ERROR : mutex_UNlock in periodic_alarm_clock");
    }
}
