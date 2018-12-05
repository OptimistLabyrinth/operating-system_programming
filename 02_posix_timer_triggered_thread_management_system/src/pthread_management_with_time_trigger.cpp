#include "../include/pthread_management_with_time_trigger.hpp"

// Global Variables - POSIX Mutex & Condition Variables
pthread_mutex_t API_Mutex;
std::vector<pthread_cond_t> COND_array;

std::vector<TCB> TCB_array;
std::unordered_map<pthread_t, int> index_table;
int position_in_array;
pthread_mutex_t mutex_TCB;
pthread_cond_t cond_TCB;

pthread_t threads[MAX_THREAD_NUM];
data_for_mgd_thr d_thread[MAX_THREAD_NUM];

timer_t TM_thread;
data_for_cond_signal d_arg;

int err_chk;





int initialize_variables(void)
{
    position_in_array = 0;
    if ((err_chk = pthread_mutex_init(&API_Mutex, nullptr)) != 0) {
        std::cerr << "ERROR : initialize_variables( ) -> pthread_mutex_init( )" << std::endl;
        return ERROR_IN_PTHREAD_MUTEX_INIT;
    }

    COND_array.resize(MAX_THREAD_NUM);
    for (auto& glob_cond_var : COND_array) {
        if ((err_chk = pthread_cond_init(&glob_cond_var, nullptr)) != 0) {
            std::cerr << "ERROR : initialize_variables( ) -> pthread_cond_init( )" << std::endl;
            return ERROR_IN_PTHREAD_COND_INIT;
        }
    }
    
    TCB_array.resize(MAX_THREAD_NUM, TCB{0,0,0});
    index_table.reserve(MAX_THREAD_NUM);

    return ON_INTIIALIZE_VARIABLES_SUCCESS;
}

int execution(void)
{
    d_arg.which_type = TIMER_FOR_COND_SIGNAL_HANDLER;
    if ((err_chk = create_posix_timer(reinterpret_cast<void*>(&d_arg))) 
            != ON_CREATE_POSIX_TIMER_SUCCESS) {
        std::cerr << "ERROR : execution( ) -> create_posix_timer( )" << std::endl;
        return ERROR_IN_CREATE_POSIX_TIMER;
    }

    for (int i=1; i <= MAX_THREAD_NUM; ++i)
    {
        print(std::to_string(i) + "-th for_LOOP");
        d_thread[i].new_period = static_cast<period_t>(i * 1000);
        if ((err_chk = pthread_create(&threads[i], NULL, thread_to_be_managed, &d_thread[i]))
                != 0) {
            std::cerr << "ERROR : execution( ) -> pthread_create( )" << std::endl;
            return ERROR_IN_PTHREAD_CREATE;
        }
    }

    return ON_EXECUTION_SUCCESS;
}

int create_posix_timer(void* arg)
{
    event ev;
    t_spec it;

    ev.sigev_notify = SIGEV_THREAD;
    ev.sigev_notify_function = [](sigval_t) -> void {};
    ev.sigev_notify_attributes = nullptr;
    ev.sigev_value.sival_ptr = arg;
    // timer_create(...);

    it.it_value.tv_sec = 0;
    it.it_value.tv_nsec = 0;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_nsec = 0;
    // timer_settime(...);

    auto arg_used_to_create_timer_and_settime = reinterpret_cast<data_for_cond_signal*>(arg);

    switch (arg_used_to_create_timer_and_settime->which_type)
    {
        case TIMER_FOR_COND_SIGNAL_HANDLER:
        {
            ev.sigev_notify_function = periodic_handler;
            if ((err_chk = timer_create(CLOCK_REALTIME, &ev, &TM_thread)) == -1) {
                std::cerr << "ERROR : create_posix_timer( ) -> timer_create( )" << std::endl;
                return ERROR_IN_TIMER_CREATE;
            }

            it.it_value.tv_nsec = 10L * MILLISECOND;
            it.it_interval.tv_nsec = 10L * MILLISECOND;
            if ((err_chk = timer_settime(TM_thread, 0, &it, NULL)) == -1) {
                std::cerr << "ERROR : create_posix_timer( ) -> timer_settime( )" << std::endl;
                return ERROR_IN_TIMER_SETTIME;
            }
            break;
        }
        default:
            std::cerr << "ERROR : SWITCH-CASE" << std::endl;
            return ERROR_IN_SWITCH_CASE;
    }

    return ON_CREATE_POSIX_TIMER_SUCCESS;
}

void* thread_to_be_managed(void* arg)
{
    auto new_period_tmp = reinterpret_cast<data_for_mgd_thr*>(arg)->new_period;
    auto tid_self = pthread_self();

    if ((err_chk = tt_thread_register(new_period_tmp, tid_self)) 
            != ON_TT_THREAD_REGISTER_SUCCESS) {
        std::cerr << "ERROR : thread_to_be_managed( ) -> tt_thread_register( )" << std::endl;
        pthread_exit(nullptr);
    }
    ret_type_of_tt_w_invk thread_invoke_data;
    while ((thread_invoke_data = tt_thread_wait_invocation(tid_self)).error_code 
                == ON_TT_THREAD_WAIT_INVOCATION_SUCCESS) {
        time_t curtime;
        time(&curtime);
        std::string S = " ";
        S += std::to_string(thread_invoke_data.index + 1) + "-th thread runniing... \t";
        S += "|| \t" + std::string(asctime(localtime(&curtime)));
        print(S, "");
    }
    if (thread_invoke_data.error_code != ON_TT_THREAD_WAIT_INVOCATION_SUCCESS) {
        std::cerr << "ERROR : thread_to_be_managed( ) -> tt_thread_wait_invocation( )" << std::endl;
        pthread_exit(nullptr);
    }

    return nullptr;
}

int tt_thread_register(period_t period, pthread_t tid)
{
    if ((err_chk = pthread_mutex_lock(&API_Mutex)) != 0) {
        std::cerr << "ERROR : tt_thread_register( ) -> pthread_mutex_lock( )" << std::endl;
        return ERROR_IN_PTHREAD_MUTEX_LOCK_REGISTER;
    }
    TCB_array[position_in_array].tid = tid;
    TCB_array[position_in_array].period = period;
    TCB_array[position_in_array].time_left_to_invoke = period;
    index_table[tid] = position_in_array;
    print(TCB_array[position_in_array].period);
    ++position_in_array;
    if ((err_chk = pthread_mutex_unlock(&API_Mutex)) != 0) {
        std::cerr << "ERROR : tt_thread_register( ) -> pthread_mutex_unlock( )" << std::endl;
        return ERROR_IN_PTHREAD_MUTEX_UNLOCK_REGISTER;
    }

    return ON_TT_THREAD_REGISTER_SUCCESS;
}

ret_type_of_tt_w_invk tt_thread_wait_invocation(pthread_t tid)
{
    ret_type_of_tt_w_invk return_struct;

    try {
        return_struct.index = index_table.at(tid);
    } catch (const std::out_of_range& e) {
        e.what();
        return_struct.error_code = ERROR_IN_SEARCHING_INDEX_TALBE;
        return_struct.index = -1;
        return return_struct;
    }

    if ((err_chk = pthread_mutex_lock(&API_Mutex)) != 0) {
        std::cerr << "ERROR : tt_thread_wait_invocation( ) -> pthread_mutex_lock( )" << std::endl;
        return_struct.error_code = ERROR_IN_PTHREAD_MUTEX_LOCK_WAIT_INVOKE;
    }
    if ((err_chk = pthread_cond_wait(&COND_array[return_struct.index], &API_Mutex)) != 0) {
        std::cerr << "ERROR : tt_thread_wait_invocation( ) -> pthread_cond_wait( )" << std::endl;
        return_struct.error_code = ERROR_IN_PTHREAD_COND_WAIT_WAIT_INVOKE;
    }
    if ((err_chk = pthread_mutex_unlock(&API_Mutex)) != 0) {
        std::cerr << "ERROR : tt_thread_wait_invocation( ) -> pthread_mutex_unlock( )" << std::endl;
        return_struct.error_code = ERROR_IN_PTHREAD_MUTEX_UNLOCK_WAIT_INVOKE;
    }

    return_struct.error_code = ON_TT_THREAD_WAIT_INVOCATION_SUCCESS;
    return return_struct;
}

void periodic_handler(sigval_t arg)
{
    if ((err_chk = pthread_mutex_lock(&API_Mutex)) != 0) {
        std::cerr << "ERROR : periodic_handler( ) -> pthread_mutex_lock( )" << std::endl;
        return;
    }
    for (int i=0; i < MAX_THREAD_NUM; ++i) 
    {
        TCB_array[i].time_left_to_invoke -= 10;
        if ((TCB_array[i].time_left_to_invoke -= 10) <= 0) {
            TCB_array[i].time_left_to_invoke = TCB_array[i].period;
            if ((err_chk = pthread_cond_signal(&COND_array[i])) != 0) {
                std::cerr << "ERROR : periodic_handler( ) -> pthread_cond_signal( )" << std::endl;
            }
        }
    }
    if ((err_chk = pthread_mutex_unlock(&API_Mutex)) != 0) {
        std::cerr << "ERROR : periodic_handler( ) -> pthread_mutex_unlock( )" << std::endl;        
    }
}
