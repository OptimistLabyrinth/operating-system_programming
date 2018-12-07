#include "../include/main_executor.hpp"

void main_executor(void)
{
    initialize_ptttm_variables();
    initialize_pbpd_variables();

    create_new_thread(DATA_ACQUISITION_THREAD_TYPE);
    create_new_thread(BLOOD_PRESSURE_PROCESSING_THREAD_TYPE);

    create_posix_timer();

    while(1) {
        pause();
    }
}

int main(int argc, const char* argv[])
{
    main_executor();

    return 0;
}
