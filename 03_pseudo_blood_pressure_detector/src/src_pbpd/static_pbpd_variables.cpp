#include "../../include/include_pbpd/static_pbpd_variables.hpp"



std::shared_ptr<pthread_cond_t> API_cond_data_acqusition;
std::shared_ptr<pthread_cond_t> API_cond_bp_processing;

std::shared_ptr<pthread_t> acq_thread;
std::shared_ptr<pthread_t> proc_thread;

std::shared_ptr<std::queue<int>> bp_queue;
std::shared_ptr<pthread_mutex_t> Q_MUtex;
std::shared_ptr<pthread_cond_t> Q_Cond;



/*

// static PBPD variables
extern std::shared_ptr<pthread_cond_t> API_cond_data_acqusition;
extern std::shared_ptr<pthread_cond_t> API_cond_bp_processing;

extern std::shared_ptr<pthread_t> acq_thread;
extern std::shared_ptr<pthread_t> proc_thread;

extern std::shared_ptr<std::queue<int>> bp_queue;
extern std::shared_ptr<pthread_mutex_t> Q_MUtex;
extern std::shared_ptr<pthread_cond_t> Q_Cond;

*/
