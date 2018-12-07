#include "../../include/include_ptttm/static_ptttm_variables.hpp"



// static PTTTM variables
std::shared_ptr<pthread_mutex_t> API_Mutex;
std::shared_ptr<timer_args> TM_Arg;
std::shared_ptr<timer_t> Timer;

std::shared_ptr<thread_args> THR_Arg__acq_thread;
std::shared_ptr<thread_args> THR_Arg__proc_thread;

std::shared_ptr<TCB> TCB_storage;



/*

// static PTTTM variables
extern std::shared_ptr<pthread_mutex_t> API_Mutex;
extern std::shared_ptr<timer_args> TM_Arg;
extern std::shared_ptr<timer_t> Timer;

extern std::shared_ptr<thread_args> THR_Arg__acq_thread;
extern std::shared_ptr<thread_args> THR_Arg__proc_thread;

extern std::shared_ptr<TCB> TCB_storage;

*/
