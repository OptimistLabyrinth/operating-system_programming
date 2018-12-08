#include "../../include/include_pbpd/initialize_pbpd_variables.hpp"



// static PBPD variables
extern std::unique_ptr<pthread_cond_t> API_cond_data_acqusition;
extern std::unique_ptr<pthread_cond_t> API_cond_bp_processing;

extern std::unique_ptr<pthread_t> acq_thread;
extern std::unique_ptr<pthread_t> proc_thread;

extern std::unique_ptr<std::queue<int>> bp_queue;
extern std::unique_ptr<pthread_mutex_t> Q_MUtex;
extern std::unique_ptr<pthread_cond_t> Q_Cond;



void initialize_pbpd_variables(void)
{
    API_cond_data_acqusition = std::make_unique<pthread_cond_t>();
    pthread_cond_init(&(*API_cond_data_acqusition), nullptr);
    API_cond_bp_processing = std::make_unique<pthread_cond_t>();
    pthread_cond_init(&(*API_cond_bp_processing), nullptr);
    
    acq_thread = std::make_unique<pthread_t>();
    proc_thread = std::make_unique<pthread_t>();

    bp_queue = std::make_unique<std::queue<int>>();
    Q_MUtex = std::make_unique<pthread_mutex_t>();
    pthread_mutex_init(&(*Q_MUtex), nullptr);
    Q_Cond = std::make_unique<pthread_cond_t>();
    pthread_cond_init(&(*Q_Cond), nullptr);
}
