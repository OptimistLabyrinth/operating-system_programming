#include "../include/pthread_management_with_time_trigger.hpp"

#define COUNT 3

// Global Variables - POSIX Mutex & Condition Variables
pthread_mutex_t API_Mutex;
std::vector<pthread_cond_t> COND_array;

std::vector<TCB> TCB_array;
std::unordered_map<pthread_t, int> index_table;
int position_in_array;
pthread_mutex_t mutex_TCB;
pthread_cond_t cond_TCB;

pthread_t threads[COUNT];
data_for_mgd_thr d_thread[COUNT];

timer_t TM_thread[COUNT];
data_for_cond_signal d_arg[COUNT];

int rv;





// int main()
// {
//     print("main begins...");

//     std::setlocale(LC_ALL, "ko_KR.UTF-8");
//     initialize_variables();
//     execution();

//     print("PAUSE LOOP");
//     while(1) {
//         pause();
//     }
    
//     return 0;
// }

int initialize_variables(void)
{
    position_in_array = 0;
    pthread_mutex_init(&API_Mutex, nullptr);

    COND_array.resize(COUNT);
    for (int i=0; i < COUNT; ++i) {
        pthread_cond_init(&COND_array[i], nullptr);
    }
    
    TCB_array.resize(COUNT, TCB{0,0,0});
    index_table.reserve(COUNT);

    return 1;
}

void execution(void)
{
    for (int i=1; i <= COUNT; ++i)
    {
        print(std::to_string(i) + "-th for_LOOP");
        d_thread[i].new_period = static_cast<period_t>(i * 1000);
        pthread_create(&threads[i], NULL, thread_to_be_managed, &d_thread[i]);

        d_arg[i].index = i;
        d_arg[i].which_type = TIMER_FOR_COND_SIGNAL_HANDLER;
        create_posix_timer(TIMER_FOR_COND_SIGNAL_HANDLER, reinterpret_cast<void*>(&d_arg[i]));
    }
}

int create_posix_timer(uint type, void* arg)
{
    event ev;
    t_spec it;

    ev.sigev_notify = SIGEV_THREAD;
    ev.sigev_notify_function = [](sigval_t) -> void {};
    ev.sigev_notify_attributes = NULL;
    ev.sigev_value.sival_ptr = arg;
    // timer_create(...);

    it.it_value.tv_sec = 0;
    it.it_value.tv_nsec = 0;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_nsec = 0;
    // timer_settime(...);

    switch (type)
    {
        case TIMER_FOR_COND_SIGNAL_HANDLER:
        {
            auto x = reinterpret_cast<data_for_cond_signal*>(arg);
            ev.sigev_notify_function = periodic_handler;
            timer_create(CLOCK_REALTIME, &ev, &TM_thread[x->index]);

            it.it_value.tv_nsec = 10L * MILLION;
            it.it_interval.tv_nsec = 10L * MILLION;
            timer_settime(&TM_thread[x->index], 0, &it, NULL);
            break;
        }
        default:
            std::cerr << "ERROR in create_posix_timer_for_cond_signal_handler";
            rv = -1;
    }

    return rv;
}

void* thread_to_be_managed(void* arg)
{
    
    auto x = reinterpret_cast<data_for_mgd_thr*>(arg)->new_period;
    auto y = pthread_self();

    tt_thread_register(x, y);
    int pos = -1;
    while ((pos =tt_thread_wait_invocation(y)) != -1) {
        time_t curtime;
        time(&curtime);
        std::string S = "";
        S += std::to_string(pos) + "-th thread runniing... ";
        S += "|| " + std::string(asctime(localtime(&curtime)));
        print(S, "");
    }

    return nullptr;
}

int tt_thread_register(period_t period, pthread_t tid)
{
    pthread_mutex_lock(&API_Mutex);
    TCB_array[position_in_array].tid = tid;
    TCB_array[position_in_array].period = period;
    TCB_array[position_in_array].time_left_to_invoke = period;
    index_table[tid] = position_in_array;
    print(TCB_array[position_in_array].period);
    ++position_in_array;
    pthread_mutex_unlock(&API_Mutex);

    return 1;
}

int tt_thread_wait_invocation(pthread_t tid)
{

    int idx = index_table[tid];

    pthread_mutex_lock(&API_Mutex);
    pthread_cond_wait(&COND_array[idx], &API_Mutex);
    pthread_mutex_unlock(&API_Mutex);

    return idx+1;
}

void periodic_handler(sigval_t arg)
{
    pthread_mutex_lock(&API_Mutex);
    for (int i=0; i < COUNT; ++i) 
    {
        TCB_array[i].time_left_to_invoke -= 10;
        if ((TCB_array[i].time_left_to_invoke -= 10) < 0) {
            TCB_array[i].time_left_to_invoke = TCB_array[i].period;
            pthread_cond_signal(&COND_array[i]);
        }
    }
    pthread_mutex_unlock(&API_Mutex);
}
