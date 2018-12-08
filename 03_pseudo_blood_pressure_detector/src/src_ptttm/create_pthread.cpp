#include "../../include/include_ptttm/create_pthread.hpp"



// static PTTTM variables
extern std::unique_ptr<pthread_mutex_t> API_Mutex;
extern std::unique_ptr<timer_args> TM_Arg;
extern std::unique_ptr<timer_t> Timer;

extern std::unique_ptr<thread_args> THR_Arg__acq_thread;
extern std::unique_ptr<thread_args> THR_Arg__proc_thread;

extern std::unique_ptr<TCB> TCB_storage;

// static PBPD variables
extern std::unique_ptr<pthread_cond_t> API_cond_data_acqusition;
extern std::unique_ptr<pthread_cond_t> API_cond_bp_processing;

extern std::unique_ptr<pthread_t> acq_thread;
extern std::unique_ptr<pthread_t> proc_thread;

extern std::unique_ptr<std::queue<int>> bp_queue;
extern std::unique_ptr<pthread_mutex_t> Q_MUtex;
extern std::unique_ptr<pthread_cond_t> Q_Cond;



inline void add_pthread_arguments(uint thread_type, size_t new_period)
{
    switch (thread_type)
    {
        case DATA_ACQUISITION_THREAD_TYPE:
            (*THR_Arg__acq_thread).period = new_period;
            break;
        case BLOOD_PRESSURE_PROCESSING_THREAD_TYPE:
            (*THR_Arg__proc_thread).period = 0UL;
            break;
        default:
        {
            std::string err_msg = "ERROR : in switch-case\n";
            err_msg.append("/n/t check argument to the function add_pthread_arguments( )");
            print(err_msg);
        }
    }
}

void create_new_thread(uint thread_type)
{
    print("create_new_thread( )", " ");
    auto rv = 0;

    switch (thread_type)
    {
        case DATA_ACQUISITION_THREAD_TYPE:
        {
            print("data_acquisition thread");
            add_pthread_arguments(DATA_ACQUISITION_THREAD_TYPE, HUNDRED);
            rv = pthread_create(&(*acq_thread), nullptr, data_acquisition_thread, 
                    reinterpret_cast<void*>(&(*THR_Arg__acq_thread)));
            break;
        }
        case BLOOD_PRESSURE_PROCESSING_THREAD_TYPE:
        {
            print("blood_pressure_processing thread");
            rv = pthread_create(&(*proc_thread), nullptr, bp_processing_thread, 
                    nullptr);
            break;
        }
        default:
        {
            std::string err_msg = "ERROR : in switch-case\n";
            err_msg.append("/n/t check argument to the function create_new_thread( )");
            print(err_msg);
        }

        if (rv != 0) {
            print("pthread_create() failed TT TT");
        }
    }
}
