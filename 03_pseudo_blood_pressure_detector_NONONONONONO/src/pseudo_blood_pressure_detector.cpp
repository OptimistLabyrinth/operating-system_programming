#include "../include/pseudo_blood_pressure_detector.hpp"

// extern pthread_mutex_t API_Mutex;
// extern std::vector<pthread_cond_t> COND_array;

// extern std::vector<TCB> TCB_array;
// extern std::unordered_map<pthread_t, int> index_table;
// extern int position_in_array;
// extern pthread_mutex_t mutex_TCB;
// extern pthread_cond_t cond_TCB;

// extern pthread_t threads[MAX_THREAD_NUM];
// extern data_for_mgd_thr d_thread[MAX_THREAD_NUM];

// extern timer_t TM_thread;
// extern data_for_cond_signal d_arg;

// int err_chk;



pthread_mutex_t g_mutex;
pthread_cond_t g_cond_data_acqusition;
pthread_cond_t g_cond_bp_processing;

timer_t tm;
event ev;
t_spec it;

pthread_t acq_thread;
pthread_t proc_thread;

std::queue<int> bp_queue;

auto m_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937_64 rand_gen(m_seed);
std::uniform_int_distribution<int> diastolic(60, 90);
std::uniform_int_distribution<int> systolic(110, 150);



void init_everything(void)
{
    pthread_mutex_init(&g_mutex, nullptr);
    pthread_cond_init(&g_cond_data_acqusition, nullptr);
    pthread_cond_init(&g_cond_bp_processing, nullptr);
}

void create_timer(void)
{
    ev.sigev_notify = SIGEV_THREAD;
    ev.sigev_notify_function = alarm_clock;
    ev.sigev_notify_attributes = nullptr;
    ev.sigev_value.sival_ptr = nullptr;

    it.it_value.tv_sec = 0;
    it.it_value.tv_nsec = 10L * MILLION;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_nsec = 10L * MILLION;

    timer_create(CLOCK_REALTIME, &ev, &tm);
    timer_settime(tm, 0, &it, nullptr);
}
void alarm_clock(sigval_t arg)
{
    pthread_mutex_lock(&g_mutex);
    pthread_cond_signal(&g_cond_data_acqusition);
    pthread_mutex_unlock(&g_mutex);
}

void run_threads(void)
{
    pthread_create(&acq_thread, nullptr, data_acquisition_thread, nullptr);
    pthread_create(&proc_thread, nullptr, bp_processing_thread, nullptr);
}

void* data_acquisition_thread(void* arg)
{
    uint turn = 0;
    while (turn++ < 10) 
    {
        pthread_mutex_lock(&g_mutex);
        pthread_cond_wait(&g_cond_data_acqusition, &g_mutex);
        enqueue_acquired_data(reinterpret_cast<void*>(&turn));

        if (turn == 10) {
            pthread_cond_signal(&g_cond_bp_processing);
            turn = 0;
        }
        pthread_mutex_unlock(&g_mutex);
    }
    
    return nullptr;
}
void enqueue_acquired_data(void* arg)
{
    auto turn_check = reinterpret_cast<uint*>(arg);
    if (*turn_check % 2 == 0) {
        bp_queue.push(diastolic(rand_gen));
    }
    else {
        bp_queue.push(systolic(rand_gen));
    }
}

void* bp_processing_thread(void* arg)
{
    bool turn = false;

    while (1)
    {
        pthread_mutex_lock(&g_mutex);
        pthread_cond_wait(&g_cond_bp_processing, &g_mutex);

        dequeue_data_to_process(reinterpret_cast<void*>(&turn));
        // display_10_data_and_dequeue_from(nullptr);

        if (turn == false) {
            turn = true;
        }
        else {
            turn = false;
            print();
        }
        pthread_mutex_unlock(&g_mutex);
    }

    return nullptr;
}
void dequeue_data_to_process(void* arg)
{
    auto is_diastolic_turn = reinterpret_cast<bool*>(arg);
    auto sum = 0U;

    if (*is_diastolic_turn) {
        for (int i=0; i < 10; ++i) {
            if (60 <= bp_queue.front() && bp_queue.front() <= 90) {
                sum += bp_queue.front();
            }
            bp_queue.pop();
        }
        print("diastolic bp = " + std::to_string(sum/5));
    }
    else {
        for (int i=0; i < 10; ++i) {
            if (110 <= bp_queue.front() && bp_queue.front() <= 150) {
                sum += bp_queue.front();
            }
            bp_queue.pop();
        }
        print("systolic bp = " + std::to_string(sum/5));
    }
}
void display_10_data_and_dequeue_from(void* arg)
{
    for (int i=0; i < 10; ++i) {
        print(bp_queue.front(), " ");
        bp_queue.pop();
    }
    print();
}
