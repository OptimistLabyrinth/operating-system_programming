#include "../../include/include_ptttm/tt_thread_wait_invocation.hpp"



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



void tt_thread_wait_invocation()
{
    if (pthread_mutex_lock(&(*API_Mutex)) != 0) {
        perr("ERROR : mutex_lock in tt_thread_wait_invocation");
    }
    if (pthread_cond_wait(&(*API_cond_data_acqusition), &(*API_Mutex)) != 0) {
        perr("ERROR : cond_wait in tt_thread_wait_invocation");
    }
    if (pthread_mutex_unlock(&(*API_Mutex)) != 0) {
        perr("ERROR : mutex_UNlock in tt_thread_wait_invocation");
    }
}
