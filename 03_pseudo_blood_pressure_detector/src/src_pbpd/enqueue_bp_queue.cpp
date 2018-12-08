#include "../../include/include_pbpd/enqueue_bp_queue.hpp"



extern std::unique_ptr<pthread_mutex_t> g_mutex;
extern std::unique_ptr<pthread_cond_t> g_cond_data_acqusition;
extern std::unique_ptr<pthread_cond_t> g_cond_bp_processing;

extern std::unique_ptr<pthread_t> acq_thread;
extern std::unique_ptr<pthread_t> proc_thread;

extern std::unique_ptr<std::queue<int>> bp_queue;
extern std::unique_ptr<pthread_mutex_t> Q_MUtex;
extern std::unique_ptr<pthread_cond_t> Q_Cond;



void enqueue_bp_queue(int bp_data)
{
    try {
        (*bp_queue).push(bp_data);
    }
    catch (std::exception e) {
        throw e;
    }
}
