#include "../include/thread_to_be_managed.hpp"



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



void* thread_to_be_managed(void* arg)
{
    auto period_v = reinterpret_cast<thread_args*>(arg)->period;
    auto tid = pthread_self();

    tt_thread_register(period_v, tid);

    while (1)
    {
        tt_thread_wait_invocation(tid);

        time_t curtime;
        time(&curtime);
        std::string S = " ";
        S += std::to_string(IDX_Table->at(tid) + 1) + "-th thread runniing... \t";
        S += "|| \t" + std::string(asctime(localtime(&curtime)));
        print(S, "");
    }
}
