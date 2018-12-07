#include "../include/tt_thread_register.hpp"



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



void tt_thread_register(size_t new_period, pthread_t tid)
{
    pthread_mutex_lock(&(*API_Mutex));
    
    pthread_mutex_lock(&(*TCB_position_Mutex));
    TCB_array->at(*TCB_position).period = new_period;
    TCB_array->at(*TCB_position).time_left_to_invoke = new_period;
    TCB_array->at(*TCB_position).tid = tid;

    (*IDX_Table)[tid] = *TCB_position;
    ++(*TCB_position);
    pthread_cond_signal(&(*TCB_position_Cond));
    pthread_mutex_unlock(&(*TCB_position_Mutex));
    
    pthread_mutex_unlock(&(*API_Mutex));
}
