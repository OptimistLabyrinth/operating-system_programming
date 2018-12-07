#include "../include/initialize_variables.hpp"



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



void initialize_variables(void)
{
    API_Mutex = std::make_shared<pthread_mutex_t>();
    pthread_mutex_init(&(*API_Mutex), nullptr);
    API_Cond_Array = std::make_shared<std::vector<pthread_cond_t>>();
    API_Cond_Array->resize(MAX_THREAD_NUM);
    for (auto& cond_var : *API_Cond_Array) {
        pthread_cond_init(&cond_var, nullptr);
    }

    TM_Arg = std::make_shared<timer_args>();
    Timer = std::make_shared<timer_t>();

    THR_Args = std::make_shared<std::vector<thread_args>>();
    THR_Args->resize(MAX_THREAD_NUM);
    Threads = std::make_shared<std::vector<pthread_t>>();
    Threads->resize(MAX_THREAD_NUM);

    TCB_array = std::make_shared<std::vector<TCB>>();
    TCB_array->resize(MAX_THREAD_NUM);
    TCB_position_Mutex = std::make_shared<pthread_mutex_t>();
    pthread_mutex_init(&(*TCB_position_Mutex), nullptr);
    TCB_position_Cond = std::make_shared<pthread_cond_t>();
    pthread_cond_init(&(*TCB_position_Cond), nullptr);
    TCB_position = std::make_shared<size_t>();
    *TCB_position = 0;
    
    IDX_Table = std::make_shared<std::unordered_map<pthread_t, size_t>>();
    IDX_Table->reserve(MAX_THREAD_NUM);
}
