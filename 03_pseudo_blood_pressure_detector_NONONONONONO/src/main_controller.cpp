#include "../include/print_functions.hpp"
#include "../include/pthread_management_with_time_trigger.hpp"
#include "../include/pseudo_blood_pressure_detector.hpp"

#define INIT_MSG "init everything"
#define CREATE_TIMER_MSG "timer is created (100 Hz)"
#define RUN_MSG "running thread begins..."
#define PAUSE_MSG "main thread PAUSE here\n"

extern pthread_t acq_thread;
extern pthread_t proc_thread;

int main()
{
        print(INIT_MSG);
        init_everything();
        
        print(CREATE_TIMER_MSG);
        create_timer();

        print(RUN_MSG);
        run_threads();

        print(PAUSE_MSG);    
        pthread_join(acq_thread, nullptr);
        pthread_join(proc_thread, nullptr);

        return 0;
}
