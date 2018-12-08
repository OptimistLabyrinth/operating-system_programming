#include "../../include/include_ptttm/initialize_ptttm_variables.hpp"



// static PTTTM variables
extern std::unique_ptr<pthread_mutex_t> API_Mutex;
extern std::unique_ptr<timer_args> TM_Arg;
extern std::unique_ptr<timer_t> Timer;

extern std::unique_ptr<thread_args> THR_Arg__acq_thread;
extern std::unique_ptr<thread_args> THR_Arg__proc_thread;

extern std::unique_ptr<TCB> TCB_storage;



void initialize_ptttm_variables(void)
{
    API_Mutex = std::make_unique<pthread_mutex_t>();
    pthread_mutex_init(&(*API_Mutex), nullptr);

    TM_Arg = std::make_unique<timer_args>();
    Timer = std::make_unique<timer_t>();
    
    THR_Arg__acq_thread = std::make_unique<thread_args>();
    THR_Arg__proc_thread = std::make_unique<thread_args>();

    TCB_storage = std::make_unique<TCB>();
}
