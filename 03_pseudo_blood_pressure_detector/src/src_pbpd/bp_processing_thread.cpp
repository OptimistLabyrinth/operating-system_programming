#include "../../include/include_pbpd/bp_processing_thread.hpp"



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



void dequeue_data_to_process(bool turn)
{
    auto is_diastolic_turn = turn;
    auto bp_data = 0U;
    auto sum = 0U;

    if (is_diastolic_turn) {
        for (int i=0; i < 10; ++i) {
            bp_data = dequeue_bp_queue();
            if (60 <= (*bp_queue).front() && (*bp_queue).front() <= 90) {
                sum += bp_data;
            }
        }
        print("diastolic bp = " + std::to_string(sum/5));
    }
    else {
        for (int i=0; i < 10; ++i) {
            bp_data = dequeue_bp_queue();
            if (110 <= (*bp_queue).front() && (*bp_queue).front() <= 150) {
                sum += bp_data;
            }
        }
        print("systolic bp = " + std::to_string(sum/5));
    }
}

void* bp_processing_thread(void* arg)
{
    bool turn = false;

    print();
    while (1)
    {
        pthread_mutex_lock(&(*API_Mutex));
        pthread_cond_wait(&(*API_cond_bp_processing), &(*API_Mutex));

        dequeue_data_to_process(turn);
        
        if (turn == false) {
            turn = true;
        }
        else {
            turn = false;
            print();
        }

        pthread_mutex_unlock(&(*API_Mutex));
    }

    return nullptr;
}
