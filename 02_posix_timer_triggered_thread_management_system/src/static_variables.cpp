#include "../include/static_variables.hpp"

std::shared_ptr<pthread_mutex_t> API_Mutex;
std::shared_ptr<std::vector<pthread_cond_t>> API_Cond_Array;

std::shared_ptr<timer_args> TM_Arg;
std::shared_ptr<timer_t> Timer;

std::shared_ptr<std::vector<thread_args>> THR_Args;
std::shared_ptr<std::vector<pthread_t>> Threads;

std::shared_ptr<std::vector<TCB>> TCB_array;
std::shared_ptr<pthread_mutex_t> TCB_position_Mutex;
std::shared_ptr<pthread_cond_t> TCB_position_Cond;
std::shared_ptr<size_t> TCB_position;

std::shared_ptr<std::unordered_map<pthread_t, size_t>> IDX_Table;



/*

extern std::shared_ptr<pthread_mutex_t> API_Mutex;
extern std::shared_ptr<std::vector<pthread_cond_t>> API_Cond_Array;
 
extern std::shared_ptr<timer_args> TM_Arg;
extern std::shared_ptr<timer_t> Timer;

extern std::shared_ptr<std::vector<thread_args>> THR_Args;
extern std::shared_ptr<std::vector<pthread_t>> Threads;

extern std::shared_ptr<std::vector<TCB>> TCB_array;
extern std::shared_ptr<pthread_mutex_t> TCB_position_Mutex;
extern std::shared_ptr<pthread_cond_t> TCB_position_Cond;
extern std::shared_ptr<size_t> TCB_position;
extern std::shared_ptr<std::unordered_map<pthread_t, size_t>> IDX_Table;

*/