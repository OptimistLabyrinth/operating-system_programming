#include "../include/periodic_handler.hpp"



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



void periodic_handler(sigval_t arg)
{
    pthread_mutex_lock(&(*API_Mutex));

    for (uint i=0; i < MAX_THREAD_NUM; ++i)
    {
        TCB_array->at(i).time_left_to_invoke -= 10;
        if ((TCB_array->at(i).time_left_to_invoke -= 10) <= 0) {
            TCB_array->at(i).time_left_to_invoke = TCB_array->at(i).period;
            pthread_cond_signal(&(API_Cond_Array->at(i)));
        }
    }

    pthread_mutex_unlock(&(*API_Mutex));
}
