#include "../include/create_posix_timer.hpp"



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



size_t get_timer_frequency(void)
{
    size_t freq;
    auto GET_METHOD = TIMER_FREQUENCY_FROM_INTERNAL;

    switch (GET_METHOD)
    {
        case TIMER_FREQUENCY_FROM_INTERNAL: 
            freq = 100UL;
            break;
        case TIMER_FREQUENCY_FROM_FILE:
            // do something
            break;
        case TIMER_FREQUENCY_FROM_STDIN:
            // do something
            break;
        default:
            print("nothing happens");
            freq = 0;
    }

    return freq;
}

void set_timer_arguments(void)
{
    auto freq = get_timer_frequency();

    if (freq == 0) {
        throw "Frequency == 0";
        std::exit(EXIT_FAILURE);
    }
    else {
        TM_Arg->ptimer_period = THOUSAND / freq;
    }
}

void create_posix_timer(void)
{
    set_timer_arguments();

    event ev;
    t_spec it;

    ev.sigev_notify = SIGEV_THREAD;
    ev.sigev_notify_function = periodic_handler;
    ev.sigev_notify_attributes = nullptr;
    ev.sigev_value.sival_ptr = nullptr;

    if (timer_create(CLOCK_REALTIME, &ev, &(*Timer)) == -1) {
        print("timer_create() failed TT TT");
    }

    it.it_value.tv_sec = 0;
    it.it_value.tv_nsec = TM_Arg->ptimer_period * MILLION;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_nsec = TM_Arg->ptimer_period * MILLION;

    if (timer_settime(*Timer, 0, &it, nullptr) == -1) {
        print("timer_settime() failed TT TT");
    }

    // ev.sigev_notify_function = [](sigval_t) -> void {};
}
