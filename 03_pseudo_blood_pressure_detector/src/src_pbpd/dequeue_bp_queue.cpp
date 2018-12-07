#include "../../include/include_pbpd/dequeue_bp_queue.hpp"



extern std::shared_ptr<pthread_mutex_t> g_mutex;
extern std::shared_ptr<pthread_cond_t> g_cond_data_acqusition;
extern std::shared_ptr<pthread_cond_t> g_cond_bp_processing;

extern std::shared_ptr<pthread_t> acq_thread;
extern std::shared_ptr<pthread_t> proc_thread;

extern std::shared_ptr<std::queue<int>> bp_queue;
extern std::shared_ptr<pthread_mutex_t> Q_MUtex;
extern std::shared_ptr<pthread_cond_t> Q_Cond;



int dequeue_bp_queue(void)
{
    auto bp_data = (*bp_queue).front();
    (*bp_queue).pop();
    return bp_data;
}
