#include "../include/pthread_management_with_time_trigger.h"

#define COUNT 3

int position_in_array;
pthread_t threads[COUNT];
data_for_mgd_thr d_thread[COUNT];
timer_t TM_thread[COUNT];

data_for_cond_signal d_arg[COUNT];

int rv;

// sigset_t sset;

// int i_array[COUNT];
// data params[COUNT];
// sig_hdl_arg thread_arg;

int G;
pthread_t PT[4];





int main()
{
    print("main begins...");

    std::setlocale(LC_ALL, "ko_KR.UTF-8");
    initialize_variables();
    execution();

    print("PAUSE LOOP");
    while(1) {
        pause();
    }
    
    return 0;
}

int initialize_variables(void)
{
    position_in_array = 0;
    pthread_mutex_init(&API_Mutex, nullptr);

    COND_array.resize(COUNT);
    for (int i=0; i < COUNT; ++i) {
        pthread_cond_init(&COND_array[i], nullptr);
    }
    
    TCB_array.resize(COUNT, TCB{0,0,0});

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

            it.it_value.tv_nsec = static_cast<long>(10) * MILLISECOND;
            it.it_interval.tv_nsec = static_cast<long>(10) * MILLISECOND;
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
    print(TCB_array[position_in_array].period);
    ++position_in_array;
    pthread_mutex_unlock(&API_Mutex);

    return 1;
}

int tt_thread_wait_invocation(pthread_t tid)
{

    int idx = -1;
    for (int i=0; i < COUNT; ++i) {
        if (TCB_array[i].tid == tid) {
            idx = i;
            break;
        }
    }

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







// void create_posix_timer(void)
// {
//     timer_t timerid;
//     struct sigevent sigev;
//     struct itimerspec itval, oitval;
//     // struct sigaction newact;
    
//     // sigemptyset(&newact.sa_mask);
//     // newact.sa_flags = SA_SIGINFO;
//     // newact.sa_sigaction = periodic_handler;
//     // sigaction(SIGRTMIN, &newact, NULL);

//     sigev.sigev_notify = SIGEV_THREAD;
//     sigev.sigev_notify_function = periodic_handler;
//     sigev.sigev_notify_attributes = NULL;
//     timer_create(CLOCK_REALTIME, &sigev, &timerid);
    
//     itval.it_value.tv_sec = 0;
//     itval.it_value.tv_nsec = static_cast<long> (MILLISECOND);
//     itval.it_interval.tv_sec = 0;
//     itval.it_interval.tv_nsec = static_cast<long> (MILLISECOND);
//     timer_settime(timerid, 0, &itval, &oitval);
// }







// *************************************************************************************** //
// void test_signal_handling(void)
// {
//     // sigemptyset(&sset);
//     // sigaddset(&sset, SIGRTMIN_def);
//     // sigaddset(&sset, SIGRTMIN_PLUS_1_def);
//     // sigaddset(&sset, SIGRTMIN_PLUS_2_def);
//     // pthread_sigmask(SIG_BLOCK, &sset, NULL);
    
//     pthread_create(&thread_arg.tid, NULL, pth_sig_hdl, reinterpret_cast<void*>(&thread_arg));

//     for (int i=0; i < COUNT; ++i) {
//         params[i].index = i;
//         i_array[i] = static_cast<int>(DIV/(i+1));
//         ptimer_start(reinterpret_cast<void*>(&params[i]));
//     }

//     while(1) 
//     {
//         print("OK ");
//         pause();
//     }

//     return;
// }

// void ptimer_start(void* arg)
// {
//     event ev;
//     t_spec it;
//     auto index = (reinterpret_cast<data*>(arg))->index;

//     ev.sigev_value.sival_ptr = arg;
//     ev.sigev_notify = SIGEV_THREAD;
//     ev.sigev_notify_function = tm_thread;
//     ev.sigev_notify_attributes = NULL;
//     timer_create(CLOCK_REALTIME, &ev, &TM[index]);

//     it.it_value.tv_sec = 1;
//     it.it_value.tv_nsec = 0;
//     it.it_interval.tv_sec = 1 * (index + 1);
//     it.it_interval.tv_nsec = 0;
//     timer_settime(TM[index], 0, &it, NULL);
// }

// void tm_thread(sigval_t arg)
// {
//     auto index = (reinterpret_cast<data*>(arg.sival_ptr))->index;
//     auto n_overrun = timer_getoverrun(TM[index]);
//     if (n_overrun >= 1) {
//         std::cerr << "Signal Overrun exists... program exit :(";
//         exit(EXIT_FAILURE);
//     }

//     print("tm_thread called..." + std::to_string(index+1) 
//             + "\ti_array[" + std::to_string(index) + "] = " + std::to_string(i_array[index]) 
//             + " ");

//     if ((--i_array[index]) <= 0)
//         timer_delete(TM[index]);

//     pthread_exit(NULL);
// }

// void* pth_sig_hdl(void* arg)
// {
//     while(1) 
//     {
//         sigwait(&sset, &reinterpret_cast<sig_hdl_arg*>(arg)->signal_number);

//         switch (reinterpret_cast<sig_hdl_arg*>(arg)->signal_number)
//         {
//             case SIGRTMIN_def:
//                 print("\t\tSIGRTMIN caught!");
//                 break;

//             case SIGRTMIN_PLUS_1_def:
//                 print("\t\tSIGRTMIN+1 caught!!");
//                 break;

//             case SIGRTMIN_PLUS_2_def:
//                 print("\t\tSIGRTMIN+2 caught!!!");
//                 break;

//             default:
//                 print("\t\tsomething wrong happend");
//         }
//     }
// }
// *************************************************************************************** //
