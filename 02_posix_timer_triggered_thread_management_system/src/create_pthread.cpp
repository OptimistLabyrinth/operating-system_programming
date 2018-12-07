#include "../include/create_pthread.hpp"



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



void add_pthread_arguments(size_t i)
{
    THR_Args->at(i).period = static_cast<size_t>(i+1) * THOUSAND;
}

void create_new_thread(void)
{
    while (*TCB_position < MAX_THREAD_NUM)
    {
        print(std::to_string(*TCB_position + 1) + "-th for LOOP");
        add_pthread_arguments(*TCB_position);

        if (pthread_create(
            &(Threads->at(*TCB_position)), 
            nullptr, 
            thread_to_be_managed, 
            &(THR_Args->at(*TCB_position))) 
                != 0) {
            print("pthread_create() failed TT TT");
        }
        
        pthread_mutex_lock(&(*TCB_position_Mutex));
        pthread_cond_wait(&(*TCB_position_Cond), &(*TCB_position_Mutex));
        pthread_mutex_unlock(&(*TCB_position_Mutex));
    }
}
