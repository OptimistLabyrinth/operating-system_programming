#include "../include/pthread_management_with_time_trigger.hpp"

extern pthread_mutex_t API_Mutex;
extern std::vector<pthread_cond_t> COND_array;
extern pthread_t threads[MAX_THREAD_NUM];

void atexit_handler(void)
{
    auto err_code = 0U; 

    pthread_mutex_destroy(&API_Mutex);
    for (auto& glob_cond_var : COND_array) {
        if ((err_code = pthread_cond_destroy(&glob_cond_var)) != 0) {
            std::cerr << "ERROR : atexit_handler( ) -> pthread_cond_t not initialized yet" << std::endl;
        }
    }

    for (auto& each_pthread : threads) {
        if ((err_code = pthread_cancel(each_pthread)) != 0) {
            std::cerr << "ERROR : atexit_handler( ) -> pthread_t not created yet" << std::endl;
        }
    }
}

int main()
{
    uint err_code = 0U;

    print("main begins...");

    std::setlocale(LC_ALL, "ko_KR.UTF-8");
    if ((err_code = initialize_variables()) != ON_INTIIALIZE_VARIABLES_SUCCESS) {
        std::exit(EXIT_FAILURE);
    }
    
    std::atexit(atexit_handler);
    
    if ((err_code = execution()) != ON_EXECUTION_SUCCESS) {
        std::exit(EXIT_FAILURE);
    }

    print("PAUSE LOOP");
    while(1) {
        pause();
    }
    
    return 0;
}
