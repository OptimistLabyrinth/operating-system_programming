#include "../include/posix_timer_test.h"

using namespace std;
 
void ClockHandler(int sig, siginfo_t* info, void* context)
{
    int n_overrun;
    n_overrun = timer_getoverrun(info);

    if (n_overrun >= 1) {
        cerr << "clock overrun = " << n_overrun << endl;
        exit(EXIT_FAILURE);
    }

    // do some periodic tasks.
}

void posix_timer_test_main(void)
{
    timer_t timerid;
    struct sigevent sigev;
    struct itimerspec itval, oitval;
    struct sigaction newact;
    
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = SA_SIGINFO;
    newact.sa_sigaction = ClockHandler;
    sigaction(SIGRTMIN, &newact, NULL);

    sigev.sigev_notify = SIGEV_SIGNAL;
    sigev.sigev_signo = SIGRTMIN;
    sigev.sigev_value.sival_ptr = &timerid;
    timer_create(CLOCK_REALTIME, &sigev, &timerid);
    
    itval.it_value.tv_sec = 0;
    itval.it_value.tv_nsec = static_cast<long>(10 * (1000000L));
    itval.it_interval.tv_sec = 0;
    itval.it_interval.tv_nsec = static_cast<long>(10*(1000000L));
    timer_settime(timerid, 0, &itval, &oitval);
}

int main()
{
    posix_timer_test_main();
    int i=0;

    while(i < 5) {
        cout << "inside while-Loop" << endl;
        pause();
        ++i;
    }

    return 0;
}


