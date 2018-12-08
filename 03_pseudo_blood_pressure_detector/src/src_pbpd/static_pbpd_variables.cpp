#include "../../include/include_pbpd/static_pbpd_variables.hpp"



std::unique_ptr<pthread_cond_t> API_cond_data_acqusition;
std::unique_ptr<pthread_cond_t> API_cond_bp_processing;

std::unique_ptr<pthread_t> acq_thread;
std::unique_ptr<pthread_t> proc_thread;

std::unique_ptr<std::queue<int>> bp_queue;
std::unique_ptr<pthread_mutex_t> Q_MUtex;
std::unique_ptr<pthread_cond_t> Q_Cond;



/*

// static PBPD variables
extern std::unique_ptr<pthread_cond_t> API_cond_data_acqusition;
extern std::unique_ptr<pthread_cond_t> API_cond_bp_processing;

extern std::unique_ptr<pthread_t> acq_thread;
extern std::unique_ptr<pthread_t> proc_thread;

extern std::unique_ptr<std::queue<int>> bp_queue;
extern std::unique_ptr<pthread_mutex_t> Q_MUtex;
extern std::unique_ptr<pthread_cond_t> Q_Cond;

*/
