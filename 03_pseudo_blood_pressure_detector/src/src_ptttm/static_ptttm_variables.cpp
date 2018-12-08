#include "../../include/include_ptttm/static_ptttm_variables.hpp"



// static PTTTM variables
std::unique_ptr<pthread_mutex_t> API_Mutex;
std::unique_ptr<timer_args> TM_Arg;
std::unique_ptr<timer_t> Timer;

std::unique_ptr<thread_args> THR_Arg__acq_thread;
std::unique_ptr<thread_args> THR_Arg__proc_thread;

std::unique_ptr<TCB> TCB_storage;

/*

// static PTTTM variables
extern std::unique_ptr<pthread_mutex_t> API_Mutex;
extern std::unique_ptr<timer_args> TM_Arg;
extern std::unique_ptr<timer_t> Timer;

extern std::unique_ptr<thread_args> THR_Arg__acq_thread;
extern std::unique_ptr<thread_args> THR_Arg__proc_thread;

extern std::unique_ptr<TCB> TCB_storage;

*/
