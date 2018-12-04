
#include "../include/pseudo_blood_pressure_detector.hpp"

pthread_mutex_t g_mutex;
pthread_cond_t g_cond_data_acqusition;
pthread_cond_t g_cond_bp_processing;

timer_t tm;
event ev;
t_spec it;

pthread_t acq_thread;
pthread_t proc_thread;

std::vector<uint> bp_queue;
uint in, out;

auto m_seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
std::mt19937_64 rand_gen(m_seed);
std::uniform_int_distribution<int> diastolic(60, 90);
std::uniform_int_distribution<int> systolic(110, 150);



void init_everything(void)
{
    pthread_mutex_init(&g_mutex, nullptr);
    pthread_cond_init(&g_cond_data_acqusition, nullptr);
    pthread_cond_init(&g_cond_bp_processing, nullptr);

    bp_queue.resize(MAX_Q_SIZE);
    in = 0;
    out = 0;
}

void create_timer(void)
{
    ev.sigev_notify = SIGEV_THREAD;
    ev.sigev_notify_function = alarm_clock;
    ev.sigev_notify_attributes = nullptr;
    ev.sigev_value.sival_ptr = nullptr;

    it.it_value.tv_sec = 0;
    it.it_value.tv_nsec = 10L * 1000000L;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_nsec = 10L * 1000000L;

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
        bp_queue[in++] = diastolic(rand_gen);
    }
    else {
        bp_queue[in++] = systolic(rand_gen);
    }
    in = in >= MAX_Q_SIZE ? 0 : in;
}

void* bp_processing_thread(void* arg)
{
    bool turn = false;

    while (1)
    {
        pthread_mutex_lock(&g_mutex);
        pthread_cond_wait(&g_cond_bp_processing, &g_mutex);
        dequeue_data_to_process(reinterpret_cast<void*>(&turn));
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
    auto idx = out;
    auto sum = 0U;
    if (*is_diastolic_turn) {
        for (; idx < out + 10U; ++idx) {
            if (60 <= bp_queue[idx] && bp_queue[idx] <= 90) {
                sum += bp_queue[idx];
            }
        }
        print("diastolic bp = " + std::to_string(sum/5));
    }
    else {
        for (; idx < out + 10U; ++idx) {
            if (110 <= bp_queue[idx] && bp_queue[idx] <= 150) {
                sum += bp_queue[idx];
            }
        }
        print("systolic bp = " + std::to_string(sum/5));
    }

    uint _ = 10;
    while (_--)
    {
        ++out;
        out = out >= MAX_Q_SIZE ? 0 : out;
    }
}
