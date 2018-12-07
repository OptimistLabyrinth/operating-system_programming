#include "../../include/include_ptttm/create_posix_timer.hpp"



// static PTTTM variables
extern std::shared_ptr<pthread_mutex_t> API_Mutex;
extern std::shared_ptr<timer_args> TM_Arg;
extern std::shared_ptr<timer_t> Timer;

extern std::shared_ptr<thread_args> THR_Arg__acq_thread;
extern std::shared_ptr<thread_args> THR_Arg__proc_thread;

extern std::shared_ptr<TCB> TCB_storage;

// static PBPD variables
extern std::shared_ptr<pthread_cond_t> API_cond_data_acqusition;
extern std::shared_ptr<pthread_cond_t> API_cond_bp_processing;

extern std::shared_ptr<pthread_t> acq_thread;
extern std::shared_ptr<pthread_t> proc_thread;

extern std::shared_ptr<std::queue<int>> bp_queue;
extern std::shared_ptr<pthread_mutex_t> Q_MUtex;
extern std::shared_ptr<pthread_cond_t> Q_Cond;



size_t get_timer_frequency(void)
{
    size_t freq;
    auto GET_METHOD = TIMER_FREQUENCY_FROM_INTERNAL;

    switch (GET_METHOD)
    {
        case TIMER_FREQUENCY_FROM_INTERNAL: 
            freq = THOUSAND;
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
    ev.sigev_notify_function = periodic_alarm_clock;
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
